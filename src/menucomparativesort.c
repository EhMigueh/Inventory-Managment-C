#include "inventory.h"
#include "sort.h"
#include "utils.h"
#include "metrics.h"
#include "plot.h"
#include "comparativesort.h"

void handle_comparative_sort(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option;
    clock_t start, end;
    double time;
    double bubble_times[5], insertion_times[5], selection_times[5];

    clean_terminal();

    print_menu_sort();

    // Solicita al usuario una opción para realizar una acción, en caso de no ser válida, se atrapa.
    fprintf(stdout, "\nSelecciona una opción: ");
    if (scanf("%d", &search_option) != 1)
    {
        clean_terminal();
        fprintf(stderr, "\nERROR entrada no válida. Por favor, introduce un número.\n\n");
        while (getchar() != '\n')
            ;
        return;
    }

    if (search_option == 0)
    {
        clean_terminal();
        fprintf(stdout, "Volviendo al menú principal...\n\n");
        return;
    }

    void (*sort_functions[])(Inventory *) = {bubble_sort_by_price, bubble_sort_by_stock, bubble_sort_by_id, bubble_sort_by_name};
    void (*selection_sort_functions[])(Inventory *) = {selection_sort_by_price, selection_sort_by_stock, selection_sort_by_id, selection_sort_by_name};
    void (*insertion_sort_functions[])(Inventory *) = {insertion_sort_by_price, insertion_sort_by_stock, insertion_sort_by_id, insertion_sort_by_name};
    const char *labels[] = {"precio", "stock", "ID", "nombre"};
    const char *plot_route = "comparatives";
    const char *plot_title = "Comparative Sort";

    if (search_option < 1 || search_option > 4)
    {
        clean_terminal();
        fprintf(stderr, "ERROR opción inválida. Solo se permite 0, 1, 2, 3 o 4.\n\n");
        return;
    }

    clean_terminal();

    Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
    int sizes[] = {10000, 25000, 50000, 75000, 100000};

    int index = search_option - 1;

    // Ejecución de Bubble Sort
    for (int i = 0; i < 5; i++)
    {
        start = clock();
        sort_functions[index](dbs[i]);
        end = clock();
        time = (double)(end - start) / CLOCKS_PER_SEC;
        bubble_times[i] = time;
        fprintf(stdout, "Tiempo de ordenamiento Bubble Sort por %s (base de datos de %d objetos): %.4f segundos.\n", labels[index], sizes[i], time);
        print_stats(dbs[i], 5);
    }

    load_all_inventories(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);

    // Ejecución de Selection Sort
    for (int i = 0; i < 5; i++)
    {
        start = clock();
        selection_sort_functions[index](dbs[i]);
        end = clock();
        time = (double)(end - start) / CLOCKS_PER_SEC;
        selection_times[i] = time;
        fprintf(stdout, "Tiempo de ordenamiento Selection Sort por %s (base de datos de %d objetos): %.4f segundos.\n", labels[index], sizes[i], time);
        print_stats(dbs[i], 5);
    }

    load_all_inventories(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);

    // Ejecución de Insertion Sort
    for (int i = 0; i < 5; i++)
    {
        start = clock();
        insertion_sort_functions[index](dbs[i]);
        end = clock();
        time = (double)(end - start) / CLOCKS_PER_SEC;
        insertion_times[i] = time;
        fprintf(stdout, "Tiempo de ordenamiento Insertion Sort por %s (base de datos de %d objetos): %.4f segundos.\n", labels[index], sizes[i], time);
        print_stats(dbs[i], 5);
    }

    load_all_inventories(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);

    fprintf(stdout, "Ordenamiento (Bubble Sort, Selection Sort e Insertion Sort) por %s completado. Sus gráficos quedaron guardados en 'plots'.", labels[index]);
    plot_comparative_sort_times(sizes, bubble_times, selection_times, insertion_times, 5, labels[index], plot_route, plot_title);
}