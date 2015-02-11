#ifndef _TV_PLOT_H_

#include <qwt_plot.h>
#include <QDebug>
#include <qwt_plot_layout.h>
#include <qwt_plot_textlabel.h>
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
#include <qwt_plot_marker.h>
#include <qwt_symbol.h>
class TVPlot: public QwtPlot
{
    Q_OBJECT

public:
    TVPlot( QWidget * = NULL );
    ~TVPlot();
public Q_SLOTS:
    void setMode( int );
    void exportPlot();

public:
    //��������,valueΪ����,lengthΪ���鳤��,strΪ����
    void populate(int value[],int length,QString str);
    //���
    void populate_clear();
    //str��ֵ 0,Ϊ���������,1Ϊ���������,2Ϊ���������ֵ,3Ϊ�����경��ֵ
    void initPlot(QStringList str);
private:
    QwtPlotHistogram *histogramJune;

    QwtPlotGrid *grid;
    QwtIntervalSeriesData data;
    double step;
private Q_SLOTS:
    void showItem( const QVariant &, bool on );
};

#endif
