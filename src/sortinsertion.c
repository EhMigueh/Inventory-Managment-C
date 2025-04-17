#include "inventory.h"
#include "sort.h"

// Ordena el inventario por precio (menor a mayor)
void insertion_sort_by_price(Inventory *inv)
{
    int n = inv->count;

    for (int i = 1; i < n; i++)
    {
        Product key = inv->products[i];

        // Optimización: salta si ya está en orden
        if (inv->products[i - 1].price <= key.price)
            continue;

        int j = i - 1;

        // Desplaza elementos mayores hacia la derecha
        while (j >= 0 && inv->products[j].price > key.price)
        {
            inv->products[j + 1] = inv->products[j];
            j--;
        }

        // Inserta en posición correcta
        inv->products[j + 1] = key;
    }
}

// Ordena el inventario por stock (menor a mayor)
void insertion_sort_by_stock(Inventory *inv)
{
    int n = inv->count;

    for (int i = 1; i < n; i++)
    {
        Product key = inv->products[i];

        // Optimización: salta si ya está en orden
        if (inv->products[i - 1].stock <= key.stock)
            continue;

        int j = i - 1;

        // Desplaza elementos mayores hacia la derecha
        while (j >= 0 && inv->products[j].stock > key.stock)
        {
            inv->products[j + 1] = inv->products[j];
            j--;
        }

        // Inserta en posición correcta
        inv->products[j + 1] = key;
    }
}

// Ordena el inventario por ID (menor a mayor)
void insertion_sort_by_id(Inventory *inv)
{
    int n = inv->count;

    for (int i = 1; i < n; i++)
    {
        Product key = inv->products[i];

        // Optimización: salta si ya está en orden
        if (inv->products[i - 1].id <= key.id)
            continue;

        int j = i - 1;

        // Desplaza elementos mayores hacia la derecha
        while (j >= 0 && inv->products[j].id > key.id)
        {
            inv->products[j + 1] = inv->products[j];
            j--;
        }

        // Inserta en posición correcta
        inv->products[j + 1] = key;
    }
}

// Ordena el inventario alfabéticamente por nombre
void insertion_sort_by_name(Inventory *inv)
{
    int n = inv->count;

    for (int i = 1; i < n; i++)
    {
        Product key = inv->products[i];

        // Optimización: salta si ya está en orden
        if (strcmp(inv->products[i - 1].name, key.name) <= 0)
            continue;

        int j = i - 1;

        // Desplaza nombres alfabéticamente mayores hacia la derecha
        while (j >= 0 && strcmp(inv->products[j].name, key.name) > 0)
        {
            inv->products[j + 1] = inv->products[j];
            j--;
        }

        // Inserta en posición correcta
        inv->products[j + 1] = key;
    }
}