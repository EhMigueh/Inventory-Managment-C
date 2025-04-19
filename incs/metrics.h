#ifndef METRICS_H
#define METRICS_H

#include <string.h>
#include <time.h>
#include "inventory.h"
typedef struct
{
    char category[50];
    int product_count;
    double total_price;
    double average_price;
} CategoryStats;

// Funciones para manejar métricas de inventario
void handle_inventory_metrics(Inventory *, Inventory *, Inventory *, Inventory *, Inventory *);
void print_stats(Inventory *, int);

// Obtiene el producto con el mayor stock en el inventario
Product *get_product_with_max_stock(Inventory *inventory);

// Obtiene el producto con el menor stock en el inventario
Product *get_product_with_min_stock(Inventory *inventory);

// Obtiene el producto más caro en el inventario
Product *get_most_expensive_product(Inventory *inventory);

// Obtiene el producto más barato en el inventario
Product *get_cheapest_product(Inventory *inventory);

// Auxiliares
int get_unique_categories(Inventory *inv, CategoryStats *stats, int max_categories);

// Obtiene el número total de productos en el inventario
int get_total_products(Inventory *inventory);

// Obtiene el valor total del inventario (suma de los precios de todos los productos)
double get_total_inventory_value(Inventory *inventory);

#endif
