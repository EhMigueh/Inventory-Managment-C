#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include "inventory.h"
#include "stdbool.h"
// Funciones de ordenación por selección
void selection_sort_by_price(Inventory *);
void selection_sort_by_stock(Inventory *);
void selection_sort_by_name(Inventory *);
void selection_sort_by_id(Inventory *);

#endif
