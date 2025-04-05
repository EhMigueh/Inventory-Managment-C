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

    
    char buffer[256];

    // Leer  y verificar 
    if (!fgets(buffer, sizeof(buffer), file)) {
        fprintf(stderr, "Error leyendo cabecera del archivo\n");
        fclose(file);
        return -1;
    }

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


//  imprimir los primeros n elementos del inventario
void print_inventory_sample(Inventory *inventory, int sample_size) {
    printf("\nMuestra del inventario (%d elementos):\n", sample_size);
    int limit = inventory->count < sample_size ? inventory->count : sample_size;
    
    for (int i = 0; i < limit; i++) {
        print_product(&inventory->products[i]);
    }
    printf("...\n");
}

void print_product(Product *product) {
    printf("ID: %d, Nombre: %s, Categoría: %s, Precio: %.2f, Stock: %d\n",
           product->id, product->name, product->category, product->price, product->stock);
}