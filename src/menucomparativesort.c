#include "inventory.h"

void handle_comparative_sort(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option;
    clock_t start, end;
    double time;
    double bubble_times[5], insertion_times[5], selection_times[5];
    int sizes[] = {10000, 25000, 50000, 75000, 100000};

    system("clear");

    fprintf(stdout, "\nSelecciona el tipo de ordenamiento:\n");
    fprintf(stdout, "1. Ordenar por precio.\n");
    fprintf(stdout, "2. Ordenar por stock.\n");
    fprintf(stdout, "3. Ordenar por ID.\n");
    fprintf(stdout, "4. Ordenar por nombre.\n");
    fprintf(stdout, "0. Volver al menú principal.\n");

    fprintf(stdout, "\nSelecciona una opción: ");
    if (scanf("%d", &search_option) != 1)
    {
        system("clear");
        fprintf(stderr, "\nERROR entrada no válida. Por favor, introduce un número.\n\n");
        while (getchar() != '\n')
            ;
        return;
    }

    if (search_option == 0)
    {
        system("clear");
        fprintf(stdout, "Volviendo al menú principal...\n\n");
        return;
    }

    void (*sort_functions[])(Inventory *) = {bubble_sort_by_price, bubble_sort_by_stock, bubble_sort_by_id, bubble_sort_by_name};
    void (*selection_sort_functions[])(Inventory *) = {selection_sort_by_price, selection_sort_by_stock, selection_sort_by_id, selection_sort_by_name};
    void (*insertion_sort_functions[])(Inventory *) = {insertion_sort_by_price, insertion_sort_by_stock, insertion_sort_by_id, insertion_sort_by_name};

    const char *labels[] = {"precio", "stock", "ID", "nombre"};
    const char *plot_titles[] = {"Bubble Sort por precio", "Bubble Sort por stock", "Bubble Sort por ID", "Bubble Sort por nombre"};
    const char *plot_filenames[] = {"Bubble Price", "Bubble Stock", "Bubble ID", "Bubble Name"};

    if (search_option < 1 || search_option > 4)
    {
        system("clear");
        fprintf(stderr, "ERROR opción inválida. Solo se permite 0, 1, 2, 3 o 4.\n\n");
        return;
    }

    system("clear");

    Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};

    int index = search_option - 1;

    // Ejecución de Bubble Sort
    for (int i = 0; i < 5; i++)
    {
        start = clock();
        sort_functions[index](dbs[i]);
        end = clock();
        time = (double)(end - start) / CLOCKS_PER_SEC;
        bubble_times[i] = time;
        fprintf(stdout, "Tiempo de ordenamiento por %s (Bubble Sort) (base de datos de %d objetos): %.4f segundos.\n", labels[index], sizes[i], time);
        print_stats(dbs[i], 5);
    }

    // Ejecución de Selection Sort
    for (int i = 0; i < 5; i++)
    {
        start = clock();
        selection_sort_functions[index](dbs[i]);
        end = clock();
        time = (double)(end - start) / CLOCKS_PER_SEC;
        selection_times[i] = time;
        fprintf(stdout, "Tiempo de ordenamiento por %s (Selection Sort) (base de datos de %d objetos): %.4f segundos.\n", labels[index], sizes[i], time);
        print_stats(dbs[i], 5);
    }

    // Ejecución de Insertion Sort
    for (int i = 0; i < 5; i++)
    {
        start = clock();
        insertion_sort_functions[index](dbs[i]);
        end = clock();
        time = (double)(end - start) / CLOCKS_PER_SEC;
        insertion_times[i] = time;
        fprintf(stdout, "Tiempo de ordenamiento por %s (Insertion Sort) (base de datos de %d objetos): %.4f segundos.\n", labels[index], sizes[i], time);
        print_stats(dbs[i], 5);
    }

    fprintf(stdout, "Ordenamiento por %s completado. Sus gráficos quedaron guardados en 'plots'.\n\n", labels[index]);

    // Generar gráficos para los tres algoritmos
    //plot_sort_times(sizes, bubble_times, 5, "Bubble Sort", plot_filenames[index]);
    //plot_sort_times(sizes, selection_times, 5, "Selection Sort", plot_filenames[index]);
    //plot_sort_times(sizes, insertion_times, 5, "Insertion Sort", plot_filenames[index]);
    plot_comparative_sort_times(sizes, bubble_times, selection_times, insertion_times, 5, labels[index]);
    fprintf(stdout, "Gráficos generados y guardados en 'plots'.\n\n");
    fprintf(stdout, "Presiona ENTER para continuar...\n\n");
}