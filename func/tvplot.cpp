#include "tvplot.h"


TVPlot::TVPlot( QWidget *parent ):
    QwtPlot( parent )
{
    setTitle( QStringLiteral("缺陷统计表") );

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setPalette( Qt::gray );
    canvas->setBorderRadius( 10 );
    setCanvas( canvas );

    plotLayout()->setAlignCanvasToScales( true );

    setAxisTitle( QwtPlot::yLeft, QStringLiteral("缺陷数量") );
    setAxisTitle( QwtPlot::xBottom, QStringLiteral("缺陷尺寸"));
    setAxisScale(QwtPlot::xBottom,0.01,0.1,0.01);
    QwtLegend *legend = new QwtLegend;
    legend->setDefaultItemMode( QwtLegendData::Checkable );
    insertLegend( legend, QwtPlot::RightLegend );
    grid = new QwtPlotGrid;
    grid->enableX( false );
    grid->enableY( true );
    grid->enableXMin( false );
    grid->enableYMin( false );
    grid->setMajorPen( Qt::black, 0, Qt::DotLine );
    grid->attach( this );
    histogramJune = new QwtPlotHistogram( QStringLiteral("数量"));
    histogramJune->setStyle( QwtPlotHistogram::Columns );

    QColor c(Qt::red);
    c.setAlpha(180);
    histogramJune->setBrush(QBrush(c));

    connect( legend, SIGNAL( checked( const QVariant &, bool, int ) ),
        SLOT( showItem( const QVariant &, bool ) ) );

    //replot(); // creating the legend items
    //populate();
    QwtPlotItemList items = itemList( QwtPlotItem::Rtti_PlotHistogram );
    for ( int i = 0; i < items.size(); i++ )
    {
        if ( i == 0 )
        {
            const QVariant itemInfo = itemToInfo( items[i] );

            QwtLegendLabel *legendLabel =
                qobject_cast<QwtLegendLabel *>( legend->legendWidget( itemInfo ) );
            if ( legendLabel )
                legendLabel->setChecked( true );

            items[i]->setVisible( true );
        }
        else
        {
            items[i]->setVisible( false );
        }
    }

    //setAutoReplot( true );

}
void TVPlot::populate_clear()
{

}
void TVPlot::populate(int Values[],int length)
{
    populate_clear();
    QVector<QwtIntervalSample> samples( length );

    for ( uint i = 0; i < length; i++ )
    {
        QwtInterval interval( double( i*0.01 ), double(i*0.01)+double(0.01) );

        samples[i] = QwtIntervalSample( Values[i], interval );
        qDebug()<<Values[i];
    }
    histogramJune->setData( new QwtIntervalSeriesData( samples ) );
    histogramJune->attach( this );

    replot();
}

void TVPlot::exportPlot()
{
    QwtPlotRenderer renderer;
    renderer.exportTo( this, "tvplot.pdf" );
}

void TVPlot::setMode( int mode )
{
    QwtPlotItemList items = itemList( QwtPlotItem::Rtti_PlotHistogram );

    for ( int i = 0; i < items.size(); i++ )
    {
        QwtPlotHistogram *histogram = static_cast<QwtPlotHistogram *>( items[i] );
        if ( mode < 3 )
        {
            histogram->setStyle( static_cast<QwtPlotHistogram::HistogramStyle>( mode ) );
            histogram->setSymbol( NULL );

            QPen pen( Qt::black, 0 );
            if ( mode == QwtPlotHistogram::Lines )
                pen.setBrush( histogram->brush() );

            histogram->setPen( pen );
        }
        else
        {
            histogram->setStyle( QwtPlotHistogram::Columns );

            QwtColumnSymbol *symbol = new QwtColumnSymbol( QwtColumnSymbol::Box );
            symbol->setFrameStyle( QwtColumnSymbol::Raised );
            symbol->setLineWidth( 2 );
            symbol->setPalette( QPalette( histogram->brush().color() ) );

            histogram->setSymbol( symbol );
        }
    }
}

void TVPlot::showItem( const QVariant &itemInfo, bool on )
{
    QwtPlotItem *plotItem = infoToItem( itemInfo );
    if ( plotItem )
        plotItem->setVisible( on );
}

