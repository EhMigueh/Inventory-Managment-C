#include "inventory.h"

// Ordena el inventario por precio.
void insertion_sort_by_price(Inventory *inv)
{
    int n = inv->count;

    for (int i = 1; i < n; i++)
    {
        Product *current = &inv->products[i];
        float current_price = current->price;

        // Si el elemnto ya está en su lugar, no se hace nada.
        if (inv->products[i - 1].price <= current_price)
            continue;

        // Copia el producto actual.
        Product key = *current;
        int j = i - 1;

        // Desplaza los elementos mayores al producto actual hacia la derecha.
        while (j >= 0 && inv->products[j].price > current_price)
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
        Product *current = &inv->products[i];
        int current_stock = current->stock;

        // Si el elemnto ya está en su lugar, no se hace nada.
        if (inv->products[i - 1].stock <= current_stock)
            continue;

        // Copia el producto actual.
        Product key = *current;
        int j = i - 1;

        // Desplaza los elementos mayores al producto actual hacia la derecha.
        while (j >= 0 && inv->products[j].stock > current_stock)
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
        Product *current = &inv->products[i];
        int current_id = current->id;

        // Si el elemnto ya está en su lugar, no se hace nada.
        if (inv->products[i - 1].id <= current_id)
            continue;

        // Copia el producto actual.
        Product key = *current;
        int j = i - 1;

        // Desplaza los elementos mayores al producto actual hacia la derecha.
        while (j >= 0 && inv->products[j].id > current_id)
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
        Product *current = &inv->products[i];
        char *current_name = current->name;

        // Si el elemnto ya está en su lugar, no se hace nada.
        if (strcmp(inv->products[i - 1].name, current_name) <= 0)
            continue;

        // Copia el producto actual.
        Product key = *current;
        int j = i - 1;

        // Desplaza los elementos mayores al producto actual hacia la derecha.
        while (j >= 0 && strcmp(inv->products[j].name, current_name) > 0)
        {
            inv->products[j + 1] = inv->products[j];
            j--;
        }

        inv->products[j + 1] = key;
    }
}