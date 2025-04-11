#include "inventory.h"

void handle_bubble_sort(Inventory *first_inv, Inventory *second_inv, Inventory *third_inv, Inventory *fourth_inv, Inventory *fifth_inv)
{
    int search_option;
    clock_t start, end;
    double time;
    double times[5];

    fprintf(stdout, "\nSelecciona el tipo de ordenamiento:\n");
    fprintf(stdout, "1. Ordenar por precio.\n");
    fprintf(stdout, "2. Ordenar por stock.\n");
    fprintf(stdout, "0. Volver al menú principal.\n");
    fprintf(stdout, "\nSelecciona una opción: ");

    if (scanf("%d", &search_option) != 1)
    {
        fprintf(stderr, "ERROR entrada no válida. Por favor, introduce un número.\n");
        while (getchar() != '\n')
            ;
        return;
    }

    if (search_option == 0)
    {
        fprintf(stdout, "\nVolviendo al menú principal...\n\n");
        return;
    }

    if (search_option == 1)
    {
        Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
        int sizes[] = {10000, 25000, 50000, 75000, 100000};
        for (int i = 0; i < 5; i++)
        {
            start = clock();
            bubble_sort_by_price(dbs[i]);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = time;
            fprintf(stdout, "Tiempo de ordenamiento por precio (base de datos de %d objetos): %.4f segundos.\n", sizes[i], time);
        }
        fprintf(stdout, "\nOrdenamiento por precio completado. Su gráfico quedó guardado en 'plots'.\n\n");
        plot_sort_times(sizes, times, 5, "Bubble Sort por precio", "Bubble Price");
    }
    else if (search_option == 2)
    {
        Inventory *dbs[] = {first_inv, second_inv, third_inv, fourth_inv, fifth_inv};
        int sizes[] = {10000, 25000, 50000, 75000, 100000};
        for (int i = 0; i < 5; i++)
        {
            start = clock();
            bubble_sort_by_stock(dbs[i]);
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            times[i] = time;
            fprintf(stdout, "Tiempo de ordenamiento por stock (base de datos de %d objetos): %.4f segundos.\n", sizes[i], time);
        }
        fprintf(stdout, "\nOrdenamiento por stock completado. Su gráfico quedó guardado en 'plots'.\n\n");
        plot_sort_times(sizes, times, 5, "Bubble Sort por stock", "Bubble Stock");
    }
    else
    {
        fprintf(stderr, "\nERROR opción inválida. Solo se permite 0, 1 o 2.\n\n");
        return;
    }
}

// Ordena el inventario por precio
void bubble_sort_by_price(Inventory *inv)
{
    int n = inv->count;
    int swapped;
    int new_limit;
    
    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0; 
        new_limit = 0;
        
        
        for (int j = 0; j < n - i - 1; j++)
        {
            if (inv->products[j].price > inv->products[j + 1].price)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
                swapped = 1; 
                new_limit = j; 
            }
        }
        
        
        if (swapped == 0)
            break;
            
      
        n = new_limit + 1;
    }
}

// Ordena el inventario por stock
void bubble_sort_by_stock(Inventory *inv)
{
    int n = inv->count;
    int swapped;
    int new_limit;
    
    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        new_limit = 0;
        
       
        for (int j = 0; j < n - i - 1; j++)
        {
            if (inv->products[j].stock > inv->products[j + 1].stock)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
                swapped = 1;
                new_limit = j; 
            }
        }
        
        // Si no hay cambios el arreglo ya está ordenado
        if (swapped == 0)
            break;
            
        
        n = new_limit + 1;
    }
}


// Implementaciones  para búsqueda binaria

// Ordena el inventario por ID
void bubble_sort_by_id(Inventory *inv)
{
    int n = inv->count;
    int swapped;
    int new_limit;
    
    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        new_limit = 0;
        
        for (int j = 0; j < n - i - 1; j++)
        {
            if (inv->products[j].id > inv->products[j + 1].id)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
                swapped = 1;
                new_limit = j;
            }
        }
        
        if (swapped == 0)
            break;
            
        n = new_limit + 1;
    }
}

// Ordena el inventario por nombre con optimizacion 
void bubble_sort_by_name(Inventory *inv)
{
    int n = inv->count;
    int swapped;
    int new_limit;
    
    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        new_limit = 0;
        
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(inv->products[j].name, inv->products[j + 1].name) > 0)
            {
                Product temp = inv->products[j];
                inv->products[j] = inv->products[j + 1];
                inv->products[j + 1] = temp;
                swapped = 1;
                new_limit = j;
            }
        }
        
        if (swapped == 0)
            break;
            
        n = new_limit + 1;
    }
}
