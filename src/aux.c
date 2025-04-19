#include "plot.h"
#include "utils.h"
#include "product.h"
#include "inventory.h"

// Imprime el menu del programa.
void print_menu()
{
    fprintf(stdout, "\n╔════════════════════════════════════════════════════╗\n");
    fprintf(stdout, "║                 MENÚ PRINCIPAL                     ║\n");
    fprintf(stdout, "╠════════════════════════════════════════════════════╣\n");
    fprintf(stdout, "║ 1. Realizar pruebas de ordenamiento BUBBLE SORT    ║\n");
    fprintf(stdout, "║ 2. Realizar pruebas de ordenamiento SELECTION SORT ║\n");
    fprintf(stdout, "║ 3. Realizar pruebas de ordenamiento INSERTION SORT ║\n");
    fprintf(stdout, "║ 4. Realizar pruebas de búsqueda SECUENCIAL         ║\n");
    fprintf(stdout, "║ 5. Realizar pruebas de búsqueda BINARIA            ║\n");
    fprintf(stdout, "║ 6. Realizar COMPARATIVA ORDENAMIENTO               ║\n");
    fprintf(stdout, "║ 7. Realizar COMPARATIVA BÚSQUEDA                   ║\n");
    fprintf(stdout, "║ 8. Mostrar MÉTRICAS del inventario                 ║\n");
    fprintf(stdout, "║ 0. Salir                                           ║\n");
    fprintf(stdout, "╚════════════════════════════════════════════════════╝\n");
}

// Imprime el menu de ordenamiento.
void print_menu_sort()
{
    fprintf(stdout, "\n╔══════════════════════════════════════════════════╗\n");
    fprintf(stdout, "║              MENÚ DE ORDENAMIENTO                ║\n");
    fprintf(stdout, "╠══════════════════════════════════════════════════╣\n");
    fprintf(stdout, "║ 1. Ordenar por precio                            ║\n");
    fprintf(stdout, "║ 2. Ordenar por stock                             ║\n");
    fprintf(stdout, "║ 3. Ordenar por ID                                ║\n");
    fprintf(stdout, "║ 4. Ordenar por nombre                            ║\n");
    fprintf(stdout, "║ 0. Volver al menú principal                      ║\n");
    fprintf(stdout, "╚══════════════════════════════════════════════════╝\n");
}

// Imprime el menu de búsqueda.
void print_menu_search()
{
    fprintf(stdout, "\n╔══════════════════════════════════════════════════╗\n");
    fprintf(stdout, "║                MENÚ DE BÚSQUEDA                  ║\n");
    fprintf(stdout, "╠══════════════════════════════════════════════════╣\n");
    fprintf(stdout, "║ 1. Búsqueda por ID                               ║\n");
    fprintf(stdout, "║ 2. Búsqueda por nombre exacto                    ║\n");
    fprintf(stdout, "║ 3. Búsqueda por rango de precios                 ║\n");
    fprintf(stdout, "║ 0. Volver al menú principal                      ║\n");
    fprintf(stdout, "╚══════════════════════════════════════════════════╝\n");
}

// Imprime el menu de métricas.
void print_menu_metrics()
{
    fprintf(stdout, "\n╔══════════════════════════════════════════════════╗\n");
    fprintf(stdout, "║            MENÚ DE MÉTRICAS DEL INVENTARIO       ║\n");
    fprintf(stdout, "╠══════════════════════════════════════════════════╣\n");
    fprintf(stdout, "║ 1. Total de productos                            ║\n");
    fprintf(stdout, "║ 2. Valor total del inventario                    ║\n");
    fprintf(stdout, "║ 3. Producto con mayor y menor stock              ║\n");
    fprintf(stdout, "║ 4. Producto más caro y más barato                ║\n");
    fprintf(stdout, "║ 5. Promedio de precios por categoría             ║\n");
    fprintf(stdout, "║ 6. Cantidad de productos por categoría           ║\n");
    fprintf(stdout, "║ 0. Volver al menú anterior                       ║\n");
    fprintf(stdout, "╚══════════════════════════════════════════════════╝\n");
}

void print_product_in_table(Product *product)
{
    if (product != NULL)
    {
        char price_formatted[50];
        char stock_formatted[50];

        format_with_commas(product->price, price_formatted);
        format_with_commas((double)product->stock, stock_formatted);

        // Imprimir el encabezado de la tabla.
        fprintf(stdout, "  ➤ Producto: %s\n", product->name);
        fprintf(stdout, "╔════════════╦════════════╦══════════════╦════════════╦════════════╗\n");
        fprintf(stdout, "║   ID       ║  Nombre    ║  Categoría   ║  Precio    ║  Stock     ║\n");
        fprintf(stdout, "╠════════════╬════════════╬══════════════╬════════════╬════════════╣\n");
        fprintf(stdout, "║ %-10d ║ %-10s ║ %-12s ║ $%-10s║ %-10s ║\n", product->id, product->name, product->category, price_formatted, stock_formatted);
        fprintf(stdout, "╚════════════╩════════════╩══════════════╩════════════╩════════════╝\n");
    }
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
void plot_test_times(int *sizes, double *times, int n, const char *title, const char *plot_route, const char *filename, int is_search)
{
    gnuplot_ctrl *gp = gnuplot_init();

    // Determinar escala según el tipo de algoritmo.
    double scale_factor;
    const char *time_unit;

    if (is_search)
    {
        scale_factor = 1e9; // Nanosegundos.
        time_unit = "ns";
    }
    else
    {
        scale_factor = 1.0; // Segundos.
        time_unit = "s";
    }

    // Escalar los tiempos.
    double scaled_times[n];
    for (int i = 0; i < n; i++)
        scaled_times[i] = times[i] * scale_factor;

    // Convertir sizes a double.
    double *sizes_double = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
        sizes_double[i] = (double)sizes[i];

    // Definir estilo y etiquetas.
    gnuplot_setstyle(gp, "linespoints");
    gnuplot_cmd(gp, "set title '%s'", title);
    gnuplot_cmd(gp, "set xlabel 'Cantidad de productos'");
    gnuplot_cmd(gp, "set ylabel 'Tiempo (%s)'", time_unit);

    // Forzar que el eje Y comience en 0.
    gnuplot_cmd(gp, "set yrange [0:*]");

    // Añadir cuadrícula para mejor visualización.
    gnuplot_cmd(gp, "set grid");

    // Configurar salida.
    gnuplot_cmd(gp, "set term png");
    gnuplot_cmd(gp, "set output 'plots/%s/%s.png'", plot_route, filename);

    // Graficar.
    gnuplot_plot_xy(gp, sizes_double, scaled_times, n, title);

    free(sizes_double);
    gnuplot_close(gp);
}

// Función para graficar los tiempos de búsqueda.
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

// Función para graficar los tiempos de ordenamiento comparativo.
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

// Función para graficar tres series de tiempos comparativos.
void plot_comparative_search_times(int sizes[], double seq_times[], double bin_iter_times[], double bin_rec_times[], int count, const char *label, const char *plot_route, const char *plot_title)
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

    //  Secuencial.
    for (int i = 0; i < count; i++)
        fprintf(gnuplot, "%d %.9f\n", sizes[i], seq_times[i]);
    fprintf(gnuplot, "e\n");

    //  Binaria Iterativa.
    for (int i = 0; i < count; i++)
        fprintf(gnuplot, "%d %.9f\n", sizes[i], bin_iter_times[i]);
    fprintf(gnuplot, "e\n");

    //  Binaria Recursiva.
    for (int i = 0; i < count; i++)
        fprintf(gnuplot, "%d %.9f\n", sizes[i], bin_rec_times[i]);
    fprintf(gnuplot, "e\n");

    pclose(gnuplot);
}

// Función auxiliar para formatear números con comas.
void format_with_commas(double number, char *output)
{
    char buffer[50];
    sprintf(buffer, "%.2f", number);

    char *dot = strchr(buffer, '.');
    int int_len = dot - buffer;
    int commas = (int_len - 1) / 3;

    int new_len = int_len + commas;
    int total_len = new_len + strlen(dot);

    int i = int_len - 1;
    int j = new_len - 1;
    int digit_count = 0;

    output[total_len] = '\0';

    // Copiar parte decimal.
    for (int k = strlen(dot) - 1; k >= 0; k--)
        output[new_len + k] = dot[k];

    while (i >= 0)
    {
        output[j--] = buffer[i--];
        digit_count++;
        if (digit_count == 3 && i >= 0)
        {
            output[j--] = ',';
            digit_count = 0;
        }
    }
}
