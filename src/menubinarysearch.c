#include "inventory.h"


void handle_binary_search(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option, id_to_search, use_recursive;
    char name_to_search[MAX_NAME_LENGTH];
    clock_t start, end;
    double time;
    double times[5];

    system("clear");

    fprintf(stdout, "\nSelecciona el tipo de búsqueda:\n");
    fprintf(stdout, "1. Búsqueda binaria por ID.\n");
    fprintf(stdout, "2. Búsqueda binaria por nombre.\n");
    fprintf(stdout, "3. Búsqueda binaria por rango de precios.\n");
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

    fprintf(stdout, "\n¿Deseas usar la versión recursiva (1) o iterativa (0)? ");
    if (scanf("%d", &use_recursive) != 1)
    {
        fprintf(stderr, "\nERROR entrada no válida. Por favor, introduce un número.\n\n");
        while (getchar() != '\n')
            ;
        return;
    }

    // Validar que sea 0 o 1.
    if (use_recursive != 0 && use_recursive != 1)
    {
        fprintf(stderr, "\nERROR opción inválida. Solo se permite 0 (iterativa) o 1 (recursiva).\n\n");
        return;
    }

    // Crear copias de los inventarios para no alterar los originales.
    Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
    int sizes[] = {10000, 25000, 50000, 75000, 100000};
    int results[5];

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
            times[i] = time;
            fprintf(stdout, "Tiempo de búsqueda binaria por ID (BD %d): %.4f seg\n", sizes[i], time);
            
            if (results[i] != -1)
            {
                Product *p = &dbs[i]->products[results[i]];
                fprintf(stdout, "Producto en pos %d: ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n\n", 
                        results[i], p->id, p->name, p->category, p->price, p->stock);
            }
            else
                fprintf(stdout, "Producto NO encontrado.\n\n");
        }
        
        // Generar gráfico para búsqueda binaria por ID
        const char *plot_title = use_recursive ? "Búsqueda Binaria Recursiva por ID" : "Búsqueda Binaria Iterativa por ID";
        const char *plot_filename = use_recursive ? "Binary_Recursive_ID" : "Binary_Iterative_ID";
        plot_search_times(sizes, times, 5, plot_title, plot_filename);
        
        fprintf(stdout, "Búsqueda binaria por ID completada. Su gráfico quedó guardado en 'plots'.\n\n");
    }
    else if (search_option == 2)
    {
        fprintf(stdout, "\nIntroduce el nombre a buscar: ");
        while (getchar() != '\n')
            ;

        if (fgets(name_to_search, MAX_NAME_LENGTH, stdin) == NULL)
        {
            fprintf(stderr, "\nERROR al leer el nombre.\n\n");
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
            times[i] = time;
            fprintf(stdout, "Tiempo de búsqueda binaria por nombre (BD %d): %.4f seg\n", sizes[i], time);
            
            if (results[i] != -1)
            {
                Product *p = &dbs[i]->products[results[i]];
                fprintf(stdout, "Producto en pos %d: ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n\n", 
                        results[i], p->id, p->name, p->category, p->price, p->stock);
            }
            else
                fprintf(stdout, "Producto NO encontrado.\n\n");
        }
        
        // Generar gráfico para búsqueda binaria por nombre
        const char *plot_title = use_recursive ? "Búsqueda Binaria Recursiva por Nombre" : "Búsqueda Binaria Iterativa por Nombre";
        const char *plot_filename = use_recursive ? "Binary_Recursive_Name" : "Binary_Iterative_Name";
        plot_search_times(sizes, times, 5, plot_title, plot_filename);
        
        fprintf(stdout, "Búsqueda binaria por nombre completada. Su gráfico quedó guardado en 'plots'.\n\n");
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

        fprintf(stdout, "Ordenando inventarios por precio para la búsqueda binaria...\n");
        for (int i = 0; i < 5; i++)
        {
            bubble_sort_by_price(dbs[i]);
        }
        fprintf(stdout, "Ordenamiento completado.\n\n");

        for (int i = 0; i < 5; i++)
        {
            Product *results_array[50];
            start = clock();
            
            int found;
            if (use_recursive)
                found = binary_search_by_price_range_recursive(dbs[i], min_price, max_price, results_array, 10);
            else
                found = binary_search_by_price_range(dbs[i], min_price, max_price, results_array, 10);
                
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
                    Product *p = results_array[j];
                    fprintf(stdout, "ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n", p->id, p->name, p->category, p->price, p->stock);
                }
                fprintf(stdout, "\n");
            }
        }
        
        //  gráfico para búsqueda binaria por rango de precios
        const char *plot_title = use_recursive ? "Búsqueda Binaria Recursiva por Rango de Precios" : "Búsqueda Binaria Iterativa por Rango de Precios";
        const char *plot_filename = use_recursive ? "Binary_Recursive_Price_Range" : "Binary_Iterative_Price_Range";
        plot_search_times(sizes, times, 5, plot_title, plot_filename);
        
        fprintf(stdout, "Búsqueda binaria por rango de precios completada. Su gráfico quedó guardado en 'plots'.\n\n");
    }
    else
    {
        fprintf(stderr, "\nERROR opción inválida. Solo se permite 0, 1, 2 o 3.\n\n");
        return;
    }
}