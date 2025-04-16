#include "inventory.h"

void handle_inventory_metrics(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option;
    Inventory *inventories[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};

    clean_terminal();
    while (1)
    {
        print_menu_metrics();

        // Solicitar opción al usuario
        fprintf(stdout, "\nSelecciona una opción: ");
        if (scanf("%d", &search_option) != 1)
        {
            clean_terminal();
            fprintf(stderr, "\nERROR entrada no válida. Por favor, introduce un número.\n\n");
            while (getchar() != '\n')
                ; // Limpiar el buffer
            continue;
        }

        if (search_option == 0)
        {
            clean_terminal();
            fprintf(stdout, "Volviendo al menú anterior...\n\n");
            return;
        }

        if (search_option < 1 || search_option > 4)
        {
            clean_terminal();
            fprintf(stderr, "ERROR opción inválida. Solo se permite 1, 2, 3, 4 o 0 para salir.\n\n");
            continue;
        }

        clean_terminal();

        switch (search_option)
        {
        case 1:
            for (int i = 0; i < 5; i++)
            {
                printf("🔸 Inventario %d: Total de productos = %d\n", i + 1, get_total_products(inventories[i]));
            }
            break;

        case 2:
        {
            char formatted[50];
            for (int i = 0; i < 5; i++)
            {
                double total = get_total_inventory_value(inventories[i]);
                format_with_commas(total, formatted);
                printf("🔸 Inventario %d: $%s\n", i + 1, formatted);
            }
            break;
        }

        case 3:
            for (int i = 0; i < 5; i++)
            {
                printf("\n Inventario %d:\n", i + 1);
                printf("  ➤ Producto con MAYOR stock:\n");
                print_product_in_table(get_product_with_max_stock(inventories[i]));
                printf("  ➤ Producto con MENOR stock:\n");
                print_product_in_table(get_product_with_min_stock(inventories[i]));
            }
            break;

        case 4:
            for (int i = 0; i < 5; i++)
            {
                printf("\n Inventario %d:\n", i + 1);
                printf("  ➤ Producto MÁS CARO:\n");
                print_product_in_table(get_most_expensive_product(inventories[i]));
                printf("  ➤ Producto MÁS BARATO:\n");
                print_product_in_table(get_cheapest_product(inventories[i]));
            }
            break;

        default:
            fprintf(stderr, "ERROR opción no válida.\n");
            break;
        }
    }
}
