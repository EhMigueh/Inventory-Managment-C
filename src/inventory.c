#include "inventory.h"

Inventory* create_inventory(int capacity) {
    Inventory *inventory = (Inventory*)malloc(sizeof(Inventory));
    if (!inventory) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el inventario\n");
        return NULL;
    }
    
    inventory->products = (Product*)malloc(capacity * sizeof(Product));
    if (!inventory->products) {
        fprintf(stderr, "Error: No se pudo asignar memoria para los productos\n");
        free(inventory);
        return NULL;
    }
    
    inventory->count = 0;
    inventory->capacity = capacity;
    
    return inventory;
}

void free_inventory(Inventory *inventory) {
    if (inventory) {
        if (inventory->products) {
            free(inventory->products);
        }
        free(inventory);
    }
}

int load_inventory_from_file(Inventory *inventory, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s\n", filename);
        return -1;
    }
    
    // Saltar la primera línea (encabezados)
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);
    
    // Leer los productos
    int count = 0;
    while (count < inventory->capacity && 
           fscanf(file, "%d,%49[^,],%29[^,],%lf,%d\n", 
                 &inventory->products[count].id,
                 inventory->products[count].name,
                 inventory->products[count].category,
                 &inventory->products[count].price,
                 &inventory->products[count].stock) == 5) {
        count++;
    }
    
    inventory->count = count;
    fclose(file);
    
    return count;
}

int save_inventory_to_file(Inventory *inventory, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s para escritura\n", filename);
        return -1;
    }
    
    // Escribir encabezados
    fprintf(file, "ID,Nombre,Categoria,Precio,Stock\n");
    
    // Escribir productos
    for (int i = 0; i < inventory->count; i++) {
        fprintf(file, "%d,%s,%s,%.2f,%d\n",
                inventory->products[i].id,
                inventory->products[i].name,
                inventory->products[i].category,
                inventory->products[i].price,
                inventory->products[i].stock);
    }
    
    fclose(file);
    return inventory->count;
}