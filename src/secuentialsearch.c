#include "inventory.h"

//  busqueda secuencial por ID
int sequential_search(Inventory *inv, int id)
{
    for (int i = 0; i < inv->count; i++)
        if (inv->products[i].id == id)
            return i;

    return -1;
}

// busqueda secuencial por nombre
int sequential_search_by_name(Inventory *inv, const char *name)
{
    for (int i = 0; i < inv->count; i++)
        if (strcmp(inv->products[i].name, name) == 0)
            return i;

    return -1;
}