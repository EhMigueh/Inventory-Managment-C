#ifndef SEQUENTIAL_SEARCH_H
#define SEQUENTIAL_SEARCH_H
#include "inventory.h"

// Funciones de búsqueda secuencial
void handle_sequential_search(Inventory *, Inventory *, Inventory *, Inventory *, Inventory *);
int sequential_search_by_id(Inventory *, int);
int sequential_search_by_name(Inventory *, const char *);
int sequential_search_by_price_range(Inventory *, double, double, Product **, int);

#endif
