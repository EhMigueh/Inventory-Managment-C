#ifndef SEARCH_UTILS_H
#define SEARCH_UTILS_H
#include "inventory.h"

// Funciones auxiliares para búsquedas recursivas
int binary_search_by_id_recursive(Inventory *, int, int, int);
int binary_search_by_name_recursive(Inventory *, const char *, int, int);
int binary_search_by_price_range_recursive(Inventory *, double, double, Product **, int);
int find_lower_bound_recursive(Inventory *, double, int, int);
int find_upper_bound_recursive(Inventory *, double, int, int);

#endif
