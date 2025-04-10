#include "inventory.h"

int main(void)
{
    Inventory *inv_small = create_inventory(SMALL_DB_SIZE);
    Inventory *inv_large = create_inventory(LARGE_DB_SIZE);

    if (!inv_small || !inv_large)
    {
        fprintf(stderr, "ERROR creando inventario.\n");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "\nCargando las bases de datos.\n");
    if (load_inventory_from_file(inv_small, "./db/small_database.csv") < 0 ||
        load_inventory_from_file(inv_large, "./db/large_database.csv") < 0)
    {
        fprintf(stderr, "ERROR cargando las bases de datos.\n");
        free_inventory(inv_small);
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Bases de datos cargadas.\n\n");

    fprintf(stdout, "Base de datos pequeña cargada con %d productos.\n", inv_small->count);
    fprintf(stdout, "Base de datos grande cargada con %d productos.\n\n", inv_large->count);

    int option;
    while (1)
    {
        fprintf(stdout, "Selecciona una opción:\n");
        fprintf(stdout, "1. Ordenar base de datos pequeña y grande por precio (BubbleSort).\n");
        fprintf(stdout, "2. Ordenar base de datos pequeña y grande por stock (BubbleSort).\n");
        fprintf(stdout, "0. Salir.");
        fprintf(stdout, "\n\nSelecciona una opción: ");
        if (scanf("%d", &option) != 1)
        {
            fprintf(stderr, "ERROR entrada no válida. Por favor, introduce un número.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        clock_t start, end;
        double time;

        switch (option)
        {
        case 1:
            start = clock();
            bubble_sort_by_price(inv_small);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(stdout, "\nTiempo de ordenamiento por precio (base de datos pequeña con BubbleSort): %.4f segundos.\n", time);
            start = clock();
            bubble_sort_by_price(inv_large);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(stdout, "Tiempo de ordenamiento por precio (base de datos grande con BubbleSort): %.4f segundos.\n\n", time);
            break;
        case 2:
            start = clock();
            bubble_sort_by_stock(inv_small);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(stdout, "\nTiempo de ordenamiento por stock (base de datos pequeña con BubbleSort): %.4f segundos.\n", time);
            start = clock();
            bubble_sort_by_stock(inv_large);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(stdout, "Tiempo de ordenamiento por stock (base de datos grande con BubbleSort): %.4f segundos.\n\n", time);
            break;
        case 0:
            fprintf(stdout, "\nSaliendo del programa.\n\n");
            free_inventory(inv_small);
            free_inventory(inv_large);
            return EXIT_SUCCESS;
        default:
            fprintf(stderr, "Opción no válida. Por favor, selecciona una opción válida.\n");
            break;
        }
    }

    return EXIT_SUCCESS;
}