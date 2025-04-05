#include "db.h"

void generate_csv(const char *, int);
void generate_unique_data(char data[][MAX_NAME_LENGTH], int);
void generate_unique_string(char *, int);
int is_duplicate(char array[][MAX_NAME_LENGTH], int size, char *value);
double random_price(double min, double max);
int random_stock(int min, int max);

int main(void)
{
    srand((unsigned int)time(NULL));

    fprintf(stdout, "\nBienvenido a la creación ALEATORIA de BASE DE DATOS.\n");
    fprintf(stdout, "CREADO Bases de Datos...\n");

    generate_csv("small_database.csv", SMALL_DB_SIZE);
    generate_csv("large_database.csv", LARGE_DB_SIZE);

    fprintf(stdout, "\nBases de Datos creadas con ÉXITO.\n\n");

    return EXIT_SUCCESS;
}

void generate_csv(const char *filename, int size)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "ERROR al abrir el archivo %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char names[size][MAX_NAME_LENGTH];
    char categories[size][MAX_CATEGORY_LENGTH];

    generate_unique_data(names, size);
    generate_unique_data(categories, size);

    fprintf(file, "ID,Nombre,Categoria,Precio,Stock\n");

    for (int i = 0; i < size; i++)
    {
        double price = random_price(2.99, 2000.00);
        int stock = random_stock(0, 50);
        fprintf(file, "%d,%s,%s,%.2f,%d\n", i + 1, names[i], categories[i], price, stock);
    }

    fclose(file);
}

void generate_unique_data(char data[][MAX_NAME_LENGTH], int count)
{
    char buffer[MAX_NAME_LENGTH];

    for (int i = 0; i < count;)
    {
        generate_unique_string(buffer, MAX_NAME_LENGTH - 1);
        if (!is_duplicate(data, i, buffer))
        {
            strncpy(data[i], buffer, MAX_NAME_LENGTH);
            data[i][MAX_NAME_LENGTH - 1] = '\0';
            i++;
        }
    }
}

void generate_unique_string(char *str, int length)
{
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    for (int i = 0; i < length - 1; i++)
        str[i] = charset[rand() % (sizeof(charset) - 1)];

    str[length - 1] = '\0';
}

int is_duplicate(char array[][MAX_NAME_LENGTH], int size, char *value)
{
    for (int i = 0; i < size; i++)
        if (strcmp(array[i], value) == 0)
            return 1;

    return 0;
}

double random_price(double min, double max)
{
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

int random_stock(int min, int max)
{
    return min + rand() % (max - min + 1);
}