#include "inventory.h"
#include "search.h"

// Busca un producto por ID usando búsqueda binaria iterativa
int binary_search_by_id(Inventory *inv, int id)
{
   int left = 0;
   int right = inv->count - 1;

   while (left <= right)
   {
       int mid = left + (right - left) / 2;  // Previene overflow

       if (inv->products[mid].id == id)
           return mid;  // Encontrado

       if (inv->products[mid].id < id)
           left = mid + 1;  // Busca en mitad derecha
       else
           right = mid - 1;  // Busca en mitad izquierda
   }

   return -1;  // No encontrado
}

// Busca un producto por nombre usando búsqueda binaria iterativa
int binary_search_by_name(Inventory *inv, const char *name)
{
   int left = 0;
   int right = inv->count - 1;

   while (left <= right)
   {
       int mid = left + (right - left) / 2;
       int cmp = strcmp(inv->products[mid].name, name);

       if (cmp == 0)
           return mid;  // Encontrado

       if (cmp < 0)
           left = mid + 1;  // Busca en mitad derecha
       else
           right = mid - 1;  // Busca en mitad izquierda
   }

   return -1;  // No encontrado
}

// Encuentra el primer producto con precio >= min_price
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
           result = mid;  // Guarda el candidato actual
           right = mid - 1;  // Sigue buscando a la izquierda
       }
       else
           left = mid + 1;
   }

   return result;
}

// Encuentra el último producto con precio <= max_price
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
           result = mid;  // Guarda el candidato actual
           left = mid + 1;  // Sigue buscando a la derecha
       }
       else
           right = mid - 1;
   }

   return result;
}

// Busca productos en un rango de precios específico
int binary_search_by_price_range(Inventory *inventory, double min_price, double max_price, Product **results, int max_results)
{
   int count = 0;
   const int NUM_ITERATIONS = 1000;
   int lower_bound, upper_bound;

   for (int iter = 0; iter < NUM_ITERATIONS; iter++)
   {
       count = 0;

       // Encuentra límite inferior del rango
       lower_bound = binary_search_lower_bound_price(inventory, min_price);
       if (lower_bound == -1)
           continue;

       // Encuentra límite superior del rango
       upper_bound = binary_search_upper_bound_price(inventory, max_price);
       if (upper_bound == -1 || upper_bound < lower_bound)
           continue;

       // Calcula cantidad de productos en el rango
       count = upper_bound - lower_bound + 1;

       // Almacena resultados solo en la última iteración
       if (iter == NUM_ITERATIONS - 1)
       {
           int to_store = (count < max_results) ? count : max_results;
           for (int i = 0; i < to_store; i++)
               results[i] = &inventory->products[lower_bound + i];
       }
   }

   return (count < max_results) ? count : max_results;
}