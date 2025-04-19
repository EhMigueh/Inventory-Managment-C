#ifndef PLOT_H
#define PLOT_H

#include <stdio.h>
#include "gnuplot_i.h"

// Grafica los tiempos de prueba (por ejemplo, tiempo de ejecución de diferentes algoritmos)
void plot_test_times(int *, double *, int, const char *, const char *, const char *, int);

// Grafica los tiempos de comparación de algoritmos de ordenamiento
void plot_comparative_sort_times(int *, double *, double *, double *, int, const char *, const char *, const char *);

// Grafica los tiempos de comparación de algoritmos de búsqueda
void plot_comparative_search_times(int *, double *, double *, double *, int, const char *, const char *, const char *);

#endif
