#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include "inventory.h"

// Ordena el inventario por precio (ascendente)..
void bubble_sort_by_price(Inventory *);

// Ordena el inventario por stock (ascendente).
void bubble_sort_by_stock(Inventory *);

// Ordena el inventario por nombre (A-Z).
void bubble_sort_by_name(Inventory *);

// Ordena el inventario por ID (ascendente).
void bubble_sort_by_id(Inventory *);

#endif // BUBBLE_SORT_H
