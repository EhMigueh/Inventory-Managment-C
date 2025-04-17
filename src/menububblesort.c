#include "inventory.h"
#include "search.h"
#include "sort.h"
#include "utils.h"
#include "metrics.h"
#include "plot.h"
void handle_bubble_sort(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option;
    clock_t start, end;
    double time;
    double times[5];

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
    const char *labels[] = {"precio", "stock", "ID", "nombre"};
    const char *plot_titles[] = {"Bubble Sort por precio", "Bubble Sort por stock", "Bubble Sort por ID", "Bubble Sort por nombre"};
    const char *plot_filenames[] = {"Bubble Price", "Bubble Stock", "Bubble ID", "Bubble Name"};
    const char *plot_route = "bubblesort";

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
    for (int i = 0; i < 5; i++)
    {
        start = clock();
        sort_functions[index](dbs[i]);
        end = clock();
        time = (double)(end - start) / CLOCKS_PER_SEC;
        times[i] = time;
        fprintf(stdout, "Tiempo de ordenamiento Bubble Sort por %s (base de datos de %d objetos): %.4f segundos.\n", labels[index], sizes[i], time);
        print_stats(dbs[i], 5);
    }

    fprintf(stdout, "Ordenamiento Bubble Sort por %s completado. Su gráfico quedó guardado en 'plots'.", labels[index]);
    plot_test_times(sizes, times, 5, plot_titles[index], plot_route, plot_filenames[index], 0);    
}