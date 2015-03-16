#include "checkthread.h"
#include "mainwindow.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QDebug>

checkThread::checkThread(QObject *parent) :
    QThread(parent),
    stopped(false),
    count(0)
{

    initVision();
 qDebug()<<"hello"<<"aaa";

    m_YM_AreaSmall   = 0, m_YM_AreaBig      = 0;
    m_YM_smoothWidth = 0, m_YM_SmoothHeight = 0;
    m_YM_OffSet      = 0;
}

void checkThread::startThread()
{
    if(! isRunning())
    {
        stopped = false;
        start();
    }
}

void checkThread::stopThread()
{
    if(! isFinished())
    {
        stopped = true;
    }
}

void checkThread::initVision()
{
    //hv_ImageFile = "//192.168.1.120/Save/Measurements/reflectCONTROL Compact/8-1_new_screen/20140801-083656+-1/";
    //hv_ImageFile = "//192.168.1.120/Save/Measurements/reflectCONTROL Compact/Default/R-L-7/L-7-1.1/";
    //open_framegrabber("File", 1, 1, 0, 0, 0, 0, "default", -1, "default", -1, "false", hv_ImageFile, "", 1, 2, &AcqHandle);

}

void checkThread::fillUpData(QString type, int num, int sum, double area, double width, double length)
{
    sent.type = type;
    sent.num = num;
    sent.sum = sum;
    sent.area = area;
    sent.width = width;
    sent.length = length;
    emit sendData(sent);
    msleep(2);
}

void checkThread::changeFilePath(HTuple path)
{
    hv_ImageFile = path;
    open_framegrabber("File", 1, 1, 0, 0, 0, 0, "default", -1, "default", -1, "false", hv_ImageFile, "", 1, 2, &AcqHandle);
}

void checkThread::run()
{    
    locker.lock();
    count++;
    /*
    int sum = 0;

    grab_image(&ho_ImageAmp, AcqHandle);
    grab_image(&Image_Base, AcqHandle);
    grab_image(&ho_ImageCurv, AcqHandle);
    disp_obj(ho_ImageAmp,winId1);
    disp_obj(ho_ImageCurv,winId2);

    //*********** 屏油墨区域检测 ****************
    set_draw(winId1,"fill");
    gray_histo(ho_ImageAmp, ho_ImageAmp, &hv_AbsoluteHisto, &hv_RelativeHisto);
    histo_to_thresh(hv_RelativeHisto, 10, &hv_MinThresh, &hv_MaxThresh);
    tuple_length(hv_MinThresh, &hv_Length);
    fast_threshold(ho_ImageAmp, &ho_Region, hv_MinThresh.SelectRank(1), hv_MinThresh.SelectRank(hv_Length-1), 1);
    fill_up_shape(ho_Region, &ho_RegionFillUp, "area", 1, 1200);
    connection(ho_RegionFillUp, &ho_ConnectedRegions);
    select_shape(ho_ConnectedRegions, &ho_RegionCheck, "area", "and", 20000, 1800000);
    erosion_circle(ho_RegionCheck, &ho_RegionCheck, 4.5);
    reduce_domain(ho_ImageAmp, ho_RegionCheck, &ho_ImageReducedA);
    intensity(ho_Region, ho_ImageAmp, &hv_Mean1, &hv_Deviation1);
    count_obj(ho_RegionCheck, &hv_Number1);

    edges_sub_pix(ho_ImageReducedA, &ho_Lines1, "canny", 1, 10, 30);
    union_adjacent_contours_xld(ho_Lines1, &ho_Lines1, 10, 1, "attr_keep");
    gen_region_contour_xld(ho_Lines1, &ho_Region, "filled");
    union1(ho_Region, &ho_Region);
    dilation_circle(ho_Region, &ho_Region, 3.5);
    connection(ho_Region, &ho_Region);
    select_shape(ho_Region, &ho_Region, (HTuple("area").Append("area")), "or", (HTuple(800).Append(4400)), (HTuple(1400).Append(5400)));
    difference(ho_RegionCheck, ho_Region, &ho_RegionCheck);
    dilation_circle(ho_RegionCheck, &ho_RegionCheck, 1.0);
    mean_image(ho_ImageAmp, &ho_ImageMean, 5, 5);
    reduce_domain(ho_ImageMean, ho_RegionCheck, &ho_ImageReducedM);
    dyn_threshold(ho_ImageReducedA, ho_ImageReducedM, &ho_RegionDynThresh, 9, "dark");

    connection(ho_RegionDynThresh, &ho_ConnectedRegions);
    select_shape(ho_ConnectedRegions, &ho_SelectedRegions, "area", "and", 12, 300);
    count_obj(ho_SelectedRegions, &hv_Number2);
    if (0 != hv_Number2)
    {
        HTuple end_val66 = hv_Number2;
        HTuple step_val66 = 1;
        sum =0;
        for (hv_i=1; hv_i.Continue(end_val66, step_val66); hv_i += step_val66)
        {
            set_color(winId1,"blue");
            select_obj(ho_SelectedRegions, &ho_ObjectSelected, hv_i);

            disp_obj(ho_ObjectSelected, winId1);
            area_center(ho_ObjectSelected, &hv_Area, &hv_Row2, &hv_Column2);
            smallest_rectangle2(ho_ObjectSelected, &hv_Row1, &hv_Column1, &hv_Phi1, &hv_Length11, &hv_Length21);
            sum++;
            fillUpData("youmo",count,sum,hv_Area[0].D()*0.01,hv_Length11[0].D()*0.2,hv_Length21[0].D()*0.2);
        }
    }
    //dump_window (3600, 'bmp', ImgPath+'dump_amp_youmo.bmp')


    //************* 屏透明区域检测 ********************
    set_draw(winId1,"fill");
    gray_histo(ho_ImageAmp, ho_ImageAmp, &hv_AbsoluteHisto, &hv_RelativeHisto);
    histo_to_thresh(hv_RelativeHisto, 20, &hv_MinThresh, &hv_MaxThresh);
    tuple_length(hv_MinThresh, &hv_Length);
    fast_threshold(ho_ImageAmp, &ho_Region, hv_MinThresh.SelectRank(hv_Length-1), hv_MaxThresh.SelectRank(hv_Length-1), 1);
    fill_up_shape(ho_Region, &ho_RegionFillUp, "area", 1, 900);

    connection(ho_RegionFillUp, &ho_ConnectedRegions);
    select_shape(ho_ConnectedRegions, &ho_RegionCheck, "area", "and", 10000, 1800000);
    erosion_circle(ho_RegionCheck, &ho_RegionCheck, 5.5);
    reduce_domain(ho_ImageAmp, ho_RegionCheck, &ho_ImageReducedA);

    //*******线条检测*******************
    set_colored(winId1,12);
    mean_image(ho_ImageReducedA, &ho_ImageMean, 3, 3);
    lines_gauss(ho_ImageMean, &ho_Lines, 0.7, 2, 6, "dark", "true", "gaussian", "true");
    select_contours_xld(ho_Lines, &ho_SelectedContours, "contour_length", 16, 2000, -0.5, 0.5);
    union_adjacent_contours_xld(ho_SelectedContours, &ho_UnionContours, 15, 1, "attr_keep");
    count_obj(ho_UnionContours, &hv_Number);

    if (0 != hv_Number)
    {
        segment_contours_xld(ho_UnionContours, &ho_ContoursSplit, "lines_circles", 2, 2, 1);
        gen_region_contour_xld(ho_ContoursSplit, &ho_RegionXLD, "filled");
        dilation_circle(ho_RegionXLD, &ho_RegionXLD, 1.5);
        HTuple end_val117 = hv_Number;
        HTuple step_val117 = 1;
        sum = 0;
        for (hv_i=1; hv_i.Continue(end_val117, step_val117); hv_i += step_val117)
        {
            set_color(winId1,"yellow");
            select_obj(ho_UnionContours, &ho_ObjectSelected, hv_i);
            disp_obj(ho_ObjectSelected, winId1);

            area_center_xld(ho_ObjectSelected, &hv_Area, &hv_Row, &hv_Column, &hv_PointOrder);
            length_xld(ho_ObjectSelected, &hv_Length_xld);

            sum++;
            fillUpData("line",count,sum,0,0,hv_Length_xld[0].D()*0.2);
        }
    }
    //dump_window (3600, 'bmp', ImgPath+'dump_amp_lines'+'.bmp')

    //*******点污检测*******************
    difference(ho_RegionCheck, ho_RegionXLD, &ho_RegionCheck);

    mean_image(ho_ImageAmp, &ho_ImageMean, 10, 10);
    reduce_domain(ho_ImageMean, ho_RegionCheck, &ho_ImageReducedM);
    dyn_threshold(ho_ImageReducedA, ho_ImageReducedM, &ho_RegionDynThresh, 9, "dark");

    connection(ho_RegionDynThresh, &ho_ConnectedRegions);
    select_shape(ho_ConnectedRegions, &ho_SelectedRegions, "area", "and", 7, 500);
    intensity(ho_SelectedRegions, ho_ImageAmp, &hv_Mean, &hv_Deviation);
    count_obj(ho_SelectedRegions, &hv_Number);

    set_draw(winId1,"margin");

    if (0 != (hv_Number>0))
    {
        HTuple end_val154 = hv_Number;
        HTuple step_val154 = 1;
        sum =0;
        for (hv_i=1; hv_i.Continue(end_val154, step_val154); hv_i += step_val154)
        {
            select_obj(ho_SelectedRegions, &ho_ObjectSelected, hv_i);
            intensity(ho_ObjectSelected, ho_ImageAmp, &hv_Mean, &hv_Deviation);

            if (0 != (hv_Mean<((hv_MinThresh.SelectRank(hv_Length-1))+36)))
            {
                set_color(winId1,"blue");
                disp_obj(ho_ObjectSelected, winId1);

                area_center(ho_ObjectSelected, &hv_Area, &hv_Row2, &hv_Column2);
                smallest_rectangle2(ho_ObjectSelected, &hv_Row1, &hv_Column1, &hv_Phi1, &hv_Length11, &hv_Length21);

                sum++;
                fillUpData("point",count,sum,hv_Area[0].D()*0.01,hv_Length11[0].D()*0.2,hv_Length21[0].D()*0.2);
            }
        }
    }
    //***************************************************
    //***************************************************
    //dump_window (3600, 'bmp', ImgPath+'dump_amp_points.bmp')

    //**************************************************
    //****** curv check ********************************
    //*** heiquan check ********
    set_draw(winId2,"fill");
    set_colored(winId2,12);
    disp_obj(ho_ImageCurv, winId2);
    union2(ho_RegionCheck, ho_RegionXLD, &ho_RegionCheck);
    erosion_circle(ho_RegionCheck, &ho_RegionCheckCurv, 11);
    mean_image(ho_ImageCurv, &ho_ImageMean, 5, 5);
    reduce_domain(ho_ImageMean, ho_RegionCheckCurv, &ho_ImageReduced);
    lines_gauss(ho_ImageReduced, &ho_Lines, 0.5, 5, 19, "light", "true", "bar-shaped", "true");
    union_adjacent_contours_xld(ho_Lines, &ho_UnionContours, 0, 1, "attr_keep");
    select_contours_xld(ho_UnionContours, &ho_SelectedContours, "closed", 0, 0.5, -0.5, 0.5);
    gen_region_contour_xld(ho_SelectedContours, &ho_Region, "filled");
    smallest_circle(ho_Region, &hv_Row, &hv_Column, &hv_Radius);
    //disp_obj(ho_ImageCurv, winId2);
    //disp_obj(ho_Region, winId2);
    set_color(winId2,"blue");
    set_draw(winId2,"margin");
    if (0 != ((hv_Row.Num())>0))
    {
        gen_circle(&ho_Circle, hv_Row, hv_Column, hv_Radius+5);
    }

    //stop ()
    //*** heikuai check ********
    set_draw(winId2,"fill");
    mean_image(ho_ImageCurv, &ho_ImageMean, 3, 3);
    reduce_domain(ho_ImageMean, ho_RegionCheckCurv, &ho_ImageReduced);
    intensity(ho_RegionCheckCurv, ho_ImageReduced, &hv_Mean, &hv_Deviation);
    fast_threshold(ho_ImageReduced, &ho_Region, 0, hv_Mean-25, 0);
    connection(ho_Region, &ho_ConnectedRegions);
    select_shape(ho_ConnectedRegions, &ho_SelectedRegions, "area", "and", 10, 65);

    count_obj(ho_SelectedRegions, &hv_Number);
    if (0 != hv_Number)
    {
        HTuple end_val222 = hv_Number;
        HTuple step_val222 = 1;
        sum =0;
        for (hv_i=1; hv_i.Continue(end_val222, step_val222); hv_i += step_val222)
        {
            select_obj(ho_SelectedRegions, &ho_ObjectSelected, 1);
            intensity(ho_ObjectSelected, ho_ImageReduced, &hv_Mean1, &hv_Deviation1);
            if (0 != ((hv_Mean-hv_Mean1)>18))
            {
                dilation_circle(ho_ObjectSelected, &ho_Dilation, 1.5);
                set_draw(winId2,"fill");
                set_color(winId2,"red");
                disp_obj(ho_Dilation, winId2);
                set_draw(winId2,"margin");
                set_color(winId2,"yellow");
                smallest_circle(ho_Dilation, &hv_Row, &hv_Column, &hv_Radius);
                gen_circle(&ho_Circle, hv_Row, hv_Column, hv_Radius+8);
                disp_obj(ho_Circle, winId2);

                sum++;
                fillUpData("heikuai",count,sum,0,0,0);
            }
        }
    }


    //stop ()
    //*** baikuai check ********
    set_draw(winId2,"fill");
    mean_image(ho_ImageCurv, &ho_ImageMean, 3, 3);
    reduce_domain(ho_ImageMean, ho_RegionCheckCurv, &ho_ImageReduced);
    intensity(ho_RegionCheckCurv, ho_ImageReduced, &hv_Mean3, &hv_Deviation3);

    fast_threshold(ho_ImageReduced, &ho_Region, hv_Mean3+30, 255, 0);
    connection(ho_Region, &ho_ConnectedRegions);
    select_shape(ho_ConnectedRegions, &ho_SelectedRegions, "area", "and", 15, 1385);
    count_obj(ho_SelectedRegions, &hv_Number_White);
    //dev_display (ImageCurv)
    HTuple end_val259 = hv_Number_White;
    HTuple step_val259 = 1;
    sum =0;
    for (hv_i=1; hv_i.Continue(end_val259, step_val259); hv_i += step_val259)
    {
        select_obj(ho_SelectedRegions, &ho_ObjectSelected1, hv_i);
        intensity(ho_ObjectSelected1, ho_ImageCurv, &hv_Mean2, &hv_Deviation2);
        if (0 != (hv_Deviation2>15))
        {
            set_draw(winId2,"fill");
            set_color(winId2,"red");
            disp_obj(ho_ObjectSelected1, winId2);
            set_draw(winId2,"margin");
            set_color(winId2,"blue");
            smallest_circle(ho_ObjectSelected1, &hv_Row, &hv_Column, &hv_Radius);
            gen_circle(&ho_Circle, hv_Row, hv_Column, hv_Radius+8);
            disp_obj(ho_Circle, winId2);

            smallest_rectangle2(ho_ObjectSelected1, &hv_Row2, &hv_Column2, &hv_Phi,
                                &hv_Length11, &hv_Length21);
            area_center(ho_ObjectSelected1, &hv_Area, &hv_Row2, &hv_Column2);

            sum++;
            fillUpData("baikuai",count,sum,hv_Area[0].D()*0.01,hv_Length11[0].D()*0.2,hv_Length21[0].D()*0.2);


            //            set_tposition(3600, hv_Row2-40, hv_Column2+5);
            //            write_string(3600, "area:"+((hv_Area*0.1)*0.1));
            //            set_tposition(3600, hv_Row2, hv_Column2+5);
            //            write_string(3600, "length:"+(hv_Length11*0.2));
            //            set_tposition(3600, hv_Row2+40, hv_Column2+5);
            //            write_string(3600, "width:"+(hv_Length21*0.2));
        }
    }

    // stop(); only in hdevelop
    //** yuanfan check *******
    mean_image(ho_ImageCurv, &ho_ImageMean, 7, 7);
    erosion_circle(ho_RegionCheckCurv, &ho_RegionCheckCurv1, 8.5);
    reduce_domain(ho_ImageMean, ho_RegionCheckCurv1, &ho_ImageReduced);
    edges_sub_pix(ho_ImageReduced, &ho_Edges, "canny", 3.9, 5, 13);
    segment_contours_xld(ho_Edges, &ho_ContoursSplit, "lines", 12, 10, 5);
    select_contours_xld(ho_ContoursSplit, &ho_SelectedContours, "contour_length", 53, 2000, -0.5, 0.5);
    gen_region_contour_xld(ho_SelectedContours, &ho_Region, "margin");
    dilation_circle(ho_Region, &ho_RegionDilation, 5.5);
    union1(ho_RegionDilation, &ho_RegionUnion);
    connection(ho_RegionUnion, &ho_ConnectedRegions);
    erosion_circle(ho_ConnectedRegions, &ho_RegionErosion, 1.5);
    count_obj(ho_RegionErosion, &hv_Number_Yuanfan);

    //dev_display (ImageCurv)
    //dev_set_draw ('fill')
    if (0 != (hv_Number_Yuanfan>0))
    {
        disp_obj(ho_RegionErosion, winId2);
        HTuple end_val301 = hv_Number_Yuanfan;
        HTuple step_val301 = 1;
        sum =0;
        for (hv_i=1; hv_i.Continue(end_val301, step_val301); hv_i += step_val301)
        {
            select_obj(ho_RegionErosion, &ho_ObjectSelected1, hv_i);

            //smallest_circle(ho_ObjectSelected1, &hv_Row, &hv_Column, &hv_Radius);
            smallest_rectangle2(ho_ObjectSelected1, &hv_Row2, &hv_Column2, &hv_Phi, &hv_Length11, &hv_Length21);
            area_center(ho_ObjectSelected1, &hv_Area, &hv_Row2, &hv_Column2);

            sum++;
            fillUpData("yuanfan",count,sum,hv_Area[0].D()*0.01,hv_Length11[0].D()*0.2,hv_Length21[0].D()*0.2);

            //            set_tposition(3600, hv_Row2-40, hv_Column2+5);
            //            write_string(3600, "area:"+((hv_Area*0.1)*0.1));
            //            set_tposition(3600, hv_Row2, hv_Column2+5);
            //            write_string(3600, "length:"+(hv_Length11*0.2));
            //            set_tposition(3600, hv_Row2+40, hv_Column2+5);
            //            write_string(3600, "width:"+(hv_Length21*0.2));
        }
    }
    //*************************************************************
    //*************************************************************
    //dump_window (3600, 'bmp', ImgPath+'dump_amp_yuanfan'+'.bmp')

    locker.unlock();
    //
    */
}


