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
    scale=1;
    recvCount=0;
    index=0;
    isLoadFile=false;
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
    if(hInstance==NULL)
        qDebug()<<"pcl dll load fail";


    inCloud=new PointCloud::Ptr(new PointCloud );
    memcpy(menu,tmp,sizeof(tmp));
    roiList=set.value("roiList").toMap();
    dataList=set.value("dataList").toMap();
    emit flushRoiList(roiList.keys());
}
/*
    打开一个窗口
*/
void halconClass::open_the_window(int handle,int width,int height)
{
    set_system("flush_graphic","true");
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
   char c[100];
   HTuple area;
   HTuple Width,Height;
   Hobject tmp;
   long w,h;
   char     type[128];
   double *p;
   QFile f(str);
   path=str;
   if(!f.exists())
   {
       emit Error("file not found");
       return;
   }
   isLoadFile=true;
   qDebug()<<"read"<<str;
   read_image(&tmp,path.toUtf8().data());

   get_image_size(tmp,&Width,&Height);

   get_image_pointer1(tmp,(long*)&p,type,&w,&h);
   //getImagebyPointer3(0,0,p,w,h);
   qDebug()<<w<<h<<type;

   getImagebyPointer1(p,w,h);
   qDebug()<<w<<h;
   img_width=Width[0].I();
   img_height=Height[0].I();
   xScale=Width[0].I()/win_width;
   yScale=Height[0].I()/win_width;
   hasData=true;
   qDebug()<<"read finish";
   //emit dispImg();
}
void halconClass::clearData()
{
	
    if (HDevWindowStack::IsOpen()&hasData)
	{
		  //Image.Reset();
        imgList.clear();
        emit deleteAllImg();
        index=0;
        clear_window(WindowHandle);
	}
	 hasData=false;
	qDebug()<<"clear";
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
        xScale=img_width/win_width;
        yScale=img_height/win_height;

        clear_window(WindowHandle);
        set_part(WindowHandle,0,0,img_height,img_width);
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
        Hlong w,h;
        get_image_size(Image,&w,&h);
        set_part(WindowHandle,0,0,win_height,win_width);
        img_width=w;
        img_height=h;
        xScale=img_width/win_width;
        yScale=img_height/win_width;
        if(str.contains("2D"))
        {
               clear_window(WindowHandle);
               set_lut(WindowHandle,"rainbow");
               set_paint(HDevWindowStack::GetActive(),"default");
               disp_img();

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
            disp_img();

        }
    }
}
void halconClass::selectImg(int i)
{
    qDebug()<<"display"<<i;
    if(imgList.size()<(i+1))
        return;
    index=i;
    copy_image(*imgList.at(i),&Image);
    disp_img();
}
void halconClass::disp_img()
{

    Hobject Rectangle;
    roiList=set.value("roiList").toMap();
   // mirror_image(Image,&Image,"column");


    if (HDevWindowStack::IsOpen()&hasData)
    {


        set_lut(WindowHandle,"rainbow");

        if(is3D)
        {
           // compoundImg(0,0);
            Hlong w,h;
            get_image_size(Image,&w,&h);
            set_part(WindowHandle,0,0,h,w);
            img_width=w;
            img_height=h;
            xScale=img_width/win_width;
            yScale=img_height/win_width;

            disp_obj(Image,WindowHandle);
            copy_image(Image,&result_img);
            set_window_param(WindowHandle,"interactive_plot", "true");
        }
        else
        {

            disp_obj(Image,WindowHandle);
            copy_image(Image,&result_img);
        }
    }

    if(HDevWindowStack::IsOpen())
    {
		if(is3D)
			return;
        //显示矩形窗口
        QStringList list=roiList.keys();

        if(list.size()==0)
            return;
        for(int i=0;i<list.size();i++)
        {
            QStringList str=roiList.value(list.at(i)).toStringList();
            if(str.at(8).toInt()==index)
            {
                set_rgb(WindowHandle,(int)((str.at(0).toULong()&(0xff<<16))>>16),(int)((str.at(0).toULong()&(0xff<<8))>>8),(int)(str.at(0).toULong()&0xff));
                //set_color(WindowHandle,str.at(0).toUtf8().data());
                set_tposition(WindowHandle,str.at(1).toInt(),str.at(2).toInt());
                write_string(WindowHandle,HTuple(list.at(i).toUtf8().data()));
                Hobject Rectangle,Contours;
                gen_rectangle1(&Rectangle, (Hlong)str.at(1).toInt(), (Hlong)str.at(2).toInt(),(Hlong)str.at(3).toDouble(), (Hlong)str.at(4).toInt());
                gen_contour_region_xld(Rectangle,&Contours,"border");
                disp_obj(Contours,WindowHandle);
          
            }
        }

    }

}
void halconClass::moveImg(int x,int y)
{
    static int count=0;
     Hobject  ImageTrans;
     // Local control variables
     HTuple  HomMat;
     Hlong row,col,row1,col1;

     if(HDevWindowStack::IsOpen()&hasData)
     {
        if(!is3D)
        {

            get_part(WindowHandle,&row,&col,&row1,&col1);

            set_part(WindowHandle,row+y,col+x,row1+y,col1+x);
            // move_rectangle(WindowHandle,row,col,row1,col1,y,x);
           // set_part(WindowHandle,row+y*scale,col+x*scale,row1+y*scale,col1+x*scale);
             //set_part(WindowHandle,posY+y,posX+x,win_height+posY+y,win_width+posX+x);
                get_part(WindowHandle,&row,&col,&row1,&col1);

             //  move_region(Image,&result_img,centerY-y*scale,centerX-x*scale);
           // disp_obj(result_img,WindowHandle);
             disp_img();

            // if (HDevWindowStack::IsOpen())
               //clear_window(HDevWindowStack::GetActive());

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
        Hlong row,col,row1,col1;
        get_part(WindowHandle,&row,&col,&row1,&col1);
        set_part(WindowHandle,row+y,col+x,row1+y,col1+x);
        // set_part(WindowHandle,posY+y*scale,posX+x*scale,img_height+posY+y*scale,img_width+posX+x*scale);
        clear_window(WindowHandle);
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
    if(is3D)
        return;

    if (HDevWindowStack::IsOpen()&hasData)
    {
        clear_window(WindowHandle);
        Hlong row,col,row1,col1;
        get_part(WindowHandle,&row,&col,&row1,&col1);
        set_part(WindowHandle,row*0.8,col*0.8,row1*0.8,col1*0.8);
        //set_part(WindowHandle,y,x,HTuple(h)+y,HTuple(w)+x);
        disp_img();

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
    if(is3D)
        return;

    if (HDevWindowStack::IsOpen()&hasData)
    {
        clear_window(WindowHandle);
        Hlong row,col,row1,col1;
        get_part(WindowHandle,&row,&col,&row1,&col1);

        set_part(WindowHandle,row*1.2,col*1.2,row1*1.2,col1*1.2);
       // set_part(WindowHandle,y,x,HTuple(h)+y,HTuple(w)+x);
        disp_img();
    }
}
void halconClass::threedControl(double lastRow, double lastCol, double Row, double Column,QString mode)
{
	
    if(!is3D|!hasData)
        return;
    if(!HDevWindowStack::IsOpen())
        return;
    //qDebug()<<lastRow*scale<<lastCol*scale<<Row*scale<<Column*scale<<mode;
   // qDebug()<<mode<<Column<<Row<<lastCol<<lastRow;
    update_window_pose(WindowHandle, lastRow*yScale, lastCol*xScale, Row*yScale, Column*xScale, mode.toUtf8().data());
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
		long w,h;
		char     type[128];
		float *p;

        read_image(&Image,path.toUtf8().data());

        get_image_size(Image,&Width,&Height);
        set_part(WindowHandle,0,0,Height-1,Width-1);
		get_image_pointer1(Image,(long*)&p,type,&w,&h);
        //this->getImagebyPointer3(0,0,(double *)p,w,h);
        img_width=Width[0].I();
        img_height=Height[0].I();
        xScale=img_width/win_width;
        yScale=img_height/win_width;
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

    compoundImg(0,0);
    disp_img();


}
void halconClass::clearRect()
{

}
void halconClass::delRect(int index)
{
    QStringList list=roiList.keys();

    QString team=roiList.value(list.at(index)).toStringList().at(5);
    QStringList data=dataList.value(team).toStringList();
    qDebug()<<"before"<<data;
    data.removeAll(list.at(index));
    qDebug()<<"delete"<<data;
    dataList.insert(team,data);
    qDebug()<<"after"<<dataList;
    roiList.remove(list.at(index));
    set.setValue("dataList",dataList);
    set.setValue("roiList",roiList);
    set.sync();
	if (HDevWindowStack::IsOpen())
		clear_window(WindowHandle);
    disp_img();
}
/*
    绘制计算区域
*/
void halconClass::drawRect(QString name,QString color,int team,double limit,int func)
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
    
    //set_color(WindowHandle,color.toUtf8().data());
	
	set_rgb(WindowHandle,(int)((color.toULong()&(0xff<<16))>>16),(int)((color.toULong()&(0xff<<8))>>8),(int)(color.toULong()&0xff));
    draw_rectangle1(WindowHandle,&Row,&Column,&Row2,&Column2);
    qDebug()<<Row[0].I()<<Column[0].I()<<Row2[0].I()<<Column2[0].I();

   //写入配置文件


    QStringList str;
    str<<color;
    str<<QString::number(Row[0].I());
    str<<QString::number(Column[0].I());
    str<<QString::number(Row2[0].I());
    str<<QString::number(Column2[0].I());
    str<<QString::number(team);
    str<<QString::number(limit);
    str<<QString::number(func);
    str<<QString::number(index);
    roiList.insert(name,QVariant(str));

    QString teamNum=QString::number(team);
    QStringList data;
    if(!dataList.contains(teamNum))
    {
        data<<name<<QString::number(limit);
        dataList.insert(teamNum,data);
    }
    else
    {
        data=dataList.value(teamNum).toStringList();
        data.removeLast();
        data<<name<<QString::number(limit);
        dataList.insert(teamNum,data);
    }

    qDebug()<<dataList;
    set.setValue("dataList",dataList);
    set.setValue("roiList",roiList);
    set.sync();

    //更新界面
    disp_img();
    emit flushRoiList(roiList.keys());
}

void halconClass::matchTemplate(int team)
{
    int num=0;
    QTime time;
    HTuple hv_TemplateID;
    time.start();
    typedef int (*MT)(Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,HTuple hv_TemplateID,HTuple* hv_Row, HTuple *hv_Column,HTuple *hv_Angle);
    MT cal=NULL;

    cal=(MT)GetProcAddress(hInstance,"Match_template");
   if (HDevWindowStack::IsOpen()&hasData)
    {
        Hobject   Rectangle, RegionComplement, ImageReduced,rect;
        HTuple  tmp, tmp2, Row2, Column2, Min=0, Max=0,Indices;
        HTuple Rows,Columns,Grayval;
        HTuple  Range,String,s,Result,Number;
        HTuple hv_Row,hv_Column,hv_Angle;
        QString n=dataList.keys().at(team);

        QStringList list=dataList.value(n).toStringList();
        qDebug()<<list;
        for(int i=0;i<list.size()-1;i++)
        {
            QStringList str=roiList.value(list.at(i)).toStringList();


            if(str.at(7).toInt()==2)
            {
                if(imgList.size()<=str.at(8).toInt())
                    continue;
                num++;
              //  (*cal)(*imgList.at(str.at(8).toInt()),str.at(1).toInt(), str.at(2).toInt(), str.at(3).toInt(), str.at(4).toInt(),&hv_TemplateID);

            }
        }

        if(num==0)
            return;
    }

    qDebug()<<QStringLiteral("生成模板时间:")<<time.elapsed()<<"ms";
}
void halconClass::createTemplate(int team)
{
    int num=0;
    QTime time;
    HTuple hv_TemplateID;
    time.start();
    typedef int (*CT)(Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,HTuple *hv_TemplateID);
    CT cal=NULL;

    cal=(CT)GetProcAddress(hInstance,"Create_template");
   if (HDevWindowStack::IsOpen()&hasData)
    {
        Hobject   Rectangle, RegionComplement, ImageReduced,rect;
        HTuple  tmp, tmp2, Row2, Column2, Min=0, Max=0,Indices;
        HTuple Rows,Columns,Grayval;
        HTuple  Range,String,s,Result,Number;

        QString n=dataList.keys().at(team);

        QStringList list=dataList.value(n).toStringList();
        qDebug()<<list;
        for(int i=0;i<list.size()-1;i++)
        {
            QStringList str=roiList.value(list.at(i)).toStringList();


            if(str.at(7).toInt()==2)
            {
                if(imgList.size()<=str.at(8).toInt())
                    continue;
                num++;
                (*cal)(*imgList.at(str.at(8).toInt()),str.at(1).toInt(), str.at(2).toInt(), str.at(3).toInt(), str.at(4).toInt(),&hv_TemplateID);

            }
        }

        if(num==0)
            return;
    }

    qDebug()<<QStringLiteral("生成模板时间:")<<time.elapsed()<<"ms";
}
/*
    计算高差
*/
void halconClass::RectHeightSub(int team)
{
    int num=0;
    QTime time;
    time.start();
   if (HDevWindowStack::IsOpen()&hasData)
    {
        Hobject   Rectangle, RegionComplement, ImageReduced,rect;
        HTuple  tmp, tmp2, Row2, Column2, Min=0, Max=0,Indices;
        HTuple Rows,Columns,Grayval;
        HTuple  Range,String,s,Result,Number;

        QString n=dataList.keys().at(team);

        QStringList list=dataList.value(n).toStringList();
        qDebug()<<list;
        for(int i=0;i<list.size()-1;i++)
        {
            QStringList str=roiList.value(list.at(i)).toStringList();


            if(str.at(7).toInt()==0)
            {
                if(imgList.size()<=str.at(8).toInt())
                    continue;
                num++;
                gen_rectangle1(&Rectangle, str.at(1).toInt(), str.at(2).toInt(), str.at(3).toInt(), str.at(4).toInt());

                reduce_domain(*imgList.at(str.at(8).toInt()), Rectangle, &ImageReduced);
                get_region_points(ImageReduced, &Rows, &Columns);
                get_grayval(ImageReduced, Rows, Columns, &Grayval);
                if(Grayval.Num()==0)
                {
                    qDebug()<<"grayval:"<<Grayval.Num();
                    continue;
                }
                tuple_max(Grayval, &tmp);

                tuple_find(Grayval,0,&Indices);
                if(Indices[0].I()!=-1)
                {
                    for(int i=0;i<Indices.Num();i++)
                    {

                        Grayval[Indices[i].I()]=tmp;
                    }
                }
                tuple_max2(tmp,Max,&Max);

                tuple_min(Grayval,&tmp2);
                if(Min[0].I()==0)
                    Min=tmp2;
                else
                    tuple_min2(tmp2,Min,&Min);




            }
        }

        if(num==0)
            return;
        tuple_sub(Max,Min,&Range);
        qDebug()<<Min[0].D()<<Max[0].D()<<Range[0].D();
        emit sendHeightSub(n.toInt(),Min[0].D(),Max[0].D(),Range[0].D());
    }

    qDebug()<<QStringLiteral("计算高差时间:")<<time.elapsed()<<"ms";
}
/*
    计算所有区域
*/
void halconClass::calculate()
{
   qDebug()<<QStringLiteral("开始计算高差");
    for(int i=0;i<dataList.size();i++)
    {
        this->RectHeightSub(i);

    }
    qDebug()<<QStringLiteral("结束计算高差");

    for(int i=0;i<dataList.size();i++)
    {

         this->calculatePlaneness(i);
    }
    qDebug()<<QStringLiteral("计算所有平面度时间")<<time.elapsed()<<"ms";
}
/*
    计算平面度
*/
void halconClass::calculatePlaneness(int team)
{

    double result1,result2;
    int num=0;
    typedef int (*Calculate)(PointCloud::Ptr &, double &);
   // typedef int (*GetChildCloud)(PointCloud::Ptr &inCloud, POINT point1,POINT point2,int width,PointCloud::Ptr outCloud);
    typedef int (*CalculateFlatness2) (PointCloud::Ptr &cloud, double &);
	typedef int (*GetChildPoint)(PointCloud::Ptr &inCloud,Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,PointCloud::Ptr outCloud);
    Calculate cal=NULL;
  //  GetChildCloud child2=NULL;
    CalculateFlatness2 Comp=NULL;
	GetChildPoint child=NULL;
    cal=(Calculate)GetProcAddress(hInstance,"CalculateFlatness");
   // child2=(GetChildCloud)GetProcAddress(hInstance,"GetChildCloud");
    Comp=(CalculateFlatness2)GetProcAddress(hInstance,"CalculateFlatness2");
	child=(GetChildPoint)GetProcAddress(hInstance,"GetChildPoint");

	QTime time;
	time.start();
    if(cal==NULL|child==NULL)
    {
        qDebug()<<"func is NULL";
        return;
    }

    PointCloud::Ptr globleCloud(new PointCloud);
    if (HDevWindowStack::IsOpen()&hasData)
    {

        Hobject   Rectangle;

        char     type[128];
        QString n=dataList.keys().at(team);
        QStringList list=dataList.value(n).toStringList();
        qDebug()<<list;
        for(int i=0;i<list.size()-1;i++)
        {
            
            QStringList str=roiList.value(list.at(i)).toStringList();

			
            if(str.at(7).toInt()==1)
            {

                if(imgList.size()<=str.at(8).toInt())
                    continue;
                 num++;
                POINT p1,p2;
                p1.x=str.at(2).toInt();
                p1.y=str.at(1).toInt();
                p2.x=str.at(4).toInt();
                p2.y=str.at(3).toInt();
                qDebug()<<"start and end"<<p1.x<<p1.y<<p2.x<<p2.y;
                PointCloud::Ptr newCloud(new PointCloud);
				
                (*child)(*inCloud,*imgList.at(str.at(8).toInt()),HTuple(p1.y),HTuple(p1.x),HTuple(p2.y),HTuple(p2.x),newCloud);
				qDebug()<<"cacule flatness"<<num;
               // pcl::io::savePCDFile(QString("roi%1.pcd").arg(i).toUtf8().data(),*(newCloud.get()));
               // (*cal)(newCloud,result1);
               // (*Comp)(newCloud,result2);
                //qDebug()<<"cal";
                *globleCloud+=*newCloud;
                //qDebug()<<list.at(i)<<i<<QStringLiteral("平整度为")<<result1<<result2<<QStringLiteral("计算时间为")<<time.elapsed()<<"ms";
            }


         }

        if(num==0)
            return;
        (*cal)(globleCloud,result1);
        (*Comp)(globleCloud,result2);
        //delete newCloud.get();
        qDebug()<<"team"<<team<<QStringLiteral("总平整度为")<<result1<<result2<<time.elapsed()<<"ms";
        emit sendPlaneness(n.toInt(),result1,result2);
     }

}
/*
    读取设置
*/
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
/*
    获取完整图像并生成点云
*/
void halconClass::getImagebyPointer3(double *x,double *y,double *z,const int w,const int h)
{
	QTime time;
    time.start();
    Hobject Image,Image2,Image3;
    float *pointer,*pointer2,*pointer3;
    unsigned short *p;
    Hlong width,height;
    char     type[128];
    HTuple Row,Column;
   
    qDebug()<<"start pointCloud"<<w<<h;
    typedef void (*Transfer2Cloud)(double* ,double* ,double* ,unsigned short* ,const int ,const int ,PointCloud::Ptr );
    Transfer2Cloud test_function =NULL;
    test_function = (Transfer2Cloud)GetProcAddress(hInstance, "Transfer2Cloud");
    qDebug("%x,test_function",test_function);
    if(test_function==NULL)
    {
        qDebug()<<"func is NULL";
        return;
    }
    double *yy=new double[h*w];
    for(int i=0;i<h;i++)
    {
		float xx=i*set.value("testValue",0.01).toFloat();
        for(int j=0;j<w;j++)
         yy[i*w+j]=xx;
		
    }
	qDebug()<<"run";
	if(x==0)
        (*test_function)(yy,yy,z,0,w,h,*inCloud);
	else
        (*test_function)(x,yy,z,0,w,h,*inCloud);
   // pcl::io::savePCDFile("out.pcd",*(inCloud->get()));
    qDebug()<<"end pointCloud,prossess time:"<<time.elapsed()<<"ms";
    delete yy;
	
	calculate();
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
/*
    刷新图像
*/
void halconClass::getImagebyPointer1(double *pdValueZ,int w,int h)
{
    HTuple  MatID, Rows, Cols, Values, MultValues;
    HTuple  Min, Max, Row, Column,Range,GrayVal,Value,i,j,Width,Height;
    Hobject Region,Imagetemp,Image1,Image2, Image3,*tmp;
  //  double *p=imgData;
    recvCount=h;

  //  if((recvCount+h)>1000)
    //    recvCount=0;

   // memcpy(&imgData[recvCount*1280],pdValueZ,w*h);
  //  recvCount+=h;
    qDebug()<<"recv:"<<h;
    char     type[128];
    Hlong     width,height;
    float *pointer=0,*p=(float *)pdValueZ;
    time.start();
    tmpImage.Reset();
    Image.Reset();
    result_img.Reset();
    if(h==set.value("rate").toInt())
    {
        if (HDevWindowStack::IsOpen()&hasData)
        {
              //Image.Reset();

            clear_window(WindowHandle);
            index++;
        }
    }
    gen_image_const(&Imagetemp,"real",w,set.value("profileCount",1000).toUInt());
    get_image_pointer1(Imagetemp,(long*)&pointer,type,&width,&height);
    scale=win_width/w;
    set_part(WindowHandle,0,0,1000,w);
    for (int row=0; row<h; row++)
    {

        for (int col=0; col<width; col++)
        {
            if(!isLoadFile)
                pointer[row*width+col] =*pdValueZ++;
            else
                pointer[row*width+col] =*p++;
        }
    }
    isLoadFile=false;
    qDebug()<<"read time:"<<time.elapsed()<<"msec";


  //  write_image(RGBImage,"bmp",0,"test.bmp");

    write_image(Imagetemp,"tiff",0,QString("test%1").arg(index).toUtf8().data());

    copy_image(Imagetemp,&Image);

    if(h>=set.value("profileCount",1000).toUInt())
	{
		img_width=width;
		img_height=height;
        xScale=width/win_width;
        yScale=height/win_height;
        Hobject *tmp=new Hobject;
        copy_image(Imagetemp,tmp);
        imgList.push_back(tmp);
        emit addImg(tmp);
        qDebug()<<"imgList.size="<<imgList.size();

        if(imgList.size()>8)
        {
            clear_obj(*imgList.takeFirst());
            emit deleteImg(0);
        }


	}
	hasData=true;

    emit dispImg();
   
}
void halconClass::compoundImg(int xOffset,int yOffset)
{
    Hobject img,tmpImg;
    HTuple w,h;
    Hlong width,height;
    float *pointer,*p2;
    char type[100];
    w=set.value("width",1280).toInt()*(imgList.size())+xOffset*(imgList.size()-1);
    //h=set.value("height",1000).toInt()*imgList.size()+yOffset*(imgList.size()-1);
    h=set.value("profileCount",1000).toInt();
    gen_image_const(&img,"real",w,h);
    qDebug()<<"com"<<w[0].I()<<h[0].I();

    get_image_pointer1(img,(long*)&pointer,type,&width,&height);
    qDebug()<<width<<height;
    for(int i=0;i<imgList.size();i++)
    {
        get_image_pointer1(*imgList.at(i),(long*)&p2,type,&width,&height);
        qDebug()<<width<<height<<(long)imgList.at(i);
        for(int y=0;y<height;y++)
        {
            for(int x=0;x<width;x++)
            {
                pointer[(y)*w[0].I()+xOffset*i+i*width+x]=*p2++;
            }
        }
    }
    gen_image_const(&Image,"real",w,h);
    copy_image(img,&Image);
    get_image_size(Image,&width,&height);
    set_part(WindowHandle,0,0,height,width);

}
