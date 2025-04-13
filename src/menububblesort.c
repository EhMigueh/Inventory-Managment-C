#include "inventory.h"

void handle_bubble_sort(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option;
    clock_t start, end;
    double time;
    double times[5];

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
        fprintf(stderr, "\nERROR entrada no válida. Por favor, introduce un número.\n\n");
        while (getchar() != '\n')
            ;
        return;
    }

    system("clear");

    if (search_option == 0)
    {
        fprintf(stdout, "Volviendo al menú principal...\n\n");
        return;
    }

    Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
    int sizes[] = {10000, 25000, 50000, 75000, 100000};

    if (search_option == 1)
    {
        for (int i = 0; i < 5; i++)
        {
            start = clock();
            bubble_sort_by_price(dbs[i]);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = time;
            fprintf(stdout, "Tiempo de ordenamiento por precio (base de datos de %d objetos): %.4f segundos.\n", sizes[i], time);
            print_stats(dbs[i], 5);
        }
        fprintf(stdout, "Ordenamiento por precio completado. Su gráfico quedó guardado en 'plots'.\n\n");
        plot_sort_times(sizes, times, 5, "Bubble Sort por precio", "Bubble Price");
    }
    else if (search_option == 2)
    {
        for (int i = 0; i < 5; i++)
        {
            start = clock();
            bubble_sort_by_stock(dbs[i]);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = time;
            fprintf(stdout, "Tiempo de ordenamiento por stock (base de datos de %d objetos): %.4f segundos.\n", sizes[i], time);
            print_stats(dbs[i], 5);
        }
        fprintf(stdout, "Ordenamiento por stock completado. Su gráfico quedó guardado en 'plots'.\n\n");
        plot_sort_times(sizes, times, 5, "Bubble Sort por stock", "Bubble Stock");
    }
    else if (search_option == 3)
    {
        for (int i = 0; i < 5; i++)
        {
            start = clock();
            bubble_sort_by_id(dbs[i]);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = time;
            fprintf(stdout, "Tiempo de ordenamiento por ID (base de datos de %d objetos): %.4f segundos.\n", sizes[i], time);
            print_stats(dbs[i], 5);
        }
        fprintf(stdout, "Ordenamiento por ID completado. Su gráfico quedó guardado en 'plots'.\n\n");
        plot_sort_times(sizes, times, 5, "Bubble Sort por ID", "Bubble ID");
    }
    else if (search_option == 4)
    {
        for (int i = 0; i < 5; i++)
        {
            start = clock();
            bubble_sort_by_name(dbs[i]);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = time;
            fprintf(stdout, "Tiempo de ordenamiento por nombre (base de datos de %d objetos): %.4f segundos.\n", sizes[i], time);
            print_stats(dbs[i], 5);
        }
        fprintf(stdout, "Ordenamiento por nombre completado. Su gráfico quedó guardado en 'plots'.\n\n");
        plot_sort_times(sizes, times, 5, "Bubble Sort por nombre", "Bubble Name");
    }
    else
    {
        fprintf(stderr, "ERROR opción inválida. Solo se permite 0, 1, 2, 3 o 4.\n\n");
        return;
    }
}