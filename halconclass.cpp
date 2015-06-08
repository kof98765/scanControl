#include "halconclass.h"
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
    unitList.clear();
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

    QMap<QString,QVariant> teamPoint = set.value("basePoint").toMap();
    if(teamPoint.size()>0)
    {
        for(int i=0;i<teamPoint.size();i++)
        {
            QMap<QString,QVariant> point=teamPoint.value(QString::number(i)).toMap();
            QPointF p=point.value(QString::number(index)).toPointF();
            qDebug()<<p.x()<<p.y();
            emit reportBasePoint(p.x(),p.y());




        }
    }
    copy_image(*imgList.at(i),&Image);
    clear_window(WindowHandle);
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

        for(int i=0;i<unitList[index].size();i++)
        {
            disp_obj(unitList[index].at(i),WindowHandle);
        }
       // disp_obj(tmpObj,WindowHandle);
        //显示矩形窗口
        QStringList list=roiList.keys();
        //绘制基准点相关图形

        QMap<QString,QVariant> teamPoint = set.value("basePoint").toMap();

        for(int i=0;i<teamPoint.size();i++)
        {
           QMap<QString,QVariant> point=teamPoint.value(QString::number(i)).toMap();
           QPointF p=point.value(QString::number(index)).toPointF();

           set_tposition(WindowHandle,p.y(),p.x());
           gen_cross_contour_xld(&Rectangle,p.y(),p.x(),20,0);
           //gen_rectangle2(&Rectangle,point.value(QString::number(index)).toPointF().y(),point.value(QString::number(index)).toPointF().x(),0,5,5);
           disp_obj(Rectangle,WindowHandle);
           write_string(WindowHandle,QString("center%1").arg(i).toUtf8().data());


            QMap<QString,QVariant> baseList=set.value("team").toMap().value(QString::number(i)).toMap();

            if(baseList.keys().size()<=0)
                continue;

            QMap<QString,QVariant> base=baseList.value(QString::number(index)).toMap();

            if(base.keys().size()<=0)
                continue;
            if(base.value("func").toInt()==2)
            {
                disp_xld(base.value("Row").toDouble(),base.value("Column").toDouble(),base.value("Row1").toDouble(),base.value("Column1").toDouble());
                disp_xld(base.value("Row2").toDouble(),base.value("Column2").toDouble(),base.value("Row3").toDouble(),base.value("Column3").toDouble());
                disp_xld(base.value("Row4").toDouble(),base.value("Column4").toDouble(),base.value("Row5").toDouble(),base.value("Column5").toDouble());
            }
            if(base.value("func").toInt()==1|base.value("func").toInt()==0)
            {
                disp_xld(base.value("Row").toDouble(),base.value("Column").toDouble(),base.value("Row1").toDouble(),base.value("Column1").toDouble());
            }
        }
        if(list.size()==0)
            return;

        for(int i=0;i<list.size();i++)
        {
            QMap<QString,QVariant> roi=set.value("team/"+list.at(i)).toMap();
            double x=0,y=0;

                QMap<QString,QVariant> point=teamPoint.value(roi.value("team").toString()).toMap();


                    x=point.value(QString::number(index)).toPointF().x();
                    y=point.value(QString::number(index)).toPointF().y();


            if(roi.value("index").toInt()==index)
            {


                Hobject Rectangle,Contours;

                if(roi.value("func").toInt()==0)
                {
                    gen_rectangle1(&Rectangle, (Hlong)roi.value("Row").toDouble(), (Hlong)roi.value("Column").toDouble(),(Hlong)roi.value("Row2").toDouble(), (Hlong)roi.value("Column2").toDouble());

                }
                else
                {

                    gen_rectangle2(&Rectangle,roi.value("Row").toDouble()+y,roi.value("Column").toDouble()+x,roi.value("Phi").toDouble(),roi.value("Length1").toDouble(),roi.value("Length2").toDouble());
                    if(roi.value("func").toInt()==5)
                    {
                        Hobject Rectangle2;
                        gen_rectangle2(&Rectangle2,roi.value("Row2").toDouble()+y,roi.value("Column2").toDouble()+x,roi.value("Phi2").toDouble(),roi.value("Length3").toDouble(),roi.value("Length4").toDouble());
                        gen_contour_region_xld(Rectangle2,&Contours,"border");
                        disp_obj(Contours,WindowHandle);

                    }
                    set_tposition(WindowHandle,roi.value("Row").toDouble()+y,roi.value("Column").toDouble()+x);



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
    HTuple hv_Exception;
    try{
    HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
    update_window_pose(WindowHandle, lastRow*yScale, lastCol*xScale, Row*yScale, Column*xScale, mode.toUtf8().data());
    disp_obj(result_img,WindowHandle);
    }catch (HException &HDevExpDefaultException)
    {
        HDevExpDefaultException.ToHTuple(&hv_Exception);
        return;
    }

}
QPoint halconClass::getPoint()
{
    double x,y;
    Hlong button;

    HTuple hv_Exception;
    try{
    HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
    if(!is3D)
        get_mposition_sub_pix(WindowHandle,&y,&x,&button);
    }catch (HException &HDevExpDefaultException)
    {
        HDevExpDefaultException.ToHTuple(&hv_Exception);
        return QPoint(0,0);
    }


    return QPoint(x,y);
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


    set.setValue("dataList",dataList);
    set.setValue("roiList",roiList);
    set.remove("team/"+name);
    set.sync();

	if (HDevWindowStack::IsOpen())
		clear_window(WindowHandle);
    disp_img();
}
/*
    获取两点一线确定基准点所需要的参数
*/
void halconClass::twoPointOneLineBasePoint(QMap<QString,QVariant> map)
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
    QMap<QString,QVariant> teamMap=set.value("team").toMap();
    QMap<QString,QVariant> local=teamMap.value(map.value("team").toString()).toMap();

    local.insert(QString::number(index),map);

    teamMap.insert(map.value("team").toString(),local);

    set.setValue("team",teamMap);
    emit Warning("");

    set.sync();
}
/*
    以一个圆来确定基准点
*/
void halconClass::oneRectBasePoint(QMap<QString,QVariant> map)
{
    Hobject Rectangle;
    HTuple  Row, Column, Row2, Column2;
    int color=map.value("color").toInt();
    set_rgb(WindowHandle,(int)((color&(0xff<<16))>>16),(int)((color&(0xff<<8))>>8),(int)(color&0xff));
    emit Warning(QStringLiteral("框一个圆或者一个方块,以找到其中心点"));
    draw_rectangle1(WindowHandle,&Row,&Column,&Row2,&Column2);
     map.insert("Row",Row[0].D());
     map.insert("Column",Column[0].D());
     map.insert("Row1",Row2[0].D());
     map.insert("Column1",Column2[0].D());
      map.insert("index",index);
      QMap<QString,QVariant> teamMap=set.value("team").toMap();
      QMap<QString,QVariant> local=teamMap.value(map.value("team").toString()).toMap();

      local.insert(QString::number(index),map);

      teamMap.insert(map.value("team").toString(),local);

      set.setValue("team",teamMap);
      emit Warning("");

      set.sync();

}
/*
    判断使用哪一种定位算法
*/
void halconClass::drawToFindBasePoint(QMap<QString,QVariant> map)
{
    int func=map.value("func").toInt();
    switch(func)
    {
    case 0:
        write_image(Image,"tiff",0,QString("%1.tif").arg(index).toUtf8().data());
        createTemplate(map);
        break;
    case 1:
        oneRectBasePoint(map);
        break;
    case 2:
        twoPointOneLineBasePoint(map);
        break;

    }
}

/*
    绘制计算区域
*/
void halconClass::drawRect(QMap<QString,QVariant> map)
{
    int i=0;
    Hobject Rectangle;
    QString name=map.value("name").toString();//区域名
    int team=map.value("team").toInt();//分组
    int color=map.value("color").toInt();//区域颜色
    int func=map.value("func").toInt();//计算方法
    double min=map.value("min").toDouble();//阈值最小值
    double max=map.value("max").toDouble();//阈值最大值
    double row=map.value("Row").toDouble();//y坐标
    double column=map.value("Column").toDouble();//x坐标
    double length1=map.value("Length1",50).toDouble();//区域长
    double length2=map.value("Length2",50).toDouble();//区域宽
    int unit=map.value("unit").toInt();
    int drawType=map.value("drawType").toInt();//是否是手动画的

    //检测文件名,如有重名,则修改,如没有名字,就设置默认
    if(name.isEmpty())
        name="rect000";
    while(set.contains("team/"+name))
    {

        name=QString("rect%1").arg(i++,3,10,QLatin1Char('0'));
    }
    //如果是定位算法,则跳转
    if(func==2|func==1|func==0)
    {
        drawToFindBasePoint(map);
        return;
    }
    HTuple  Row, Column, Row2, Column2,Phi,Length1,Length2, Max;
    QStringList str;
    Roi roi2;

    QMap<QString,QVariant> roi;//用于存储整个计算区域的所有属性
    //先设置绘制的颜色
    set_rgb(WindowHandle,(int)((color&(0xff<<16))>>16),(int)((color&(0xff<<8))>>8),(int)(color&0xff));

    roi.insert("color",color);
    //3为平面度计算 4为平面-高差计算 5为两点高差计算
    if(func==3|func==4|func==5)
    {
        if(drawType)
        {
            draw_rectangle2(WindowHandle,&Row,&Column,&Phi,&Length1,&Length2);
            //roiList[1-5]
            double x=0,y=0;
            QMap<QString,QVariant> teamPoint=set.value("basePoint").toMap();
            qDebug()<<teamPoint;
            QMap<QString,QVariant> point=teamPoint.value(map.value("team").toString()).toMap();

            x=point.value(QString::number(index)).toPointF().x();
            y=point.value(QString::number(index)).toPointF().y();



            roi.insert("Row",Row[0].D()-y);
            roi.insert("Column",Column[0].D()-x);
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
            qDebug()<<"xy"<<Row[0].D()<<Column[0].D()<<x<<y;
            //两点高差计算需要第二个点
            if(func==5)
            {
                emit Warning(QStringLiteral("请绘制第二个计算点,按右键结束"));
                draw_rectangle2(WindowHandle,&Row,&Column,&Phi,&Length1,&Length2);
                emit Warning("");
                roi.insert("Row2",Row[0].D()-y);
                roi.insert("Column2",Column[0].D()-x);
                roi.insert("Phi2",Phi[0].D());
                roi.insert("Length3",Length1[0].D());
                roi.insert("Length4",Length2[0].D());
            }

        }
        else
        {


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

        }
    }
    else
    {
        if(!drawType&(func==0|func==1|func==2))
        {
            Error(QStringLiteral("定位不支持键入区域!!"));
            return;
        }
        draw_rectangle1(WindowHandle,&Row,&Column,&Row2,&Column2);
        //roiList[1-5]

        roi.insert("Row",Row[0].D());
        roi.insert("Column",Column[0].D());
        roi.insert("Row2",Row2[0].D());
        roi.insert("Column2",Column2[0].D());



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
    /*
    QVariant v;
    v.setValue(roi2);
    set.setValue("roi",v);
    if(v.canConvert<Roi>())   //判断能否转化为相应类型
        {
            Roi v11 = var1.value<struct1>();
        }

    Roi aa = v.value<Roi>();
    */
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
    qDebug()<<"add finish";
    //更新界面

    disp_img();
    emit flushRoiList(roiList.keys());
}
QPointF halconClass::matchTemplate(QMap<QString,QVariant> roi)
{
    HTuple TemplateID,Row,Column,hv_Angle,Result;
    typedef int (*MT)(Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,HTuple hv_mode,HTuple hv__min,HTuple hv__max,HTuple hv_TemplateID,HTuple* hv_Row, HTuple *hv_Column,HTuple *hv_Angle,HTuple *hv_Score);
    MT cal=NULL;

    cal=(MT)GetProcAddress(hInstance,"Match_template");


    QFile f(QString("%1_%2.mod").arg(roi.value("index").toInt()).arg(roi.value("team").toInt()).toUtf8().data());
    if(!f.exists())
    {
        emit Error(QStringLiteral("没有")+ QString("%1_%2.mod").arg(roi.value("index").toInt()).arg(roi.value("team").toInt()).toUtf8().data());
        return QPointF(0,0);
    }

    read_ncc_model(QString("%1_%2.mod").arg(roi.value("index").toInt()).arg(roi.value("team").toInt()).toUtf8().data(),&TemplateID);


    qDebug()<<"start match";
    double minRange,maxRange;
    minRange=set.value("minMeasuringRange","-7.5").toDouble();
    maxRange=set.value("maxMeasuringRange","7.5").toDouble();

    int ret=(*cal)(*imgList.at(roi.value("index").toInt()),roi.value("Row").toDouble()-200, roi.value("Column").toDouble()-200,roi.value("Row1").toDouble()+200, roi.value("Column1").toDouble()+200,1,minRange,maxRange,TemplateID,&Row,&Column,&hv_Angle,&Result);
    clear_ncc_model(TemplateID);
    qDebug()<<"ret ="<<ret;
    if(ret==-1)
    {
        qDebug()<<"at lease one not match";
        emit Error("match fail!!");
        return QPointF(0,0);
    }
    if(ret==1)
    {
        return QPointF(Column[0].D(),Row[0].D());

    }


}
/*
 *  name:matchTemplate
    type:函数
    arg:[1]:int为分组dataList的index


    disciption:
        匹配模板

*/
/*
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
*/
/*
 *  name:createTemplate
    type:函数
    arg:[1]:int为分组dataList的index


    disciption:
        创建模板

*/
void halconClass::createTemplate(QMap<QString,QVariant> map)
{
    int num=0;
    QTime time;
    HTuple templateID;
    time.start();
    Hobject Rectangle;
    HTuple  Row, Column, Row2, Column2;
    int color=map.value("color").toInt();
    set_rgb(WindowHandle,(int)((color&(0xff<<16))>>16),(int)((color&(0xff<<8))>>8),(int)(color&0xff));
    emit Warning(QStringLiteral("框一个特征明显的物体,以创建模板"));
    draw_rectangle1(WindowHandle,&Row,&Column,&Row2,&Column2);
     map.insert("Row",Row[0].D());
     map.insert("Column",Column[0].D());
     map.insert("Row1",Row2[0].D());
     map.insert("Column1",Column2[0].D());
      map.insert("index",index);
      QMap<QString,QVariant> teamMap=set.value("team").toMap();
      QMap<QString,QVariant> local=teamMap.value(map.value("team").toString()).toMap();

      local.insert(QString::number(index),map);

      teamMap.insert(map.value("team").toString(),local);

      set.setValue("team",teamMap);
      emit Warning("");

      set.sync();

    CT cal=NULL;

    cal=(CT)GetProcAddress(hInstance,"Create_template");

    Hobject image;



    num++;
    QFile f(QString("%1.tif").arg(index));
    if(!f.exists())
    {
        emit Error("no file to locate");
        return;
    }
    read_image(&image,QString("%1.tif").arg(map.value("index").toInt()).toUtf8().data());
    HTuple min,max,range;


    double minRange,maxRange;
    minRange=set.value("minMeasuringRange","-7.5").toDouble();
    maxRange=set.value("maxMeasuringRange","7.5").toDouble();
    int result=(*cal)(image,Row[0].D(), Column[0].D(),Row2[0].D(),Column2[0].D(),1,minRange,maxRange,&templateID);
    qDebug()<<"Create_template"<<result;
    if(templateID.Num()!=0)
    {
        write_ncc_model(templateID,QString("%1_%2.mod").arg(map.value("index").toInt()).arg(map.value("team").toInt()).toUtf8().data());


        qDebug()<<"templateID get";
    }
    else
    {
        emit Error("create templateID fail");
        return;
    }

    qDebug()<<QStringLiteral("生成模板时间:")<<time.elapsed()<<"ms";
}
/*
    取平面拟合点,计算平面度
*/
void halconClass::calculatePlaneness(int team)
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

         std::vector<double> xv,yv,zv;
         xv.resize(100);
         yv.resize(100);
         zv.resize(100);
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
                double x=0,y=0;
                QMap<QString,QVariant> teamPoint=set.value("basePoint").toMap();

                    QMap<QString,QVariant> point=teamPoint.value(roi.value("team").toString()).toMap();

                    x=point.value(roi.value("index").toString()).toPointF().x();
                    y=point.value(roi.value("index").toString()).toPointF().y();


                 qDebug()<<"start planePoint";


                 gen_rectangle2(&Rectangle,roi.value("Row").toDouble()+y,roi.value("Column").toDouble()+x,roi.value("Phi").toDouble(),roi.value("Lenght1").toDouble(),roi.value("Length2").toDouble());

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

                 double sumResult;
                 tuple_sum(Grayval,&sumResult);
                 double mean=sumResult/(Grayval.Num());


                 xv[in]=roi.value("Column").toFloat()+x;
                 yv[in]=roi.value("Row").toFloat()+y;


                 zv[in]=mean;
                 qDebug()<<"xyz"<<xv[in]<<yv[in]<<zv[in]<<in;
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

         tagPoint p;
         tagPlane Plane;

         HTuple dist;
         tagPoint *pointList=listToPoint(&xv[0],&yv[0],&zv[0],in);
         //求平面方程
         PlaneSet(pointList,Plane,in);
         for(int i=0;i<in;i++)
         {
            //点到平面高度
             result=PointToPlane(pointList[i],Plane,result);
             dist.Append(result);

         }

         tuple_max(dist,&Max);
         tuple_min(dist,&Min);
         result=abs(Max[0].D()-Min[0].D());
         /// (*cal)(&x[0],&y[0],&z[0],in,result);

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
    static int order=0;

    // Local control variables
    HTuple  Length, Max, Indices, Area;
    HTuple  PointOrder;
    Hlong num;
    QMap<QString,QVariant> roi=set.value("locationList").toMap();
    gen_rectangle1(&Rectangle,Row,Column,Row2,Column2);
   // qDebug()<<Row[0].D()<<Column[0].D()<<Row2[0].D()<<Column2[0].D();
    HTuple low=1,hight=2;
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

    select_contours_xld(Edges,&ObjectSelected,"contour_length",Max,Max,-0.5,0.5);

   // area_center_xld(ObjectSelected, &Area, &Row, &Column, &PointOrder);
    get_contour_xld(ObjectSelected,&Row,&Column);
    disp_obj(ObjectSelected,WindowHandle);


    return QPoint(Column[0].D(),Row[0].D());

}
QPointF halconClass::findRectCenter(QMap<QString,QVariant> roi)
{
    Hobject Region,Edges,ImageReduced,SelectedContours,ContEllipse;
    HTuple Length,Max,Area,PointOrder,Row,Column,Radius1,Radius2,Phi,StartPhi,EndPhi;
    gen_rectangle1(&Region,roi.value("Row").toDouble(),roi.value("Column").toDouble(),roi.value("Row1").toDouble(),roi.value("Column1").toDouble());
    reduce_domain(*imgList.at(roi.value("index").toInt()),Region,&ImageReduced);
    HTuple low=1,hight=2;
    edges_sub_pix(ImageReduced, &Edges, "canny", 1, low,hight);
    select_contours_xld(Edges,&SelectedContours,"curvature",5,50, 0, 0);
    length_xld(SelectedContours, &Length);
    if(Length.Num()<1)
    {
        qDebug()<<"not find the center!";
        return QPointF(0,0);
    }
    tuple_max(Length, &Max);
    select_contours_xld(Edges, &SelectedContours, "contour_length", Max, Max, -0.5, 0.5);
    HTuple hv_Exception;
    try{
        HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
        fit_ellipse_contour_xld(SelectedContours, "fitzgibbon", -1, 0, 0, 200, 3, 2, &Row,
                                &Column, &Phi, &Radius1, &Radius2, &StartPhi, &EndPhi, &PointOrder);
        gen_ellipse_contour_xld(&ContEllipse, Row, Column, Phi, Radius1, Radius2, 0, 6.28318,
                                "positive", 1.5);


    }catch (HException &HDevExpDefaultException)
    {
        HDevExpDefaultException.ToHTuple(&hv_Exception);
        qDebug()<<QStringLiteral("没找到中心");
        return QPointF(0,0);
    }
    return QPointF(Column[0].D(),Row[0].D());
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

        std::vector<double> xv,yv,zv,temp;
        xv.resize(100);
        yv.resize(100);
        zv.resize(100);
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

              //  if(matList.value(roi.value("index").toString(),NULL)==NULL)
              //  {
               //     emit Error(QStringLiteral("定位失败"));
               //     return;
               // }
                double x=0,y=0;
                QMap<QString,QVariant> teamPoint=set.value("basePoint").toMap();

                QMap<QString,QVariant> point=teamPoint.value(roi.value("team").toString()).toMap();

                x=point.value(roi.value("index").toString()).toPointF().x();
                y=point.value(roi.value("index").toString()).toPointF().y();


                 gen_rectangle2(&Rectangle,roi.value("Row").toDouble()+y,roi.value("Column").toDouble()+x,roi.value("Phi").toDouble(),roi.value("Lenght1").toDouble(),roi.value("Length2").toDouble());

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

                tuple_find(Grayval,0,&Indices);
                double sumResult;
                tuple_sum(Grayval,&sumResult);
                double mean=sumResult/(Grayval.Num());


                xv[in]=roi.value("Column").toFloat()+x;
                yv[in]=roi.value("Row").toFloat()+y;

                zv[in]=mean;
                temp[in]=i;
                qDebug()<<"xyz"<<xv[in]<<yv[in]<<zv[in]<<in;
                in++;
            }
        }

        if(num==0)
            return;


        double result;

        VectorInfo vec;
       // result=(*comp)(&x[0],&y[0],&z[0],in,&vec);

        if(in<set.value("check_num",4).toInt()+1)
        {
            emit Error(QString("not enough four point,at least %1 point!!").arg(set.value("check_num",4).toInt()+1));
            return;
        }
        tagPlane Plane;
        tagPoint *pointList=listToPoint((double *)&xv[0],(double *)&yv[0],(double *)&zv[0],in);
        PlaneSet(pointList,Plane,in);
        for(int j=0;j<in;j++)
        {

            QMap<QString,QVariant> roi=set.value("team/"+list.at(temp[j])).toMap();

            HTuple dist;


           if(roi.value("func").toInt()==4)
           {
               tagPoint p;
               p.x=xv[j];
               p.y=yv[j];
               p.z=zv[j];
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

             //   if(matList.value(roi.value("index").toString(),NULL)==NULL)
              //  {
              //      emit Error(QStringLiteral("定位失败"));
               //     return;
              //  }
                double x=0,y=0;
                QMap<QString,QVariant> teamPoint=set.value("basePoint").toMap();

                    QMap<QString,QVariant> point=teamPoint.value(roi.value("team").toString()).toMap();

                        x=point.value(roi.value("index").toString()).toPointF().x();
                        y=point.value(roi.value("index").toString()).toPointF().y();


                gen_rectangle2(&Rectangle,roi.value("Row").toDouble()+y,roi.value("Column").toDouble()+x,roi.value("Phi").toDouble(),roi.value("Lenght1").toDouble(),roi.value("Length2").toDouble());

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


                if(Grayval.Num()<=0)
                {
                    qDebug()<<"ptop error";
                    return;
                }
                tuple_mean(-Grayval,&tmp);

                //min_max_gray(ImageReduced,ImageReduced,0,&Min,&Max,&Range);
                gen_rectangle2(&Rectangle,roi.value("Row2").toDouble()+y,roi.value("Column2").toDouble()+x,roi.value("Phi2").toDouble(),roi.value("Lenght3").toDouble(),roi.value("Length4").toDouble());


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
    qDebug()<<QStringLiteral("计算两点高差结束");
}
/*
    计算所有区域
*/
void halconClass::calculate()
{
    unitList.clear();

    calculateBasePoint();

    emit disp_img();

    for(int i=0;i<dataList.size();i++)
    {

        calculatePlaneness(i);
        RectHeightSub(i);
        pointToPoint(i);
    }




}

/*
    读取设置
*/
void halconClass::readSettings()
{

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

    clear_window(WindowHandle);
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
QPointF halconClass::findTwoPointOneLineBasePoint(QMap<QString,QVariant> roi)
{
    HTuple  Area, Row, Column;
    HTuple Row1,Column1,Row2,Column2,Length2;
    Hobject  ROI_0, ImageReduced, ROI_1, ImageReduced1;
    HTuple  Length;
    HTuple  Max, RowBegin, ColBegin, RowEnd, ColEnd, Nr, Nc;
    HTuple  Dist;
    Hobject  Edges, SelectedContours, ROI_2, ImageReduced2, RegionLines;


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


    edges_sub_pix(ImageReduced, &Edges, "canny", 1, HTuple(0.1), HTuple(0.2));
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
    Hobject tmpobj;

    gen_region_line(&tmpobj,RowBegin-1000,ColBegin,RowEnd+1000,ColEnd);
    unitList[index].append(tmpobj);
    QPoint p1=findCenter(*imgList.at(roi.value("index").toInt()),Row1[1].D(),Column1[1].D(),Row2[1].D(),Column2[1].D());

    QPoint p2=findCenter(*imgList.at(roi.value("index").toInt()), Row1[2].D(), Column1[2].D(), Row2[2].D(), Column2[2].D());


    gen_region_line(&RegionLines, p1.y(), p1.x(),p2.y(), p2.x());
    qDebug()<<"p1,p2"<<p1<<p2;
    //Clear measure when done
    area_center(RegionLines, &Area, &Row, &Column);
    //debug
  qDebug()<<Column[0].D()<<Row[0].D();
    gen_rectangle2(&tmpobj,p1.y(),p1.x(),0,5,5);
    unitList[index].append(tmpobj);
    gen_rectangle2(&tmpobj,p2.y(),p2.x(),0,5,5);
    unitList[index].append(tmpobj);
    //end debug
    QPointF base=pointToLine(QPointF(ColBegin[0].D(),RowBegin[0].D()-1000),QPointF(ColEnd[0].D(),RowEnd[0].D()+1000),QPointF(Column[0].D(),Row[0].D()));
  return base;
}
/*
    根据三条线段确定一个基准点
    Row1,Column1,Row2,Column2为四个数组,里面共有三组矩阵数据
    矩阵都需要包含一条边
    计算结果为根据后面两条边的中点相连后得出的线段中点,垂直于第一条边的交点
*/
void  halconClass::calculateBasePoint()
{

    // Local control variables
    QMap<QString,QVariant> teamPoint;

    QMap<QString,QVariant> team=set.value("team").toMap();
    for(int i=0;i<team.keys().size();i++)
    {
        QMap<QString,QVariant> map=team.value(QString::number(i)).toMap();
        QMap<QString,QVariant> indexPoint;
        QPointF p;
        for(int j=0;j<imgList.size();j++)
        {
            QMap<QString,QVariant> roi=map.value(QString::number(j)).toMap();
            if(roi.value("func",-1).toInt()<0)
                p=QPointF(0,0);
            if(roi.value("func",-1).toInt()==0)
            {
                p= matchTemplate(roi);
            }
            if(roi.value("func",-1).toInt()==1)
            {

                p= findRectCenter(roi);

            }
            if(roi.value("func",-1).toInt()==2)
                p= findTwoPointOneLineBasePoint(roi);
            indexPoint.insert(QString::number(j),p);
        }

        teamPoint.insert(QString::number(i),indexPoint);


    }


      set.setValue("basePoint",teamPoint);
      set.sync();

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
