#include "inventory.h"
#include "search.h"
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
int sequential_search_by_price_range(Inventory *inventory, double min_price, double max_price, Product **results, int max_results) {
    int count = 0;

    for (int i = 0; i < inventory->count; i++) {
        if (inventory->products[i].price >= min_price && inventory->products[i].price <= max_price) {
            if (count < max_results) {
                results[count] = &inventory->products[i];
            }
            count++;
        }
    }
    
    return (count < max_results) ? count : max_results;
}