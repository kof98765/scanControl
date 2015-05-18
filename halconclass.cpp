﻿#include "halconclass.h"
#include "Flatness.h"

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
    HomMat2D=NULL;
    img_width=0;
    img_height=0;
    detect_action tmp[9]={};
    hInstance = LoadLibrary("PCL_Library_Dll.dll");
    if(hInstance==NULL)
        qDebug()<<"pcl dll load fail";



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
    if(img_width!=0&img_height!=0)
        resizePart();
    else
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
void halconClass::resizePart()
{
    double ratio_win=(double)win_width/win_height;
    double ratio_img=(double)img_width/img_height;
    int _beginRow, _begin_Col, _endRow, _endCol;

    if (ratio_win >= ratio_img)
    {

        _beginRow = 0;
        _endRow = img_height - 1;
        _begin_Col = (int)(-img_width * (ratio_win / ratio_img - 1.0) / 2.0);
        _endCol = (int)(img_width + img_width * (ratio_win / ratio_img - 1.0) / 2.0);
    }
    else
    {
        _begin_Col = 0;
        _endCol = img_width - 1;
        _beginRow = (int)(-img_height * (ratio_img / ratio_win - 1.0) / 2.0);
        _endRow = (int)(img_height + img_height * (ratio_img / ratio_win - 1.0) / 2.0);
    }

    set_part(WindowHandle,_beginRow,_begin_Col,_endRow,_endCol);
}
/*
    启动线程,读取图像文件
*/
void halconClass::read_img(QString str)
{

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

   QTextCodec* gbk = QTextCodec::codecForName("GBK");
   //QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");
   //编码器可以把QString转换为自己的编码：
   QByteArray ba = gbk->fromUnicode(path);

   char* c = ba.data();
   read_image(&tmp,c);

   get_image_size(tmp,&Width,&Height);

   get_image_pointer1(tmp,(long*)&p,type,&w,&h);
   //getImagebyPointer3(0,0,p,w,h);
   qDebug()<<w<<h<<type;
    if(type==gbk->fromUnicode("byte").data())
    {
        emit Error("thi image type is byte,not real!!");
        return;
    }
    img_width=Width[0].I();
    img_height=Height[0].I();
    xScale=Width[0].I()/win_width;
    yScale=Height[0].I()/win_width;
   getImagebyPointer1(p,w,h);
   qDebug()<<w<<h;

   hasData=true;
   qDebug()<<"read finish";
   //emit dispImg();
}
void halconClass::clearData()
{
	
    if (HDevWindowStack::IsOpen()&hasData)
	{
		  //Image.Reset();
        for(int i=0;i<imgList.size();i++)
        {
            clear_obj(*imgList.at(i));
        }
        imgList.clear();

        emit deleteAllImg();
        index=0;
        matList.clear();
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
        set_part(WindowHandle,0,0,win_height,win_width);
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
        resizePart();
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
void halconClass::disp_xld(HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2)
{
    Hobject Rectangle,Contour;

    gen_rectangle1(&Rectangle,Row1,Column1,Row2,Column2);
    gen_contour_region_xld(Rectangle,&Contour,"border");
    if (HDevWindowStack::IsOpen()&hasData)
    {
        disp_obj(Contour,WindowHandle);
    }
}
void halconClass::disp_xld(double Row,double Column,double Row1,double Column1)
{
    disp_xld(HTuple(Row),HTuple(Column),HTuple(Row1),HTuple(Column1));
}

void halconClass::disp_xld(HTuple Row,HTuple Column,HTuple Phi,HTuple Length1,HTuple Length2)
{
    Hobject Rectangle,Contour;
    gen_rectangle2(&Rectangle,Row,Column,Phi,Length1,Length2);
    gen_contour_region_xld(Rectangle,&Contour,"border");
    if (HDevWindowStack::IsOpen()&hasData)
    {
        disp_obj(Contour,WindowHandle);
    }
}
void halconClass::disp_xld(double Row,double Column,double Phi,double Length1,double Length2)
{
    disp_xld(HTuple(Row),HTuple(Column),HTuple(Phi),HTuple(Length1),HTuple(Length2));
}


void halconClass::disp_img()
{

    Hobject Rectangle,RegionAffineTrans,Contours;

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
            yScale=img_height/win_height;

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
        //绘制基准点相关图形
        QMap<QString,QVariant> point=set.value("basePoint").toMap();
        set_tposition(WindowHandle,point.value(QString::number(index)).toPointF().y(),point.value(QString::number(index)).toPointF().x());
        gen_rectangle2(&Rectangle,point.value(QString::number(index)).toPointF().y(),point.value(QString::number(index)).toPointF().x(),0,5,5);
        disp_obj(Rectangle,WindowHandle);
        write_string(WindowHandle,"center");
         QMap<QString,QVariant> base=set.value("locationList").toMap().value(QString::number(index)).toMap();
        disp_xld(base.value("Row").toDouble(),base.value("Column").toDouble(),base.value("Row1").toDouble(),base.value("Column1").toDouble());
        disp_xld(base.value("Row2").toDouble(),base.value("Column2").toDouble(),base.value("Row3").toDouble(),base.value("Column3").toDouble());
        disp_xld(base.value("Row4").toDouble(),base.value("Column4").toDouble(),base.value("Row5").toDouble(),base.value("Column5").toDouble());
        if(list.size()==0)
            return;

        for(int i=0;i<list.size();i++)
        {
            QMap<QString,QVariant> roi=set.value("team/"+list.at(i)).toMap();

            if(roi.value("index").toInt()==index)
            {


                Hobject Rectangle,Contours;

                if(roi.value("func").toInt()==1|roi.value("func").toInt()==0)
                {
                    gen_rectangle1(&Rectangle, (Hlong)roi.value("Row").toDouble(), (Hlong)roi.value("Column").toDouble(),(Hlong)roi.value("Row2").toDouble(), (Hlong)roi.value("Column2").toDouble());

                }
                else
                {
                    if(roi.value("isDraw").toInt()==0)
                    {
                        gen_rectangle2(&Rectangle,roi.value("Row").toDouble()+point.value(QString::number(index)).toPointF().y(),roi.value("Column").toDouble()+point.value(QString::number(index)).toPointF().x(),roi.value("Phi").toDouble(),roi.value("Length1").toDouble(),roi.value("Length2").toDouble());
                        if(roi.value("func").toInt()==5)
                        {
                            Hobject Rectangle2;
                            gen_rectangle2(&Rectangle2,roi.value("Row2").toDouble()+point.value(QString::number(index)).toPointF().y(),roi.value("Column2").toDouble()+point.value(QString::number(index)).toPointF().x(),roi.value("Phi2").toDouble(),roi.value("Length3").toDouble(),roi.value("Length4").toDouble());
                            gen_contour_region_xld(Rectangle2,&Contours,"border");
                            disp_obj(Contours,WindowHandle);

                        }
                        set_tposition(WindowHandle,roi.value("Row").toDouble()+point.value(QString::number(index)).toPointF().y(),roi.value("Column").toDouble()+point.value(QString::number(index)).toPointF().x());
                    }
                    else
                    {
                        gen_rectangle2(&Rectangle,roi.value("Row").toDouble(),roi.value("Column").toDouble(),roi.value("Phi").toDouble(),roi.value("Length1").toDouble(),roi.value("Length2").toDouble());
                        if(roi.value("func").toInt()==5)
                        {
                            Hobject Rectangle2;
                            gen_rectangle2(&Rectangle2,roi.value("Row2").toDouble(),roi.value("Column2").toDouble(),roi.value("Phi2").toDouble(),roi.value("Length3").toDouble(),roi.value("Length4").toDouble());
                            gen_contour_region_xld(Rectangle2,&Contours,"border");
                            disp_obj(Contours,WindowHandle);

                        }
                        set_tposition(WindowHandle,roi.value("Row").toDouble(),roi.value("Column").toDouble());
                    }

                }
                set_rgb(WindowHandle,(int)((roi.value("color").toInt()&(0xff<<16))>>16),(int)((roi.value("color").toInt()&(0xff<<8))>>8),(int)(roi.value("color").toInt()&0xff));


                write_string(WindowHandle,HTuple(list.at(i).toUtf8().data()));
                /*
                if(matList.value(roi.value("index").toString(),NULL)!=NULL&roi.value("func").toInt()!=1)
                {
                    affine_trans_region(Rectangle,&Rectangle,matList.value(roi.value("index").toString()),"false");
                    HTuple Row,Column;
                    affine_trans_pixel(matList.value(roi.value("index").toString(),NULL),roi.value("Row").toDouble(),roi.value("Column").toDouble(),&Row,&Column);
                    set_rgb(WindowHandle,(int)((roi.value("color").toInt()&(0xff<<16))>>16),(int)((roi.value("color").toInt()&(0xff<<8))>>8),(int)(roi.value("color").toInt()&0xff));

                    set_tposition(WindowHandle,Row,Column);
                    write_string(WindowHandle,HTuple(list.at(i).toUtf8().data()));
                }
                else
                {
                    set_rgb(WindowHandle,(int)((roi.value("color").toInt()&(0xff<<16))>>16),(int)((roi.value("color").toInt()&(0xff<<8))>>8),(int)(roi.value("color").toInt()&0xff));

                    set_tposition(WindowHandle,roi.value("Row").toDouble(),roi.value("Column").toDouble());
                    write_string(WindowHandle,HTuple(list.at(i).toUtf8().data()));
                }
                */

                gen_contour_region_xld(Rectangle,&Contours,"border");
                disp_obj(Contours,WindowHandle);


            }
        }
       // QMap<QString,QVariant> roi=set.value("locationList").toMap();
        //gen_rectangle1(&Rectangle,roi.value("Row").toDouble(),roi.value("Column").toDouble(),roi.value("Row2").toDouble(),roi.value("Column2").toDouble());


        //gen_contour_region_xld(Rectangle,&Contours,"border");
        //disp_obj(Contours,WindowHandle);


    }

}
void halconClass::moveImg(int x,int y)
{
     static int count=0;
     Hobject  ImageTrans;
     HTuple  HomMat;
     Hlong row,col,row1,col1;
     if(HDevWindowStack::IsOpen()&hasData)
     {
        if(!is3D)
        {

            get_part(WindowHandle,&row,&col,&row1,&col1);
            set_part(WindowHandle,row+y,col+x,row1+y,col1+x);
            get_part(WindowHandle,&row,&col,&row1,&col1);
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
/*

*/
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
QPoint halconClass::getPoint()
{
    double x,y;
    Hlong button;
    HTuple hv_Exception;

    get_mposition_sub_pix(WindowHandle,&y,&x,&button);

    QPoint p(x,y);
    return p;
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
/*
    删除区域
*/
void halconClass::delRect(QString name)
{

    roiList.remove(name);


    QMap<QString,QVariant> roi=set.value("team/"+name).toMap();
    QStringList data=dataList.value(roi.value("team").toString()).toStringList();

    data.removeAll(name);


    dataList.insert(roi.value("team","0").toString(),data);
    qDebug()<<"del"<<roi.value("team").toString()<<dataList;

    set.setValue("dataList",dataList);
    set.setValue("roiList",roiList);
    set.remove("team/"+name);
    set.sync();

	if (HDevWindowStack::IsOpen())
		clear_window(WindowHandle);
    disp_img();
}
void halconClass::drawToFindBasePoint(QMap<QString,QVariant> map)
{
    HTuple  Row, Column, Row2, Column2,Phi,Length1,Length2, Max;
    QString name=map.value("name").toString();
    int color=map.value("color").toInt();
    int func=map.value("func").toInt();
    emit Warning(QStringLiteral("请选择一条边"));
    set_rgb(WindowHandle,(int)((color&(0xff<<16))>>16),(int)((color&(0xff<<8))>>8),(int)(color&0xff));
    draw_rectangle1(WindowHandle,&Row,&Column,&Row2,&Column2);
    map.insert("Row",Row[0].D());
    map.insert("Column",Column[0].D());
    map.insert("Row1",Row2[0].D());
    map.insert("Column1",Column2[0].D());
    disp_xld(Row,Column,Row2,Column2);
    emit Warning(QStringLiteral("请选择两条平行线中的一条"));
    draw_rectangle1(WindowHandle,&Row,&Column,&Row2,&Column2);
    map.insert("Row2",Row[0].D());
    map.insert("Column2",Column[0].D());
    map.insert("Row3",Row2[0].D());
    map.insert("Column3",Column2[0].D());
    disp_xld(Row,Column,Row2,Column2);
    emit Warning(QStringLiteral("请选择两条平行线中的另一条"));
    draw_rectangle1(WindowHandle,&Row,&Column,&Row2,&Column2);
    map.insert("Row4",Row[0].D());
    map.insert("Column4",Column[0].D());
    map.insert("Row5",Row2[0].D());
    map.insert("Column5",Column2[0].D());
    disp_xld(Row,Column,Row2,Column2);

    map.insert("index",index);
    QMap<QString,QVariant> local=set.value("locationList").toMap();
    local.insert(QString::number(index),map);
    set.setValue("locationList",local);
    emit Warning("");

    set.sync();
}

/*
    绘制计算区域
*/
void halconClass::drawRect(QMap<QString,QVariant> map)
{
    int i=0;
    Hobject Rectangle;
    QString name=map.value("name").toString();
    int team=map.value("team").toInt();
    int color=map.value("color").toInt();
    int func=map.value("func").toInt();
    double min=map.value("min").toDouble();
    double max=map.value("max").toDouble();
    double row=map.value("Row").toDouble();
    double column=map.value("Column").toDouble();
    double length1=map.value("Length1",50).toDouble();
    double length2=map.value("Length2",50).toDouble();
    int unit=map.value("unit").toInt();
    int drawType=map.value("drawType").toInt();
    if(name.isEmpty())
        name="rect000";
    while(set.contains("team/"+name))
    {

        name=QString("rect%1").arg(i++,3,10,QLatin1Char('0'));
    }
    if(func==2)
    {
        drawToFindBasePoint(map);
        return;
    }
    HTuple  Row, Column, Row2, Column2,Phi,Length1,Length2, Max;
    QStringList str;
    QMap<QString,QVariant> roi;
    //Roi roi;
    //set_color(WindowHandle,color.toUtf8().data());

    set_rgb(WindowHandle,(int)((color&(0xff<<16))>>16),(int)((color&(0xff<<8))>>8),(int)(color&0xff));
    //roiList[0]
    //roi.color=color;
    roi.insert("color",color);
    if(func==3|func==4|func==5)
    {
        if(drawType)
        {
            draw_rectangle2(WindowHandle,&Row,&Column,&Phi,&Length1,&Length2);
        //roiList[1-5]

            roi.insert("Row",Row[0].D());
            roi.insert("Column",Column[0].D());
            roi.insert("Phi",Phi[0].D());
            roi.insert("Length1",Length1[0].D());
            roi.insert("Length2",Length2[0].D());
            roi.insert("isDraw",1);
            roi.insert("x",0);
            roi.insert("y",0);
            if(HDevWindowStack::IsOpen()&hasData)
            {
                Hobject Rectangle;
                gen_rectangle2(&Rectangle,Row,Column,Phi,Length1,Length2);
                disp_obj(Rectangle,WindowHandle);
            }
            if(func==5)
            {
                emit Warning(QStringLiteral("请绘制第二个计算点,按右键结束"));
                draw_rectangle2(WindowHandle,&Row,&Column,&Phi,&Length1,&Length2);
                emit Warning("");
                roi.insert("Row2",Row[0].D());
                roi.insert("Column2",Column[0].D());
                roi.insert("Phi2",Phi[0].D());
                roi.insert("Length3",Length1[0].D());
                roi.insert("Length4",Length2[0].D());
            }
            qDebug()<<"func"<<func<<Row[0].D()<<Column[0].D()<<Phi[0].D();
        }
        else
        {
            //手动输入时需要定位点,所以有了x,y
            double x,y;
            QPoint point=set.value("locationList").toMap().value(QString::number(index)).toPoint();

            x=point.x();
            y=point.y();



            roi.insert("Row",row);
            roi.insert("Column",column);
            roi.insert("Phi",0);
            roi.insert("Length1",length1);
            roi.insert("Length2",length2);
            roi.insert("isDraw",0);
            if(func==5)
            {
                roi.insert("Row2",map.value("Row2").toDouble());
                roi.insert("Column2",map.value("Column2").toDouble());
                roi.insert("Phi2",map.value("Phi2").toDouble());
                roi.insert("Length3",map.value("Length3").toDouble());
                roi.insert("Length4",map.value("Length4").toDouble());
            }
            qDebug()<<"func"<<row<<column<<length1<<length2;
        }
    }
    else
    {
            if(!drawType&(func==0|func==1))
            {
                Error(QStringLiteral("定位与搜索不支持键入区域!!"));
                return;
            }
            draw_rectangle1(WindowHandle,&Row,&Column,&Row2,&Column2);
            //roiList[1-5]





            roi.insert("Row",Row[0].D());
            roi.insert("Column",Column[0].D());
            roi.insert("Row2",Row2[0].D());
            roi.insert("Column2",Column2[0].D());


            qDebug()<<"func"<<func<<Row[0].D()<<Column[0].D();


    }


   //写入配置文件
    //roiList[6-9]

    roi.insert("team",team);
    roi.insert("func",func);
    roi.insert("index",index);
    roi.insert("min",min);
    roi.insert("max",max);
    if(func==2)
        set.setValue("locationList",roi);

    set.setValue("team/"+name,roi);
    roiList.insert(name,QVariant(str));

    QString teamNum=QString::number(team);
    QStringList data;


    data=dataList.value(teamNum).toStringList();

    if(!data.contains(name))
        data<<name;

    dataList.insert(teamNum,data);

    set.setValue("dataList",dataList);
    set.setValue("roiList",roiList);
    set.sync();
    if(func==0)
    {
      //  write_image(Image,"tiff",0,QString("%1_%2.tif").arg(roi.value("team").toInt()).arg(roi.value("index").toInt()).toUtf8().data());
       // createTemplate(team);
    }
    //更新界面
    disp_img();
    emit flushRoiList(roiList.keys());
}

/*
 *  name:matchTemplate
    type:函数
    arg:[1]:int为分组dataList的index


    disciption:
        匹配模板

*/
void halconClass::matchTemplate(int team)
{
    int num=0;
    int ret;
    QTime time;
    HTuple hv_TemplateID;
    QMap<QString,Hobject> rectMap;
    QMap<QString,QList<HTuple>> resultList;
    time.start();
    typedef int (*MT)(Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,HTuple hv_mode,HTuple hv__min,HTuple hv__max,HTuple hv_TemplateID,HTuple* hv_Row, HTuple *hv_Column,HTuple *hv_Angle,HTuple *hv_Score);
    MT cal=NULL;

    cal=(MT)GetProcAddress(hInstance,"Match_template");
   if (HDevWindowStack::IsOpen()&hasData)
    {
        Hobject   Rectangle, image, ImageReduced,rect;
        HTuple  hv_Angle, Area, Row, Column, Min=0, Max=0,Indices;
        HTuple Row2,Column2,Grayval;
        HTuple  Range,String,s,Result,Number;
        HTuple hv_Row,hv_Column;
        QString n=dataList.keys().at(team);

        QStringList list=dataList.value(n).toStringList();

        for(int i=0;i<list.size();i++)
        {
            QStringList str=roiList.value(list.at(i)).toStringList();
            QMap<QString,QVariant> roi=set.value("team/"+list.at(i)).toMap();
            if(roi.value("func").toInt()==0)
            {

                if(imgList.size()<=roi.value("index").toInt())
                    continue;
                gen_rectangle1(&Rectangle,roi.value("Row").toDouble(),roi.value("Column").toDouble(),roi.value("Row2").toDouble(),roi.value("Column2").toDouble());
                rectMap.insert(roi.value("index").toString(),Rectangle);

            }
            if(roi.value("func").toInt()==1)
            {
                if(imgList.size()<=roi.value("index").toInt())
                    continue;


                HTuple TemplateID;
                QFile f(QString("%1_%2.mod").arg(roi.value("team").toInt()).arg(roi.value("index").toInt()).toUtf8().data());
                if(!f.exists())
                {
                    emit Error(QStringLiteral("没有")+ QString("%1_%2.mod").arg(roi.value("team").toInt()).arg(roi.value("index").toInt()).toUtf8().data());
                    return;
                }

                read_ncc_model(QString("%1_%2.mod").arg(roi.value("team").toInt()).arg(roi.value("index").toInt()).toUtf8().data(),&TemplateID);


                qDebug()<<"start match";
                double minRange,maxRange;
                minRange=set.value("minMeasuringRange","-7.5").toDouble();
                maxRange=set.value("maxMeasuringRange","7.5").toDouble();

                ret=(*cal)(*imgList.at(roi.value("index").toInt()),roi.value("Row").toDouble(), roi.value("Column").toDouble(), roi.value("Row2").toDouble(), roi.value("Column2").toDouble(),1,minRange,maxRange,TemplateID,&Row,&Column,&hv_Angle,&Result);
                clear_ncc_model(TemplateID);
                qDebug()<<"ret ="<<ret;
                if(ret==-1)
                {
                    qDebug()<<"at lease one not match";
                    emit Error("match fail!!");
                    return;
                }
                if(ret==1)
                {
                    QList<HTuple> tmp;
                    tmp<<Row<<Column<<hv_Angle;
                    resultList.insert(roi.value("index").toString(),tmp);
                    num++;
                    QStringList l;
                    l<<QString::number(Row[0].D())<<QString::number(Column[0].D())<<QString::number(hv_Angle[0].D());
                    locateList.insert(roi.value("index").toString(),tmp);
                    qDebug()<<"locate"<<l;
                }


            }
        }

        if(num==0)
            return;

        QStringList indexList=rectMap.keys();
        for(int i=0;i<indexList.size();i++)
        {
            HTuple HomMat2D;
            area_center(rectMap.value(indexList.at(i)),&Area,&Row2,&Column2);
            vector_angle_to_rigid(Row2,Column2,0,resultList.value(indexList.at(i)).at(0),resultList.value(indexList.at(i)).at(1),resultList.value(indexList.at(i)).at(2),&HomMat2D);
            matList.insert(indexList.at(i),HomMat2D);


            qDebug()<<"match orginal point"<<Row2[0].D()<<Column2[0].D();

       }
    }

    qDebug()<<QStringLiteral("匹配模板时间:")<<time.elapsed()<<"ms";
}
/*
 *  name:createTemplate
    type:函数
    arg:[1]:int为分组dataList的index


    disciption:
        创建模板

*/
void halconClass::createTemplate(int team)
{
    int num=0;
    QTime time;
    HTuple templateID;
    time.start();

    CT cal=NULL;

    cal=(CT)GetProcAddress(hInstance,"Create_template");
   if (HDevWindowStack::IsOpen()&hasData)
    {
        Hobject image, RegionComplement, ImageReduced,rect;
        HTuple  tmp, tmp2, Row2, Column2, Min=0, Max=0,Indices;
        HTuple Rows,Columns,Grayval;
        HTuple  Range,String,s,Result,Number;

        QString n=dataList.keys().at(team);

        QStringList list=dataList.value(n).toStringList();
        qDebug()<<"create"<<list;
        for(int i=0;i<list.size();i++)
        {
            QStringList str=roiList.value(list.at(i)).toStringList();

            QMap<QString,QVariant> roi=set.value("team/"+list.at(i)).toMap();
            qDebug()<<roi;
            if(roi.value("func").toInt()==0)
            {
                qDebug()<<"create template"<<list.at(i)<<"imgList size"<<imgList.size()<<roi.value("index").toInt();
                if(imgList.size()<=roi.value("index").toInt())
                    continue;
                num++;
                QFile f(QString("%1_%2.tif").arg(roi.value("team").toInt()).arg(roi.value("index").toInt()));
                if(!f.exists())
                {
                    emit Error("no file to locate");
                    return;
                }
                read_image(&image,QString("%1_%2.tif").arg(roi.value("team").toInt()).arg(roi.value("index").toInt()).toUtf8().data());
                HTuple min,max,range;

                qDebug()<<"creat point"<<roi.value("Row").toDouble()<<roi.value("Column").toDouble()<<roi.value("Row2").toDouble()<<roi.value("Column2").toDouble();
                double minRange,maxRange;
                minRange=set.value("minMeasuringRange","-7.5").toDouble();
                maxRange=set.value("maxMeasuringRange","7.5").toDouble();
                int result=(*cal)(image,roi.value("Row").toDouble(), roi.value("Column").toDouble(), roi.value("Row2").toDouble(), roi.value("Column2").toDouble(),1,minRange,maxRange,&templateID);
                qDebug()<<"Create_template"<<result;
                if(templateID.Num()!=0)
                {
                    write_ncc_model(templateID,QString("%1_%2.mod").arg(roi.value("team").toInt()).arg(roi.value("index").toInt()).toUtf8().data());


                    qDebug()<<"templateID get";
                }
                else
                {
                    emit Error("create templateID fail");
                    return;
                }
                }

        }

        if(num==0)
            return;
    }

    qDebug()<<QStringLiteral("生成模板时间:")<<time.elapsed()<<"ms";
}
/*
    取平面拟合点,计算平面度
*/
void halconClass::planePoint(int team)
{
    int num=0;
    if (HDevWindowStack::IsOpen()&hasData)
     {
         Hobject   Rectangle, RegionAffineTrans, ImageReduced,rect;
         HTuple  tmp, Area, Row, Column, Min=0, Max=0,Indices;
         HTuple Rows,Columns,Grayval;
         HTuple  Range,String,s,Result;


         Calculate_Flatness2 cal=NULL;


         cal=(Calculate_Flatness2)GetProcAddress(hInstance,"Calculate_Flatness");



         QString n=dataList.keys().at(team);

         QStringList list=dataList.value(n).toStringList();

         std::vector<double> x,y,z;
         x.resize(100);
         y.resize(100);
         z.resize(100);
         int in=0;
        qDebug()<<"plane list.size"<<list.size();
         for(int i=0;i<list.size();i++)
         {

            QMap<QString,QVariant> roi=set.value("team/"+list.at(i)).toMap();
            if(imgList.size()<=roi.value("index").toInt())
                continue;
             if(roi.value("func").toInt()==3)
             {

                // if(matList.value(roi.value("index").toString(),NULL)==NULL)
              //   {
                //     emit Error(QStringLiteral("定位失败"));
               //      return;
               //  }
                num++;
                 QMap<QString,QVariant> point=set.value("basePoint").toMap();

                 qDebug()<<"start planePoint";
                 qDebug()<<roi.value("index").toString();
                 if(roi.value("isDraw").toInt()==0)
                     gen_rectangle2(&Rectangle,roi.value("Row").toDouble()+point.value(roi.value("index").toString()).toPointF().y(),roi.value("Column").toDouble()+point.value(roi.value("index").toString()).toPointF().x(),roi.value("Phi").toDouble(),roi.value("Lenght1").toDouble(),roi.value("Length2").toDouble());
                 else
                     gen_rectangle2(&Rectangle,roi.value("Row").toDouble(),roi.value("Column").toDouble(),roi.value("Phi").toDouble(),roi.value("Lenght1").toDouble(),roi.value("Length2").toDouble());
                 //affine_trans_region(Rectangle,&RegionAffineTrans,matList.value(roi.value("index").toString()),"false");
                // disp_obj(RegionAffineTrans,WindowHandle);
                // qDebug()<<"planePoint orginal point"<<roi.value("Row").toDouble()<<roi.value("Column").toDouble();
                // area_center(RegionAffineTrans,&Area,&Row,&Column);
                // qDebug()<<"planePoint now point"<<Row[0].D()<<Column[0].D();


                 reduce_domain(*imgList.at(roi.value("index").toInt()), Rectangle, &ImageReduced);

                 get_region_points(ImageReduced, &Rows, &Columns);
                 get_grayval(ImageReduced, Rows, Columns, &Grayval);
                 if(Grayval.Num()==0)
                 {
                     qDebug()<<"grayval:"<<Grayval.Num();
                     continue;
                 }

                 tuple_max(Grayval, &tmp);
                 qDebug()<<"max"<<tmp[0].D();
                 tuple_find(Grayval,0,&Indices);
                 double sumResult;
                 tuple_sum(Grayval,&sumResult);
                 double mean=sumResult/(Grayval.Num());
                 /*
                 if(Indices[0].I()!=-1)
                 {
                     for(int i=0;i<Indices.Num();i++)
                     {

                         Grayval[Indices[i].I()]=tmp;
                     }
                 }
                 tuple_mean(Grayval,&mean);
                 */
                 x[in]=roi.value("Column").toFloat()+point.value(roi.value("index").toString()).toPointF().y();
                 y[in]=roi.value("Row").toFloat()+point.value(roi.value("index").toString()).toPointF().x();
                 z[in]=mean;
                 qDebug()<<"xyz"<<x[in]<<y[in]<<z[in]<<in;
                 in++;


             }
         }
         if(num==0)
             return;


         double result;

         if(in<set.value("check_num",4).toInt())
         {
             emit Error(QString("not enough four point,at lease %1 point").arg(set.value("check_num",4).toInt()));
             return;
         }
         qDebug()<<"cloud";
         tagPoint p;
         tagPlane Plane;

         HTuple dist;
         tagPoint *pointList=listToPoint((double *)&x[0],(double *)&y[0],(double *)&z[0],in);
         PlaneSet(pointList,Plane,in);
         for(int i=0;i<in;i++)
         {
             result=PointToPlane(pointList[i],Plane,result);
             dist.Append(result);
             qDebug()<<result;
         }

         tuple_max(dist,&Max);
         tuple_min(dist,&Min);
         result=abs(Max[0].D()-Min[0].D());
         /// (*cal)(&x[0],&y[0],&z[0],in,result);
         qDebug()<<"cloud"<<result;
         emit sendPlaneness(n.toInt(),result);
         qDebug()<<QStringLiteral("平面度为:")<<result<<Max[0].D()<<Min[0].D();



    }
}
QPoint halconClass::findCenter(Hobject image,double Row,double Column,double Row2,double Column2)
{

    return findCenter(image,HTuple(Row),HTuple(Column),HTuple(Row2),HTuple(Column2));

}
/*
    找一条线的中心点
*/
QPoint halconClass::findCenter(Hobject image,HTuple Row,HTuple Column,HTuple Row2,HTuple Column2)
{
    Hobject Rectangle;
    Hobject ImageReduced, Edges, ObjectSelected;


    // Local control variables
    HTuple  Length, Max, Indices, Area;
    HTuple  PointOrder;
    Hlong num;
    QMap<QString,QVariant> roi=set.value("locationList").toMap();
    gen_rectangle1(&Rectangle,Row,Column,Row2,Column2);

    HTuple low=0.01,hight=0.02;
    reduce_domain(image, Rectangle, &ImageReduced);

    edges_sub_pix(ImageReduced, &Edges, "canny", 1, low,hight);
    length_xld(Edges, &Length);
    count_obj(Edges,&num);

    if(Length.Num()<1)
    {
        qDebug()<<"obj count"<<num;
        emit Error(QStringLiteral("没找到中点!!"));
        return QPoint(-1,-1);
    }
    tuple_max(Length, &Max);
    tuple_find(Length, Max, &Indices);
    select_obj(Edges, &ObjectSelected, Indices+1);
    area_center_xld(ObjectSelected, &Area, &Row, &Column, &PointOrder);
    disp_obj(ObjectSelected,WindowHandle);



    return QPoint(Column[0].D(),Row[0].D());

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
        Hobject   Rectangle, RegionAffineTrans, ImageReduced,rect;
        HTuple  tmp, Row, Column, Area, Min=0, Max=0,Indices;
        HTuple Rows,Columns,Grayval;
        HTuple  Range,s,Result,Number;

        compute_PointNormal2 comp=NULL;
        Distance_point2plane dis=NULL;

        comp=(compute_PointNormal2)GetProcAddress(hInstance,"compute_PointNormal");
        dis=(Distance_point2plane)GetProcAddress(hInstance,"Distance_point2plane");
        QString n=dataList.keys().at(team);

        QStringList list=dataList.value(n).toStringList();

        std::vector<double> x,y,z,temp;
        x.resize(100);
        y.resize(100);
        z.resize(100);
        temp.resize(100);
        int in=0;
        qDebug()<<"heightsub list.size"<<list.size();

        for(int i=0;i<list.size();i++)
        {


            QMap<QString,QVariant> roi=set.value("team/"+list.at(i)).toMap();

            if(roi.value("func").toInt()==4)
            {
                if(imgList.size()<=roi.value("index").toInt())
                    continue;
                num++;
                qDebug()<<"start heightsub";
              //  if(matList.value(roi.value("index").toString(),NULL)==NULL)
              //  {
               //     emit Error(QStringLiteral("定位失败"));
               //     return;
               // }
                 QMap<QString,QVariant> point=set.value("basePoint").toMap();
                if(roi.value("isDraw").toInt()==0)
                    gen_rectangle2(&Rectangle,roi.value("Row").toDouble()+point.value(roi.value("index").toString()).toPointF().y(),roi.value("Column").toDouble()+point.value(roi.value("index").toString()).toPointF().x(),roi.value("Phi").toDouble(),roi.value("Lenght1").toDouble(),roi.value("Length2").toDouble());
                else
                    gen_rectangle2(&Rectangle,roi.value("Row").toDouble(),roi.value("Column").toDouble(),roi.value("Phi").toDouble(),roi.value("Lenght1").toDouble(),roi.value("Length2").toDouble());
                //affine_trans_region(Rectangle,&RegionAffineTrans,matList.value(roi.value("index").toString()),"false");
               //  disp_obj(RegionAffineTrans,WindowHandle);
               // qDebug()<<"RectHeightSub orginal point"<<roi.value("Row").toDouble()<<roi.value("Column").toDouble();
               // area_center(RegionAffineTrans,&Area,&Row,&Column);
              //  qDebug()<<"RectHeightSub now point"<<Row[0].D()<<Column[0].D();
                reduce_domain(*imgList.at(roi.value("index").toInt()), Rectangle, &ImageReduced);
                get_region_points(ImageReduced, &Rows, &Columns);
                get_grayval(ImageReduced, Rows, Columns, &Grayval);
                if(Grayval.Num()==0)
                {
                    qDebug()<<"grayval:"<<Grayval.Num();
                    continue;
                }
                tuple_max(Grayval, &tmp);
                qDebug()<<"max"<<tmp[0].D();
                tuple_find(Grayval,0,&Indices);
                double sumResult;
                tuple_sum(Grayval,&sumResult);
                double mean=sumResult/(Grayval.Num());

                x[in]=roi.value("Row").toFloat()+point.value(roi.value("index").toString()).toPointF().y();
                y[in]=roi.value("Column").toFloat()+point.value(roi.value("index").toString()).toPointF().x();
                z[in]=mean;
                temp[in]=i;
                qDebug()<<"xyz"<<x[in]<<y[in]<<z[in]<<in;
                in++;
            }
        }

        if(num==0)
            return;

        qDebug()<<"creat cloud";
        double result;

        VectorInfo vec;
       // result=(*comp)(&x[0],&y[0],&z[0],in,&vec);

        if(in<set.value("check_num",4).toInt()+1)
        {
            emit Error(QString("not enough four point,at least %1 point!!").arg(set.value("check_num",4).toInt()+1));
            return;
        }
        tagPlane Plane;
        tagPoint *pointList=listToPoint((double *)&x[0],(double *)&y[0],(double *)&z[0],in);
        PlaneSet(pointList,Plane,in);
        for(int j=0;j<in;j++)
        {

            QMap<QString,QVariant> roi=set.value("team/"+list.at(temp[j])).toMap();

            HTuple dist;


           if(roi.value("func").toInt()==4)
           {
               tagPoint p;
               p.x=x[j];
               p.y=y[j];
               p.z=z[j];
               result=PointToPlane(pointList[j],Plane,result);
               dist.Append(result);

              // (*dis)(p,vec,result);
               qDebug()<<"heightSub"<<list.at(temp[j])<<result;
               emit sendHeightSub(list.at(temp[j]),0,0,result);
           }


        }
        }


    qDebug()<<QStringLiteral("计算高差时间:")<<time.elapsed()<<"ms";
}
/*
    两点之间的高差
*/
void halconClass::pointToPoint(int team)
{
    int num=0;
    QTime time;
    time.start();
    if (HDevWindowStack::IsOpen()&hasData)
    {
        Hobject   Rectangle, RegionAffineTrans, ImageReduced,rect;
        HTuple  tmp, Row, Column, Area, Min=0, Max=0,Indices;
        HTuple Rows,Columns,Grayval;
        HTuple  Range,s,Result,Number;


        Distance_point2plane dis=NULL;
        dis=(Distance_point2plane)GetProcAddress(hInstance,"Distance_point2plane");
        QString n=dataList.keys().at(team);

        QStringList list=dataList.value(n).toStringList();


        int in=0;
        qDebug()<<"pointtoponit list.size"<<list.size();

        for(int i=0;i<list.size();i++)
        {
            QMap<QString,QVariant> roi=set.value("team/"+list.at(i)).toMap();

            if(roi.value("func").toInt()==5)
            {
                if(imgList.size()<=roi.value("index").toInt())
                    continue;
                num++;
                qDebug()<<"start ptop";
             //   if(matList.value(roi.value("index").toString(),NULL)==NULL)
              //  {
              //      emit Error(QStringLiteral("定位失败"));
               //     return;
              //  }
                QMap<QString,QVariant> point=set.value("basePoint").toMap();
                if(roi.value("isDraw").toInt()==0)
                    gen_rectangle2(&Rectangle,roi.value("Row").toDouble()+point.value(roi.value("index").toString()).toPointF().y(),roi.value("Column").toDouble()+point.value(roi.value("index").toString()).toPointF().x(),roi.value("Phi").toDouble(),roi.value("Lenght1").toDouble(),roi.value("Length2").toDouble());
                else
                    gen_rectangle2(&Rectangle,roi.value("Row").toDouble(),roi.value("Column").toDouble(),roi.value("Phi").toDouble(),roi.value("Lenght1").toDouble(),roi.value("Length2").toDouble());
               // affine_trans_region(Rectangle,&RegionAffineTrans,matList.value(roi.value("index").toString()),"false");
               //  disp_obj(RegionAffineTrans,WindowHandle);
                //qDebug()<<"ptop orginal point"<<roi.value("Row").toDouble()<<roi.value("Column").toDouble();
               // area_center(RegionAffineTrans,&Area,&Row,&Column);
               // qDebug()<<"ptop now point"<<Row[0].D()<<Column[0].D();
                reduce_domain(*imgList.at(roi.value("index").toInt()), Rectangle, &ImageReduced);
                get_region_points(ImageReduced, &Rows, &Columns);
                get_grayval(ImageReduced, Rows, Columns, &Grayval);

                tuple_sort(-Grayval,&Grayval);

                tuple_select_range(Grayval,0,5,&Grayval);

                tuple_mean(-Grayval,&tmp);
                //min_max_gray(ImageReduced,ImageReduced,0,&Min,&Max,&Range);
                if(roi.value("isDraw").toInt()==0)
                    gen_rectangle2(&Rectangle,roi.value("Row2").toDouble()+point.value(roi.value("index").toString()).toPointF().y(),roi.value("Column2").toDouble()+point.value(roi.value("index").toString()).toPointF().x(),roi.value("Phi2").toDouble(),roi.value("Lenght3").toDouble(),roi.value("Length4").toDouble());
                else
                    gen_rectangle2(&Rectangle,roi.value("Row2").toDouble(),roi.value("Column2").toDouble(),roi.value("Phi2").toDouble(),roi.value("Lenght13").toDouble(),roi.value("Length4").toDouble());

                reduce_domain(*imgList.at(roi.value("index").toInt()), Rectangle, &ImageReduced);
                get_region_points(ImageReduced, &Rows, &Columns);
                get_grayval(ImageReduced, Rows, Columns, &Grayval);

                tuple_sort(-Grayval,&Grayval);

                tuple_select_range(Grayval,0,5,&Grayval);
                if(Grayval.Num()<=0)
                {
                    qDebug()<<"ptop error";
                    return;
                }
                tuple_mean(-Grayval,&Max);

                tuple_sub(Max,tmp,&Result);
                tuple_abs(Result,&Result);
                emit sendHeightSub(list.at(i),0,0,Result[0].D());


            }
        }

    }
}
/*
    计算所有区域
*/
void halconClass::calculate()
{
   // emit reConnect();
    //emit clearMemory();
    QMap<QString,QVariant> point;
    for(int i=0;i<imgList.size();i++)
    {
        QPointF p=calculateBasePoint(i);

        point.insert(QString::number(i),p);

         //emit Warning(QString("basePoint:%1,%2").arg(basePointList.at(i).x()).arg(basePointList.at(i).y()));
    }
    set.setValue("basePoint",point);
    set.sync();
    emit disp_img();

    for(int i=0;i<dataList.size();i++)
    {

        //matchTemplate(i);

        planePoint(i);
        RectHeightSub(i);
        pointToPoint(i);
    }




}
/*
    计算平面度-已废弃
*/
void halconClass::calculatePlaneness(int team)
{

    double result1,result2;
    int num=0;


	QTime time;
	time.start();



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
            QMap<QString,QVariant> roi=set.value("team/"+list.at(i)).toMap();
			
            if(roi.value("func").toInt()==1)
            {

                if(imgList.size()<=roi.value("index").toInt())
                    continue;
                 num++;
                POINT p1,p2;
                p1.x=roi.value("Column").toInt()+roi.value("index").toInt()*img_width;
                p1.y=roi.value("Row").toInt();
                p2.x=roi.value("Column2").toInt()+roi.value("index").toInt()*img_width;
                p2.y=roi.value("Row2").toInt();
                qDebug()<<"start and end"<<p1.x<<p1.y<<p2.x<<p2.y;

				

				qDebug()<<"cacule flatness"<<num;
               // pcl::io::savePCDFile(QString("roi%1.pcd").arg(i).toUtf8().data(),*(newCloud.get()));


            }
         }

        if(num==0)
            return;

        //delete newCloud.get();
        qDebug()<<"team"<<team<<QStringLiteral("总平整度为")<<result1<<result2<<time.elapsed()<<"ms";
        emit sendPlaneness(n.toInt(),result1);
     }

}
/*
    读取设置
*/
void halconClass::readSettings()
{

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


    double *yy=new double[h*w];
    for(int i=0;i<h;i++)
    {
		float xx=i*set.value("testValue",0.01).toFloat();
        for(int j=0;j<w;j++)
         yy[i*w+j]=xx;
		
    }
	qDebug()<<"run";

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
    static int num=0;

    if(imgList.size()==set.value("imgNum",8).toInt())
    {
        clearData();
    }

    if(num>set.value("imgNum",8).toInt()|imgList.size()==0)
    {
        num=0;
        index=imgList.size()-1;

    }

    index++;
    Hobject Imagetemp;
    recvCount=h;
    if(!HDevWindowStack::IsOpen())
        return;


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
            clear_window(WindowHandle);
        }
    }
    gen_image_const(&Imagetemp,"real",w,set.value("profileCount",1000).toUInt()>h?set.value("profileCount",1000).toUInt():h);
    get_image_pointer1(Imagetemp,(long*)&pointer,type,&width,&height);
    scale=win_width/w;
    xScale=w/win_width;
    yScale=h/win_height;
    //set_part(WindowHandle,0,0,h,w*yScale);

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


    if(set.value("doubleTurn",false).toBool()&num!=0&num%2==1)
    {
        mirror_image(Imagetemp,&Imagetemp,"row");
        qDebug()<<"mirror";
    }
    write_image(Imagetemp,"tiff",0,QString("test%1").arg(num).toUtf8().data());
    resizePart();
    copy_image(Imagetemp,&Image);
    //copy_obj(Imagetemp,&Image,1,1);

    if(h>=set.value("profileCount",1000).toUInt()|isLoadFile)
	{
		img_width=width;
		img_height=height;
        xScale=width/win_width;
        yScale=height/win_height;
        Hobject *tmp=new Hobject;
        //copy_image(Imagetemp,tmp);
        copy_obj(Imagetemp,tmp,1,1);
        imgList.push_back(tmp);


        num++;
        emit addImg(tmp);
        if(imgList.size()==set.value("imgNum",8).toInt())
            calculate();
        if(imgList.size()>set.value("imgNum",8).toInt())
        {
            Hobject *obj=imgList.takeFirst();
            qDebug("obj=%x",obj);
            clear_obj(*obj);

            emit deleteImg(0);
            index=0;

            selectImg(index);


        }


	}
	hasData=true;
    isLoadFile=false;


    emit dispImg();
   
}
/*
合成3D,有缺陷
*/
void halconClass::compoundImg(int xOffset,int yOffset)
{
    HTuple hv_Exception;
   // try{
  //  HException::InstallHHandler(&CPPExpDefaultExceptionHandler);

    Hobject img,tmpImg;
    HTuple w,h;
    Hlong width,height;
    float *pointer,*p2;
    char type[100];
    /*
    for(int i=0;i<imgList.size();i++)
    {

        concat_obj(*imgList.at(i),img,&img);

    }

    tile_images(img,&tmpImg,imgList.size(),"horizontal");
    get_image_size(tmpImg,&width,&height);
    qDebug()<<width<<height;
    gen_image_const(&Image,"real",width,height);
    copy_image(tmpImg,&Image);
    set_part(WindowHandle,0,0,height,width);
    return;
*/
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
    set_part(WindowHandle,0,0,height,width*yScale);
    //}catch (HException &HDevExpDefaultException)
   // {
   //     HDevExpDefaultException.ToHTuple(&hv_Exception);
   //     qDebug()<<hv_Exception.;
  //  }

}

/*
    根据三条线段确定一个基准点
    Row1,Column1,Row2,Column2为四个数组,里面共有三组矩阵数据
    矩阵都需要包含一条边
    计算结果为根据后面两条边的中点相连后得出的线段中点,垂直于第一条边的交点
*/
QPointF halconClass::calculateBasePoint(int index)
{
    Hobject  ROI_0, ImageReduced, ROI_1, ImageReduced1;
      Hobject  Edges, SelectedContours, ROI_2, ImageReduced2, RegionLines;


      // Local control variables
      HTuple  Length;
      HTuple  Max, RowBegin, ColBegin, RowEnd, ColEnd, Nr, Nc;
      HTuple  Dist;
      HTuple  Area, Row, Column;

      QMap<QString,QVariant> roi=set.value("locationList").toMap().value(QString::number(index)).toMap();
      HTuple Row1,Column1,Row2,Column2,Length2;
      Row1.Append(roi.value("Row").toDouble());
      Row2.Append(roi.value("Row1").toDouble());
      Row1.Append(roi.value("Row2").toDouble());
      Row2.Append(roi.value("Row3").toDouble());
      Row1.Append(roi.value("Row4").toDouble());
      Row2.Append(roi.value("Row5").toDouble());
      Column1.Append(roi.value("Column").toDouble());
      Column2.Append(roi.value("Column1").toDouble());
      Column1.Append(roi.value("Column2").toDouble());
      Column2.Append(roi.value("Column3").toDouble());
      Column1.Append(roi.value("Column4").toDouble());
      Column2.Append(roi.value("Column5").toDouble());


      //gen_rectangle1(&ROI_0, Row1, Column1, Row2, Column2);

      gen_rectangle1(&ROI_0,Row1[0].D(),Column1[0].D(),Row2[0].D(),Column2[0].D());
      reduce_domain(*imgList.at(roi.value("index").toInt()), ROI_0, &ImageReduced);


      edges_sub_pix(ImageReduced, &Edges, "canny", 1, HTuple(0.01), HTuple(0.02));
      length_xld(Edges,&Length);
      if(Length.Num()<1)
      {
          return QPointF(0,0);
      }
      tuple_max(Length,&Max);
      select_contours_xld(Edges, &SelectedContours, "contour_length", Max, Max, 0.01,
            0.02);
      disp_obj(SelectedContours,WindowHandle);
      fit_line_contour_xld(SelectedContours, "tukey", -1, 0, 5, 2, &RowBegin, &ColBegin,
          &RowEnd, &ColEnd, &Nr, &Nc, &Dist);
      qDebug()<<"line"<<RowBegin[0].D()<<ColBegin[0].D()<<RowEnd[0].D()<<ColEnd[0].D();


      QPoint p1=findCenter(*imgList.at(roi.value("index").toInt()),Row1[1].D(),Column1[1].D(),Row2[1].D(),Column2[1].D());

      QPoint p2=findCenter(*imgList.at(roi.value("index").toInt()), Row1[2].D(), Column1[2].D(), Row2[2].D(), Column2[2].D());


      gen_region_line(&RegionLines, p1.y(), p1.x(),p2.y(), p2.x());
      //Clear measure when done
      area_center(RegionLines, &Area, &Row, &Column);
    qDebug()<<Column[0].D()<<Row[0].D();
        QPointF base=pointToLine(QPointF(ColBegin[0].D(),RowBegin[0].D()),QPointF(ColEnd[0].D(),RowEnd[0].D()),QPointF(Column[0].D(),Row[0].D()));
      return base;
}

/** @ brief 根据两点求出垂线过第三点的直线的交点
    @ param pt1 直线上的第一个点
    @ param pt2 直线上的第二个点
    @ param pt3 垂线上的点
    @ return 返回点到直线的垂直交点坐标
  */
QPointF halconClass::pointToLine(const QPointF &pt1, const QPointF &pt2, const QPointF &pt3)
{
    //874 207.5 278 207.5
    qreal A = (pt1.y()-pt2.y())/(pt1.x()- pt2.x());
    qreal B = (pt1.y()-A*pt1.x());
    /// > 0 = ax +b -y;  对应垂线方程为 -x -ay + m = 0;(mm为系数)
    /// > A = a; B = b;
    qreal m = pt3.x() + A*pt3.y();

    /// 求两直线交点坐标
    QPointF ptCross;
    ptCross.setX((m-A*B)/(A*A + 1));
    ptCross.setY(A*ptCross.x()+B);
    return ptCross;
}
void CPPExpDefaultExceptionHandler(const Halcon::HException& except)
{
  throw except;
}
