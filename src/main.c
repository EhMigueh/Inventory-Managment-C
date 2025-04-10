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
        free_inventory(inv_large);
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
        fprintf(stdout, "2. Ordenar base de datos pequeña y grande por stock (BubbleSort).\n");        fprintf(stdout, "3. Realizar pruebas de búsqueda.\n");
        fprintf(stdout, "0. Salir.");
        fprintf(stdout, "\n\nSelecciona una opción: ");
        if (scanf("%d", &option) != 1)
        {
            fprintf(stderr, "ERROR entrada no válida. Por favor, introduce un número.\n");
            while (getchar() != '\n');
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
        case 3:
        {
            int search_option;
            fprintf(stdout, "\nSelecciona el tipo de búsqueda:\n");
            fprintf(stdout, "1. Búsqueda secuencial no optimizada (por ID).\n");
            fprintf(stdout, "0. Volver al menú principal.\n");
            fprintf(stdout, "\nSelecciona una opción: ");

            if (scanf("%d", &search_option) != 1)
            {
                fprintf(stderr, "ERROR entrada no válida. Por favor, introduce un número.\n");
                while (getchar() != '\n');
                continue;
            }

            if (search_option != 0 && search_option != 1)
            {
                fprintf(stderr, "ERROR: opción inválida. Solo se permite 0 o 1.\n");
                continue;
            }

            if (search_option == 0) break;

            int id_to_search;
            fprintf(stdout, "Introduce el ID a buscar: ");
            if (scanf("%d", &id_to_search) != 1)
            {
                fprintf(stderr, "ERROR entrada no válida. Por favor, introduce un número.\n");
                while (getchar() != '\n');
                continue;
            }

            int result_small = -1, result_large = -1;

            start = clock();
            result_small = sequential_search(inv_small, id_to_search);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(stdout, "\nTiempo de búsqueda secuencial no optimizada (base pequeña): %.6f segundos.\n", time);

            start = clock();
            result_large = sequential_search(inv_large, id_to_search);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(stdout, "Tiempo de búsqueda secuencial no optimizada (base grande): %.6f segundos.\n", time);

            // revisar
            fprintf(stdout, "\n========================================\n");
            fprintf(stdout, "         RESULTADOS DE LA BÚSQUEDA\n");
            fprintf(stdout, "========================================\n\n");

            if (result_small != -1)
            {
                fprintf(stdout, "En base pequeña: Producto encontrado en posición %d\n", result_small);
                fprintf(stdout, "ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n\n",
                        inv_small->products[result_small].id,
                        inv_small->products[result_small].name,
                        inv_small->products[result_small].category,
                        inv_small->products[result_small].price,
                        inv_small->products[result_small].stock);
            }
            else
            {
                fprintf(stdout, "En base pequeña: Producto NO encontrado.\n\n");
            }

            if (result_large != -1)
            {
                fprintf(stdout, "En base grande: Producto encontrado en posición %d\n", result_large);
                fprintf(stdout, "ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n",
                        inv_large->products[result_large].id,
                        inv_large->products[result_large].name,
                        inv_large->products[result_large].category,
                        inv_large->products[result_large].price,
                        inv_large->products[result_large].stock);
            }
            else
            {
                fprintf(stdout, "En base grande: Producto NO encontrado.\n");
            }

            fprintf(stdout, "\n----------------------------------------\n\n");
            break;
        }
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
