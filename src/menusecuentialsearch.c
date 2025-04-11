#include "inventory.h"

void handle_sequential_search(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option, id_to_search;
    char name_to_search[MAX_NAME_LENGTH];
    clock_t start, end;
    double time;
    double times[5]; 

    fprintf(stdout, "\nSelecciona el tipo de búsqueda secuencial:\n");
    fprintf(stdout, "1. Búsqueda por ID.\n");
    fprintf(stdout, "2. Búsqueda por nombre exacto.\n");
    fprintf(stdout, "4. Búsqueda por rango de precios.\n");
    fprintf(stdout, "0. Volver al menú principal.\n");
    fprintf(stdout, "\nSelecciona una opción: ");

    if (scanf("%d", &search_option) != 1)
    {
        fprintf(stderr, "ERROR entrada no válida. Por favor, introduce un número.\n");
        while (getchar() != '\n');
        return;
    }

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
            fprintf(stderr, "ERROR entrada no válida.\n");
            while (getchar() != '\n');
            return;
        }

        int results[5];
        for (int i = 0; i < 5; i++)
        {
            start = clock();
            results[i] = sequential_search(dbs[i], id_to_search);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = time; 
            fprintf(stdout, "Tiempo (BD %d): %.4f seg\n", sizes[i], time);
        }

        plot_search_times(sizes, times, 5, "Búsqueda Secuencial por ID", "Search ID");

        for (int i = 0; i < 5; i++)
        {
            if (results[i] != -1)
            {
                Product *p = &dbs[i]->products[results[i]];
                fprintf(stdout, "BD %d → Producto en pos %d: ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n\n",
                        sizes[i], results[i], p->id, p->name, p->category, p->price, p->stock);
            }
            else
                fprintf(stdout, "BD %d → Producto NO encontrado.\n\n", sizes[i]);
        }
    }

    else if (search_option == 2)
    {
        fprintf(stdout, "\nIntroduce el nombre: ");
        while (getchar() != '\n');
        if (fgets(name_to_search, MAX_NAME_LENGTH, stdin) == NULL)
        {
            fprintf(stderr, "ERROR al leer el nombre.\n");
            return;
        }

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
                fprintf(stdout, "Producto en pos %d: ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n\n",
                        pos, p->id, p->name, p->category, p->price, p->stock);
            }
            else
                fprintf(stdout, "Producto NO encontrado.\n\n");
        }

        plot_search_times(sizes, times, 5, "Búsqueda Secuencial por Nombre", "Search Name");
    }

    else if (search_option == 4)
    {
        double min_price, max_price;
        fprintf(stdout, "\nIntroduce el precio mínimo: ");
        if (scanf("%lf", &min_price) != 1) { fprintf(stderr, "ERROR.\n"); return; }

        fprintf(stdout, "Introduce el precio máximo: ");
        if (scanf("%lf", &max_price) != 1) { fprintf(stderr, "ERROR.\n"); return; }

        for (int i = 0; i < 5; i++)
        {
            Product *results[50];
            start = clock();
            int found = sequential_search_by_price_range(dbs[i], min_price, max_price, results, 50);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = time;

            fprintf(stdout, "BD %d → %d resultados en %.4f seg:\n", sizes[i], found, time);
            if (found == 0)
                fprintf(stdout, "No hay productos en ese rango.\n\n");
            else
            {
                for (int j = 0; j < found; j++)
                {
                    Product *p = results[j];
                    fprintf(stdout, "ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n",
                            p->id, p->name, p->category, p->price, p->stock);
                }
                fprintf(stdout, "\n");
            }
        }

        plot_search_times(sizes, times, 5, "Búsqueda Secuencial por Precio", "Search Price");
    }

    else
    {
        fprintf(stderr, "\nERROR opción inválida. Selecciona entre 0, 1, 2 y 4.\n\n");
        return;
    }
}
