#ifndef INVENTORY_H
#define INVENTORY_H

#include "product.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    Product *products;  // Puntero a un arreglo de productos
    int count;          // Número actual de productos en el inventario
    int capacity;       // Capacidad máxima del inventario
} Inventory;

// Funciones relacionadas con la creación y liberación de inventarios

// Crea un inventario con la capacidad especificada (se asigna memoria para el arreglo de productos)
Inventory *create_inventory(int capacity);

// Libera la memoria ocupada por el inventario
void free_inventory(Inventory *inventory);

// Libera la memoria de cinco inventarios diferentes
void free_invs(Inventory *inv1, Inventory *inv2, Inventory *inv3, Inventory *inv4, Inventory *inv5);

// Carga los productos desde un archivo CSV en un inventario
int load_inventory_from_file(Inventory *inventory, const char *filename);

// Carga los productos en cinco inventarios diferentes desde archivos
void load_all_inventories(Inventory *inv1, Inventory *inv2, Inventory *inv3, Inventory *inv4, Inventory *inv5);

// Obtiene el número total de productos en el inventario
int get_total_products(Inventory *inventory);

// Obtiene el valor total del inventario (suma de los precios de todos los productos)
double get_total_inventory_value(Inventory *inventory);

// Obtiene el producto con el mayor stock en el inventario
Product *get_product_with_max_stock(Inventory *inventory);

// Obtiene el producto con el menor stock en el inventario
Product *get_product_with_min_stock(Inventory *inventory);

// Obtiene el producto más caro en el inventario
Product *get_most_expensive_product(Inventory *inventory);

// Obtiene el producto más barato en el inventario
Product *get_cheapest_product(Inventory *inventory);

#endif  