#include "inventory.h"

void handle_sequential_search(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option;
    clock_t start, end;
    double search_time;
    double times[5];

    clean_terminal();

    fprintf(stdout, "\nSelecciona el tipo de búsqueda secuencial:\n");
    fprintf(stdout, "1. Búsqueda secuencial por ID.\n");
    fprintf(stdout, "2. Búsqueda secuencial por nombre.\n");
    fprintf(stdout, "3. Búsqueda secuencial por rango de precios.\n");
    fprintf(stdout, "0. Volver al menú principal.\n");
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

    // Crear copias de los inventarios para no alterar los originales.
    Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
    int sizes[] = {10000, 25000, 50000, 75000, 100000};
    const char *plot_route = "sequentialsearch";

    if (search_option == 1)
    {
        // Búsqueda de 10 IDs aleatorios
        int ids_to_search[10];
        fprintf(stdout, "\nBuscando 10 IDs aleatorios...\n");
        
        // Generar 10 IDs aleatorios entre 1 y 10000
        srand((unsigned int)time(NULL));
        for (int i = 0; i < 10; i++) {
            ids_to_search[i] = rand() % 10000 + 1;
            fprintf(stdout, "ID #%d a buscar: %d\n", i+1, ids_to_search[i]);
        }
        fprintf(stdout, "\n");

        for (int i = 0; i < 5; i++)
        {
            int found_count = 0;
            start = clock();
            
            for (int j = 0; j < 10; j++) {
                int result = sequential_search_by_id(dbs[i], ids_to_search[j]);
                if (result != -1)
                    found_count++;
            }
            
            end = clock();
            search_time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = search_time;
            fprintf(stdout, "Tiempo de búsqueda secuencial por ID (BD %d): %.4f seg - Encontrados: %d/10\n", sizes[i], search_time, found_count);
        }

        // Generar gráfico para búsqueda secuencial por ID
        const char *plot_title = "Búsqueda Secuencial por ID (10 búsquedas)";
        const char *plot_filename = "Sequential ID 10";
        plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename);

        fprintf(stdout, "Búsqueda secuencial por ID completada. Su gráfico quedó guardado en 'plots'.\n\n");
    }
    else if (search_option == 2)
    {
        // 10 nombres para buscar
        const char *names_to_search[10] = {
            "Laptop", "Televisor", "Smartphone", "Auriculares", "Tablet",
            "Impresora", "Monitor", "Teclado", "Mouse", "Cámara"
        };
        
        fprintf(stdout, "\nBuscando 10 nombres de productos comunes:\n");
        for (int i = 0; i < 10; i++) {
            fprintf(stdout, "Nombre #%d a buscar: %s\n", i+1, names_to_search[i]);
        }
        fprintf(stdout, "\n");

        for (int i = 0; i < 5; i++)
        {
            int found_count = 0;
            start = clock();
            
            for (int j = 0; j < 10; j++) {
                int result = sequential_search_by_name(dbs[i], names_to_search[j]);
                if (result != -1)
                    found_count++;
            }
            
            end = clock();
            search_time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = search_time;
            fprintf(stdout, "Tiempo de búsqueda secuencial por nombre (BD %d): %.4f seg - Encontrados: %d/10\n", sizes[i], search_time, found_count);
        }

        // Generar gráfico para búsqueda secuencial por nombre
        const char *plot_title = "Búsqueda Secuencial por Nombre (10 búsquedas)";
        const char *plot_filename = "Sequential Name 10";
        plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename);

        fprintf(stdout, "Búsqueda secuencial por nombre completada. Su gráfico quedó guardado en 'plots'.\n\n");
    }
    else if (search_option == 3)
    {
        // 10 rangos de precios diferentes para probar
        double price_ranges[10][2] = {
            {10.0, 50.0}, {50.0, 100.0}, {100.0, 200.0}, {200.0, 300.0}, {300.0, 500.0},
            {500.0, 700.0}, {700.0, 1000.0}, {1000.0, 1500.0}, {1500.0, 2000.0}, {2000.0, 3000.0}
        };
        
        fprintf(stdout, "\nBuscando productos en 10 rangos de precios diferentes:\n");
        for (int i = 0; i < 10; i++) {
            fprintf(stdout, "Rango #%d: %.2f - %.2f\n", i+1, price_ranges[i][0], price_ranges[i][1]);
        }
        fprintf(stdout, "\n");

        for (int i = 0; i < 5; i++)
        {
            int total_found = 0;
            start = clock();
            
            for (int j = 0; j < 10; j++) {
                Product *results_array[50];
                int found = sequential_search_by_price_range(dbs[i], price_ranges[j][0], price_ranges[j][1], results_array, 5);
                total_found += (found > 0) ? 1 : 0; // Contamos cuántos rangos dieron resultados
            }
            
            end = clock();
            search_time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = search_time;

            fprintf(stdout, "Base de datos de %d → %d rangos con resultados en %.4f seg\n", sizes[i], total_found, search_time);
        }

        // Gráfico para búsqueda secuencial por rango de precios
        const char *plot_title = "Búsqueda Secuencial por Rangos de Precios (10 rangos)";
        const char *plot_filename = "Sequential Price Range 10";
        plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename);

        fprintf(stdout, "Búsqueda secuencial por rango de precios completada. Su gráfico quedó guardado en 'plots'.\n\n");
    }
    else
    {
        fprintf(stderr, "\nERROR opción inválida. Solo se permite 0, 1, 2 o 3.\n\n");
        return;
    }
}