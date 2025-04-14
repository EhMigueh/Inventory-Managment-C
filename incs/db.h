#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FIRST_DB_SIZE 10000
#define SECOND_DB_SIZE 25000
#define THIRD_DB_SIZE 50000
#define FOURTH_DB_SIZE 75000
#define FIFTH_DB_SIZE 100000
#define MAX_NAME_LENGTH 10
#define MAX_CATEGORY_LENGTH 10

void generate_csv(const char *, int);
void shuffle_array(int *, int);
void generate_unique_data(char data[][MAX_NAME_LENGTH], int);
void generate_unique_string(char *, int);
int is_duplicate(char array[][MAX_NAME_LENGTH], int, char *);
double random_price(double, double);
int random_stock(int, int);