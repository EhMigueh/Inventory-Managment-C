#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gnuplot_i.h"

#define FIRST_DB_SIZE 10000
#define SECOND_DB_SIZE 25000
#define THIRD_DB_SIZE 50000
#define FOURTH_DB_SIZE 75000
#define FIFTH_DB_SIZE 100000
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

// Funciones para graficar.
void plot_sort_times(int *, double *, int, const char *, const char *);
void plot_search_times(int *, double *, int, const char *, const char *);

// Algoritmo BubbleSort.
void handle_bubble_sort(Inventory *, Inventory *, Inventory *, Inventory *, Inventory *);
void bubble_sort_by_price(Inventory *);
void bubble_sort_by_stock(Inventory *);
void bubble_sort_by_name(Inventory *);
void bubble_sort_by_id(Inventory *);

// Algoritmo Busqueda Secuencial
void handle_sequential_search(Inventory *, Inventory *, Inventory *, Inventory *, Inventory *);
int sequential_search_by_id(Inventory *, int);
int sequential_search_by_name(Inventory *, const char *);
int sequential_search_by_price_range(Inventory *, double, double, Product **, int);

// Algoritmo Busqueda Binaria
void handle_binary_search(Inventory *, Inventory *, Inventory *, Inventory *, Inventory *);
int binary_search_by_id(Inventory *, int);
int binary_search_by_name(Inventory *, const char *);

// Algoritmo Busqueda Binaria Optimizada (Recursiva)
int binary_search_by_id_recursive(Inventory *, int, int, int);
int binary_search_by_name_recursive(Inventory *, const char *, int, int);