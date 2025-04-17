#ifndef DB_H
#define DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define FIRST_DB_SIZE 10000        // Tamaño de base de datos 1
#define SECOND_DB_SIZE 25000       // Tamaño de base de datos 2
#define THIRD_DB_SIZE 50000        // Tamaño de base de datos 3
#define FOURTH_DB_SIZE 75000       // Tamaño de base de datos 4
#define FIFTH_DB_SIZE 100000       // Tamaño de base de datos 5
#define MAX_NAME_LENGTH 10         // Longitud máxima de los nombres
#define MAX_CATEGORY_LENGTH 10     // Longitud máxima de las categorías

// Prototipos de funciones
void generate_csv(const char *filename, int total_products);       // Genera el archivo CSV con productos aleatorios
void shuffle_array(int *array, int size);                          // Mezcla un arreglo de enteros (IDs)
void generate_unique_data(char data[][MAX_NAME_LENGTH], int total); // Genera datos únicos (nombres o categorías)
void generate_unique_string(char *str, int length);                // Genera una cadena aleatoria
int is_duplicate(char array[][MAX_NAME_LENGTH], int total, char *str); // Verifica si una cadena ya existe en un array
double random_price(double min_price, double max_price);           // Devuelve un precio aleatorio
int random_stock(int min_stock, int max_stock);                    // Devuelve un stock aleatorio

#endif