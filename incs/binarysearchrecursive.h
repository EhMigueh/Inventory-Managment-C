#ifndef SEARCH_UTILS_H
#define SEARCH_UTILS_H

#include "inventory.h"  

// Búsqueda binaria recursiva por ID
int binary_search_by_id_recursive(Inventory *, int id, int left, int right);

// Búsqueda binaria recursiva por nombre
int binary_search_by_name_recursive(Inventory *, const char *name, int left, int right);

// Búsqueda de productos por rango de precio
int binary_search_by_price_range_recursive(Inventory *, double min_price, double max_price, Product **results, int max_results);

// Encuentra el primer producto con precio >= min_price
int find_lower_bound_recursive(Inventory *, double min_price, int left, int right);

// Encuentra el último producto con precio <= max_price
int find_upper_bound_recursive(Inventory *, double max_price, int left, int right);

#endif  // SEARCH_UTILS_H
