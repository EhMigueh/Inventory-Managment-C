#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SMALL_DB_SIZE 1000
#define LARGE_DB_SIZE 10000
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

// Estructura para inventario.
typedef struct
{
    Product *products; // Puntero a array de productos.
    int count;         // Productos almacenados en este momento.
    int capacity;      // Capacidad maxima de productos.
} Inventory;

// Manejo del inventario.
Inventory *create_inventory(int capacity);
void free_inventory(Inventory *inventory);
int load_inventory_from_file(Inventory *inventory, const char *filename);
int save_inventory_to_file(Inventory *inventory, const char *filename);
void print_inventory_sample(Inventory *inventory, int sample_size);
void print_product(Product *product);