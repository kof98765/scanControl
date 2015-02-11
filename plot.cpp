#include "plot.h"
#include "settings.h"
#include <qwt_plot_curve.h>
#include <qwt_plot_legenditem.h>
#include <qwt_legend.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_layout.h>



Plot::Plot( QWidget *parent ):
    QwtPlot( parent ),
    d_isDirty( false )
{
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setFocusIndicator( QwtPlotCanvas::CanvasFocusIndicator );
    canvas->setFocusPolicy( Qt::StrongFocus );
    canvas->setPalette( Qt::black );

    canvas->setLineWidth( 1 );
    canvas->setFrameStyle( QFrame::Box | QFrame::Plain );
    canvas->setBorderRadius( 15 );

    QPalette canvasPalette( Qt::white );
    canvasPalette.setColor( QPalette::Foreground, QColor( 133, 190, 232 ) );
    canvas->setPalette( canvasPalette );

    setCanvas( canvas );

    //鼠标缩放功能,拖动放大区域,右键恢复
/*
    QwtPlotZoomer* zoomer = new QwtPlotZoomer( canvas );
    zoomer->setRubberBandPen( QColor( Qt::green ) );
    zoomer->setTrackerPen( QColor( Qt::green ) );
    zoomer->setMousePattern(QwtEventPattern::);
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3,
        Qt::RightButton );

*/
    setAutoReplot( false );
    ( void ) new QwtPlotPanner( canvas );
    ( void ) new QwtPlotMagnifier( canvas );

}
void Plot::setXScale(double min,double max)
{

    setAxisScale( QwtPlot::xBottom, min, max);
}
void Plot::setYScale(double min,double max)
{
    setAxisScale( QwtPlot::yLeft, min, max );
}
void Plot::initPlot(QStringList list)
{
    //0,为纵坐标标题,1为横坐标标题,2为横坐标最大值,3为横坐标步长值



    setAxisTitle(QwtPlot::yLeft,list.at(0));
    setAxisTitle(QwtPlot::xBottom,list.at(1));
    step=list.at(3).toDouble();
    // grid
    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableXMin( true );
    grid->setMajorPen( Qt::gray, 0, Qt::DotLine );
    grid->setMinorPen( Qt::darkGray, 0, Qt::DotLine );
    grid->attach( this );

    // axis
    setAxisScale( QwtPlot::yLeft, 0.0, 1000.0 );
    setAxisScale( QwtPlot::xBottom, 0, list.at(2).toDouble(),step);
}
Plot::~Plot()
{

}
void Plot::upDate2(double *x,double *y,int size)
{
    static int frame=0;
        for(int i=0;i<size;i++)
        {
            QwtPlotMarker *mPos = new QwtPlotMarker();
            mPos->setRenderHint( QwtPlotItem::RenderAntialiased, true );
            mPos->setItemAttribute( QwtPlotItem::AutoScale, true );
            //mPos->setSymbol( new ArrowSymbol() );
            mPos->setValue( QPointF( frame, i ) );
            mPos->setLabel( QString( "%1" ).arg(y[i]) );
            mPos->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );

            mPos->attach( this );
        }
    frame++;
    replot();
}
void Plot::upDate(double *x,double *y,int size)
{
    QwtPlotItemList curveList = itemList(QwtPlotItem::Rtti_PlotCurve);
    if(curveList.size()>0)
    {
        QwtPlotCurve* curve = (QwtPlotCurve *)curveList.takeFirst();
        QVector<QPointF> points;
        curve->setRenderHint( QwtPlotItem::RenderAntialiased );
        curve->setSamples(x,y,size);
         //   curve->setSamples(points);


    }

    replot();

}
void Plot::insertCurve(double value[],int length,QString str)
{
    static int counter = 1;

    const char *colors[] = 
    { 
        "LightSalmon",
        "SteelBlue",
        "Yellow",
        "Fuchsia",
        "PaleGreen",
        "PaleTurquoise",
        "Cornsilk",
        "HotPink",
        "Peru",
        "Maroon"
    };

    const int numColors = sizeof( colors ) / sizeof( colors[0] );

    QwtPlotCurve *curve = new QwtPlotCurve;
    curve->setTitle(str);
    QVector<QPointF> points;
    curve->setRenderHint( QwtPlotItem::RenderAntialiased );
    double y;
    if(length != 0)
    {
        for ( int x = 0; x <= length; x += 1)
        {
            y=value[x];
            if(y>max)
                max=y;
            if(y<min)
                min=y;
            points += QPointF( x, y );
        }
        curve->setSamples(points);


    }
    curve->setPen( QColor( colors[ counter % numColors ] ), 1 );
    curve->attach( this );
    this->setAxisScale(QwtPlot::yLeft,min,max);
    replot();
}
void Plot::clearCurve()
{
    QwtPlotItemList curveList = itemList( QwtPlotItem::Rtti_PlotCurve );

    while ( curveList.size() > 0 )
    {
        QwtPlotItem* curve = curveList.takeFirst();
        delete curve;
    }



}



void Plot::replot()
{
    if ( autoReplot() )
    {
        d_isDirty = true;
        return;
    }

    QwtPlot::replot();
}
