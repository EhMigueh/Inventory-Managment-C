#include "inventory.h"
#include "sort.h"
// Ordena el inventario por precio.
void selection_sort_by_price(Inventory *inv)
{
    int n = inv->count;
    bool already_sorted = true;

    // Verifica si ya está ordenado.
    for (int i = 0; i < n - 1; i++)
        if (inv->products[i].price > inv->products[i + 1].price)
        {
            already_sorted = false; // Se detectó un cambio.
            break;
        }

    if (already_sorted)
        return;

    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;

        for (int j = i + 1; j < n; j++)
            if (inv->products[j].price < inv->products[min_index].price)
                min_index = j;

        // Solo se intercambia si se encontró un nuevo índice mínimo.
        if (min_index != i)
        {
            Product temp = inv->products[i];
            inv->products[i] = inv->products[min_index];
            inv->products[min_index] = temp;
        }
    }
}

// Ordena el inventario por stock.
void selection_sort_by_stock(Inventory *inv)
{
    int n = inv->count;
    bool already_sorted = true;

    // Verifica si ya está ordenado.
    for (int i = 0; i < n - 1; i++)
        if (inv->products[i].stock > inv->products[i + 1].stock)
        {
            already_sorted = false; // Se detectó un cambio.
            break;
        }

    if (already_sorted)
        return;

    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;

        for (int j = i + 1; j < n; j++)
            if (inv->products[j].stock < inv->products[min_index].stock)
                min_index = j;

        // Solo se intercambia si se encontró un nuevo índice mínimo.
        if (min_index != i)
        {
            Product temp = inv->products[i];
            inv->products[i] = inv->products[min_index];
            inv->products[min_index] = temp;
        }
    }
}

// Ordena el inventario por ID.
void selection_sort_by_id(Inventory *inv)
{
    int n = inv->count;
    bool already_sorted = true;

    // Verifica si ya está ordenado.
    for (int i = 0; i < n - 1; i++)
        if (inv->products[i].id > inv->products[i + 1].id)
        {
            already_sorted = false; // Se detectó un cambio.
            break;
        }

    if (already_sorted)
        return;

    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;

        for (int j = i + 1; j < n; j++)
            if (inv->products[j].id < inv->products[min_index].id)
                min_index = j;

        // Solo se intercambia si se encontró un nuevo índice mínimo.
        if (min_index != i)
        {
            Product temp = inv->products[i];
            inv->products[i] = inv->products[min_index];
            inv->products[min_index] = temp;
        }
    }
}

// Ordena el inventario por nombre (Falla).
void selection_sort_by_name(Inventory *inv)
{
    int n = inv->count;
    bool already_sorted = true;

    // Verifica si ya está ordenado.
    for (int i = 0; i < n - 1; i++)
        if (strcmp(inv->products[i].name, inv->products[i + 1].name) > 0)
        {
            already_sorted = false; // Se detectó un cambio.
            break;
        }

    if (already_sorted)
        return;

    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;

        for (int j = i + 1; j < n; j++)
            if (strcmp(inv->products[j].name, inv->products[min_index].name) < 0)
                min_index = j;

        // Solo se intercambia si se encontró un nuevo índice mínimo.
        if (min_index != i)
        {
            Product temp = inv->products[i];
            inv->products[i] = inv->products[min_index];
            inv->products[min_index] = temp;
        }
    }
}