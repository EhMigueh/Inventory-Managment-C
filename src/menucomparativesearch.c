#include "inventory.h"


void handle_comparative_search(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    double seq_times[5], bin_iter_times[5], bin_rec_times[5];
    struct timespec start_time, end_time;
    const int NUM_REPETITIONS = 1000;
    
    clean_terminal();
    
    fprintf(stdout, "\nComparando búsqueda secuencial vs binaria...\n");
    
    // Opciones de búsqueda
    fprintf(stdout, "\nSelecciona el tipo de búsqueda a comparar:\n");
    fprintf(stdout, "1. Búsqueda por ID.\n");
    fprintf(stdout, "2. Búsqueda por nombre.\n");
    fprintf(stdout, "3. Búsqueda por rango de precios.\n");
    fprintf(stdout, "0. Volver al menú anterior.\n");
    fprintf(stdout, "\nSelecciona una opción: ");
    
    int search_option;
    if (scanf("%d", &search_option) != 1)
    {
        fprintf(stderr, "\nERROR entrada no válida. Por favor, introduce un número.\n\n");
        while (getchar() != '\n');
        return;
    }
    
    if (search_option == 0)
    {
        fprintf(stdout, "\nVolviendo al menú anterior...\n\n");
        return;
    }
    
    if (search_option < 1 || search_option > 3)
    {
        fprintf(stderr, "\nERROR opción inválida. Solo se permite 0, 1, 2 o 3.\n\n");
        while (getchar() != '\n');
        return;
    }
    
    clean_terminal();
    
    Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
    int sizes[] = {10000, 25000, 50000, 75000, 100000};
    const char *plot_route = "comparative";
    
    // Para buscar IDs o nombres
    if (search_option == 1 || search_option == 2)
    {
        int ids_to_search[10];
        const char *names_to_search[10] = {
            "Laptop", "Televisor", "Smartphone", "Auriculares", "Tablet",
            "Impresora", "Monitor", "Teclado", "Mouse", "Cámara"
        };
        
        if (search_option == 1)
        {
            fprintf(stdout, "\nBuscando 10 IDs aleatorios...\n");
            srand((unsigned int)time(NULL));
            for (int i = 0; i < 10; i++)
            {
                ids_to_search[i] = rand() % 10000 + 1;
                fprintf(stdout, "ID #%d a buscar: %d\n", i + 1, ids_to_search[i]);
            }
        }
        else
        {
            fprintf(stdout, "\nBuscando 10 nombres de productos comunes:\n");
            for (int i = 0; i < 10; i++)
                fprintf(stdout, "Nombre #%d a buscar: %s\n", i + 1, names_to_search[i]);
        }
        
        fprintf(stdout, "\n");
        
        // Realizar búsqueda secuencial primero
        for (int i = 0; i < 5; i++)
        {
            int found_count = 0;
            clock_gettime(CLOCK_MONOTONIC, &start_time);
            
            for (int rep = 0; rep < NUM_REPETITIONS; rep++)
            {
                for (int j = 0; j < 10; j++)
                {
                    int result;
                    if (search_option == 1)
                        result = sequential_search_by_id(dbs[i], ids_to_search[j]);
                    else
                        result = sequential_search_by_name(dbs[i], names_to_search[j]);
                    
                    if (rep == NUM_REPETITIONS - 1 && result != -1)
                        found_count++;
                }
            }
            
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            double search_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec)) / 1e9;
            seq_times[i] = search_time / NUM_REPETITIONS;
            
            fprintf(stdout, "Tiempo de búsqueda secuencial por %s (BD %d): %.9f seg - Encontrados: %d/10\n",
                    search_option == 1 ? "ID" : "nombre", sizes[i], seq_times[i], found_count);
        }
        
        // Ordenar los inventarios antes de la búsqueda binaria
        fprintf(stdout, "\nOrdenando inventarios por %s usando Selection Sort...\n",
                search_option == 1 ? "ID" : "nombre");
        
        for (int i = 0; i < 5; i++)
        {
            if (search_option == 1)
                selection_sort_by_id(dbs[i]);
            else
                selection_sort_by_name(dbs[i]);
        }
        
        fprintf(stdout, "Ordenamiento completado.\n\n");
        
        // Búsqueda binaria iterativa
        for (int i = 0; i < 5; i++)
        {
            int found_count = 0;
            clock_gettime(CLOCK_MONOTONIC, &start_time);
            
            for (int rep = 0; rep < NUM_REPETITIONS; rep++)
            {
                for (int j = 0; j < 10; j++)
                {
                    int result;
                    if (search_option == 1)
                        result = binary_search_by_id(dbs[i], ids_to_search[j]);
                    else
                        result = binary_search_by_name(dbs[i], names_to_search[j]);
                    
                    if (rep == NUM_REPETITIONS - 1 && result != -1)
                        found_count++;
                }
            }
            
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            double search_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec)) / 1e9;
            bin_iter_times[i] = search_time / NUM_REPETITIONS;
            
            fprintf(stdout, "Tiempo de búsqueda binaria iterativa por %s (BD %d): %.9f seg - Encontrados: %d/10\n",
                    search_option == 1 ? "ID" : "nombre", sizes[i], bin_iter_times[i], found_count);
        }
        
        // Búsqueda binaria recursiva
        for (int i = 0; i < 5; i++)
        {
            int found_count = 0;
            clock_gettime(CLOCK_MONOTONIC, &start_time);
            
            for (int rep = 0; rep < NUM_REPETITIONS; rep++)
            {
                for (int j = 0; j < 10; j++)
                {
                    int result;
                    if (search_option == 1)
                        result = binary_search_by_id_recursive(dbs[i], ids_to_search[j], 0, dbs[i]->count - 1);
                    else
                        result = binary_search_by_name_recursive(dbs[i], names_to_search[j], 0, dbs[i]->count - 1);
                    
                    if (rep == NUM_REPETITIONS - 1 && result != -1)
                        found_count++;
                }
            }
            
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            double search_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec)) / 1e9;
            bin_rec_times[i] = search_time / NUM_REPETITIONS;
            
            fprintf(stdout, "Tiempo de búsqueda binaria recursiva por %s (BD %d): %.9f seg - Encontrados: %d/10\n",
                    search_option == 1 ? "ID" : "nombre", sizes[i], bin_rec_times[i], found_count);
        }
        
        // Generar gráfico para la comparación
        const char *plot_title = search_option == 1 ? 
                                 "Comparación de Búsquedas por ID" : 
                                 "Comparación de Búsquedas por Nombre";
        const char *plot_filename = search_option == 1 ? 
                                   "Comparative search by id" : 
                                   "Comparative search by name";
        
        // Asumiendo que tienes una función para graficar tres series de datos
        plot_comparative_search_times(sizes, seq_times, bin_iter_times, bin_rec_times, 5,
                                    plot_title, plot_route, plot_filename);
        
        fprintf(stdout, "\nComparación de búsquedas por %s completada. Su gráfico quedó guardado en 'plots'.\n\n",
                search_option == 1 ? "ID" : "nombre");
    }
    else if (search_option == 3) // Búsqueda por rango de precios
    {
        // Definir 10 rangos de precios para probar
        double price_ranges[10][2] = {
            {10.0, 50.0}, {50.0, 100.0}, {100.0, 200.0}, {200.0, 300.0}, {300.0, 500.0},
            {500.0, 700.0}, {700.0, 1000.0}, {1000.0, 1500.0}, {1500.0, 2000.0}, {2000.0, 3000.0}
        };
        
        fprintf(stdout, "\nBuscando productos en 10 rangos de precios diferentes:\n");
        for (int i = 0; i < 10; i++)
            fprintf(stdout, "Rango #%d: %.2f - %.2f\n", i + 1, price_ranges[i][0], price_ranges[i][1]);
        
        fprintf(stdout, "\n");
        
        // Búsqueda secuencial por rango de precios
        for (int i = 0; i < 5; i++)
        {
            int total_found = 0;
            Product *results_array[50];
            
            clock_gettime(CLOCK_MONOTONIC, &start_time);
            
            for (int rep = 0; rep < NUM_REPETITIONS; rep++)
            {
                for (int j = 0; j < 10; j++)
                {
                    int found = 0;
                    // Implementar la versión adaptada para medición en nanosegundos
                    if (rep == NUM_REPETITIONS - 1) {
                        found = sequential_search_by_price_range(dbs[i], price_ranges[j][0], price_ranges[j][1], results_array, 5);
                        if (found > 0)
                            total_found++;
                    } else {
                        // Simulación del conteo sin almacenar resultados
                        for (int k = 0; k < dbs[i]->count; k++) {
                            if (dbs[i]->products[k].price >= price_ranges[j][0] && 
                                dbs[i]->products[k].price <= price_ranges[j][1]) {
                                found++;
                                if (found >= 5) break; // Simular el límite de resultados
                            }
                        }
                    }
                }
            }
            
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            double search_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec)) / 1e9;
            seq_times[i] = search_time / NUM_REPETITIONS;
            
            fprintf(stdout, "Base de datos de %d → %d rangos con resultados en %.9f seg (Secuencial)\n",
                    sizes[i], total_found, seq_times[i]);
        }
        
        // Ordenar los inventarios por precio para la búsqueda binaria
        fprintf(stdout, "\nOrdenando inventarios por precio usando Selection Sort...\n");
        for (int i = 0; i < 5; i++)
            selection_sort_by_price(dbs[i]);
        fprintf(stdout, "Ordenamiento completado.\n\n");
        
        // Búsqueda binaria iterativa por rango de precios
        for (int i = 0; i < 5; i++)
        {
            int total_found = 0;
            Product *results_array[50];
            
            clock_gettime(CLOCK_MONOTONIC, &start_time);
            
            for (int rep = 0; rep < NUM_REPETITIONS; rep++)
            {
                for (int j = 0; j < 10; j++)
                {
                    int found = 0;
                    if (rep == NUM_REPETITIONS - 1) {
                        found = binary_search_by_price_range(dbs[i], price_ranges[j][0], price_ranges[j][1], results_array, 5);
                        if (found > 0)
                            total_found++;
                    } else {
                        // Simulación simple para medición de rendimiento sin almacenar resultados
                        int lower = binary_search_lower_bound_price(dbs[i], price_ranges[j][0]);
                        int upper = binary_search_upper_bound_price(dbs[i], price_ranges[j][1]);
                        if (lower != -1 && upper != -1 && lower <= upper) {
                            found = upper - lower + 1;
                            if (found > 5) found = 5; 
                        }
                    }
                }
            }
            
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            double search_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec)) / 1e9;
            bin_iter_times[i] = search_time / NUM_REPETITIONS;
            
            fprintf(stdout, "Base de datos de %d → %d rangos con resultados en %.9f seg (Binaria Iterativa)\n",
                    sizes[i], total_found, bin_iter_times[i]);
        }
        
        // Búsqueda binaria recursiva por rango de precios
        for (int i = 0; i < 5; i++)
        {
            int total_found = 0;
            Product *results_array[50];
            
            clock_gettime(CLOCK_MONOTONIC, &start_time);
            
            for (int rep = 0; rep < NUM_REPETITIONS; rep++)
            {
                for (int j = 0; j < 10; j++)
                {
                    int found = 0;
                    if (rep == NUM_REPETITIONS - 1) {
                        found = binary_search_by_price_range_recursive(dbs[i], price_ranges[j][0], price_ranges[j][1], results_array, 5);
                        if (found > 0)
                            total_found++;
                    } else {
                        // Simulación para medición de rendimiento
                        int lower = find_lower_bound_recursive(dbs[i], price_ranges[j][0], 0, dbs[i]->count - 1);
                        int upper = find_upper_bound_recursive(dbs[i], price_ranges[j][1], 0, dbs[i]->count - 1);
                        if (lower != -1 && upper != -1 && lower <= upper) {
                            found = upper - lower + 1;
                            if (found > 5) found = 5; 
                        }
                    }
                }
            }
            
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            double search_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec)) / 1e9;
            bin_rec_times[i] = search_time / NUM_REPETITIONS;
            
            fprintf(stdout, "Base de datos de %d → %d rangos con resultados en %.9f seg (Binaria Recursiva)\n",
                    sizes[i], total_found, bin_rec_times[i]);
        }
        
        // Generar gráfico para la comparación
        const char *plot_title = "Comparación de Búsquedas por Rango de Precios";
        const char *plot_filename = "Comparative search by price";
        
        // Graficar los tres conjuntos de tiempos
        plot_comparative_search_times(sizes, seq_times, bin_iter_times, bin_rec_times, 5,
                                    plot_title, plot_route, plot_filename);
        
        fprintf(stdout, "\nComparación de búsquedas por rango de precios completada. Su gráfico quedó guardado en 'plots'.\n\n");
    }
    
    // Recargar los inventarios originales
    load_all_inventories(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
}
