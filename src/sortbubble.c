#include "inventory.h"
#include "sort.h"
// Ordena el inventario por precio.
void bubble_sort_by_price(Inventory *inv)
{
    int n = inv->count;
    while (n > 1)
    {
        int new_limit = 0;
        for (int j = 0; j < n - 1; j++)
        {
            if (inv->products[j].price > inv->products[j + 1].price)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
                new_limit = j + 1;
            }
        }
        n = new_limit;
    }
}

// Ordena el inventario por stock.
void bubble_sort_by_stock(Inventory *inv)
{
    int n = inv->count;
    while (n > 1)
    {
        int new_limit = 0;
        for (int j = 0; j < n - 1; j++)
        {
            if (inv->products[j].stock > inv->products[j + 1].stock)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
                new_limit = j + 1;
            }
        }
        n = new_limit;
    }
}

// Ordena el inventario por ID.
void bubble_sort_by_id(Inventory *inv)
{
    int n = inv->count;
    while (n > 1)
    {
        int new_limit = 0;
        for (int j = 0; j < n - 1; j++)
        {
            if (inv->products[j].id > inv->products[j + 1].id)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
                new_limit = j + 1;
            }
        }
        n = new_limit;
    }
}

// Ordena el inventario por nombre.
void bubble_sort_by_name(Inventory *inv)
{
    int n = inv->count;
    while (n > 1)
    {
        int new_limit = 0;
        for (int j = 0; j < n - 1; j++)
        {
            if (strcmp(inv->products[j].name, inv->products[j + 1].name) > 0)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
                new_limit = j + 1;
            }
        }
        n = new_limit;
    }
}
