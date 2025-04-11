#include "inventory.h"

void handle_bubble_sort(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option;
    clock_t start, end;
    double time;

    fprintf(stdout, "\nSelecciona el tipo de ordenamiento:\n");
    fprintf(stdout, "1. Ordenar por precio.\n");
    fprintf(stdout, "2. Ordenar por stock.\n");
    fprintf(stdout, "0. Volver al menú principal.\n");
    fprintf(stdout, "\nSelecciona una opción: ");

    if (scanf("%d", &search_option) != 1)
    {
        fprintf(stderr, "ERROR entrada no válida. Por favor, introduce un número.\n");
        while (getchar() != '\n')
            ;
        return;
    }

    if (search_option == 0)
    {
        fprintf(stdout, "\nVolviendo al menú principal...\n\n");
        return;
    }

    if (search_option == 1)
    {
        Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
        int sizes[] = {10000, 25000, 50000, 75000, 100000};
        for (int i = 0; i < 5; i++)
        {
            start = clock();
            bubble_sort_by_price(dbs[i]);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(stdout, "Tiempo de ordenamiento por precio (base de datos de %d objetos): %.4f segundos.\n", sizes[i], time);
        }
        fprintf(stdout, "\nOrdenamiento por precio completado.\n\n");
    }
    else if (search_option == 2)
    {
        Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
        int sizes[] = {10000, 25000, 50000, 75000, 100000};
        for (int i = 0; i < 5; i++)
        {
            start = clock();
            bubble_sort_by_stock(dbs[i]);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(stdout, "Tiempo de ordenamiento por stock (base de datos de %d objetos): %.4f segundos.\n", sizes[i], time);
        }
        fprintf(stdout, "\nOrdenamiento por stock completado.\n\n");
    }
    else
    {
        fprintf(stderr, "\nERROR opción inválida. Solo se permite 0, 1 o 2.\n\n");
        return;
    }
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