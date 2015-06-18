#include "pointdatadialog.h"
#include "ui_pointdatadialog.h"

pointDataDialog::pointDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pointDataDialog)
{
    ui->setupUi(this);

}

pointDataDialog::~pointDataDialog()
{

    delete ui;
}

void pointDataDialog::on_roiColor_clicked()
{
    QColor color=QColorDialog::getColor();
    if(color.isValid()){
        int r,g,b;
        color.getRgb(&r,&g,&b);
        QString str;
        str=QString("background-color: rgb(%1,%2,%3)").arg(r).arg(g).arg(b);
        ui->roiColor->setStyleSheet(str.toUtf8().data());
        //QPalette pal=ui->roiColor->palette();
        //pal.setColor(QPalette::Active,QPalette::Button, color);
        //ui->roiColor->setPalette(pal);
        qDebug()<<color.rgb();
        qDebug()<<((color.rgb()&(0xff<<16))>>16)<<((color.rgb()&(0xff<<8))>>8)<<(color.rgb()&(0xff));
        ui->roiColor->update();
    }
}
float pointDataDialog::convertPoint(float num,int xy)
{
    switch(xy)
    {
        case 0:
        num=num/ui->scaleX->value();
        break;
    case 1:
        num=num/ui->scaleY->value();
        break;
    }
    return num;
}
void pointDataDialog::loadLua(char *name)
{
    if(luaL_loadfilex(l,name,NULL)||(lua_pcall(l,0,0,0)))
        qDebug("load faild\n");
}
void pointDataDialog::getPoint()
{
    QMap<QString,QVariant> map;
    l=luaL_newstate();
    luaL_openlibs(l);
    double scaleX,scaleY;
    QString filePath=QFileDialog::getOpenFileName(this,QStringLiteral("点位文件"),".","txt (*.txt) lua (*.lua)");
    if(filePath.isEmpty())
        return;
    if(luaL_loadfile(l,filePath.toUtf8().data())||lua_pcall(l,0,0,0))
        qDebug("%s\n",lua_tostring(l, -1));
    lua_getglobal(l,"scaleX");
    lua_getglobal(l,"scaleY");
    scaleX=lua_tonumber(l,-2);
    scaleY=lua_tonumber(l,-1);
    lua_pop(l,1);
    lua_pop(l,1);
    lua_getglobal(l,"data");
    lua_pushnil(l);
    lua_next(l,-2);
    lua_pushnil(l);

    while(lua_next(l,-2))
    {
        map.clear();

        map.insert("name",lua_tostring(l,-2));
        lua_getfield(l,-1,"color");
        map.insert("color",lua_tointeger(l,-1));
        lua_pop(l,1);
        lua_getfield(l,-1,"team");
        map.insert("team",lua_tointeger(l,-1));
        lua_pop(l,1);
        lua_getfield(l,-1,"func");
        map.insert("func",lua_tointeger(l,-1));
        lua_pop(l,1);
        lua_getfield(l,-1,"Row");
        map.insert("Row",lua_tonumber(l,-1)/scaleY);
        lua_pop(l,1);
        lua_getfield(l,-1,"Column");
        map.insert("Column",lua_tonumber(l,-1)/scaleX);
        lua_pop(l,1);
        lua_getfield(l,-1,"Length1");
        map.insert("Length1",lua_tonumber(l,-1));
        lua_pop(l,1);
        lua_getfield(l,-1,"Length2");
        map.insert("Length2",lua_tonumber(l,-1));
        lua_pop(l,1);
        lua_getfield(l,-1,"drawType");
        map.insert("drawType",lua_tonumber(l,-1));
        lua_pop(l,1);
        lua_getfield(l,-1,"isDraw");
        map.insert("isDraw",lua_tonumber(l,-1));
        lua_pop(l,1);
        lua_getfield(l,-1,"index");
        map.insert("index",lua_tonumber(l,-1));
        qDebug()<<"index"<<lua_tonumber(l,-1);
        lua_pop(l,1);
        lua_getfield(l,-1,"Row2");
        map.insert("Row2",lua_tonumber(l,-1)/scaleY);
        lua_pop(l,1);
        lua_getfield(l,-1,"Column2");
        map.insert("Column2",lua_tonumber(l,-1)/scaleX);
        lua_pop(l,1);
        lua_getfield(l,-1,"Length3");
        map.insert("Length3",lua_tonumber(l,-1));
        lua_pop(l,1);
        lua_getfield(l,-1,"Length4");
        map.insert("Length4",lua_tonumber(l,-1));
        lua_pop(l,1);
        lua_pop(l,1);
        emit addRoi(map);
    }
        lua_close(l);
}
void pointDataDialog::on_loadPoint_clicked()
{
    emit getPoint();
    return;
    QString filePath=QFileDialog::getOpenFileName(this,QStringLiteral("点位文件"),".","txt (*.txt)");
    if(filePath.isEmpty())
        return;
    QFile f(filePath);
    f.open(QFile::ReadOnly);
    QPoint p,p2;
    QTextStream txtInput(&f);
    QString buf;
    int i=0;
    while(!txtInput.atEnd())
    {
        buf=txtInput.readLine();

        p.setX(convertPoint(buf.mid(0,buf.indexOf(",")).toFloat(),0));
        buf=buf.mid(buf.indexOf(",")+1,buf.length());

        if(ui->func->currentIndex()==2)
        {

            p.setY(convertPoint(buf.mid(0,buf.indexOf(",")).toFloat(),1));
            buf=buf.mid(buf.indexOf(",")+1,buf.length());

            p2.setX(convertPoint(buf.mid(0,buf.indexOf(",")).toFloat(),0));
            buf=buf.mid(buf.indexOf(",")+1,buf.length());

            p2.setY(convertPoint(buf.mid(0,buf.indexOf(",")).toFloat(),1));

        }
        else
        {
            p.setY(convertPoint(buf.mid(0,buf.indexOf(",")).toFloat(),1));
        }
        qDebug()<<"point"<<p;
        QString name=buf.mid(0,buf.length());
        QMap<QString,QVariant> map,limit;

        map.insert("Row",p.y());
        map.insert("Column",p.x());

        map.insert("Length1",ui->roiSize->value());
        map.insert("Length2",ui->roiSize->value());
        if(name.isEmpty())
            map.insert("name",ui->roiName->text()+QString("00%1").arg(++i));
        else
            map.insert("name",name);
        map.insert("color",ui->roiColor->palette().background().color().rgb());
        map.insert("team",ui->roiTeam->currentIndex());
        switch(ui->func->currentIndex())
        {
        case 0:
             map.insert("func",3);
            break;
        case 1:
             map.insert("func",4);
            break;
        case 2:
             map.insert("func",5);
             map.insert("Row2",p2.y());
             map.insert("Column2",p2.x());
             map.insert("Length3",ui->roiSize->value());
             map.insert("Length4",ui->roiSize->value());

            break;
        }

        map.insert("drawType",0);


        qDebug()<<ui->roiName->text();
         emit addRoi(map);

    }


    close();




}
