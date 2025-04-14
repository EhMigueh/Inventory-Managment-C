#include "db.h"

// Generador de datos aleatorios para la base de datos
void generate_csv(const char *filename, int size)
{
    // Se crea la base de datos, en caso de no poder abrir el archivo -> ERROR.
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "ERROR al abrir el archivo %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char names[size][MAX_NAME_LENGTH];
    char categories[size][MAX_CATEGORY_LENGTH];
    int ids[size];

    // Llenar y mezclar IDs
    for (int i = 0; i < size; i++)
        ids[i] = i + 1;

    shuffle_array(ids, size);
    generate_unique_data(names, size);
    generate_unique_data(categories, size);

    fprintf(file, "ID,Nombre,Categoria,Precio,Stock\n");

    // Se generan los datos aleatorios para cada producto (stock y precio) coloca esos datos en la base de datos.
    for (int i = 0; i < size; i++)
    {
        double price = random_price(2.99, 2000.00);
        int stock = random_stock(0, 1000);
        fprintf(file, "%d,%s,%s,%.2f,%d\n", ids[i], names[i], categories[i], price, stock);
    }

    fclose(file);
}

// Mezcla las IDs de los productos para que no estén en orden utilizando el algoritmo Fisher-Yates.
void shuffle_array(int *array, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// Generador de cadenas únicas (verifica que no se repitan).
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

// Generador de cadenas aleatorias (nombres y categorias).
void generate_unique_string(char *str, int length)
{
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    for (int i = 0; i < length - 1; i++)
        str[i] = charset[rand() % (sizeof(charset) - 1)];

    str[length - 1] = '\0';
}

// Verifica si la cadena ya existe en el array.
int is_duplicate(char array[][MAX_NAME_LENGTH], int size, char *value)
{
    for (int i = 0; i < size; i++)
        if (strcmp(array[i], value) == 0)
            return 1;

    return 0;
}

// Generador de precios aleatorios.
double random_price(double min, double max)
{
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

// Generador de stock aleatorio.
int random_stock(int min, int max)
{
    return min + rand() % (max - min + 1);
}
