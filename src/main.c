#include "db.h"
#include "createdb.h"
#include "inventory.h"
int main(void)
{
    srand((unsigned int)time(NULL));

    fprintf(stdout, "CREADO Bases de Datos...\n");
    generate_csv("small_database.csv", SMALL_DB_SIZE);
    generate_csv("large_database.csv", LARGE_DB_SIZE);

    // SOLO POR MOTIVO DE TEST 

    Inventory *inventory = create_inventory(LARGE_DB_SIZE);
    if (!inventory) {
        fprintf(stderr, "Error creando inventario\n");
        return EXIT_FAILURE;
    }
     // Cargar datos
     printf("Cargando datos...\n");
     int loaded = load_inventory_from_file(inventory, "large_database.csv");
     if (loaded < 0) {
         fprintf(stderr, "Error cargando datos\n");
         free_inventory(inventory);
         return EXIT_FAILURE;
     }
     printf("Se cargaron %d productos\n", loaded);
     
 
     // Mostrar muestra de los datos originales
     print_inventory_sample(inventory, 5);


    return EXIT_SUCCESS;
}