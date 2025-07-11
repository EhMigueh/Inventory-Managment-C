#include "inventory.h"

// Creación de un inventario con capacidad especificada.
Inventory *create_inventory(int capacity)
{
    // Asigna y verifica si se puede asignar memoria al inventario.
    Inventory *inv = malloc(sizeof(Inventory));
    if (!inv)
    {
        fprintf(stderr, "\nERROR No se pudo asignar memoria para el inventario.\n");
        return NULL;
    }

    // Asigna y verifica si se puede asignar memoria para los productos.
    inv->products = malloc(capacity * sizeof(Product));
    if (!inv->products)
    {
        fprintf(stderr, "\nERROR No se pudo asignar memoria para los productos.\n");
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

// Liberar memoria de varios inventarios.
void free_invs(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    free_inventory(first_inv);
    free_inventory(second_inv);
    free_inventory(third_inv);
    free_inventory(fourth_inv);
    free_inventory(fifth_inv);
}

// Carga de inventario desde un archivo CSV.
int load_inventory_from_file(Inventory *inv, const char *filename)
{
    // Verifica si el inventario y el nombre del archivo son válidos.
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "\nERROR no se pudo abrir el archivo %s.\n", filename);
        return -1;
    }

    // Verifica si el inventario tiene capacidad.
    char buffer[256];
    if (!fgets(buffer, sizeof(buffer), file))
    {
        fprintf(stderr, "\nERROR no se pudo leer el encabezado del archivo %s.\n", filename);
        fclose(file);
        return -1;
    }

    int count = 0;

    // Lee el archivo línea por línea y almacena los productos en el inventario.
    while (count < inv->capacity && fgets(buffer, sizeof(buffer), file))
        if (sscanf(buffer, "%d,%49[^,],%29[^,],%lf,%d", &inv->products[count].id, inv->products[count].name, inv->products[count].category, &inv->products[count].price, &inv->products[count].stock) == 5)
            count++;

    inv->count = count;
    fclose(file);

    return count;
}

// Carga de todos los inventarios desde archivos CSV y verifica si se cargaron correctamente.
void load_all_inventories(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    if (load_inventory_from_file(first_inv, "./db/database10.csv") < 0 || load_inventory_from_file(second_inv, "./db/database25.csv") < 0 || load_inventory_from_file(third_inv, "./db/database50.csv") < 0 || load_inventory_from_file(fourth_inv, "./db/database75.csv") < 0 || load_inventory_from_file(fifth_inv, "./db/database100.csv") < 0)
    {
        fprintf(stderr, "\nERROR cargando las bases de datos.\n");
        free_invs(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
        exit(EXIT_FAILURE);
    }
}
