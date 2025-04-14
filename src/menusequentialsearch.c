#include "inventory.h"

void handle_sequential_search(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option, id_to_search;
    char name_to_search[MAX_NAME_LENGTH];
    clock_t start, end;
    double time;
    double times[5];

    clean_terminal();

    print_menu_search();

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
        fprintf(stdout, "\nVolviendo al menú principal...\n\n");
        return;
    }

    clean_terminal();

    Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
    int sizes[] = {10000, 25000, 50000, 75000, 100000};
    const char *plot_route = "sequentialsearch";

    if (search_option == 1)
    {
        fprintf(stdout, "\nIntroduce el ID a buscar: ");
        if (scanf("%d", &id_to_search) != 1)
        {
            fprintf(stderr, "\nERROR entrada no válida. Por favor, introduce un número.\n\n");
            while (getchar() != '\n')
                ;
            return;
        }
        fprintf(stdout, "\n");

        int results[5];
        for (int i = 0; i < 5; i++)
        {
            start = clock();
            results[i] = sequential_search_by_id(dbs[i], id_to_search);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = time;
            fprintf(stdout, "Tiempo de búsqueda Secuencial por ID (base de datos %d objetos): %.4f seg\n", sizes[i], time);
            if (results[i] != -1)
            {
                Product *p = &dbs[i]->products[results[i]];
                fprintf(stdout, "Datos del producto encontrado = POSICIÓN: %d - ID: %d - NOMBRE: %s - CATEGORÍA: %s - PRECIO: %.2f - STOCK: %d\n\n", results[i], p->id, p->name, p->category, p->price, p->stock);
            }
            else
                fprintf(stdout, "Producto NO encontrado.\n\n");
        }
        fprintf(stdout, "Búsqueda Secuencial Search por ID completado. Su gráfico quedó guardado en 'plots'.");
        plot_test_times(sizes, times, 5, "Búsqueda Secuencial por ID", plot_route, "Search ID");
    }
    else if (search_option == 2)
    {
        fprintf(stdout, "\nIntroduce el nombre: ");
        while (getchar() != '\n')
            ;
        if (fgets(name_to_search, MAX_NAME_LENGTH, stdin) == NULL)
        {
            fprintf(stderr, "\nERROR entrada no válida. Por favor introduce una cadena de caracteres.\n");
            return;
        }
        fprintf(stdout, "\n");

        // Eliminar el salto de línea al final de la cadena
        size_t len = strlen(name_to_search);
        if (len > 0 && name_to_search[len - 1] == '\n')
            name_to_search[len - 1] = '\0';

        for (int i = 0; i < 5; i++)
        {
            start = clock();
            int pos = sequential_search_by_name(dbs[i], name_to_search);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = time;
            fprintf(stdout, "Tiempo de búsqueda Secuencial por Nombre (base de datos de %d objetos): %.4f segundos.\n", sizes[i], time);
            if (pos != -1)
            {
                Product *p = &dbs[i]->products[pos];
                fprintf(stdout, "Datos del producto encontrado = POS: %d - ID: %d - NOMBRE: %s - CATEGORIA: %s - PRECIO: %.2f - STOCK: %d\n\n", pos, p->id, p->name, p->category, p->price, p->stock);
            }
            else
                fprintf(stdout, "Producto NO encontrado.\n\n");
        }
        fprintf(stdout, "Búsqueda Secuencial Search por Nombre completado. Su gráfico quedó guardado en 'plots'.");
        plot_test_times(sizes, times, 5, "Búsqueda Secuencial por Nombre", plot_route, "Search Name");
    }
    else if (search_option == 3)
    {
        double min_price, max_price;

        fprintf(stdout, "\nIntroduce el precio mínimo: ");
        if (scanf("%lf", &min_price) != 1)
        {
            fprintf(stderr, "\nERROR introduce un número válido.\n\n");
            return;
        }

        fprintf(stdout, "Introduce el precio máximo: ");
        if (scanf("%lf", &max_price) != 1)
        {
            fprintf(stderr, "\nERROR introduce un número válido.\n\n");
            return;
        }
        fprintf(stdout, "\n");

        for (int i = 0; i < 5; i++)
        {
            Product *results[50];
            start = clock();
            int pos = sequential_search_by_price_range(dbs[i], min_price, max_price, results, 10);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = time;
            fprintf(stdout, "Tiempo de búsqueda Secuencial por Rango de Precios (base de datos de %d objetos): %.4f segundos.\n", sizes[i], time);
            if (pos == 0)
                fprintf(stdout, "\nNo hay productos en ese rango.\n");
            else
            {
                for (int j = 0; j < pos; j++)
                {
                    Product *p = results[j];
                    fprintf(stdout, "Datos del producto encontrado = POS: %d - ID: %d - NOMBRE: %s - CATEGORIA: %s - PRECIO: %.2f - STOCK: %d\n\n", pos, p->id, p->name, p->category, p->price, p->stock);
                }
            }
        }
        fprintf(stdout, "Búsqueda Secuencial Search por Rango de Precios completado. Su gráfico quedó guardado en 'plots'.");
        plot_test_times(sizes, times, 5, "Búsqueda Secuencial por Rango de Precios", plot_route, "Search Price Range");
    }
    else
    {
        fprintf(stderr, "ERROR opción inválida. Selecciona entre 0, 1, 2 o 3.\n\n");
        return;
    }
}
