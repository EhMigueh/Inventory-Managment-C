#ifndef SORT_H
#define SORT_H
#include <string.h>
#include "stdbool.h"
#include "bubblesort.h"
#include "insertionsort.h"
#include "selectionsort.h"
#include "comparativesort.h"

// Funciones para manejar diferentes tipos de ordenamientos
void handle_bubble_sort(Inventory *, Inventory *, Inventory *, Inventory *, Inventory *);
void handle_insertion_sort(Inventory *, Inventory *, Inventory *, Inventory *, Inventory *);
void handle_selection_sort(Inventory *, Inventory *, Inventory *, Inventory *, Inventory *);

#endif
