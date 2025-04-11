#include "inventory.h"

void handle_sequential_search(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option, id_to_search;
    char name_to_search[MAX_NAME_LENGTH];
    clock_t start, end;
    double time;

    fprintf(stdout, "\nSelecciona el tipo de búsqueda:\n");
    fprintf(stdout, "1. Búsqueda por ID.\n");
    fprintf(stdout, "2. Búsqueda por nombre.\n");
    fprintf(stdout, "0. Volver al menú principal.\n");
    fprintf(stdout, "\nSelecciona una opción: ");

    if (scanf("%d", &search_option) != 1)
    {
        fprintf(stderr, "ERROR entrada no válida. Por favor, introduce un número.\n");
        while (getchar() != '\n')
            ;
        return;
    }

    if (search_option == 0)
    {
        fprintf(stdout, "\nVolviendo al menú principal...\n\n");
        return;
    }

    if (search_option == 1)
    {
        fprintf(stdout, "\nIntroduce el ID a buscar: ");
        if (scanf("%d", &id_to_search) != 1)
        {
            fprintf(stderr, "ERROR entrada no válida. Por favor, introduce un número.\n");
            while (getchar() != '\n')
                ;
            return;
        }
        fprintf(stdout, "\n");

        Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
        int sizes[] = {10000, 25000, 50000, 75000, 100000};
        int results[5];

        for (int i = 0; i < 5; i++)
        {
            start = clock();
            results[i] = sequential_search(dbs[i], id_to_search);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(stdout, "Tiempo de búsqueda secuencial (base de datos %d): %.4f segundos.\n", sizes[i], time);
        }

        fprintf(stdout, "\nResultados de la búsqueda:\n\n");
        for (int i = 0; i < 5; i++)
        {
            if (results[i] != -1)
            {
                fprintf(stdout, "En base de datos %d: Producto encontrado en posición %d\n", sizes[i], results[i]);
                fprintf(stdout, "ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n\n",
                        dbs[i]->products[results[i]].id,
                        dbs[i]->products[results[i]].name,
                        dbs[i]->products[results[i]].category,
                        dbs[i]->products[results[i]].price,
                        dbs[i]->products[results[i]].stock);
            }
            else
                fprintf(stdout, "En base de datos %d: Producto NO encontrado.\n\n", sizes[i]);
        }
        fprintf(stdout, "Búsqueda por ID completada.\n\n");
    }
    else if (search_option == 2)
    {
        fprintf(stdout, "\nIntroduce el nombre a buscar: ");
        while (getchar() != '\n')
            ;

        if (fgets(name_to_search, MAX_NAME_LENGTH, stdin) == NULL)
        {
            fprintf(stderr, "ERROR al leer el nombre.\n");
            return;
        }

        // Eliminar el salto al final
        size_t len = strlen(name_to_search);
        if (len > 0 && name_to_search[len - 1] == '\n')
            name_to_search[len - 1] = '\0';

        fprintf(stdout, "\n");

        Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
        int sizes[] = {10000, 25000, 50000, 75000, 100000};
        int results[5];

        for (int i = 0; i < 5; i++)
        {
            start = clock();
            results[i] = sequential_search_by_name(dbs[i], name_to_search);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(stdout, "Tiempo de búsqueda secuencial por nombre (base de datos %d): %.4f segundos.\n", sizes[i], time);
        }

        fprintf(stdout, "\nResultados de la búsqueda:\n\n");
        for (int i = 0; i < 5; i++)
        {
            if (results[i] != -1)
            {
                fprintf(stdout, "En base de datos %d: Producto encontrado en posición %d\n", sizes[i], results[i]);
                fprintf(stdout, "ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n\n",
                        dbs[i]->products[results[i]].id,
                        dbs[i]->products[results[i]].name,
                        dbs[i]->products[results[i]].category,
                        dbs[i]->products[results[i]].price,
                        dbs[i]->products[results[i]].stock);
            }
            else
                fprintf(stdout, "En base de datos %d: Producto NO encontrado.\n\n", sizes[i]);
        }
        fprintf(stdout, "Búsqueda por nombre completada.\n\n");
    }
    else
    {
        fprintf(stderr, "\nERROR opción inválida. Solo se permite 0, 1 o 2.\n\n");
        return;
    }
}

//  busqueda secuencial por ID
int sequential_search(Inventory *inv, int id)
{
    for (int i = 0; i < inv->count; i++)
        if (inv->products[i].id == id)
            return i;

    return -1;
}

// busqueda secuencial por nombre
int sequential_search_by_name(Inventory *inv, const char *name)
{
    for (int i = 0; i < inv->count; i++)
        if (strcmp(inv->products[i].name, name) == 0)
            return i;

    return -1;
}