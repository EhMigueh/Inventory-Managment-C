#include "inventory.h"

// Ordena el inventario por precio.
void bubble_sort_by_price(Inventory *inv)
{
    int n = inv->count;
    int swapped;
    int new_limit;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        new_limit = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (inv->products[j].price > inv->products[j + 1].price)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
                swapped = 1;
                new_limit = j;
            }
        }

        // Si no hay cambios el arreglo ya está ordenado.
        if (swapped == 0)
            break;

        n = new_limit + 1;
    }
}

// Ordena el inventario por stock.
void bubble_sort_by_stock(Inventory *inv)
{
    int n = inv->count;
    int swapped;
    int new_limit;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        new_limit = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (inv->products[j].stock > inv->products[j + 1].stock)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
                swapped = 1;
                new_limit = j;
            }
        }

        // Si no hay cambios el arreglo ya está ordenado.
        if (swapped == 0)
            break;

        n = new_limit + 1;
    }
}

// Ordena el inventario por ID.
void bubble_sort_by_id(Inventory *inv)
{
    int n = inv->count;
    int swapped;
    int new_limit;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        new_limit = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (inv->products[j].id > inv->products[j + 1].id)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
                swapped = 1;
                new_limit = j;
            }
        }

        // Si no hay cambios el arreglo ya está ordenado.
        if (swapped == 0)
            break;

        n = new_limit + 1;
    }
}

// Ordena el inventario por nombre con optimizacion.
void bubble_sort_by_name(Inventory *inv)
{
    int n = inv->count;
    int swapped;
    int new_limit;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        new_limit = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(inv->products[j].name, inv->products[j + 1].name) > 0)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
                swapped = 1;
                new_limit = j;
            }
        }

        // Si no hay cambios el arreglo ya está ordenado.
        if (swapped == 0)
            break;

        n = new_limit + 1;
    }
}
