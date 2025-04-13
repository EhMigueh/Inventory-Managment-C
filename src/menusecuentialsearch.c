#include "inventory.h"

void handle_sequential_search(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option, id_to_search;
    char name_to_search[MAX_NAME_LENGTH];
    clock_t start, end;
    double time;
    double times[5];

    system("clear");

    fprintf(stdout, "\nSelecciona el tipo de búsqueda secuencial:\n");
    fprintf(stdout, "1. Búsqueda por ID.\n");
    fprintf(stdout, "2. Búsqueda por nombre exacto.\n");
    fprintf(stdout, "3. Búsqueda por rango de precios.\n");
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
        fprintf(stdout, "\nVolviendo al menú principal...\n\n");
        return;
    }

    Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
    int sizes[] = {10000, 25000, 50000, 75000, 100000};

    if (search_option == 1)
    {
        fprintf(stdout, "\nIntroduce el ID a buscar: ");
        if (scanf("%d", &id_to_search) != 1)
        {
            fprintf(stderr, "\nERROR entrada no válida.\n\n");
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
            fprintf(stdout, "Tiempo (BD %d): %.4f seg\n", sizes[i], time);
            if (results[i] != -1)
            {
                Product *p = &dbs[i]->products[results[i]];
                fprintf(stdout, "Producto en pos %d: ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n\n", results[i], p->id, p->name, p->category, p->price, p->stock);
            }
            else
                fprintf(stdout, "Producto NO encontrado.\n\n");
        }
        plot_search_times(sizes, times, 5, "Búsqueda Secuencial por ID", "Search ID");
    }
    else if (search_option == 2)
    {
        fprintf(stdout, "\nIntroduce el nombre: ");
        while (getchar() != '\n')
            ;
        if (fgets(name_to_search, MAX_NAME_LENGTH, stdin) == NULL)
        {
            fprintf(stderr, "\nERROR al leer el nombre.\n");
            return;
        }
        fprintf(stdout, "\n");

        size_t len = strlen(name_to_search);
        if (len > 0 && name_to_search[len - 1] == '\n')
            name_to_search[len - 1] = '\0';

        for (int i = 0; i < 5; i++)
        {
            int pos;
            start = clock();
            pos = sequential_search_by_name(dbs[i], name_to_search);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = time;

            fprintf(stdout, "BD %d → Tiempo: %.4f seg\n", sizes[i], time);
            if (pos != -1)
            {
                Product *p = &dbs[i]->products[pos];
                fprintf(stdout, "Producto en pos %d: ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n\n", pos, p->id, p->name, p->category, p->price, p->stock);
            }
            else
                fprintf(stdout, "Producto NO encontrado.\n\n");
        }
        plot_search_times(sizes, times, 5, "Búsqueda Secuencial por Nombre", "Search Name");
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
            int found = sequential_search_by_price_range(dbs[i], min_price, max_price, results, 10);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = time;
            fprintf(stdout, "Base de datos de %d → %d resultados en %.4f seg:\n", sizes[i], found, time);
            if (found == 0)
                fprintf(stdout, "\nNo hay productos en ese rango.\n");
            else
            {
                for (int j = 0; j < found; j++)
                {
                    Product *p = results[j];
                    fprintf(stdout, "ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n", p->id, p->name, p->category, p->price, p->stock);
                }
                fprintf(stdout, "\n");
            }
        }
        plot_search_times(sizes, times, 5, "Búsqueda Secuencial por Precio", "Search Price");
    }
    else
    {
        fprintf(stderr, "ERROR opción inválida. Selecciona entre 0, 1, 2 o 3.\n\n");
        return;
    }
}
