#include "inventory.h"
#include "utils.h"
#include "search.h"
#include "sort.h"
#include "plot.h"
void handle_binary_search(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option, use_recursive;
    clock_t start, end;
    double search_time;
    double times[5];

    clean_terminal();

    print_menu_search();

    fprintf(stdout, "\nSelecciona una opción: ");
    if (scanf("%d", &search_option) != 1)
    {
        fprintf(stderr, "\nERROR entrada no válida. Por favor, introduce un número.\n\n");
        while (getchar() != '\n')
            ;
        return;
    }

    clean_terminal();

    if (search_option == 0)
    {
        fprintf(stdout, "\nVolviendo al menú principal...\n\n");
        return;
    }

    fprintf(stdout, "\n¿Deseas usar la versión recursiva (1) o iterativa (0)? ");
    if (scanf("%d", &use_recursive) != 1 || (use_recursive != 0 && use_recursive != 1))
    {
        fprintf(stderr, "\nERROR opción inválida. Solo se permite 0 (iterativa) o 1 (recursiva).\n\n");
        while (getchar() != '\n')
            ;
        return;
    }

    // Arreglos con los inventarios y sus tamaños para simplificar el código
    Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
    int sizes[] = {10000, 25000, 50000, 75000, 100000};
    const char *plot_route = "binarysearch";

    if (search_option == 1)
    {
        // Opción 1: Búsqueda binaria por ID
        int num_ids;
        fprintf(stdout, "Cuántos IDs deseas buscar: ");
        if (scanf("%d", &num_ids) != 1)
        {
            fprintf(stderr, "\nERROR entrada no válida.\n\n");
            return;
        }

        int *ids_to_search = (int *)malloc(num_ids * sizeof(int));
        if (ids_to_search == NULL) {
            fprintf(stderr, "\nERROR: No se pudo asignar memoria.\n\n");
            return;
        }

        // El usuario ingresa los IDs a buscar
        fprintf(stdout, "\nIngresa los IDs a buscar:\n");
        for (int i = 0; i < num_ids; i++)
        {
            fprintf(stdout, "ID #%d: ", i + 1);
            if (scanf("%d", &ids_to_search[i]) != 1)
            {
                fprintf(stderr, "\nERROR entrada no válida.\n\n");
                free(ids_to_search);
                return;
            }
        }

        fprintf(stdout, "\nOrdenando inventarios por ID usando Selection Sort...\n");
        for (int i = 0; i < 5; i++)
            selection_sort_by_id(dbs[i]);
        fprintf(stdout, "\nOrdenamiento completado.\n\n");

        // Realiza búsquedas en cada inventario
        for (int i = 0; i < 5; i++)
        {
            int found_count = 0;
            start = clock();  // Inicia temporizador

            // Busca cada ID y cuenta encontrados
            for (int j = 0; j < num_ids; j++)
            {
                int result = use_recursive ? 
                    binary_search_by_id_recursive(dbs[i], ids_to_search[j], 0, dbs[i]->count - 1) : 
                    binary_search_by_id(dbs[i], ids_to_search[j]);
                
                if (result != -1)
                    found_count++;
            }

            end = clock();  // Finaliza temporizador
            search_time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = search_time;  // Guarda el tiempo para el gráfico
            
            // Mostrar tiempo independientemente de si se encontraron IDs o no
            fprintf(stdout, "Tiempo de búsqueda binaria por ID (base de datos de %d): %.4f segundos\n", 
                    sizes[i], search_time);
            fprintf(stdout, "IDs encontrados: %d/%d\n", found_count, num_ids);
            
            // Mostrar explícitamente si algún ID no se encontró
            if (found_count < num_ids) {
                fprintf(stdout, "Advertencia: %d ID(s) no encontrado(s)\n", num_ids - found_count);
            }
        }

        // Genera gráfico con los resultados
        const char *plot_title = use_recursive ? "Búsqueda Binaria Recursiva por ID" : "Búsqueda Binaria Iterativa por ID";
        const char *plot_filename = use_recursive ? "Binary_Recursive_ID" : "Binary_Iterative_ID";
        plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename, 1);

        free(ids_to_search);
        fprintf(stdout, "\nBúsqueda binaria por ID completada. Su gráfico quedó guardado en 'plots'.\n");
    }
    else if (search_option == 2)
    {
        // Opción 2: Búsqueda binaria por nombre
        int num_names;
        fprintf(stdout, "Cuántos nombres deseas buscar: ");
        if (scanf("%d", &num_names) != 1)
        {
            fprintf(stderr, "\nERROR entrada no válida.\n\n");
            return;
        }

        char (*names_to_search)[50] = (char (*)[50])malloc(num_names * sizeof(char[50]));
        if (names_to_search == NULL) {
            fprintf(stderr, "\nERROR: No se pudo asignar memoria.\n\n");
            return;
        }

        // Limpiar buffer de entrada
        while (getchar() != '\n');

        // Pide al usuario que ingrese los nombres a buscar
        fprintf(stdout, "\nIngresa los nombres de los productos a buscar:\n");
        for (int i = 0; i < num_names; i++)
        {
            fprintf(stdout, "Nombre #%d: ", i + 1);
            if (scanf("%49s", names_to_search[i]) != 1) // Limitamos a 49 caracteres para evitar desbordamientos
            {
                fprintf(stderr, "\nERROR entrada no válida.\n\n");
                free(names_to_search);
                return;
            }
        }

        fprintf(stdout, "\nOrdenando inventarios por nombre usando Selection Sort...\n");
        for (int i = 0; i < 5; i++)
            selection_sort_by_name(dbs[i]);
        fprintf(stdout, "\nOrdenamiento completado.\n\n");

        // Realiza búsquedas en cada inventario
        for (int i = 0; i < 5; i++)
        {
            int found_count = 0;
            start = clock();  // Inicia temporizador

            // Busca cada nombre y cuenta encontrados
            for (int j = 0; j < num_names; j++)
            {
                int result = use_recursive ?
                    binary_search_by_name_recursive(dbs[i], names_to_search[j], 0, dbs[i]->count - 1) :
                    binary_search_by_name(dbs[i], names_to_search[j]);
                
                if (result != -1)
                    found_count++;
            }

            end = clock();  // Finaliza temporizador
            search_time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = search_time;  // Guarda el tiempo para el gráfico
            
            // Mostrar tiempos independientemente de si se encontraron nombres o no
            fprintf(stdout, "Tiempo de búsqueda binaria por nombre (base de datos de %d): %.4f segundos\n", 
                    sizes[i], search_time);
            fprintf(stdout, "Nombres encontrados: %d/%d\n", found_count, num_names);
            
            // Mostrar explícitamente si algún nombre no se encontró
            if (found_count < num_names) {
                fprintf(stdout, "Advertencia: %d nombre(s) no encontrado(s)\n", num_names - found_count);
            }
        }

        // Genera gráfico con los resultados
        const char *plot_title = use_recursive ? "Búsqueda Binaria Recursiva por Nombre" : "Búsqueda Binaria Iterativa por Nombre";
        const char *plot_filename = use_recursive ? "Binary Recursive Name" : "Binary_Iterative_Name";
        plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename, 1);

        free(names_to_search);
        fprintf(stdout, "\nBúsqueda binaria por nombre completada. Su gráfico quedó guardado en 'plots'.\n");
    }
    else if (search_option == 3)
    {
        // Opción 3: Búsqueda binaria por rango de precios
        int num_ranges;
        fprintf(stdout, "Cuántos rangos de precios deseas buscar: ");
        if (scanf("%d", &num_ranges) != 1)
        {
            fprintf(stderr, "\nERROR entrada no válida.\n\n");
            return;
        }

        double (*price_ranges)[2] = (double (*)[2])malloc(num_ranges * sizeof(double[2]));
        if (price_ranges == NULL) {
            fprintf(stderr, "\nERROR: No se pudo asignar memoria.\n\n");
            return;
        }

        // Pide al usuario que ingrese los rangos de precios
        fprintf(stdout, "\nIngresa los rangos de precios (min y max):\n");
        for (int i = 0; i < num_ranges; i++)
        {
            fprintf(stdout, "Rango #%d - Precio mínimo: ", i + 1);
            if (scanf("%lf", &price_ranges[i][0]) != 1)
            {
                fprintf(stderr, "\nERROR entrada no válida.\n\n");
                free(price_ranges);
                return;
            }

            fprintf(stdout, "Rango #%d - Precio máximo: ", i + 1);
            if (scanf("%lf", &price_ranges[i][1]) != 1)
            {
                fprintf(stderr, "\nERROR entrada no válida.\n\n");
                free(price_ranges);
                return;
            }
        }

        fprintf(stdout, "\nOrdenando inventarios por precio usando Selection Sort...\n");
        for (int i = 0; i < 5; i++)
            selection_sort_by_price(dbs[i]);
        fprintf(stdout, "\nOrdenamiento completado.\n\n");

        // Realiza búsquedas en cada inventario
        for (int i = 0; i < 5; i++)
        {
            int total_found = 0;
            int products_found = 0;
            start = clock();  // Inicia temporizador

            // Busca en cada rango de precios
            for (int j = 0; j < num_ranges; j++)
            {
                Product *results_array[50];  // Arreglo para almacenar los resultados
                int found = use_recursive ?
                    binary_search_by_price_range_recursive(dbs[i], price_ranges[j][0], price_ranges[j][1], results_array, 50) :
                    binary_search_by_price_range(dbs[i], price_ranges[j][0], price_ranges[j][1], results_array, 50);
                
                if (found > 0) {
                    total_found++;  // Incrementa si se encontró al menos un producto en este rango
                    products_found += found;  // Suma el total de productos encontrados
                }
            }

            end = clock();  // Finaliza temporizador
            search_time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = search_time;  // Guarda el tiempo para el gráfico

            // Mostrar tiempos independientemente de si se encontraron productos o no
            fprintf(stdout, "Tiempo de búsqueda binaria por rango de precio (base de datos de %d): %.4f segundos\n", 
                    sizes[i], search_time);
            fprintf(stdout, "Rangos con productos encontrados: %d/%d\n", total_found, num_ranges);
            fprintf(stdout, "Total de productos encontrados: %d\n", products_found);
            
            // Mostrar explícitamente si algún rango no tuvo resultados
            if (total_found < num_ranges) {
                fprintf(stdout, "Advertencia: %d rango(s) sin productos\n", num_ranges - total_found);
            }
        }

        // Genera gráfico con los resultados
        const char *plot_title = use_recursive ? "Búsqueda Binaria Recursiva por Rangos de Precios" : "Búsqueda Binaria Iterativa por Rangos de Precios";
        const char *plot_filename = use_recursive ? "Binary_Recursive_Price_Range" : "Binary_Iterative_Price_Range";
        plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename, 1);

        free(price_ranges);
        fprintf(stdout, "\nBúsqueda binaria por rango de precios completada. Su gráfico quedó guardado en 'plots'.\n");
    }
    else
    {
        fprintf(stderr, "\nERROR opción inválida. Solo se permite 0, 1, 2 o 3.\n\n");
        return;
    }
    
    // Esperar a que el usuario presione una tecla antes de continuar
    fprintf(stdout, "\nPresiona Enter para continuar...");
    while (getchar() != '\n');
    getchar();
}
