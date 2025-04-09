#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SMALL_DB_SIZE 1000
#define LARGE_DB_SIZE 10000
#define MAX_NAME_LENGTH 10
#define MAX_CATEGORY_LENGTH 10

void generate_csv(const char *filename, int size);
void generate_unique_data(char data[][MAX_NAME_LENGTH], int count);
void generate_unique_string(char *str, int length);
int is_duplicate(char array[][MAX_NAME_LENGTH], int size, char *value);
double random_price(double min, double max);
int random_stock(int min, int max);