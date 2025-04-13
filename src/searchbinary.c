#include "inventory.h"

// Implementación iterativa de búsqueda binaria por ID.
int binary_search_by_id(Inventory *inv, int id)
{
    int left = 0;
    int right = inv->count - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // Evita overflow.

        if (inv->products[mid].id == id)
            return mid;

        if (inv->products[mid].id < id)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1; // No encontrado.
}

// Implementación recursiva por ID.
int binary_search_by_id_recursive(Inventory *inv, int id, int left, int right)
{
    if (left > right)
        return -1; // Caso base no se encontro.

    int mid = left + (right - left) / 2; // Evitar el overflow.

    if (inv->products[mid].id == id)
        return mid;

    if (inv->products[mid].id < id)
        return binary_search_by_id_recursive(inv, id, mid + 1, right);
    else
        return binary_search_by_id_recursive(inv, id, left, mid - 1);
}

// Implementación iterativa de búsqueda binaria por nombre.
int binary_search_by_name(Inventory *inv, const char *name)
{
    int left = 0;
    int right = inv->count - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // Evitar el overflow.
        int cmp = strcmp(inv->products[mid].name, name);

        if (cmp == 0)
            return mid;

        if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

// Implementacion optimizada recursiva de busqueda binaria por nombre.
int binary_search_by_name_recursive(Inventory *inv, const char *name, int left, int right)
{
    if (left > right)
        return -1; // Caso base no se encontro.

    int mid = left + (right - left) / 2; // Evitar el overflow.
    int cmp = strcmp(inv->products[mid].name, name);

    if (cmp == 0)
        return mid;

    if (cmp < 0)
        return binary_search_by_name_recursive(inv, name, mid + 1, right);
    else
        return binary_search_by_name_recursive(inv, name, left, mid - 1);
}