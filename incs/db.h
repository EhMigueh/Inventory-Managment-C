#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SMALL_DB_SIZE 50000
#define LARGE_DB_SIZE 100000
#define MAX_NAME_LENGTH 10
#define MAX_CATEGORY_LENGTH 10
#define search_option 1



void generate_csv(const char *, int);
void generate_unique_data(char data[][MAX_NAME_LENGTH], int);
void generate_unique_string(char *, int);
int is_duplicate(char array[][MAX_NAME_LENGTH], int, char *);
double random_price(double, double);
int random_stock(int, int);