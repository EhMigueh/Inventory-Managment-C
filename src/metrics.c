#include "inventory.h"

int get_total_products(Inventory *inv) {
    return inv->count;
}

double get_total_inventory_value(Inventory *inv) {
    double total = 0.0;
    for (int i = 0; i < inv->count; i++)
        total += inv->products[i].price * inv->products[i].stock;
    return total;
}

Product *get_product_with_max_stock(Inventory *inv) {
    if (inv->count == 0) return NULL;
    Product *max = &inv->products[0];
    for (int i = 1; i < inv->count; i++)
        if (inv->products[i].stock > max->stock)
            max = &inv->products[i];
    return max;
}

Product *get_product_with_min_stock(Inventory *inv) {
    if (inv->count == 0) return NULL;
    Product *min = &inv->products[0];
    for (int i = 1; i < inv->count; i++)
        if (inv->products[i].stock < min->stock)
            min = &inv->products[i];
    return min;
}

Product *get_most_expensive_product(Inventory *inv) {
    if (inv->count == 0) return NULL;
    Product *max = &inv->products[0];
    for (int i = 1; i < inv->count; i++)
        if (inv->products[i].price > max->price)
            max = &inv->products[i];
    return max;
}

Product *get_cheapest_product(Inventory *inv) {
    if (inv->count == 0) return NULL;
    Product *min = &inv->products[0];
    for (int i = 1; i < inv->count; i++)
        if (inv->products[i].price < min->price)
            min = &inv->products[i];
    return min;
}
