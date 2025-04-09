#include "inventory.h"

int main(void)
{
    Inventory *inventory = create_inventory(LARGE_DB_SIZE);
    if (!inventory)
    {
        fprintf(stderr, "Error creando inventario\n");
        return EXIT_FAILURE;
    }

    // Cargar datos de la base de datos grande para testear.
    fprintf(stdout, "Cargando datos...\n");

    int loaded = load_inventory_from_file(inventory, "./db/large_database.csv");

    if (loaded < 0)
    {
        fprintf(stderr, "ERROR cargando datos\n");
        free_inventory(inventory);
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Se cargaron %d productos\n", loaded);

    // Mostrar muestra de los datos originales.
    print_inventory_sample(inventory, 5);

    return EXIT_SUCCESS;
}