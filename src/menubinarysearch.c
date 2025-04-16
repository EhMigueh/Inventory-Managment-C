#include "inventory.h"

void handle_binary_search(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option, use_recursive;
    struct timespec start_time, end_time;
    double search_time;
    double times[5];
    const int NUM_REPETITIONS = 1000;

    clean_terminal();

    print_menu_search();

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

    Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
    int sizes[] = {10000, 25000, 50000, 75000, 100000};
    const char *plot_route = "binarysearch";

    if (search_option == 1) // Búsqueda por ID
    {
        int ids_to_search[10];
        fprintf(stdout, "\nBuscando 10 IDs aleatorios...\n");
        srand((unsigned int)time(NULL));
        for (int i = 0; i < 10; i++)
        {
            ids_to_search[i] = rand() % 10000 + 1;
            fprintf(stdout, "ID #%d a buscar: %d\n", i + 1, ids_to_search[i]);
        }

        fprintf(stdout, "\nOrdenando inventarios por ID usando Selection Sort...\n");
        for (int i = 0; i < 5; i++)
            selection_sort_by_id(dbs[i]);
        fprintf(stdout, "\nOrdenamiento completado.\n\n");

        for (int i = 0; i < 5; i++)
        {
            int found_count = 0;
            clock_gettime(CLOCK_MONOTONIC, &start_time);
            for (int rep = 0; rep < NUM_REPETITIONS; rep++)
            {
                for (int j = 0; j < 10; j++)
                {
                    int result = use_recursive ? binary_search_by_id_recursive(dbs[i], ids_to_search[j], 0, dbs[i]->count - 1) : binary_search_by_id(dbs[i], ids_to_search[j]);
                    if (rep == NUM_REPETITIONS - 1 && result != -1)
                        found_count++;
                }
            }
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            search_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec)) / 1e9;
            times[i] = search_time / NUM_REPETITIONS;
            fprintf(stdout, "Tiempo de búsqueda binaria por ID (BD %d): %.9f seg - Encontrados: %d/10\n", sizes[i], times[i], found_count);
        }

        const char *plot_title = use_recursive ? "Búsqueda Binaria Recursiva por ID (10 búsquedas)" : "Búsqueda Binaria Iterativa por ID (10 búsquedas)";
        const char *plot_filename = use_recursive ? "Binary_Recursive_ID_10" : "Binary_Iterative_ID_10";
        plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename);
        fprintf(stdout, "\nBúsqueda binaria por ID completada. Su gráfico quedó guardado en 'plots'.");
    }
    else if (search_option == 2) // Búsqueda por nombre
    {
        const char *names_to_search[10] = {
            "Laptop", "Televiso", "Smartfon", "Auricular", "Tablet",
            "Impresora", "Monitor", "Teclado", "Mouse", "Cámara"};

        fprintf(stdout, "\nBuscando 10 nombres de productos comunes:\n");
        for (int i = 0; i < 10; i++)
            fprintf(stdout, "Nombre #%d a buscar: %s\n", i + 1, names_to_search[i]);

        fprintf(stdout, "\nOrdenando inventarios por nombre usando Selection Sort...\n");
        for (int i = 0; i < 5; i++)
            selection_sort_by_name(dbs[i]);
        fprintf(stdout, "Ordenamiento completado.\n\n");

        for (int i = 0; i < 5; i++)
        {
            int found_count = 0;
            clock_gettime(CLOCK_MONOTONIC, &start_time);
            for (int rep = 0; rep < NUM_REPETITIONS; rep++)
            {
                for (int j = 0; j < 10; j++)
                {
                    int result = use_recursive
                                     ? binary_search_by_name_recursive(dbs[i], names_to_search[j], 0, dbs[i]->count - 1)
                                     : binary_search_by_name(dbs[i], names_to_search[j]);
                    if (rep == NUM_REPETITIONS - 1 && result != -1)
                        found_count++;
                }
            }
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            search_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec)) / 1e9;
            times[i] = search_time / NUM_REPETITIONS;
            fprintf(stdout, "Tiempo de búsqueda binaria por nombre (BD %d): %.9f seg - Encontrados: %d/10\n",
                    sizes[i], times[i], found_count);
        }

        const char *plot_title = use_recursive ? "Búsqueda Binaria Recursiva por Nombre (10 búsquedas)" : "Búsqueda Binaria Iterativa por Nombre (10 búsquedas)";
        const char *plot_filename = use_recursive ? "Binary_Recursive_Name_10" : "Binary_Iterative_Name_10";
        plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename);
        fprintf(stdout, "\nBúsqueda binaria por nombre completada. Su gráfico quedó guardado en 'plots'.");
    }
    else if (search_option == 3) // Búsqueda por rango de precios
    {
        double price_ranges[10][2] = {
            {10.0, 50.0}, {50.0, 100.0}, {100.0, 200.0}, {200.0, 300.0}, {300.0, 500.0}, {500.0, 700.0}, {700.0, 1000.0}, {1000.0, 1500.0}, {1500.0, 2000.0}, {2000.0, 3000.0}};

        fprintf(stdout, "\nBuscando productos en 10 rangos de precios diferentes:\n");
        for (int i = 0; i < 10; i++)
            fprintf(stdout, "Rango #%d: %.2f - %.2f\n", i + 1, price_ranges[i][0], price_ranges[i][1]);

        fprintf(stdout, "\nOrdenando inventarios por precio usando Selection Sort...\n");
        for (int i = 0; i < 5; i++)
            selection_sort_by_price(dbs[i]);
        fprintf(stdout, "Ordenamiento completado.\n\n");

        for (int i = 0; i < 5; i++)
        {
            int total_found = 0;
            clock_gettime(CLOCK_MONOTONIC, &start_time);
            for (int rep = 0; rep < NUM_REPETITIONS; rep++)
            {
                for (int j = 0; j < 10; j++)
                {
                    Product *results_array[50];
                    int found = use_recursive
                                    ? binary_search_by_price_range_recursive(dbs[i], price_ranges[j][0], price_ranges[j][1], results_array, 5)
                                    : binary_search_by_price_range(dbs[i], price_ranges[j][0], price_ranges[j][1], results_array, 5);
                    if (rep == NUM_REPETITIONS - 1 && found > 0)
                        total_found++;
                }
            }
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            search_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec)) / 1e9;
            times[i] = search_time / NUM_REPETITIONS;
            fprintf(stdout, "Base de datos de %d → %d rangos con resultados en %.9f seg\n",
                    sizes[i], total_found, times[i]);
        }

        const char *plot_title = use_recursive ? "Búsqueda Binaria Recursiva por Rango de Precios (10 búsquedas)" : "Búsqueda Binaria Iterativa por Rango de Precios (10 búsquedas)";
        const char *plot_filename = use_recursive ? "Binary_Recursive_Price_10" : "Binary_Iterative_Price_10";
        plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename);
        fprintf(stdout, "\nBúsqueda binaria por rango de precios completada. Su gráfico quedó guardado en 'plots'.");
    }
}
