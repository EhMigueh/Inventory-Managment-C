#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "inventory.h"

// Funciones de ordenación por inserción
void insertion_sort_by_price(Inventory *);   // Ordena los productos por precio de menor a mayor
void insertion_sort_by_stock(Inventory *);   // Ordena los productos por cantidad en stock de menor a mayor
void insertion_sort_by_name(Inventory *);    // Ordena los productos alfabéticamente por nombre
void insertion_sort_by_id(Inventory *);      // Ordena los productos por ID de menor a mayor

#endif