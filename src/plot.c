#include "inventory.h"

// Función para graficar los tiempos de ordenamiento
void plot_sort_times(int *sizes, double *times, int n, const char *titulo, const char *nombre_archivo)
{
    gnuplot_ctrl *gp = gnuplot_init();

    gnuplot_setstyle(gp, "linespoints");
    gnuplot_cmd(gp, "set title '%s'", titulo);
    gnuplot_cmd(gp, "set xlabel 'Cantidad de productos'");
    gnuplot_cmd(gp, "set ylabel 'Tiempo (s)'");
    gnuplot_cmd(gp, "set term png");
    gnuplot_cmd(gp, "set output 'plots/%s.png'", nombre_archivo);

    double *sizes_double = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; ++i)
        sizes_double[i] = (double)sizes[i];

    gnuplot_plot_xy(gp, sizes_double, times, n, titulo);

    free(sizes_double);
    gnuplot_close(gp);
}
