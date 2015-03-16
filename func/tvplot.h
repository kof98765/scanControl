#ifndef _TV_PLOT_H_

#include <qwt_plot.h>
#include <QDebug>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_renderer.h>
#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>
#include <qpen.h>
#include <stdlib.h>
class TVPlot: public QwtPlot
{
    Q_OBJECT

public:
    TVPlot( QWidget * = NULL );

public Q_SLOTS:
    void setMode( int );
    void exportPlot();

public:
    void populate(int value[],int length);
    void populate_clear();
private:
    QwtPlotHistogram *histogramJune;
    QwtPlotGrid *grid;

private Q_SLOTS:
    void showItem( const QVariant &, bool on );
};

#endif
