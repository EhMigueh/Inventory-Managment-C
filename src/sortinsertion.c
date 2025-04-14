#include "inventory.h"

// Ordena el inventario por precio.
void insertion_sort_by_price(Inventory *inv)
{
    int n = inv->count;

    for (int i = 1; i < n; i++)
    {
        Product key = inv->products[i];

        // Evita mover elementos si ya están en orden.
        if (inv->products[i - 1].price <= key.price)
            continue;

        int j = i - 1;

        // Desplaza los elementos mayores al producto actual hacia la derecha.
        while (j >= 0 && inv->products[j].price > key.price)
        {
            inv->products[j + 1] = inv->products[j];
            j--;
        }

        inv->products[j + 1] = key;
    }
}

// Ordena el inventario por stock.
void insertion_sort_by_stock(Inventory *inv)
{
    int n = inv->count;

    for (int i = 1; i < n; i++)
    {
        Product key = inv->products[i];

        // Evita mover elementos si ya están en orden.
        if (inv->products[i - 1].stock <= key.stock)
            continue;

        int j = i - 1;

        // Desplaza los elementos mayores al producto actual hacia la derecha.
        while (j >= 0 && inv->products[j].stock > key.stock)
        {
            inv->products[j + 1] = inv->products[j];
            j--;
        }

        inv->products[j + 1] = key;
    }
}

// Ordena el inventario por ID.
void insertion_sort_by_id(Inventory *inv)
{
    int n = inv->count;

    for (int i = 1; i < n; i++)
    {
        Product key = inv->products[i];

        // Evita mover elementos si ya están en orden.
        if (inv->products[i - 1].id <= key.id)
            continue;

        int j = i - 1;

        // Desplaza los elementos mayores al producto actual hacia la derecha.
        while (j >= 0 && inv->products[j].id > key.id)
        {
            inv->products[j + 1] = inv->products[j];
            j--;
        }

        inv->products[j + 1] = key;
    }
}

// Ordena el inventario por nombre.
void insertion_sort_by_name(Inventory *inv)
{
    int n = inv->count;

    for (int i = 1; i < n; i++)
    {
        Product key = inv->products[i];

        // Evita mover elementos si ya están en orden.
        if (strcmp(inv->products[i - 1].name, key.name) <= 0)
            continue;

        int j = i - 1;

        // Desplaza los elementos mayores al producto actual hacia la derecha.
        while (j >= 0 && strcmp(inv->products[j].name, key.name) > 0)
        {
            inv->products[j + 1] = inv->products[j];
            j--;
        }

        inv->products[j + 1] = key;
    }
}