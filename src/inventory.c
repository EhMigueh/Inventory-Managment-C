#include "inventory.h"

// Creación de un inventario con capacidad especificada.
Inventory *create_inventory(int capacity)
{
    // Asigna y verifica si se puede asignar memoria al inventario.
    Inventory *inv = malloc(sizeof(Inventory));
    if (!inv)
    {
        fprintf(stderr, "ERROR No se pudo asignar memoria para el inventario.\n");
        return NULL;
    }

    // Asigna y verifica si se puede asignar memoria para los productos.
    inv->products = malloc(capacity * sizeof(Product));
    if (!inv->products)
    {
        fprintf(stderr, "ERROR No se pudo asignar memoria para los productos.\n");
        free(inv);
        return NULL;
    }

    inv->count = 0;
    inv->capacity = capacity;

    return inv;
}

// Liberar memoria del inventario.
void free_inventory(Inventory *inv)
{
    if (inv)
    {
        free(inv->products);
        free(inv);
    }
}

// Carga de inventario desde un archivo CSV.
int load_inventory_from_file(Inventory *inv, const char *filename)
{
    // Verifica si el inventario y el nombre del archivo son válidos.
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "ERROR no se pudo abrir el archivo %s.\n", filename);
        return -1;
    }

    char buffer[256];

    if (!fgets(buffer, sizeof(buffer), file))
    {
        fprintf(stderr, "ERROR no se pudo leer el encabezado del archivo %s.\n", filename);
        fclose(file);
        return -1;
    }

    int count = 0;

    // Lee el archivo línea por línea y almacena los productos en el inventario.
    while (count < inv->capacity && fgets(buffer, sizeof(buffer), file))
    {
        if (sscanf(buffer, "%d,%49[^,],%29[^,],%lf,%d",
                   &inv->products[count].id,
                   inv->products[count].name,
                   inv->products[count].category,
                   &inv->products[count].price,
                   &inv->products[count].stock) == 5)
        {
            count++;
        }
    }

    inv->count = count;
    fclose(file);

    return count;
}

// Ordena el inventario por precio usando el algoritmo BubbleSort.
void bubble_sort_by_price(Inventory *inv)
{
    for (int i = 0; i < inv->count - 1; i++)
    {
        for (int j = 0; j < inv->count - i - 1; j++)
        {
            if (inv->products[j].price > inv->products[j + 1].price)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
            }
        }
    }
}

// Ordena el inventario por stock usando el algoritmo BubbleSort.
void bubble_sort_by_stock(Inventory *inv)
{
    for (int i = 0; i < inv->count - 1; i++)
    {
        for (int j = 0; j < inv->count - i - 1; j++)
        {
            if (inv->products[j].stock > inv->products[j + 1].stock)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
            }
        }
    }
}