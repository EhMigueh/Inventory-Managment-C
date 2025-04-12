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
void gnuplot_close(gnuplot_ctrl *);
void gnuplot_setstyle(gnuplot_ctrl *, const char *);
void gnuplot_settitle(gnuplot_ctrl *, const char *);
void gnuplot_set_xlabel(gnuplot_ctrl *, const char *);
void gnuplot_set_ylabel(gnuplot_ctrl *, const char *);
void gnuplot_plot_xy(gnuplot_ctrl *, const double *, const double *, int, const char *);
void gnuplot_saveplot(gnuplot_ctrl *, const char *);
void gnuplot_cmd(gnuplot_ctrl *, const char *, ...);

#endif
