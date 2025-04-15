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

int binary_search_lower_bound_price(Inventory *inv, double min_price)
{
    int left = 0;
    int right = inv->count - 1;
    int result = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (inv->products[mid].price >= min_price)
        {
            result = mid;
            right = mid - 1;
        }
        else
            left = mid + 1;
    }

    return result;
}

// Encuentra la posición del último producto con precio <= max_price
int binary_search_upper_bound_price(Inventory *inv, double max_price)
{
    int left = 0;
    int right = inv->count - 1;
    int result = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (inv->products[mid].price <= max_price)
        {
            result = mid;
            left = mid + 1;
        }
        else
            right = mid - 1;
    }

    return result;
}

// Búsqueda binaria por rango de precios (iterativa)
int binary_search_by_price_range(Inventory *inventory, double min_price, double max_price, Product **results, int max_results)
{
    // El inventario debe estar ordenado por precio
    int count = 0;

    const int NUM_ITERATIONS = 1000;
    struct timespec start, end;

    // límites del rango de precios
    int lower_bound, upper_bound;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int iter = 0; iter < NUM_ITERATIONS; iter++)
    {
        count = 0;

        // Encuentra el índice del primer producto con precio >= min_price
        lower_bound = binary_search_lower_bound_price(inventory, min_price);

        if (lower_bound == -1)
            continue; // No hay productos con precio >= min_price

        // Encuentra el índice del último producto con precio <= max_price
        upper_bound = binary_search_upper_bound_price(inventory, max_price);

        if (upper_bound == -1 || upper_bound < lower_bound)
            continue; // No hay productos con precio <= max_price o el rango está vacío

        // Cuenta y almacena los productos en el rango
        count = upper_bound - lower_bound + 1;

        // Solo almacena resultados en la última iteración
        if (iter == NUM_ITERATIONS - 1)
        {
            int to_store = (count < max_results) ? count : max_results;
            for (int i = 0; i < to_store; i++)
                results[i] = &inventory->products[lower_bound + i];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);



    return (count < max_results) ? count : max_results;
}

// Funciones auxiliares para búsqueda recursiva por rango de precios
int find_lower_bound_recursive(Inventory *inv, double min_price, int left, int right)
{
    if (left > right)
        return -1;

    int mid = left + (right - left) / 2;

    if (inv->products[mid].price >= min_price)
    {
        int res = find_lower_bound_recursive(inv, min_price, left, mid - 1);
        return (res != -1) ? res : mid;
    }
    else
    {
        return find_lower_bound_recursive(inv, min_price, mid + 1, right);
    }
}

int find_upper_bound_recursive(Inventory *inv, double max_price, int left, int right)
{
    if (left > right)
        return -1;

    int mid = left + (right - left) / 2;

    if (inv->products[mid].price <= max_price)
    {
        int res = find_upper_bound_recursive(inv, max_price, mid + 1, right);
        return (res != -1) ? res : mid;
    }
    else
    {
        return find_upper_bound_recursive(inv, max_price, left, mid - 1);
    }
}


// Búsqueda binaria por rango de precios recursiva
int binary_search_by_price_range_recursive(Inventory *inventory, double min_price, double max_price, Product **results, int max_results)
{
    // El inventario debe estar ordenado por precio
    int count = 0;

    const int NUM_ITERATIONS = 1000;
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int iter = 0; iter < NUM_ITERATIONS; iter++)
    {
        count = 0;

        // Encuentra  índice del primer producto con precio >= min_price
        int lower_bound = find_lower_bound_recursive(inventory, min_price, 0, inventory->count - 1);

        if (lower_bound == -1)
            continue; 

        // Encuentra índice del último producto con precio <= max_price
        int upper_bound = find_upper_bound_recursive(inventory, max_price, 0, inventory->count - 1);

        if (upper_bound == -1 || upper_bound < lower_bound)
            continue; 

        // Cuenta y almacena los productos en el rango
        count = upper_bound - lower_bound + 1;

        // Solo almacena resultados en la última iteración
        if (iter == NUM_ITERATIONS - 1)
        {
            int to_store = (count < max_results) ? count : max_results;
            for (int i = 0; i < to_store; i++)
                results[i] = &inventory->products[lower_bound + i];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);


    return (count < max_results) ? count : max_results;
}