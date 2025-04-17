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
   double times[5];  

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
       int num_ids;
       fprintf(stdout, "Cuántos IDs deseas buscar: ");
       if (scanf("%d", &num_ids) != 1)
       {
           fprintf(stderr, "\nERROR entrada no válida.\n\n");
           return;
       }

       int *ids_to_search = (int *)malloc(num_ids * sizeof(int));

       // Genera IDs aleatorios o pide al usuario que los ingrese
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

       // Realiza búsquedas en cada inventario
       for (int i = 0; i < 5; i++)
       {
           int found_count = 0;
           start = clock();  // Inicia temporizador

           // Busca cada ID y cuenta encontrados
           for (int j = 0; j < num_ids; j++)
           {
               int result = sequential_search_by_id(dbs[i], ids_to_search[j]);
               if (result != -1)
                   found_count++;
           }

           end = clock();  // Finaliza temporizador
           search_time = (double)(end - start) / CLOCKS_PER_SEC;
           times[i] = search_time;  // Guarda el tiempo para el gráfico
           fprintf(stdout, "Tiempo de búsqueda Sequential Search por ID (base de datos de %d): %.4f segundos - IDs encontrados: %d/%d\n", sizes[i], search_time, found_count, num_ids);
       }

       // Genera gráfico con los resultados
       const char *plot_title = "Búsqueda Secuencial por ID";
       const char *plot_filename = "Sequential ID";
       plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename, 1);

       free(ids_to_search);
       fprintf(stdout, "\nBúsqueda Sequential Search por ID completada. Su gráfico quedó guardado en 'plots'.");
   }
   else if (search_option == 2)
   {
       // Opción 2: Búsqueda secuencial por nombre
       int num_names;
       fprintf(stdout, "Cuántos nombres deseas buscar: ");
       if (scanf("%d", &num_names) != 1)
       {
           fprintf(stderr, "\nERROR entrada no válida.\n\n");
           return;
       }

       char (*names_to_search)[50] = (char (*)[50])malloc(num_names * sizeof(char[50]));

       // Pide al usuario que ingrese los nombres a buscar
       fprintf(stdout, "\nIngresa los nombres de los productos a buscar:\n");
       for (int i = 0; i < num_names; i++)
       {
           fprintf(stdout, "Nombre #%d: ", i + 1);
           if (scanf("%s", names_to_search[i]) != 1)
           {
               fprintf(stderr, "\nERROR entrada no válida.\n\n");
               free(names_to_search);
               return;
           }
       }

       // Realiza búsquedas en cada inventario
       for (int i = 0; i < 5; i++)
       {
           int found_count = 0;
           start = clock();  // Inicia temporizador

           // Busca cada nombre y cuenta encontrados
           for (int j = 0; j < num_names; j++)
           {
               int result = sequential_search_by_name(dbs[i], names_to_search[j]);
               if (result != -1)
                   found_count++;
           }

           end = clock();  // Finaliza temporizador
           search_time = (double)(end - start) / CLOCKS_PER_SEC;
           times[i] = search_time;  // Guarda el tiempo para el gráfico
           fprintf(stdout, "Tiempo de búsqueda Sequential Search por nombre (base de datos de %d): %.4f segundos - Nombres encontrados: %d/%d\n", sizes[i], search_time, found_count, num_names);
       }

       // Genera gráfico con los resultados
       const char *plot_title = "Búsqueda Secuencial por Nombre";
       const char *plot_filename = "Sequential Name";
       plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename, 1);

       free(names_to_search);
       fprintf(stdout, "\nBúsqueda Sequential Search por nombre completada. Su gráfico quedó guardado en 'plots'.");
   }
   else if (search_option == 3)
   {
       // Opción 3: Búsqueda secuencial por rango de precios
       int num_ranges;
       fprintf(stdout, "Cuántos rangos de precios deseas buscar: ");
       if (scanf("%d", &num_ranges) != 1)
       {
           fprintf(stderr, "\nERROR entrada no válida.\n\n");
           return;
       }

       double (*price_ranges)[2] = (double (*)[2])malloc(num_ranges * sizeof(double[2]));

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

       // Realiza búsquedas en cada inventario
       for (int i = 0; i < 5; i++)
       {
           int total_found = 0;
           start = clock();  // Inicia temporizador

           // Busca en cada rango de precios
           for (int j = 0; j < num_ranges; j++)
           {
               Product *results_array[50];
               int found = sequential_search_by_price_range(dbs[i], price_ranges[j][0], price_ranges[j][1], results_array, 5);
               total_found += (found > 0) ? 1 : 0;  // Cuenta rangos con resultados
           }

           end = clock();  // Finaliza temporizador
           search_time = (double)(end - start) / CLOCKS_PER_SEC;
           times[i] = search_time;  // Guarda el tiempo para el gráfico

           fprintf(stdout, "\nTiempo de búsqueda Sequential Search por rango de precio (base de datos de %d): %.4f - Total rangos: %d\n\n", sizes[i], search_time, total_found);
       }

       // Genera gráfico con los resultados
       const char *plot_title = "Búsqueda Secuencial por Rangos de Precios";
       const char *plot_filename = "Sequential Price Range";
       plot_test_times(sizes, times, 5, plot_title, plot_route, plot_filename, 1);

       free(price_ranges);
       fprintf(stdout, "Búsqueda Sequential Search por rango de precios completada. Su gráfico quedó guardado en 'plots'.");
   }
   else
   {
       fprintf(stderr, "\nERROR opción inválida. Solo se permite 0, 1, 2 o 3.\n\n");
       return;
   }
}
