#include "inventory.h"

int sequential_search(Inventory *inv, int id)
{
    for (int i = 0; i < inv->count; i++)
    {
        if (inv->products[i].id == id)
        {
            return i; // Retorna id
        }
    }
    return -1; // No se encontro
}
