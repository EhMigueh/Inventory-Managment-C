#ifndef PRODUCT_H 
#define PRODUCT_H

// Definición de constantes para el tamaño máximo de nombre y categoría
#define MAX_NAME_LENGTH 10  // Longitud máxima para el nombre del producto
#define MAX_CATEGORY_LENGTH 10  // Longitud máxima para la categoría del producto

// Definición de la estructura Product
typedef struct {
    int id;  // Identificador único del producto
    char name[MAX_NAME_LENGTH];  // Nombre del producto, con longitud limitada a MAX_NAME_LENGTH
    char category[MAX_CATEGORY_LENGTH];  // Categoría del producto, con longitud limitada a MAX_CATEGORY_LENGTH
    double price;  // Precio del producto
    int stock;  // Cantidad en inventario (stock) del producto
} Product;  

#endif  