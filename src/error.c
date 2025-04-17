#include "inventory.h"
#include <stdio.h>

void save_sorted_inventory(Inventory *inv, const char *sort_criteria)
{
    char filename[100];
    snprintf(filename, sizeof(filename), "sorted_by_%s.txt", sort_criteria);

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("No se pudo abrir el archivo");
        return;
    }

    fprintf(file, "ID\tNombre\t\tPrecio\tStock\n");
    fprintf(file, "------------------------------------------\n");

    for (int i = 0; i < inv->count; i++)
    {
        fprintf(file, "%d\t%-15s\t%.2f\t%d\n",
                inv->products[i].id,
                inv->products[i].name,
                inv->products[i].price,
                inv->products[i].stock);
    }

    fclose(file);
}