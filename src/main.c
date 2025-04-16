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

    load_all_inventories(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);

    fprintf(stdout, "\nPrimera base de datos cargada con %d productos.\n", first_inv->count);
    fprintf(stdout, "Segunda base de datos cargada con %d productos.\n", second_inv->count);
    fprintf(stdout, "Tercera base de datos cargada con %d productos.\n", third_inv->count);
    fprintf(stdout, "Cuarta base de datos cargada con %d productos.\n", fourth_inv->count);
    fprintf(stdout, "Quinta base de datos cargada con %d productos.\n", fifth_inv->count);

    int option;
    while (1)
    {
        print_menu();

        // Solicita al usuario una opción para realizar una acción, en caso de no ser válida, se atrapa.
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
            load_all_inventories(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            break;
        case 2:
            handle_selection_sort(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            load_all_inventories(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            break;
        case 3:
            handle_insertion_sort(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            load_all_inventories(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            break;
        case 4:
            handle_sequential_search(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            load_all_inventories(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            break;
        case 5:
            handle_binary_search(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            load_all_inventories(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            break;
        case 6:
            handle_comparative_sort(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            break;
        case 7:
            handle_comparative_search(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            fprintf(stdout, "\nComparativa de BÚSQUEDA (en progreso).\n\n");
            break;
        case 8:
            handle_inventory_metrics(first_inv, second_inv, third_inv, fourth_inv, fifth_inv);
            fprintf(stdout, "\nMétricas del inventario (en progreso).\n\n");
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
