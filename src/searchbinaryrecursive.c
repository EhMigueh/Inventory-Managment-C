#include "inventory.h"
#include "search.h"

// Busca un producto por ID usando búsqueda binaria recursiva
int binary_search_by_id_recursive(Inventory *inv, int id, int left, int right)
{
   if (left > right)
       return -1;  // No encontrado

   int mid = left + (right - left) / 2;  // Evita desbordamiento

   if (inv->products[mid].id == id)
       return mid;  // Encontrado

   if (inv->products[mid].id < id)
       return binary_search_by_id_recursive(inv, id, mid + 1, right);  // Busca en mitad derecha
   else
       return binary_search_by_id_recursive(inv, id, left, mid - 1);  // Busca en mitad izquierda
}

// Busca un producto por nombre usando búsqueda binaria recursiva
int binary_search_by_name_recursive(Inventory *inv, const char *name, int left, int right)
{
   if (left > right)
       return -1;  // No encontrado

   int mid = left + (right - left) / 2;
   int cmp = strcmp(inv->products[mid].name, name);

   if (cmp == 0)
       return mid;  // Encontrado

   if (cmp < 0)
       return binary_search_by_name_recursive(inv, name, mid + 1, right);  // Busca en mitad derecha
   else
       return binary_search_by_name_recursive(inv, name, left, mid - 1);  // Busca en mitad izquierda
}

// Encuentra recursivamente el primer producto cuyo precio es >= min_price
int find_lower_bound_recursive(Inventory *inv, double min_price, int left, int right)
{
   if (left > right)
       return -1;

   int mid = left + (right - left) / 2;

   if (inv->products[mid].price >= min_price)
   {
       // Intenta encontrar otro producto válido más a la izquierda
       int res = find_lower_bound_recursive(inv, min_price, left, mid - 1);
       return (res != -1) ? res : mid;
   }
   else
   {
       return find_lower_bound_recursive(inv, min_price, mid + 1, right);
   }
}

// Encuentra recursivamente el último producto cuyo precio es <= max_price
int find_upper_bound_recursive(Inventory *inv, double max_price, int left, int right)
{
   if (left > right)
       return -1;

   int mid = left + (right - left) / 2;

   if (inv->products[mid].price <= max_price)
   {
       // Intenta encontrar otro producto válido más a la derecha
       int res = find_upper_bound_recursive(inv, max_price, mid + 1, right);
       return (res != -1) ? res : mid;
   }
   else
   {
       return find_upper_bound_recursive(inv, max_price, left, mid - 1);
   }
}

// Busca productos en un rango de precios específico
int binary_search_by_price_range_recursive(Inventory *inventory, double min_price, double max_price, Product **results, int max_results)
{
   int count = 0;
   const int NUM_ITERATIONS = 1000;
   struct timespec start, end;

   clock_gettime(CLOCK_MONOTONIC, &start);  // Inicia medición de tiempo

   for (int iter = 0; iter < NUM_ITERATIONS; iter++)
   {
       count = 0;

       // Busca el límite inferior del rango
       int lower_bound = find_lower_bound_recursive(inventory, min_price, 0, inventory->count - 1);
       if (lower_bound == -1) continue;

       // Busca el límite superior del rango
       int upper_bound = find_upper_bound_recursive(inventory, max_price, 0, inventory->count - 1);
       if (upper_bound == -1 || upper_bound < lower_bound) continue;

       count = upper_bound - lower_bound + 1;

       // Almacena resultados solo en la última iteración
       if (iter == NUM_ITERATIONS - 1)
       {
           int to_store = (count < max_results) ? count : max_results;
           for (int i = 0; i < to_store; i++)
               results[i] = &inventory->products[lower_bound + i];
       }
   }

   clock_gettime(CLOCK_MONOTONIC, &end);  // Termina medición de tiempo

   return (count < max_results) ? count : max_results;
}