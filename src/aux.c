#include "inventory.h"

// Imprime el menu del programa.
void print_menu()
{
    fprintf(stdout, "\n\nSelecciona una opción:\n");
    fprintf(stdout, "1. Realizar pruebas de ordenamiento BUBBLE SORT.\n");
    fprintf(stdout, "2. Realizar pruebas de ordenamiento SELECTION SORT.\n");
    fprintf(stdout, "3. Realizar pruebas de ordenamiento INSERTION SORT.\n");
    fprintf(stdout, "4. Realizar pruebas de búsqueda SECUENCIAL (EN PROGRESO).\n");
    fprintf(stdout, "5. Realizar pruebas de búsqueda BINARIA (EN PROGRESO).\n");
    fprintf(stdout, "6. Realizar COMPARATIVA ORDENAMIENTO.\n");
    fprintf(stdout, "7. Realizar COMPARATIVA BUSQUEDA (EN PROGRESO).\n");
    fprintf(stdout, "0. Salir.");
}

// Imprime el menu de ordenamiento.
void print_menu_sort()
{
    fprintf(stdout, "\nSelecciona el tipo de ordenamiento:\n");
    fprintf(stdout, "1. Ordenar por precio.\n");
    fprintf(stdout, "2. Ordenar por stock.\n");
    fprintf(stdout, "3. Ordenar por ID.\n");
    fprintf(stdout, "4. Ordenar por nombre.\n");
    fprintf(stdout, "0. Volver al menú principal.\n");
}

// Imprime el menu de búsqueda.
void print_menu_search()
{
    fprintf(stdout, "\nSelecciona el tipo de búsqueda:\n");
    fprintf(stdout, "1. Búsqueda por ID.\n");
    fprintf(stdout, "2. Búsqueda por nombre exacto.\n");
    fprintf(stdout, "3. Búsqueda por rango de precios.\n");
    fprintf(stdout, "0. Volver al menú principal.\n");
}

// Imprime los resultados de las pruebas de ordenamiento.
void print_stats(Inventory *inv, int size)
{
    fprintf(stdout, "Pequeño ejemplo de inventario:\n");
    for (int i = 0; i < size; i++)
        fprintf(stdout, "ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n", inv->products[i].id, inv->products[i].name, inv->products[i].category, inv->products[i].price, inv->products[i].stock);
    fprintf(stdout, "\n");
}

void clean_terminal()
{
    int result = system("clear");
    (void)result;
}

// Función para graficar los tiempos de ordenamiento.
void plot_test_times(int *sizes, double *times, int n, const char *title, const char *plot_route, const char *filename) 
{
    gnuplot_ctrl *gp = gnuplot_init();
    
    // Determinar el valor mínimo y máximo para ajustar la escala
    double min_time = times[0];
    double max_time = times[0];
    for (int i = 1; i < n; i++) {
        if (times[i] < min_time) min_time = times[i];
        if (times[i] > max_time) max_time = times[i];
    }
    
    // Convertir a nanosegundos para tiempos muy pequeños
    double scale_factor = 1e9;  //  nanosegundos
    char *time_unit = "ns";
    
    double scaled_times[n];
    for (int i = 0; i < n; i++) {
        scaled_times[i] = times[i] * scale_factor;
    }
    
    gnuplot_setstyle(gp, "linespoints");
    gnuplot_cmd(gp, "set title '%s'", title);
    gnuplot_cmd(gp, "set xlabel 'Cantidad de productos'");
    gnuplot_cmd(gp, "set ylabel 'Tiempo (%s)'", time_unit);
    
    // Forzar un rango específico para el eje Y con un margen del 10%
    double y_min = 0.9 * scaled_times[0];  // 10% menos que el mínimo
    double y_max = 1.1 * scaled_times[n-1];  // 10% más que el máximo
    
    // Asegurar que el rango nunca sea vacío o demasiado pequeño
    if (y_max - y_min < 1.0) {
        y_min = scaled_times[0] - 1.0;
        y_max = scaled_times[n-1] + 1.0;
    }
    
    gnuplot_cmd(gp, "set yrange [%f:%f]", y_min, y_max);
    gnuplot_cmd(gp, "set term png");
    gnuplot_cmd(gp, "set output 'plots/%s/%s.png'", plot_route, filename);
    
    double *sizes_double = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; ++i)
        sizes_double[i] = (double)sizes[i];
    
    // Usar los tiempos escalados en lugar de los originales
    gnuplot_plot_xy(gp, sizes_double, scaled_times, n, title);
    
    free(sizes_double);
    gnuplot_close(gp);
}


// Función para graficar los tiempos de búsqueda (REVISAR).
void plot_search_times(int *sizes, double *times, int n, const char *title, const char *label)
{
    char filename[128];
    snprintf(filename, sizeof(filename), "plots/%s.png", label);

    FILE *gp = popen("gnuplot -persistent", "w");
    if (gp == NULL)
    {
        fprintf(stderr, "Error al abrir gnuplot.\n");
        return;
    }

    fprintf(gp, "set terminal png\n");
    fprintf(gp, "set output '%s'\n", filename);
    fprintf(gp, "set title \"%s\"\n", title);
    fprintf(gp, "set xlabel \"Tamaño de la base de datos\"\n");
    fprintf(gp, "set ylabel \"Tiempo de búsqueda (segundos)\"\n");
    fprintf(gp, "plot '-' using 1:2 title \"%s\" with linespoints\n", label);

    for (int i = 0; i < n; i++)
        fprintf(gp, "%d %f\n", sizes[i], times[i]);

    fprintf(gp, "e\n");

    pclose(gp);
}

// Función para graficar los tiempos de ordenamiento comparativo (REVISAR).
void plot_comparative_sort_times(int *sizes, double *bubble_times, double *selection_times, double *insertion_times, int count, const char *label, const char *plot_route, const char *plot_title)
{
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (!gnuplot)
    {
        fprintf(stderr, "Error al abrir Gnuplot.\n");
        return;
    }

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "plots/%s/%s.png", plot_route, plot_title);

    fprintf(gnuplot, "set terminal png size 800,600\n");
    fprintf(gnuplot, "set output '%s'\n", output_filename);
    fprintf(gnuplot, "set title 'Comparación de algoritmos de Ordenamiento por %s'\n", label);
    fprintf(gnuplot, "set xlabel 'Cantidad de productos'\n");
    fprintf(gnuplot, "set ylabel 'Tiempo (s)'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot '-' using 1:2 with linespoints title 'Bubble Sort', "
                     "'-' using 1:2 with linespoints title 'Selection Sort', "
                     "'-' using 1:2 with linespoints title 'Insertion Sort'\n");

    for (int i = 0; i < count; i++)
        fprintf(gnuplot, "%d %f\n", sizes[i], bubble_times[i]);
    fprintf(gnuplot, "e\n");

    for (int i = 0; i < count; i++)
        fprintf(gnuplot, "%d %f\n", sizes[i], selection_times[i]);
    fprintf(gnuplot, "e\n");

    for (int i = 0; i < count; i++)
        fprintf(gnuplot, "%d %f\n", sizes[i], insertion_times[i]);
    fprintf(gnuplot, "e\n");

    pclose(gnuplot);
}


// Función para graficar tres series de tiempos comparativos
void plot_comparative_search_times(int sizes[], double seq_times[], double bin_iter_times[], double bin_rec_times[],
    int count, const char *label, const char *plot_route, const char *plot_title)
{
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (!gnuplot)
    {
    fprintf(stderr, "Error al abrir Gnuplot.\n");
    return;
    }

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "plots/%s/%s.png", plot_route, plot_title);

    fprintf(gnuplot, "set terminal png size 800,600\n");
    fprintf(gnuplot, "set output '%s'\n", output_filename);
    fprintf(gnuplot, "set title 'Comparación de algoritmos de Búsqueda por %s'\n", label);
    fprintf(gnuplot, "set xlabel 'Tamaño de la base de datos'\n");
    fprintf(gnuplot, "set ylabel 'Tiempo (segundos)'\n");
    fprintf(gnuplot, "set logscale y\n"); // Escala logarítmica en Y
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "set key outside right top\n");
    fprintf(gnuplot, "plot '-' using 1:2 with linespoints title 'Secuencial', "
        "'-' using 1:2 with linespoints title 'Binaria Iterativa', "
        "'-' using 1:2 with linespoints title 'Binaria Recursiva'\n");

    //  Secuencial
    for (int i = 0; i < count; i++)
    fprintf(gnuplot, "%d %.9f\n", sizes[i], seq_times[i]);
    fprintf(gnuplot, "e\n");

    //  Binaria Iterativa
    for (int i = 0; i < count; i++)
    fprintf(gnuplot, "%d %.9f\n", sizes[i], bin_iter_times[i]);
    fprintf(gnuplot, "e\n");

    //  Binaria Recursiva
    for (int i = 0; i < count; i++)
    fprintf(gnuplot, "%d %.9f\n", sizes[i], bin_rec_times[i]);
    fprintf(gnuplot, "e\n");

    pclose(gnuplot);
}
