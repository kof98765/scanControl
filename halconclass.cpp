#include "halconclass.h"


halconClass::halconClass(QObject *parent) :
    QThread(parent),
    stopped(false),
    count(0),
    useDefault(true)
{
    set_system("do_low_error","false");
    posX=0;
    posY=0;
    step=0;
    recvCount=0;
    is3D=false;
    hasData=false;
    imgData=new double[1280000];
    detect_action tmp[9]={&halconClass::one_white_line,
                           &halconClass::two_black_line,
                           &halconClass::three_black_block,
                           &halconClass::four_white_block,
                           &halconClass::five_black_block,
                           &halconClass::six_senve_night_white_line,
                           &halconClass::sixteen_white_line,
                           &halconClass::seventeen_white_line,
                           &halconClass::E128_detect
                                                   };
    hInstance = LoadLibrary("PCL_Library_Dll.dll");



    inCloud=new PointCloud::Ptr(new PointCloud );
    memcpy(menu,tmp,sizeof(tmp));
    roiList=set.value("roiList").toMap();

    emit flushRoiList(roiList.keys());
}
/*
    打开一个窗口
*/
void halconClass::open_the_window(int handle,int width,int height)
{

    Hobject Rectangle;
    close_the_window();

    open_window(0,0,width,height,handle,"visible","",&WindowHandle);
    HDevWindowStack::Push(WindowHandle);
    set_part(WindowHandle,0,0,1024-1,1280-1);
    disp_img();
    emit flushRoiList(roiList.keys());
    win_width=width;
    win_height=height;
}
/*
   打开新窗口前,关闭所有窗口
*/
void halconClass::close_the_window()
{
    if (HDevWindowStack::IsOpen())
    {

        HDevWindowStack::CloseAll();
    }
}
/*
    启动线程,读取图像文件
*/
void halconClass::read_img(QString str)
{

   path=str;
   this->start();
}
void halconClass::clearData()
{
    hasData=false;
    Image.Reset();

    if (HDevWindowStack::IsOpen())
        clear_window(WindowHandle);

}
/*
    重置图像窗口,并刷新数据
*/
void halconClass::reset()
{
    Hlong Width,Height;
    posX=0;
    posY=0;

    if (HDevWindowStack::IsOpen()&hasData)
    {
        get_image_size(Image,&Width,&Height);
        img_height=Height;
        img_width=Width;
        clear_window(WindowHandle);
        set_part(WindowHandle,0,0,Height-1,Width-1);
        disp_obj(result_img,WindowHandle);
        this->threedControl(0,0,0,0,"rotate");

    }
}
/*
    设置halcon的窗口显示模式
*/
void halconClass::setMode(QString str)
{
    if (HDevWindowStack::IsOpen()&hasData)
    {
        if(str.contains("2D"))
        {
               clear_window(WindowHandle);
               set_lut(WindowHandle,"rainbow");
               set_paint(HDevWindowStack::GetActive(),"default");
               disp_obj(Image,WindowHandle);
               copy_image(Image,&result_img);
                is3D=false;
        }
        else
        {
            is3D=true;
            clear_window(WindowHandle);
           // set_paint(HDevWindowStack::GetActive(),"3d_plot");
            set_lut(WindowHandle,"rainbow");
            set_window_param(WindowHandle,"display_grid","false");
           set_paint(WindowHandle, ((HTuple("3d_plot").Concat("shaded")).Concat(1)).Concat("auto"));
            disp_obj(Image,WindowHandle);
            copy_image(Image,&result_img);
        }
    }
}
void halconClass::disp_img()
{

    Hobject Rectangle;
    roiList=set.value("roiList").toMap();
   // mirror_image(Image,&Image,"column");

    if (HDevWindowStack::IsOpen())
        clear_window(WindowHandle);
    if (HDevWindowStack::IsOpen()&hasData)
    {
        set_lut(WindowHandle,"rainbow");

        if(is3D)
        {
            disp_obj(Image,WindowHandle);
            copy_image(Image,&result_img);
            set_window_param(WindowHandle,"interactive_plot", "true");
            qDebug()<<"disp_3d";
        }
        else
        {
            disp_obj(Image,WindowHandle);
            copy_image(Image,&result_img);
            qDebug()<<"disp_2d";
        }


    }

    if(HDevWindowStack::IsOpen())
    {

        //显示矩形窗口
        QStringList list=roiList.keys();

        if(list.size()==0)
            return;
        for(int i=0;i<list.size();i++)
        {
            QStringList str=roiList.value(list.at(i)).toStringList();
            set_color(WindowHandle,str.at(0).toUtf8().data());
            set_tposition(WindowHandle,str.at(1).toInt(),str.at(2).toInt());
            write_string(WindowHandle,HTuple(list.at(i).toUtf8().data()));
            Hobject Rectangle,Contours;
            gen_rectangle1(&Rectangle, (Hlong)str.at(1).toInt(), (Hlong)str.at(2).toInt(),(Hlong)str.at(3).toDouble(), (Hlong)str.at(4).toInt());
            gen_contour_region_xld(Rectangle,&Contours,"border");
            disp_obj(Contours,WindowHandle);
            //计算高差
            if(recvCount==set.value("profileCount",0).toInt())
                RectHeightSub();
        }

    }

}
void halconClass::moveImg(int x,int y)
{
    static int count=0;
     Hobject  ImageTrans;
     // Local control variables
     HTuple  HomMat;

     if(HDevWindowStack::IsOpen()&hasData)
     {
        if(!is3D)
        {
             set_part(WindowHandle,posY+y*scale,posX+x*scale,img_height+posY+y*scale,img_width+posX+x*scale);

             disp_img();
        }

     }

     /*
      矩阵变换相关代码
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
    if(!HDevWindowStack::IsOpen())
        return;
    if(!is3D&hasData)
    {
        posX+=x*scale;
        posY+=y*scale;
        disp_img();
    }
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
    if (HDevWindowStack::IsOpen()&hasData)
    {

        img_height*=0.8;
        img_width*=0.8;
        posX*=0.8;
        posY*=0.8;
        clear_window(WindowHandle);
        set_part(WindowHandle,posY,posX,HTuple(img_height)+posY,HTuple(img_width)+posX);
        disp_img();

    }
}
/*
    函数名:ZoomIn
    参数:无
    返回值:无
    作用:
    halcon显示窗口放大,如果没有窗口打开,则无作用

*/k
void halconClass::zoomIn()
{

    if (HDevWindowStack::IsOpen()&hasData)
    {

        img_height*=1.2;
        img_width*=1.2;
        posX*=1.2;
        posY*=1.2;
        clear_window(WindowHandle);
        set_part(WindowHandle,posY,posX,HTuple(img_height)+posY,HTuple(img_width)+posX);
        disp_img();
    }
}
void halconClass::threedControl(double lastRow, double lastCol, double Row, double Column,QString mode)
{

    if(!is3D|!hasData)
        return;
    if(!HDevWindowStack::IsOpen())
        return;

   // qDebug()<<mode<<Column<<Row<<lastCol<<lastRow;
    update_window_pose(WindowHandle, lastRow*scale, lastCol*scale, Row*scale, Column*scale, mode.toUtf8().data());
    disp_obj(result_img,WindowHandle);


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
    if(HDevWindowStack::IsOpen()&hasData)
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
    if(path.endsWith("mtx"))
    {
        readMTX(path);

        emit dispImg();
    }
    else
    {
        HTuple Width,Height;
        read_image(&Image,path.toUtf8().data());

        get_image_size(Image,&Width,&Height);
        set_part(WindowHandle,0,0,Height-1,Width-1);

        img_width=Width[0].I();
        img_height=Height[0].I();
        scale=Width[0].I()/win_width;
        hasData=true;
        qDebug()<<"read finish";
        emit dispImg();


    }

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
      set_color(WindowHandle,"red");
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
      Hobject Contours1;

      // Local control variables
      HTuple  ImgPath, AcqHandle, j, Number_Point, i,Area,Length1,Length2,Phi;
      HTuple  Mean2, Deviation2, Row1, Column1, Row21, Column21;
      HTuple  Mean3, Deviation3, Dev_Mean, Row, Column, Radius;


      // dev_update_off(...); only in hdevelop

        readSettings();
        if (HDevWindowStack::IsOpen())
          set_colored(HDevWindowStack::GetActive(),12);
        if (HDevWindowStack::IsOpen())
          set_draw(HDevWindowStack::GetActive(),"fill");

        fast_threshold(Image, &Region, minGray, maxGray, 0);
        fill_up_shape(Region, &RegionFillUp, "area", 1, 1200);
        connection(RegionFillUp, &ConnectedRegions);
        erosion_circle(ConnectedRegions, &RegionErosion, erosion);
        connection(RegionErosion, &ConnectedRegions);
        select_shape(ConnectedRegions, &RegionDilation, "area", "and", checkMinArea, checkMaxArea);
        gen_contour_region_xld(RegionDilation, &Contours1, "border");

        if (HDevWindowStack::IsOpen())
          disp_obj(Image, HDevWindowStack::GetActive());

        //*** ֣ *****

        mean_image(Image, &ImageMean, smothWidth, smothHeight);
        reduce_domain(Image, RegionDilation, &ImageReduced);
        dyn_threshold(ImageReduced, ImageMean, &RegionDynThresh_D, grayDvalue, "dark");
        connection(RegionDynThresh_D, &ConnectedRegions);
        select_shape(ConnectedRegions, &SelectedRegions, (((HTuple("area").Append("width")).Append("height")).Append("outer_radius")),
            "and", (((HTuple(badMinArea).Append(badMinWidth)).Append(badMinHeight)).Append(badMinRadius)), HTuple(badMaxArea).Append(badMaxWidth).Append(badMaxHeight).Append(badMaxradius));
        count_obj(SelectedRegions, &Number_Point);

        if (HDevWindowStack::IsOpen())
        {

          disp_obj(Image, HDevWindowStack::GetActive());
          disp_obj(Contours1,HDevWindowStack::GetActive());
        }

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

                    if(!useDefault)
                    {

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
                      set_color(HDevWindowStack::GetActive(),"red");
                    if (HDevWindowStack::IsOpen())
                      set_draw(HDevWindowStack::GetActive(),"margin");
                    gen_circle(&Circle, Row, Column, Radius+12);
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
/*
函数名:readMTX
参数:str 矩阵文件名
作用:读取一个矩阵文件,并生成一个test.tiff原始图像,并且生成一个彩虹色图像以供显示


*/
void halconClass::readMTX(QString str)
{

      // Local control variables
      HTuple  MatID, Rows, Cols, Values, MultValues;
      HTuple  Min, Max, Row, Column,Range,GrayVal,Value,i,j,Width,Height;
      Hobject Region,Imagetemp,Image1,Image2, Image3;
      time.start();
      read_matrix(str.toUtf8().data(), &MatID);
      qDebug()<<QStringLiteral("读取矩阵的时间:")<<time.elapsed()<<"msec";

      get_size_matrix(MatID, &Rows, &Cols);
      get_full_matrix(MatID, &Values);

      gen_image_const(&Image, "real", Cols, Rows);
      get_region_points(Image, &Row, &Column);
      set_grayval(Image, Row, Column, Values);
      //write_image(Image,"tiff",0,"test");

      qDebug()<<QStringLiteral("转换时间:")<<time.elapsed()<<"msec";
    hasData=true;

}
void halconClass::test()
{
    /*
    pcl::PointCloud<pcl::PointXYZ>::Ptr inCloud(new pcl::PointCloud<pcl::PointXYZ>);
    for (float x = -5.0; x <= 5.0; x += 0.25)
    {
        for (float y = -5.0; y <= 5.0; y += 0.1)
        {
            pcl::PointXYZ cloud;

            cloud.x = x;
            cloud.y = y;
            //cloud.z = 1+(float)rand();
            cloud.z = 1+x;
            inCloud->push_back(cloud);
        }
    }

    pcl::io::savePCDFile("plane_cloud_out.pcd", *inCloud);
    */

    this->calculatePlaneness();


}
void halconClass::clearRect()
{

}
void halconClass::delRect(int index)
{
    QStringList list=roiList.keys();

    roiList.remove(list.at(index));
    set.setValue("roiList",roiList);
    set.sync();
    disp_img();
}
void halconClass::drawRect(QString name,QString color)
{
    int i=0;
    Hobject Rectangle;
    if(name.isEmpty())
        name="rect";
    while(roiList.contains(name))
    {

        name=QString("%1_%2").arg(name.mid(0,name.lastIndexOf("_"))).arg(i++);
    }
    HTuple  Row, Column, Row2, Column2,Length2, Max;
    
    set_color(WindowHandle,color.toUtf8().data());

    draw_rectangle1(WindowHandle,&Row,&Column,&Row2,&Column2);
    qDebug()<<Row[0].I()<<Column[0].I()<<Row2[0].I()<<Column2[0].I();

   //写入配置文件
    QStringList str;
    str<<color;
    str<<QString::number(Row[0].I());
    str<<QString::number(Column[0].I());
    str<<QString::number(Row2[0].I());
    str<<QString::number(Column2[0].I());

    roiList.insert(name,QVariant(str));
    set.setValue("roiList",roiList);
    set.sync();

    //更新界面
    disp_img();
    emit flushRoiList(roiList.keys());
}

void halconClass::RectHeightSub()
{
    QTime time;
    time.start();
   if (HDevWindowStack::IsOpen()&hasData)
    {
        Hobject   Rectangle, RegionComplement, ImageReduced,rect;
        HTuple  Row1, Column1, Row2, Column2, Min, Max,Indices;
        HTuple Rows,Columns,Grayval;
        HTuple  Range,String,s,Result,Number;
        QStringList list=roiList.keys();
        for(int i=0;i<list.size();i++)
        {
            QStringList str=roiList.value(list.at(i)).toStringList();
            gen_rectangle1(&Rectangle, str.at(1).toInt(), str.at(2).toInt(), str.at(3).toInt(), str.at(4).toInt());

            reduce_domain(Image, Rectangle, &ImageReduced);


            get_region_points(ImageReduced, &Rows, &Columns);
            get_grayval(ImageReduced, Rows, Columns, &Grayval);

            tuple_max(Grayval, &Max);

            tuple_find(Grayval,0,&Indices);
            if(Indices[0].I()!=-1)
            {
                for(int i=0;i<Indices.Num();i++)
                {

                    Grayval[Indices[i].I()]=Max;
                }
            }


            tuple_min(Grayval,&Min);

            tuple_sub(Max,Min,&Range);
            qDebug()<<Min[0].D()<<Max[0].D()<<Range[0].D();
            emit sendHeightSub(list.at(i),Min[0].D(),Max[0].D(),Range[0].D());
        }


    }
    qDebug()<<QStringLiteral("计算高差时间:")<<time.elapsed()<<"ms";
}
void halconClass::calculatePlaneness()
{
    QTime time;
    time.start();
    double result;
    typedef int (*Calculate)(PointCloud::Ptr &inCloud, double &_result);
    Calculate cal=NULL;
    cal=(Calculate)GetProcAddress(hInstance,"CalculateFlatness");
    if (HDevWindowStack::IsOpen()&hasData)
    {
        Hobject   Rectangle;

        char     type[128];
        QStringList list=roiList.keys();
        for(int i=0;i<list.size();i++)
        {
            QStringList str=roiList.value(list.at(i)).toStringList();

            PointCloud::Ptr newCloud;

            for(int i=str.at(1).toInt();i<str.at(3).toInt();i++)
            {
                for(int j=str.at(2).toInt();i<str.at(4).toInt();i++)
                {
                    newCloud.get()->push_back((*inCloud).get()[i][j]);
                }
            }


            qDebug()<<"cal";
            (*cal)(newCloud,result);



        }
     }
    qDebug()<<QStringLiteral("平整度为")<<result<<"/n"<<QStringLiteral("计算平面度时间:")<<time.elapsed()<<"ms";
}
void halconClass::readSettings()
{

    badMinArea=set.value("badMinArea",3).toInt();
    badMaxArea=set.value("badMaxArea",200).toInt();
    badMaxHeight=set.value("badMaxHeight",40).toInt();
    badMaxWidth=set.value("badMaxWidth",40).toInt();
    badMinHeight=set.value("badMinHeight",2).toInt();
    contrast=set.value("contrast",1.0).toDouble();
    grayDvalue=set.value("grayDvalue",20).toInt();
    checkMinArea=set.value("checkMinArea",2000000).toInt();
    badMinWidth=set.value("badMinWidth",2).toInt();
    checkMaxArea=set.value("checkMaxArea",45700000).toInt();
    erosion=set.value("erosion",200).toInt();
    badMaxradius=set.value("badMaxradius",10).toInt();
    minGray=set.value("minGray",100).toInt();
    maxGray=set.value("maxGray",255).toInt();
    badMinRadius=set.value("badMinRadius",1).toInt();
    smothWidth=set.value("smothWidth",7).toInt();
    smothHeight=set.value("smothHeight",7).toInt();

}
void halconClass::getImagebyPointer3(double *x,double *y,double *z,const int w,const int h)
{
    time.start();
    Hobject Image,Image2,Image3;
    float *pointer,*pointer2,*pointer3;
    unsigned short *p;
    Hlong width,height;
    char     type[128];
    HTuple Row,Column;

    qDebug()<<"start pointCloud"<<w<<h;
    typedef void (*Transfer2Cloud)(double* X,double* Y,double* Z,unsigned short* I,const int col,const int row,PointCloud::Ptr inCloud);
    Transfer2Cloud test_function =NULL;
    test_function = (Transfer2Cloud)GetProcAddress(hInstance, "Transfer2Cloud");
    double *yy=new double[h];
    for(int i=0;i<h;i++)
    {
         yy[i]=i;
    }

    //(*test_function)(x,yy,z,0,w,h,*inCloud);
    qDebug()<<"end pointCloud";
    delete yy;
    return;
    p=(unsigned short *)y;
    gen_image_const(&Image,"real",w,h);
    gen_image_const(&Image2,"real",w,h);
    gen_image_const(&Image3,"real",w,h);

    get_image_pointer1(Image,(long*)&pointer,type,&width,&height);
    get_image_pointer1(Image2,(long*)&pointer2,type,&width,&height);
    get_image_pointer1(Image3,(long*)&pointer3,type,&width,&height);

    for (int row=0; row<height; row++)
    {
      for (int col=0; col<width; col++)
      {

        pointer[row*width+col] =*x++;
        pointer2[row*width+col] =*p++;
        pointer3[row*width+col] =*z++;
      }

    }
    write_image(Image,"tiff",0,"1");
    write_image(Image2,"tiff",0,"2");
    write_image(Image3,"tiff",0,"3");
    compose3(Image,Image2,Image3,&Image);

    write_image(Image,"tiff",0,"gray");

    qDebug()<<QStringLiteral("生成TIFF文件时间:")<<time.elapsed()<<"msec";
}

void halconClass::getImagebyPointer1(double *pdValueZ,int w,int h)
{
    HTuple  MatID, Rows, Cols, Values, MultValues;
    HTuple  Min, Max, Row, Column,Range,GrayVal,Value,i,j,Width,Height;
    Hobject Region,Imagetemp,Image1,Image2, Image3;
  //  double *p=imgData;
    recvCount=h;

  //  if((recvCount+h)>1000)
    //    recvCount=0;

   // memcpy(&imgData[recvCount*1280],pdValueZ,w*h);
  //  recvCount+=h;
    qDebug()<<"recv:"<<h;
    char     type[128];
    Hlong     width,height;
    float *pointer=0;
    time.start();
    Image.Reset();

    gen_image_const(&Image,"real",w,1000);
    get_image_pointer1(Image,(long*)&pointer,type,&width,&height);
    qDebug()<<width<<height;


    for (int row=0; row<h; row++)
    {
        for (int col=0; col<width; col++)
        {

          pointer[row*width+col] =*pdValueZ++;
        }
    }
    qDebug()<<"read time:"<<time.elapsed()<<"msec";


  //  write_image(RGBImage,"bmp",0,"test.bmp");
    write_image(Image,"tiff",0,"test");
    /*
    threshold(Image, &Region, 1, 255);
    min_max_gray(Region, Image, 0, &Min, &Max, &Range);
    qDebug()<<"img"<<Min[0].D()<<Max[0].D()<<Range[0].D();
    gen_image_const (&Imagetemp, "byte", w, h);
 //   gen_image_const(&Image, "real", Cols, Rows);
    cfa_to_rgb(Imagetemp, &RGBImage, "bayer_gb", "bilinear");
    decompose3(RGBImage, &Image1, &Image2, &Image3);

    get_image_size(RGBImage,&Width,&Height);


    img_width=Width[0].I();
    img_height=Height[0].I();
    scale=Width[0].I()/win_width;

   // cfa_to_rgb (Image, &Image, "bayer_gb", "bilinear");
    HTuple step=Range/6;

    HTuple RGBValue;
    for(i=0;i<h-1;i++)
    {
        for(j=0;j<w-1;j++)
        {
            get_grayval(Image,i,j,&GrayVal);

            Value=(GrayVal-Min)/step;

            tuple_int (Value, &Value);

            RGBValue.Reset();
            switch (Value[0].I())
            {
                default:
                RGBValue.Append(0);
                RGBValue.Append(0);
                RGBValue.Append(0);
                break;

                case 0:
                    //RGBValue=[128-GrayValue*128/Standard,0,255];
                      RGBValue.Append(128-(GrayVal-Min)*128/step);
                      RGBValue.Append(0);
                      RGBValue.Append(255);

                      break;
                case 1:
                  //  RGBValue:=[0,(GrayValue-Standard)*255/Standard,255];
                    //  *ptr|=HTuple(0<<16+((GrayVal-Min-step)*255/step)<<8+255)[0].I();
                      RGBValue.Append(0);
                      RGBValue.Append(((GrayVal-Min-step)*255/step));
                      RGBValue.Append(255);

                      break;
                case 2:
                    //RGBValue:=[0,255,255-(GrayValue-Standard*2)*255/Standard];
                    //  *ptr|=HTuple(0<<16+255<<8+255-((GrayVal-Min)/step*255-step*255))[0].I();
                      RGBValue.Append(0);
                      RGBValue.Append(255);
                      RGBValue.Append(255-((GrayVal-Min)/step*255-step*255));
                      break;
                case 3:
                 //   RGBValue:=[(GrayValue-Standard*3)*255/Standard,255,0];
                     // *ptr|=HTuple((GrayVal-Min-step*3)*255/step<<16+255<<8)[0].I();
                      RGBValue.Append(((GrayVal-Min-step*3)*255/step));
                      RGBValue.Append(255);
                      RGBValue.Append(0);
                      break;
                case 4:
                 //   RGBValue:=[255,255-(GrayValue-Standard*4)*128/Standard,0];
                   //   *ptr|=HTuple(255<<16+(255-(GrayVal-Min-step*4)*128/step)<<8)[0].I();
                      RGBValue.Append(255);
                      RGBValue.Append((255-(GrayVal-Min-step*4)*128/step));
                      RGBValue.Append(0);
                      break;
                case 5:
                   // RGBValue:=[255,128-(GrayValue-Standard*5)*128/Standard,0];
                    //*ptr|=HTuple(255<<16+(128-(GrayVal-Min-step*5)*128/step)<<8)[0].I();
                      RGBValue.Append(255);
                      RGBValue.Append(128-(GrayVal-Min-step*5)*128/step);
                      RGBValue.Append(0);
                      break;
                case 6:
                  //  RGBValue:=[255,(GrayValue-Standard*6)*128/Standard,(GrayValue-Standard*6)*128/Standard];
                     // *ptr|=HTuple(255<<16+((GrayVal-Min-step*6)*128/step)<<8+(GrayVal-Min-step*6)*128/step)[0].I();
                      RGBValue.Append(255);
                      RGBValue.Append((GrayVal-Min-step*6)*128/step);
                      RGBValue.Append((GrayVal-Min-step*6)*128/step);
                      break;

            }


            set_grayval (Image1, i, j, RGBValue[0]);
            set_grayval (Image2, i, j, RGBValue[1]);
            set_grayval (Image3, i, j, RGBValue[2]);
        }
    }
 */
    hasData=true;

    emit dispImg();

}

