#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include "product.h"

// Limpia la pantalla del terminal.
void clean_terminal();

// Imprime el menú principal.
void print_menu();

// Imprime el menú para opciones de ordenamiento.
void print_menu_sort();

// Imprime el menú para opciones de búsqueda.
void print_menu_search();

// Imprime el menú para mostrar métricas.
void print_menu_metrics();

// Imprime los detalles de un producto en formato de tabla.
void print_product_in_table(Product *);

// Formatea un número con comas para mejorar su legibilidad.
void format_with_commas(double, char *);

#endif
