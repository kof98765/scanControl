#include "halconclass.h"

halconClass::detect_action halconClass::menu[]={&halconClass::one_white_line,
                       &halconClass::two_black_line,
                       &halconClass::three_black_block,
                       &halconClass::four_white_block,
                       &halconClass::five_black_block,
                       &halconClass::six_senve_night_white_line,
                       &halconClass::sixteen_white_line,
                       &halconClass::seventeen_white_line,
                       &halconClass::E128_detect
                                               };
halconClass::halconClass(QObject *parent) :
    QThread(parent),
    stopped(false),
    count(0),
    useDefault(true)
{
    set_system("do_low_error","false");
    posX=0;
    posY=0;

}
/*
    函数名:pointDetect
    参数:无
    返回值:无
    作用:
    图像上的白点检测
*/
void halconClass::pointDetect()
{

      // Local iconic variables
      Hobject  image, Image1, Image2, Image3, Region;
      // Local control variables
      HTuple  Width, Height, Number;

      read_image(&image, fileName.toUtf8().data());
      get_image_size(image, &Width, &Height);
      set_window_attr("background_color","black");



      if (HDevWindowStack::IsOpen())
        disp_obj(image, HDevWindowStack::GetActive());
      decompose3(image, &Image1, &Image2, &Image3);
      threshold(Image2, &Region, 128, 255);
      count_obj(Region, &Number);

}
void halconClass::open_the_window(int handle,int width,int height)
{

    if (HDevWindowStack::IsOpen())
         close_window(WindowHandle);
    open_window(0,0,width,height,handle,"visible","",&WindowHandle);
    HDevWindowStack::Push(WindowHandle);
    win_width=width;
    win_height=height;
}
void halconClass::disp_img(QString str)
{
    Hlong Width,Height;
    read_image(&Image,str.toUtf8().data());
    mirror_image(Image,&Image,"column");
    get_image_size(Image,&Width,&Height);
    if (HDevWindowStack::IsOpen())
    {
        set_part(WindowHandle,0,0,Width-1,Height-1);
        disp_obj(Image,WindowHandle);
        copy_image(Image,&result_img);
    }
    img_width=Width;
    img_height=Height;
    scale=img_width/win_width;
}
void halconClass::moveImg(int x,int y)
{
     Hobject  ImageTrans;
     // Local control variables
     HTuple  HomMat;

     if(HDevWindowStack::IsOpen())
     {
       //  clear_window(WindowHandle);
         set_part(WindowHandle,posY+y*scale,posX+x*scale,img_height+posY+y*scale,img_width+posX+x*scale);

         disp_obj(result_img,WindowHandle);
     }
        qDebug()<<posY+y*scale<<posX+x*scale<<img_height+posY+y*scale<<img_width+posX+x*scale;
     /*
     hom_mat2d_identity(&HomMat);
     hom_mat2d_translate(HomMat,posX,posY, &HomMat);
     affine_trans_image(Image, &ImageTrans, HomMat, "constant", "false");
     if (HDevWindowStack::IsOpen())
       clear_window(HDevWindowStack::GetActive());
     if (HDevWindowStack::IsOpen())
       disp_obj(ImageTrans, HDevWindowStack::GetActive());
*/

}
void halconClass::set_pos(int x,int y)
{
    posX+=x*scale;
    posY+=y*scale;

}
/*
    函数名:ZoomOut
    参数:无
    返回值:无
    作用:
    halcon显示窗口缩小,如果没有窗口打开,则无作用

*/
void halconClass::zoomOut()
{
    if (HDevWindowStack::IsOpen())
    {

        img_height*=0.8;
        img_width*=0.8;
        posX*=0.8;
        posY*=0.8;
      //  clear_window(WindowHandle);
        set_part(WindowHandle,posY,posX,HTuple(img_height)+posY,HTuple(img_width)+posX);
        disp_obj(result_img, HDevWindowStack::GetActive());

    }
}
/*
    函数名:ZoomIn
    参数:无
    返回值:无
    作用:
    halcon显示窗口放大,如果没有窗口打开,则无作用

*/
void halconClass::zoomIn()
{


    if (HDevWindowStack::IsOpen())
    {

        img_height*=1.2;
        img_width*=1.2;
        posX*=1.2;
        posY*=1.2;
        //clear_window(WindowHandle);
        set_part(WindowHandle,posY,posX,HTuple(img_height)+posY,HTuple(img_width)+posX);
        disp_obj(result_img, HDevWindowStack::GetActive());

    }
}


/*
    函数名:saveResult
    参数:无
    返回值:无
    作用:
    保存当前的图像,并显示结果

*/
void halconClass::saveResult()
{
    if(HDevWindowStack::IsOpen())
    {
        dump_window_image(&result_img,WindowHandle);
        clear_window(WindowHandle);
        set_part(WindowHandle,0,0,HTuple(img_height),HTuple(img_width));
        disp_obj(result_img, WindowHandle);

        set_tposition(WindowHandle,0,0);
        write_string(WindowHandle,"NG...");
        qDebug()<<"result";
    }
}


void halconClass::run()
{
        locker.lock();

        qDebug()<<"end detect";
        emit detectFinish();

        locker.unlock();

}

void halconClass::startThread()
{
    if(! isRunning())
    {
        stopped = false;

        start();
    }
}

void halconClass::stopThread()
{
    if(! isFinished())
    {
        stopped = true;
    }
}

void halconClass::one_white_line()
{

    // Local iconic variables
    Hobject  Regions, ConnectedRegions1, Contours3;
    Hobject  SelectedContours, Region, ImageReduced, SelectedContours1;
    Hobject  ObjectSelected, Region2, RegionComplement, Region1;
    Hobject  Contours, ConnectedRegions, SelectedRegions, result;
    Hobject  ObjectSelected1, Contours1;


    // Local control variables
    HTuple  Number1, Index, Number, Index1,Area,Row,Column,Length,PointOrder,Length1,Length2;


    disp_obj(Image,WindowHandle);
    auto_threshold(Image, &Regions, 2);
    connection(Regions, &ConnectedRegions1);
    gen_contour_region_xld(ConnectedRegions1, &Contours3, "border");
    select_contours_xld(Contours3, &SelectedContours, "contour_length", 900, 1200,
        -0.5, 0.5);
    gen_region_contour_xld(SelectedContours, &Region, "filled");
    reduce_domain(Image, Region, &ImageReduced);

    select_contours_xld(Contours3, &SelectedContours1, "contour_length", 150, 160,
        -0.5, 0.5);

    count_obj(SelectedContours1, &Number1);
    for (Index=1; Index<=Number1; Index+=1)
    {
      select_obj(SelectedContours1, &ObjectSelected, Index);
      gen_region_contour_xld(ObjectSelected, &Region2, "filled");
      complement(Region2, &RegionComplement);
      reduce_domain(ImageReduced, RegionComplement, &ImageReduced);
    }


    threshold(ImageReduced, &Region1, 70, 98);
    gen_contour_region_xld(Region1, &Contours, "border");

    connection(Region1, &ConnectedRegions);

    select_shape(ConnectedRegions, &SelectedRegions, "area", "and", 100, 1000);
    count_obj(SelectedRegions, &Number);
    gen_empty_obj(&result);
    for (Index1=1; Index1<=Number; Index1+=1)
    {
      select_obj(SelectedRegions, &ObjectSelected1, Index1);
      area_center(ObjectSelected1,&Area,&Row,&Column);
      dilation_circle(ObjectSelected1,&ObjectSelected1,3.5);
      gen_contour_region_xld(ObjectSelected1, &Contours1, "border");

      concat_obj(Contours1, result, &result);
     
     // emit badResult(0,Row[0].I(),Column[0].I(),Area[0].I());

    }

    set_color(WindowHandle,"red");
    if (HDevWindowStack::IsOpen())
      disp_obj(Image, WindowHandle);
    if (HDevWindowStack::IsOpen())
      disp_obj(SelectedContours, WindowHandle);
    if (HDevWindowStack::IsOpen())
      disp_obj(result, WindowHandle);
    dump_window_image(&result_img,WindowHandle);

    emit sumResult(0,Number[0].I());



}
void halconClass::two_black_line()
{
    Hobject   Regions, ConnectedRegions1, Contours3;
     Hobject  SelectedContours, Region, ImageReduced, SelectedContours1;
     Hobject  ObjectSelected, Region2, RegionComplement, Region1;
     Hobject  SelectedRegions1, result, ObjectSelected1, Contours1;


     // Local control variables
     HTuple  Number1, Index, Number, Index1, Area;
     HTuple  Row, Column;

    auto_threshold(Image, &Regions, 2);
      connection(Regions, &ConnectedRegions1);
      gen_contour_region_xld(ConnectedRegions1, &Contours3, "border");
      select_contours_xld(Contours3, &SelectedContours, "contour_length", 900, 1200,
          -0.5, 0.5);
      gen_region_contour_xld(SelectedContours, &Region, "filled");
      reduce_domain(Image, Region, &ImageReduced);

      select_contours_xld(Contours3, &SelectedContours1, "contour_length", 140, 160,
          -0.5, 0.5);

      count_obj(SelectedContours1, &Number1);
      for (Index=1; Index<=Number1; Index+=1)
      {
        select_obj(SelectedContours1, &ObjectSelected, Index);
        gen_region_contour_xld(ObjectSelected, &Region2, "filled");
        complement(Region2, &RegionComplement);
        reduce_domain(ImageReduced, RegionComplement, &ImageReduced);
      }


      fast_threshold(ImageReduced, &Region1, 35, 50, 20);
      connection(Region1, &ConnectedRegions1);

      select_shape(ConnectedRegions1, &SelectedRegions1, "area", "and", 150, 210);

      count_obj(SelectedRegions1, &Number);

      gen_empty_obj(&result);
      for (Index1=1; Index1<=Number; Index1+=1)
      {
        select_obj(SelectedRegions1, &ObjectSelected1, Index1);
        area_center(ObjectSelected1, &Area, &Row, &Column);
        dilation_circle(ObjectSelected1, &ObjectSelected1, 3.5);
        gen_contour_region_xld(ObjectSelected1, &Contours1, "border");


        concat_obj(Contours1, result, &result);
        // emit badResult(1,Row[0].I(),Column[0].I(),Area[0].I());
      }
      set_color(WindowHandle,"red");
      if (HDevWindowStack::IsOpen())
        disp_obj(Image, WindowHandle);
      if (HDevWindowStack::IsOpen())
        disp_obj(SelectedContours, WindowHandle);
      if (HDevWindowStack::IsOpen())
        disp_obj(result, WindowHandle);
      dump_window_image(&result_img,WindowHandle);

      emit sumResult(1,Number[0].I());

}
void halconClass::three_black_block()
{

}
void halconClass::four_white_block()
{

}
void halconClass::five_black_block()
{

}
void halconClass::six_senve_night_white_line()
{

}
void halconClass::eight_white_line()
{

}
void halconClass::sixteen_white_line()
{

}
void halconClass::seventeen_white_line()
{

}
void halconClass::E128_detect()
{
    // Local iconic variables
      Hobject  Region, RegionFillUp, ConnectedRegions;
      Hobject  RegionErosion, RegionDilation, ImageMean, ImageReduced;
      Hobject  RegionDynThresh_D, SelectedRegions, ObjectSelected1;
      Hobject  Rectangle, Circle;


      // Local control variables
      HTuple  ImgPath, AcqHandle, j, Number_Point, i,Area,Length1,Length2,Phi;
      HTuple  Mean2, Deviation2, Row1, Column1, Row21, Column21;
      HTuple  Mean3, Deviation3, Dev_Mean, Row, Column, Radius;


      // dev_update_off(...); only in hdevelop


        if (HDevWindowStack::IsOpen())
          set_colored(HDevWindowStack::GetActive(),12);
        if (HDevWindowStack::IsOpen())
          set_draw(HDevWindowStack::GetActive(),"fill");

        fast_threshold(Image, &Region, 100, 255, 0);
        fill_up_shape(Region, &RegionFillUp, "area", 1, 1200);
        connection(RegionFillUp, &ConnectedRegions);
        erosion_circle(ConnectedRegions, &RegionErosion, 5.5);
        connection(RegionErosion, &ConnectedRegions);
        select_shape(ConnectedRegions, &RegionDilation, "area", "and", 2000000, 45700000);

        if (HDevWindowStack::IsOpen())
          disp_obj(Image, HDevWindowStack::GetActive());

        //*** ֣ *****

        mean_image(Image, &ImageMean, 7, 7);
        reduce_domain(Image, RegionDilation, &ImageReduced);
        dyn_threshold(ImageReduced, ImageMean, &RegionDynThresh_D, 8, "dark");
        connection(RegionDynThresh_D, &ConnectedRegions);
        select_shape(ConnectedRegions, &SelectedRegions, ((HTuple("area").Append("width")).Append("height")),
            "and", ((HTuple(3).Append(2)).Append(2)), ((HTuple(250).Append(20)).Append(20)));
        count_obj(SelectedRegions, &Number_Point);

        if (HDevWindowStack::IsOpen())
          disp_obj(Image, HDevWindowStack::GetActive());
        j=0;
        for (i=1; i<=Number_Point; i+=1)
        {
              select_obj(SelectedRegions, &ObjectSelected1, i);
              intensity(ObjectSelected1, Image, &Mean2, &Deviation2);

              smallest_rectangle1(ObjectSelected1, &Row1, &Column1, &Row21, &Column21);
              gen_rectangle1(&Rectangle, Row1-2, Column1-2, Row21+2, Column21+2);
              intensity(Rectangle, Image, &Mean3, &Deviation3);
              Dev_Mean = Mean3-Mean2;

              if (0 != (HTuple(Deviation2>7).And(Dev_Mean>15)))
              {
                    smallest_rectangle2(ObjectSelected1,&Row,&Column,&Phi,&Length1,&Length2);
                    area_center(ObjectSelected1,&Area,&Row,&Column);
                    qDebug()<<minArea[0].D()<<maxArea[0].D();
                    if(!useDefault)
                    {
                        qDebug()<<((Area[0].I()*0.000625)>maxArea[0].D())<<(((Area[0].I()*0.000625)<minArea[0].D()));
                        if((
                                    ((Area[0].I()*0.000625)>maxArea[0].D())|
                                    ((Area[0].I()*0.000625)<minArea[0].D())
                             )
                           )
                            continue;

                    }

                    j+=1;
                    emit badResult(1,Row[0].I(),Column[0].I(),Length1[0].I(),Length2[0].I(),Area[0].I());
                    if (HDevWindowStack::IsOpen())
                      disp_obj(ObjectSelected1, HDevWindowStack::GetActive());
                    smallest_circle(ObjectSelected1, &Row, &Column, &Radius);

                    if (HDevWindowStack::IsOpen())
                      set_color(HDevWindowStack::GetActive(),"blue");
                    if (HDevWindowStack::IsOpen())
                      set_draw(HDevWindowStack::GetActive(),"margin");
                    gen_circle(&Circle, Row, Column, Radius+8);
                    if (HDevWindowStack::IsOpen())
                      disp_obj(Circle, HDevWindowStack::GetActive());

              }
        }
        emit sumResult(1,j[0].I());
        // stop(); only in hdevelop
        //dump_window (3600, 'bmp', ImgPath+'dump_amp_fushi'+'.bmp')


}

void halconClass::setMinMaxLength(double min,double max)
{
    minLength=HTuple(min);
    maxLength=HTuple(max);
}
void halconClass::setMinMaxArea(double min,double max)
{
    minArea=HTuple(min);
    maxArea=HTuple(max);
}
void halconClass::setUseDefault(bool def)
{
    useDefault=def;
}
