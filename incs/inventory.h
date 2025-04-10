#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SMALL_DB_SIZE 50000
#define LARGE_DB_SIZE 100000
#define MAX_NAME_LENGTH 10
#define MAX_CATEGORY_LENGTH 10


// Estrucutra para representar los productos.
typedef struct
{
    int id;
    char name[MAX_NAME_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    double price;
    int stock;
} Product;

// Estructura para representar un inventario.
typedef struct
{
    Product *products; // Puntero a array de productos.
    int count;         // Productos almacenados en este momento.
    int capacity;      // Capacidad maxima de productos.
} Inventory;

// Manejo del inventario.
Inventory *create_inventory(int);
void free_inventory(Inventory *);
int load_inventory_from_file(Inventory *, const char *);

// Algoritmo BubbleSort por precio y stock.
void bubble_sort_by_price(Inventory *inventory);
void bubble_sort_by_stock(Inventory *inventory);

// Busqueda Secuencial
int sequential_search(Inventory *inv, int id);