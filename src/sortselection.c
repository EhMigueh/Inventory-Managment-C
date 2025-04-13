#include "inventory.h"

// Ordena el inventario por precio.
void selection_sort_by_price(Inventory *inv)
{
    int n = inv->count;

    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;
        bool sorted = true;

        for (int j = i + 1; j < n; j++)
        {
            if (inv->products[j].price < inv->products[min_index].price)
            {
                min_index = j;
                sorted = false; // Se detectó un cambio.
            }
        }

        // Solo se intercambia si se encontró un nuevo índice mínimo.
        if (min_index != i)
        {
            Product temp = inv->products[i];
            inv->products[i] = inv->products[min_index];
            inv->products[min_index] = temp;
        }

        // Si no se hacen cambios en la iteración, el arreglo ya está ordenado.
        if (sorted)
            break;
    }
}

// Ordena el inventario por stock.
void selection_sort_by_stock(Inventory *inv)
{
    int n = inv->count;

    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;
        bool sorted = true;

        for (int j = i + 1; j < n; j++)
        {
            if (inv->products[j].stock < inv->products[min_index].stock)
            {
                min_index = j;
                sorted = false; // Se detectó un cambio.
            }
        }

        // Solo se intercambia si se encontró un nuevo índice mínimo.
        if (min_index != i)
        {
            Product temp = inv->products[i];
            inv->products[i] = inv->products[min_index];
            inv->products[min_index] = temp;
        }

        // Si no se hacen cambios en la iteración, el arreglo ya está ordenado.
        if (sorted)
            break;
    }
}

// Ordena el inventario por ID.
void selection_sort_by_id(Inventory *inv)
{
    int n = inv->count;

    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;
        bool sorted = true;

        for (int j = i + 1; j < n; j++)
        {
            if (inv->products[j].id < inv->products[min_index].id)
            {
                min_index = j;
                sorted = false; // Se detectó un cambio.
            }
        }

        // Solo se intercambia si se encontró un nuevo índice mínimo.
        if (min_index != i)
        {
            Product temp = inv->products[i];
            inv->products[i] = inv->products[min_index];
            inv->products[min_index] = temp;
        }

        // Si no se hacen cambios en la iteración, el arreglo ya está ordenado.
        if (sorted)
            break;
    }
}

// Ordena el inventario por nombre.
void selection_sort_by_name(Inventory *inv)
{
    int n = inv->count;

    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;
        bool sorted = true;

        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(inv->products[j].name, inv->products[min_index].name) < 0)
            {
                min_index = j;
                sorted = false; // Se detectó un cambio.
            }
        }

        // Solo se intercambia si se encontró un nuevo índice mínimo.
        if (min_index != i)
        {
            Product temp = inv->products[i];
            inv->products[i] = inv->products[min_index];
            inv->products[min_index] = temp;
        }

        // Si no se hacen cambios en la iteración, el arreglo ya está ordenado.
        if (sorted)
            break;
    }
}