#include "inventory.h"

int main(void)
{
    Inventory *first_inv = create_inventory(FIRST_DB_SIZE);
    Inventory *second_inv = create_inventory(SECOND_DB_SIZE);
    Inventory *third_inv = create_inventory(THIRD_DB_SIZE);
    Inventory *fourth_inv = create_inventory(FOURTH_DB_SIZE);
    Inventory *fifth_inv = create_inventory(FIFTH_DB_SIZE);

    // Verifica si se crearon correctamente los inventarios.
    if (!first_inv || !second_inv || !third_inv || !fourth_inv || !fifth_inv)
    {
        fprintf(stderr, "\nERROR creando inventario.\n");
        return EXIT_FAILURE;
    }

    // Carga los inventarios desde los archivos CSV a una estructura.
    if (load_inventory_from_file(first_inv, "./db/database10.csv") < 0 || load_inventory_from_file(second_inv, "./db/database25.csv") < 0 || load_inventory_from_file(third_inv, "./db/database50.csv") < 0 || load_inventory_from_file(fourth_inv, "./db/database75.csv") < 0 || load_inventory_from_file(fifth_inv, "./db/database100.csv") < 0)
    {
        fprintf(stderr, "\nERROR cargando las bases de datos.\n");
        free_invs(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
        return EXIT_FAILURE;
    }

    fprintf(stdout, "\nPrimera base de datos cargada con %d productos.\n", first_inv->count);
    fprintf(stdout, "Segunda base de datos cargada con %d productos.\n", second_inv->count);
    fprintf(stdout, "Tercera base de datos cargada con %d productos.\n", third_inv->count);
    fprintf(stdout, "Cuarta base de datos cargada con %d productos.\n", fourth_inv->count);
    fprintf(stdout, "Quinta base de datos cargada con %d productos.\n\n", fifth_inv->count);

    int option;
    while (1)
    {
        fprintf(stdout, "Selecciona una opción:\n");
        fprintf(stdout, "1. Realizar pruebas de ordenamiento BUBBLE SORT.\n");
        fprintf(stdout, "2. Realizar pruebas de ordenamiento SELECTION SORT.\n");
        fprintf(stdout, "3. Realizar pruebas de ordenamiento INSERTION SORT.\n");
        fprintf(stdout, "4. Realizar pruebas de búsqueda SECUENCIAL.\n");
        fprintf(stdout, "5. Realizar pruebas de búsqueda BINARIA .\n");
        fprintf(stdout, "6. Realizar COMPARATIVA ORDENAMIENTO (en progreso).\n");
        fprintf(stdout, "7. Realizar COMPARATIVA BUSQUEDA (en progreso).\n");
        fprintf(stdout, "0. Salir.");

        fprintf(stdout, "\n\nSelecciona una opción: ");
        if (scanf("%d", &option) != 1)
        {
            fprintf(stderr, "\nERROR entrada no válida. Por favor, introduce un número.\n\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (option)
        {
        case 1:
            handle_bubble_sort(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            break;
        case 2:
            handle_selection_sort(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            break;
        case 3:
            handle_insertion_sort(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            break;
        case 4:
            handle_sequential_search(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            break;
        case 5:
            handle_binary_search(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            break;
        case 6:
            fprintf(stdout, "\nComparativa de ORDENAMIENTO (en progreso).\n\n");
            break;
        case 7:
            fprintf(stdout, "\nComparativa de BÚSQUEDA (en progreso).\n\n");
            break;
        case 0:
            fprintf(stdout, "\nSaliendo del programa...\n\n");
            free_invs(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            return EXIT_SUCCESS;
        default:
            fprintf(stderr, "\nOpción no válida. Por favor, selecciona una opción válida.\n\n");
            break;
        }
    }

    return EXIT_SUCCESS;
}
