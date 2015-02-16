#ifndef _PLOT_H_
#define _PLOT_H_

#include <qwt_plot.h>
#include "settings.h"
#include <qwt_plot_zoomer.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_marker.h>
class Settings;
class LegendItem;
class QwtLegend;

class Plot: public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget *parent = NULL );
    virtual ~Plot();

public:
    virtual void replot();
    void initPlot(QStringList list);
    void insertCurve(double value[],int length,QString str);
    void clearCurve();


    void upDate2(double *x,double *y,int size);
    void setXScale(double min,double max);
    void setYScale(double min,double max);
public slots:
    void upDate(double *x,double *y,int size);
    void upScanControlData(unsigned short *,unsigned short *,double *x,double *y,int size);
private:
    double step;
    bool d_isDirty;
    double min,max;

};

#endif
