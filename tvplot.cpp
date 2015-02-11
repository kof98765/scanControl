#include "tvplot.h"


TVPlot::TVPlot( QWidget *parent ):
    QwtPlot( parent )
{

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setPalette( Qt::gray );
    canvas->setBorderRadius( 10 );
    setCanvas( canvas );
    QFont f;
    f.setPointSize(8);
    setAxisFont(QwtPlot::yLeft,f);
    setAxisFont(QwtPlot::xBottom,f);
    plotLayout()->setAlignCanvasToScales( true );


    //setAutoReplot( true );

}
void TVPlot::initPlot(QStringList str)
{
    populate_clear();
    //0,为纵坐标标题,1为横坐标标题,2为横坐标最大值,3为横坐标步长值
    setAxisTitle( QwtPlot::yLeft, str.at(0));
    setAxisTitle( QwtPlot::xBottom, str.at(1));
    setAxisScale(QwtPlot::xBottom,0,str.at(2).toDouble(),str.at(3).toDouble());
    step=str.at(3).toDouble();
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

}
TVPlot::~TVPlot()
{

}
void TVPlot::populate_clear()
{
    //data.setSamples(QVector<QwtIntervalSample>());
   // histogramJune->setData(&data);

    QwtPlotItemList items = itemList( QwtPlotItem::Rtti_PlotItem );
    if(items.size()>0)
    {
        for ( int i = 0; i < items.size(); i++ )
        {
            items[i]->detach();

        }
    }
    replot();

}
void TVPlot::populate(int Values[],int length,QString str)
{
    populate_clear();

    histogramJune = new QwtPlotHistogram(str);
    histogramJune->setStyle( QwtPlotHistogram::Columns );
    QColor c(Qt::red);
    c.setAlpha(180);
    histogramJune->setBrush(QBrush(c));
    histogramJune->attach( this );
    QVector<QwtIntervalSample> samples( length );

    for ( int i = 0; i < length; i++ )
    {
        QwtInterval interval( double( i*step ), double(i*step)+double(step) );

        samples[i] = QwtIntervalSample( Values[i], interval );

        QwtPlotMarker *mPos = new QwtPlotMarker();
        mPos->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        mPos->setItemAttribute( QwtPlotItem::AutoScale, true );
        //mPos->setSymbol( new ArrowSymbol() );
        mPos->setValue( QPointF( i*step, Values[i]+3 ) );
        mPos->setLabel( QString( "%1" ).arg( Values[i]) );
        mPos->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
        
        mPos->attach( this );

    }
    data.setSamples(samples);



    histogramJune->setData( &data);


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

