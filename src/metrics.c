#include "inventory.h"
#include "metrics.h"

int get_total_products(Inventory *inv)
{
    return inv->count;
}

double get_total_inventory_value(Inventory *inv)
{
    double total = 0.0;
    for (int i = 0; i < inv->count; i++)
        total += inv->products[i].price * inv->products[i].stock;
    return total;
}

Product *get_product_with_max_stock(Inventory *inv)
{
    if (inv->count == 0)
        return NULL;
    Product *max = &inv->products[0];
    for (int i = 1; i < inv->count; i++)
        if (inv->products[i].stock > max->stock)
            max = &inv->products[i];
    return max;
}

Product *get_product_with_min_stock(Inventory *inv)
{
    if (inv->count == 0)
        return NULL;
    Product *min = &inv->products[0];
    for (int i = 1; i < inv->count; i++)
        if (inv->products[i].stock < min->stock)
            min = &inv->products[i];
    return min;
}

Product *get_most_expensive_product(Inventory *inv)
{
    if (inv->count == 0)
        return NULL;
    Product *max = &inv->products[0];
    for (int i = 1; i < inv->count; i++)
        if (inv->products[i].price > max->price)
            max = &inv->products[i];
    return max;
}

Product *get_cheapest_product(Inventory *inv)
{
    if (inv->count == 0)
        return NULL;
    Product *min = &inv->products[0];
    for (int i = 1; i < inv->count; i++)
        if (inv->products[i].price < min->price)
            min = &inv->products[i];
    return min;
}

// Obtiene el número de categorías únicas y las almacena en el array proporcionado.
int get_unique_categories(Inventory *inv, CategoryStats *stats, int max_categories)
{
    int category_count = 0;

    // Para cada producto.
    for (int i = 0; i < inv->count; i++)
    {
        char *current_category = inv->products[i].category;
        int found = 0;

        // Buscar si ya tenemos esta categoría.
        for (int j = 0; j < category_count; j++)
            if (strcmp(stats[j].category, current_category) == 0) // Incrementar contador y suma de precios para esta categoría.
            {
                stats[j].product_count++;
                stats[j].total_price += inv->products[i].price;
                found = 1;
                break;
            }

        // Si es una nueva categoría, añadirla (si hay espacio).
        if (!found && category_count < max_categories)
        {
            strcpy(stats[category_count].category, current_category);
            stats[category_count].product_count = 1;
            stats[category_count].total_price = inv->products[i].price;
            category_count++;
        }
    }

    // Calcular promedios para cada categoría.
    for (int i = 0; i < category_count; i++)
        stats[i].average_price = stats[i].total_price / stats[i].product_count;

    return category_count;
}

// Función para obtener el promedio de precios por categoría.
void get_average_price_by_category(Inventory *inv)
{
    CategoryStats stats[20] = {0};
    int category_count = get_unique_categories(inv, stats, 20);

    fprintf(stdout, "Promedio de precios por categoría:\n");
    for (int i = 0; i < category_count; i++)
        fprintf(stdout, "- %s: %.2f\n", stats[i].category, stats[i].average_price);
}

// Función para obtener la cantidad de productos por categoría.
void get_products_count_by_category(Inventory *inv)
{
    CategoryStats stats[20] = {0};
    int category_count = get_unique_categories(inv, stats, 20);

    fprintf(stdout, "Cantidad de productos por categoría:\n");
    for (int i = 0; i < category_count; i++)
        fprintf(stdout, "- %s: %d\n", stats[i].category, stats[i].product_count);
}