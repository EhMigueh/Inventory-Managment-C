#ifndef CREATEDB_H
#define CREATEDB_H

// generar archivo CSV con datos aleatorios
void generate_csv(const char *filename, int size);

// Funciones auxiliares
void generate_unique_data(char data[][MAX_NAME_LENGTH], int count);
void generate_unique_string(char *str, int length);
int is_duplicate(char array[][MAX_NAME_LENGTH], int size, char *value);
double random_price(double min, double max);
int random_stock(int min, int max);

#endif 