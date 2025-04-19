#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include "inventory.h"
#include "stdbool.h"

// Gestiona diferentes tipos de búsqueda binaria sobre el inventario.
void handle_binary_search(Inventory *, Inventory *, Inventory *, Inventory *, Inventory *);

//  Busca un producto por su ID en el inventario.
int binary_search_by_id(Inventory *, int);

// Busca un producto por su nombre en el inventario.
int binary_search_by_name(Inventory *, const char *);

// Busca productos dentro de un rango de precios.
int binary_search_by_price_range(Inventory *, double, double, Product **, int);

//Encuentra el primer producto cuyo precio sea >= al mínimo.
int binary_search_lower_bound_price(Inventory *, double);

// b Encuentra el último producto cuyo precio sea <= al máximo.
int binary_search_upper_bound_price(Inventory *, double);

#endif
