#include "inventory.h"

// Búsqueda secuencial por ID
int sequential_search_by_id(Inventory *inv, int id)
{
    for (int i = 0; i < inv->count; i++)
        if (inv->products[i].id == id)
            return i;

    return -1;
}
// busqueda secuencial por nombre.
int sequential_search_by_name(Inventory *inv, const char *name)
{
    for (int i = 0; i < inv->count; i++)
        if (strcmp(inv->products[i].name, name) == 0)
            return i;

    return -1;
}

// Busqueda secuencial por rango de precio
int sequential_search_by_price_range(Inventory *inventory, double min_price, double max_price, Product **results, int max_results)
{
    int count = 0;

    // Número de iteraciones para tener mediciones más precisas
    const int NUM_ITERATIONS = 1000;
    struct timespec start, end;
    double total_time = 0.0;

    // Forzar recorrido completo del inventario siempre
    int found_items = 0;

    for (int i = 0; i < inventory->count; i++)
        if (inventory->products[i].price >= min_price && inventory->products[i].price <= max_price)
            found_items++;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int iter = 0; iter < NUM_ITERATIONS; iter++)
    {
        count = 0;

        for (int i = 0; i < inventory->count; i++)
            if (inventory->products[i].price >= min_price && inventory->products[i].price <= max_price)
            {

                if (count < max_results && iter == NUM_ITERATIONS - 1)
                    results[count] = &inventory->products[i];
                count++;
            }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    total_time = ((end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec)) / 1e9;
    double avg_time = total_time / NUM_ITERATIONS;

    printf("Tiempo promedio: %.9f segundos\n", avg_time);
    printf("Total elementos encontrados: %d (mostrando máximo %d)\n", count, max_results);

    return (count < max_results) ? count : max_results;
}