#include "inventory.h"
#include "search.h"

// Búsqueda secuencial por ID
int sequential_search_by_id(Inventory *inv, int id)
{
    // Comprobación de casos  base
    if (inv->count <= 0) return -1;
    
    // Procesamiento por bloques (desenrollado de bucle)
    int i = 0;
    for (; i < inv->count - 3; i += 4) {
        if (inv->products[i].id == id) return i;
        if (inv->products[i+1].id == id) return i+1;
        if (inv->products[i+2].id == id) return i+2;
        if (inv->products[i+3].id == id) return i+3;
    }
    
    // Procesar elementos restantes
    for (; i < inv->count; i++) {
        if (inv->products[i].id == id) return i;
    }
    
    return -1;
}


// Búsqueda secuencial por nombre optimizada
int sequential_search_by_name(Inventory *inv, const char *name) {
    if (inv == NULL || inv->count <= 0 || name == NULL) 
        return -1;
    
    size_t name_len = strlen(name);
    
    // Optimización: primero comparamos longitud y primer caracter
    for (int i = 0; i < inv->count; i++) {
        if (strlen(inv->products[i].name) == name_len && 
            inv->products[i].name[0] == name[0]) {
            // Si coinciden, hacemos la comparación completa
            if (strcmp(inv->products[i].name, name) == 0)
                return i;
        }
    }
    
    return -1;
}

// Búsqueda secuencial por rango de precio optimizada

int sequential_search_by_price_range(Inventory *inventory, double min_price,
                                     double max_price, Product **results,
                                     int max_results) {
    if (inventory == NULL || inventory->count <= 0 || results == NULL || max_results <= 0)
        return 0;

    int found = 0;

    // Recorremos el inventario buscando productos en el rango de precios
    for (int i = 0; i < inventory->count && found < max_results; i++) {
        double price = inventory->products[i].price;
        if (price >= min_price && price <= max_price) {
            results[found++] = &inventory->products[i];
        }
    }

    return found; // Devuelve cuántos productos se encontraron
}
