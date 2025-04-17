#include "inventory.h"
#include "search.h"
#include "utils.h"
#include "metrics.h" 
#include "plot.h"
#include "comparativesearch.h"

// Maneja las pruebas de búsqueda secuencial con diferentes tamaños de inventarios
void handle_sequential_search(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
   int search_option;
   clock_t start, end;
   double search_time;
   double times[5];  // Almacena tiempos para cada tamaño de inventario

   clean_terminal();

   print_menu_search();

   fprintf(stdout, "\nSelecciona una opción: ");
   if (scanf("%d", &search_option) != 1)
   {
       fprintf(stderr, "\nERROR entrada no válida. Por favor, introduce un número.\n\n");
       while (getchar() != '\n')  // Limpia el buffer de entrada
           ;
       return;
   }

   clean_terminal();

   if (search_option == 0)
   {
       fprintf(stdout, "\nVolviendo al menú principal...\n\n");
       return;
   }

   // Arreglos con los inventarios y sus tamaños para simplificar el código
   Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
   int sizes[] = {10000, 25000, 50000, 75000, 100000};
   const char *plot_route = "sequentialsearch";  // Directorio para guardar gráficos

   if (search_option == 1)
   {
       // Opción 1: Búsqueda secuencial por ID
       int ids_to_search[10];
       fprintf(stdout, "\nBuscando 10 IDs aleatorias:\n\n");

       // Genera IDs aleatorios para buscar
       srand((unsigned int)time(NULL));
       for (int i = 0; i < 10; i++)
       {
           ids_to_search[i] = rand() % 10000 + 1;
           fprintf(stdout, "ID #%d a buscar: %d\n", i + 1, ids_to_search[i]);
       }
       fprintf(stdout, "\n");

       // Realiza búsquedas en cada inventario
       for (int i = 0; i < 5; i++)
       {
           int found_count = 0;
           start = clock();  // Inicia temporizador

           // Busca cada ID y cuenta encontrados
           for (int j = 0; j < 10; j++)
           {
               int result = sequential_search_by_id(dbs[i], ids_to_search[j]);
               if (result != -1)
                   found_count++;
           }

           end = clock();  // Finaliza temporizador
           search_time = (double)(end - start) / CLOCKS_PER_SEC;
           times[i] = search_time;  // Guarda el tiempo para el gráfico
           fprintf(stdout, "Tiempo de búsqueda Sequential Search por ID (base de datos de %d): %.4f segundos - IDs encontrados: %d/10\n", sizes[i], search_time, found_count);
       }

       // Genera gráfico con los resultados
       const char *plot_title = "Búsqueda Secuencial por ID (10 búsquedas)";
       const char *plot_filename = "Sequential ID 10";
       plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename, 1);

       fprintf(stdout, "\nBúsqueda Sequential Search por ID completada. Su gráfico quedó guardado en 'plots'.");
   }
   else if (search_option == 2)
   {
       // Opción 2: Búsqueda secuencial por nombre
       const char *names_to_search[10] = {
           "Laptop", "Televiso", "Smartfon", "Auricular", "Tablet",
           "Impresora", "Monitor", "Teclado", "Mouse", "Cámara"};

       fprintf(stdout, "\nBuscando 10 nombres de productos comunes:\n\n");
       for (int i = 0; i < 10; i++)
           fprintf(stdout, "Nombre #%d a buscar: %s\n", i + 1, names_to_search[i]);
       fprintf(stdout, "\n");

       // Realiza búsquedas en cada inventario
       for (int i = 0; i < 5; i++)
       {
           int found_count = 0;
           start = clock();  // Inicia temporizador

           // Busca cada nombre y cuenta encontrados
           for (int j = 0; j < 10; j++)
           {
               int result = sequential_search_by_name(dbs[i], names_to_search[j]);
               if (result != -1)
                   found_count++;
           }

           end = clock();  // Finaliza temporizador
           search_time = (double)(end - start) / CLOCKS_PER_SEC;
           times[i] = search_time;  // Guarda el tiempo para el gráfico
           fprintf(stdout, "Tiempo de búsqueda Sequential Search por nombre (base de datos de %d): %.4f segundos - Nombres encontrados: %d/10\n", sizes[i], search_time, found_count);
       }

       // Genera gráfico con los resultados
       const char *plot_title = "Búsqueda Secuencial por Nombre (10 búsquedas)";
       const char *plot_filename = "Sequential Name 10";
       plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename, 1);

       fprintf(stdout, "\nBúsqueda Sequential Search por nombre completada. Su gráfico quedó guardado en 'plots'.");
   }
   else if (search_option == 3)
   {
       // Opción 3: Búsqueda secuencial por rango de precios
       double price_ranges[10][2] = {
           {10.0, 50.0}, {50.0, 100.0}, {100.0, 200.0}, {200.0, 300.0}, {300.0, 500.0}, 
           {500.0, 700.0}, {700.0, 1000.0}, {1000.0, 1500.0}, {1500.0, 2000.0}, {2000.0, 3000.0}};

       fprintf(stdout, "\nBuscando productos en 10 rangos de precios diferentes:\n\n");
       for (int i = 0; i < 10; i++)
           fprintf(stdout, "Rango #%d: %.2f - %.2f\n", i + 1, price_ranges[i][0], price_ranges[i][1]);
       fprintf(stdout, "\n");

       // Realiza búsquedas en cada inventario
       for (int i = 0; i < 5; i++)
       {
           int total_found = 0;
           start = clock();  // Inicia temporizador

           // Busca en cada rango de precios
           for (int j = 0; j < 10; j++)
           {
               Product *results_array[50];
               int found = sequential_search_by_price_range(dbs[i], price_ranges[j][0], price_ranges[j][1], results_array, 5);
               total_found += (found > 0) ? 1 : 0;  // Cuenta rangos con resultados
           }

           end = clock();  // Finaliza temporizador
           search_time = (double)(end - start) / CLOCKS_PER_SEC;
           times[i] = search_time;  // Guarda el tiempo para el gráfico

           fprintf(stdout, "\nTiempo de busqueda Sequential Search por rango de precio (base de datos de %d): %.4f - Total rangos: %d\n\n", sizes[i], search_time, total_found);
       }

       // Genera gráfico con los resultados
       const char *plot_title = "Búsqueda Secuencial por Rangos de Precios (10 rangos)";
       const char *plot_filename = "Sequential Price Range 10";
       plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename, 1);

       fprintf(stdout, "Búsqueda Sequential Search por rango de precios completada. Su gráfico quedó guardado en 'plots'.");
   }
   else
   {
       fprintf(stderr, "\nERROR opción inválida. Solo se permite 0, 1, 2 o 3.\n\n");
       return;
   }
}