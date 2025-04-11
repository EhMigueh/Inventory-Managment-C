#include "inventory.h"
void handle_binary_search(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option, id_to_search, use_recursive;
    char name_to_search[MAX_NAME_LENGTH];
    clock_t start, end;
    double time;

    fprintf(stdout, "\nSelecciona el tipo de búsqueda:\n");
    fprintf(stdout, "1. Búsqueda binaria por ID.\n");
    fprintf(stdout, "2. Búsqueda binaria por nombre. (Requiere arreglo o revision)\n");
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

    fprintf(stdout, "\n¿Deseas usar la versión recursiva (1) o iterativa (0)? \n");
    if (scanf("%d", &use_recursive) != 1)
    {
        fprintf(stderr, "ERROR entrada no válida. Por favor, introduce un número.\n");
        while (getchar() != '\n')
            ;
        return;
    }
    
    // Validar que sea 0 o 1
    if (use_recursive != 0 && use_recursive != 1)
    {
        fprintf(stderr, "ERROR opción inválida. Solo se permite 0 (iterativa) o 1 (recursiva).\n");
        return;
    }
    


    // Crear copias de los inventarios para no alterar los originales
    Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
    int sizes[] = {10000, 25000, 50000, 75000, 100000};
    int results[5];

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

        fprintf(stdout, "Ordenando inventarios por ID para la búsqueda binaria...\n");
        for (int i = 0; i < 5; i++)
        {
            bubble_sort_by_id(dbs[i]);
        }
        fprintf(stdout, "Ordenamiento completado.\n\n");

        for (int i = 0; i < 5; i++)
        {
            start = clock();
            if (use_recursive)
                results[i] = binary_search_by_id_recursive(dbs[i], id_to_search, 0, dbs[i]->count - 1);
            else
                results[i] = binary_search_by_id(dbs[i], id_to_search);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(stdout, "Tiempo de búsqueda binaria por ID (base de datos %d): %.4f segundos.\n", sizes[i], time);
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
        fprintf(stdout, "Búsqueda binaria por ID completada.\n\n");
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
        

        size_t len = strlen(name_to_search);
        if (len > 0 && name_to_search[len - 1] == '\n')
            name_to_search[len - 1] = '\0';
        
        fprintf(stdout, "\n");

        
        fprintf(stdout, "Ordenando inventarios por nombre para la búsqueda binaria...\n");
        for (int i = 0; i < 5; i++)
        {
            bubble_sort_by_name(dbs[i]);
        }
        fprintf(stdout, "Ordenamiento completado.\n\n");

        for (int i = 0; i < 5; i++)
        {
            start = clock();
            if (use_recursive)
                results[i] = binary_search_by_name_recursive(dbs[i], name_to_search, 0, dbs[i]->count - 1);
            else
                results[i] = binary_search_by_name(dbs[i], name_to_search);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(stdout, "Tiempo de búsqueda binaria por nombre (base de datos %d): %.4f segundos.\n", sizes[i], time);
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
        fprintf(stdout, "Búsqueda binaria por nombre completada.\n\n");
    }
    else
    {
        fprintf(stderr, "\nERROR opción inválida. Solo se permite 0, 1 o 2.\n\n");
        return;
    }
}

// Implementación iterativa de búsqueda binaria por ID
int binary_search_by_id(Inventory *inv, int id)
{
    int left = 0;
    int right = inv->count - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // Evita overflow

        if (inv->products[mid].id == id)
            return mid;

        if (inv->products[mid].id < id)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1; // No encontrado
}

// Implementación recursiva por ID
int binary_search_by_id_recursive(Inventory *inv, int id, int left, int right)
{
    if (left > right)
        return -1; // Caso base no se encontro

    int mid = left + (right - left) / 2; //Evitar el overflow

    if (inv->products[mid].id == id)
        return mid;

    if (inv->products[mid].id < id)
        return binary_search_by_id_recursive(inv, id, mid + 1, right);
    else
        return binary_search_by_id_recursive(inv, id, left, mid - 1);
}

// Implementación iterativa de búsqueda binaria por nombre
int binary_search_by_name(Inventory *inv, const char *name)
{
    int left = 0;
    int right = inv->count - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // Evitar el overflow
        int cmp = strcmp(inv->products[mid].name, name);

        if (cmp == 0)
            return mid;

        if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1; 
}

// Implementacion optimizada recursiva de busqueda binaria por nombre
int binary_search_by_name_recursive(Inventory *inv, const char *name, int left, int right)
{
    if (left > right)
        return -1; // Caso base no se encontro

    int mid = left + (right - left) / 2; // Evitar el overflow
    int cmp = strcmp(inv->products[mid].name, name);

    if (cmp == 0)
        return mid;

    if (cmp < 0)
        return binary_search_by_name_recursive(inv, name, mid + 1, right);
    else
        return binary_search_by_name_recursive(inv, name, left, mid - 1);
}