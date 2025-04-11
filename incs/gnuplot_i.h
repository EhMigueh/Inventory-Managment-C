#ifndef GNUPLOT_I_H
#define GNUPLOT_I_H

#include <stdio.h>
#include <stdlib.h>

#define GP_MAX_TMP_FILES 64

// Estructura para manejar la comunicación con gnuplot.
typedef struct _gnuplot_ctrl
{
    FILE *gp_pipe;
    char *tmp_filename_tbl[GP_MAX_TMP_FILES];
    int nplots;
} gnuplot_ctrl;

// Prototipo de funciones para el manejo de gnuplot.
gnuplot_ctrl *gnuplot_init(void);
void gnuplot_close(gnuplot_ctrl *handle);
void gnuplot_setstyle(gnuplot_ctrl *handle, const char *plot_style);
void gnuplot_settitle(gnuplot_ctrl *handle, const char *title);
void gnuplot_set_xlabel(gnuplot_ctrl *handle, const char *label);
void gnuplot_set_ylabel(gnuplot_ctrl *handle, const char *label);
void gnuplot_plot_xy(gnuplot_ctrl *handle, const double *x, const double *y, int n, const char *title);
void gnuplot_saveplot(gnuplot_ctrl *handle, const char *filename);
void gnuplot_cmd(gnuplot_ctrl *handle, const char *cmd, ...);

#endif
