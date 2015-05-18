#include "Flatness.h"

tagPoint* listToPoint(double *x,double *y,double *z,int length)
{
    tagPoint p[1000];
    for(int i=0;i<length;i++)
    {
        p[i].x=x[i];
        p[i].y=y[i];
        p[i].z=z[i];
    }
    return p;
}
/*************************************************************

'  函数名：Intersect

'  功能：  求两向量之间的夹角

'  参数： v1  - tagVector

'         v2  - tagVector

'         LinePlane  -long   0:表示两直线之间的夹角,其它值:表示如线与平面之间,平面与平面之间的夹角(0~90)

'  返回值：Double型,单位:度.

'*************************************************************/

double Intersect(tagVector v1,tagVector v2, long LinePlane)
{
	//LinePlane 0 :line -line ,1:line --Plane
	double tmp,tmpSqr1,tmpSqr2;
	tmp = (v1.a * v2.a + v1.b * v2.b + v1.c * v2.c);
	//'MsgBox tm
	tmpSqr1 = sqrt(v1.a * v1.a + v1.b * v1.b  + v1.c *v1.c);
	tmpSqr2 = sqrt(v2.a * v2.a + v2.b * v2.b  + v2.c *v2.c);
	if (tmpSqr1 != 0)
	{
		if (tmpSqr2 != 0)
		{
			tmp = tmp/tmpSqr1/tmpSqr2;
		}
		else
		{
			tmp = tmp / tmpSqr1;
		}
	}
	else
	{
		if (tmpSqr2 != 0)
			tmp = tmp / tmpSqr2;
		else
			tmp = 0;
	}
	if (LinePlane != 0)
	{
		tmp = abs(tmp);
	}
	if (-tmp * tmp + 1 != 0)
	{
		tmp = atan(-tmp / sqrt(-tmp * tmp + 1)) + 2 * atan(1.0);
		tmp = tmp / 3.1415926 * 180;
	}
	else
	{
		tmp = 90;
	}
	return tmp;
}

/*************************************************************

'  函数名：PointToPlane

'  功能：  求点到平面的距离

'  参数：  dataRaw  - tagPoint型  自定义点类型(x,y,z)

'          Plane  - tagPlane  Double

'          RtnDistance -Double    其值为点到直线的距离.

'          AbsDist     -Long　　　０：点到平面距离（有正有负），其它值：点到平面距离（绝对值）

'  返回值：Long型，失败为0，成功为-1

'*************************************************************/
double PointToPlane(tagPoint dataRaw,tagPlane Plane,double& rtnDistance, bool AbsDist)
{
	long i,lb,ub;
	double tmp = (Plane.ax * dataRaw.x + Plane.by * dataRaw.y + Plane.cz * dataRaw.z + Plane.d)\
			/sqrt(Plane.ax*Plane.ax + Plane.by*Plane.by + Plane.cz*Plane.cz);
	if (AbsDist != false)
		tmp = abs(tmp);
	rtnDistance = tmp;
	return rtnDistance;
};
/************************************************
平面度计算
tagPoint dataRaw[] --- 输入的点，包括X,Y,Z数据
tagPlane& Plane    --- 输出计算的平面相关参数
int AMT            --- 输入的点的个数
*************************************************/
long PlaneSet(tagPoint dataRaw[],tagPlane& Plane,int AMT) // z+Ax+BY+C=0
{
	double MaxF,MinF,tmp;
	if (AMT < 3)
		return 0;
	long i,n;
	n = AMT;
	double x,y,z,XY,XZ,YZ;
	double X2,Y2;
	double a,b,c,d;
	double a1,b1,z1;
	double a2,b2,z2;
	tagVector n1;     //{.ax,by,1}  s1
	tagVector n2;     //{0,0,N} XY plane  s2
	tagVector n3;     //line projected plane
	tagVector xLine,yLine,zLine,SLine;
	tagVector VectorPlane;
	xLine.a = 1; 
	xLine.b = 0; 
	xLine.c = 0;

	yLine.a = 0;
	yLine.b = 1;
	yLine.c = 0;

	zLine.a = 0;
	zLine.b = 0;
	zLine.c = 1;

	x = y = z =0;
	XY = XZ = YZ = 0;
	X2 = Y2 = 0;

	for ( i = 0;i < AMT;i++)
	{
		x += dataRaw[i].x;
		y += dataRaw[i].y;
		z += dataRaw[i].z;

		XY += dataRaw[i].x * dataRaw[i].y;
		XZ += dataRaw[i].x * dataRaw[i].z;
		YZ += dataRaw[i].y * dataRaw[i].z;
		X2 += dataRaw[i].x * dataRaw[i].x;
		Y2 += dataRaw[i].y * dataRaw[i].y;
	}
	z1 = n * XZ - x * z;//              'e=z-Ax-By-C  z=Ax+By+D
	a1 = n * X2 - x * x;//
	b1 = n * XY - x * y;
	z2 = n * YZ - y * z;
	a2 = n * XY - x * y;
	b2 = n * Y2 - y * y;
	a = (z1 * b2 - z2 * b1) / (a1 * b2 - a2 * b1);
	b = (a1 * z2 - a2 * z1) / (a1 * b2 - a2 * b1);
	c = 1;
	d = (z - a * x - b * y) / n;


	Plane.x = x / AMT;
	Plane.y = y / AMT;
	Plane.z = z / AMT;
	//'sum(Mi *Ri)/sum(Mi) ,Mi is mass . here  Mi is seted to be 1 and .z is just the average of z
	Plane.ax = -a;
	Plane.by = -b;
	Plane.cz = 1;
	Plane.d = -d; //z=Ax+By+D-----Ax+By+Z+D=0

	VectorPlane.a = Plane.ax;
	VectorPlane.b = Plane.by;
	VectorPlane.c = 1;

	Plane.xAn = Intersect(VectorPlane, xLine);
	Plane.yAn = Intersect(VectorPlane, yLine);
	Plane.zAn = Intersect(VectorPlane, zLine);

	n1.a = Plane.ax; 
	n1.b = Plane.by;
	n1.c = 1;

	SLine.a = Plane.ax;
	SLine.b = Plane.by;
	SLine.c = 0;

	Plane.Angle = Intersect(xLine, SLine);// (xLine.A * SLine.A + xLine.A * SLine.B + xLine.C * SLine.C)
	//if (SLine.b < 0)
	{
		Plane.Angle = 360 - Plane.Angle;
		double MaxF,MinF,rDist;
		double MinZ,MaxZ;
		for (int i = 0;i < AMT;i++)
		{
			PointToPlane(dataRaw[i],Plane,rDist,false);
			if (i == 0)
			{
				MaxF = MinF = rDist;
				MaxZ = MinZ = dataRaw[i].z;
			}
			else
			{
				if (MaxF < rDist)
					MaxF = rDist;
				if (MinF > rDist)
					MinF = rDist;

				if (MaxZ < dataRaw[i].z)
					MaxZ = dataRaw[i].z;
				if (MinZ > dataRaw[i].z)
					MinZ = dataRaw[i].z;
			}
		}
		Plane.MaxFlat = MaxF;
		Plane.MinFlat = MinF;
		Plane.Flat = MaxF - MinF;

		Plane.MinZ = MinZ;
		Plane.MaxZ = MaxZ;
	}
} 

//int main(int argc, char *argv[])
//{
	
//	cout<<"init plane"<<endl;
//	tagPoint dataRaw[41000];
//	int index = 0;
//	for (float x = -1.0; x < 1.0; x += 0.01)
//	{
//	  for (float y = -1.0; y < 1.0; y += 0.01)
//		{
		 
//		  dataRaw[index].x = x;
//		  dataRaw[index].y = y;
//		  dataRaw[index].z = 1- x;
		 
//		  index++;

//	  }
//	}
//	cout<<"calc plane"<<endl;
//	tagPlane Plane;
//	PlaneSet(dataRaw,Plane,40000);
//	cout<<"plane ax = "<< Plane.ax <<"  by = "<< Plane.by<< "  cz = " <<Plane.cz << "  D = "<<Plane.d<<endl;


//	return 0;
//}
