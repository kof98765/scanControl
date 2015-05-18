#ifndef FLATNESS_H
#define FLATNESS_H
#include <math.h>
struct tagPoint
{
    double x;// As Double
    double y;// As Double
    double z;// As Double
};

struct tagLine2D
{
    double k;
    double b;
    double Angle;
    double Straightness;
    double RSQ;
};

/*
3D line's formula is showing as following.
'1)|Ax +By +Z+D =0
'  |A1x+B1y+z+D1=0
'2)(x-x0)/m=(y-y0)/n=(z-z0)/p----(x-x0)/m=(y-y0)/n=z/1
'3)x=mt+x0,y=nt+y0,z=pt+z0
'Only point's coordinate is (a+b*Z, c+d*Z,Z),so the line's vector is {b,d,1}
*/

struct tagLine3D
{
    double x;// As Double
    double y;// As Double
    double z;// As Double
    double x0;// As Double
    double y0;// As Double
    double z0;// As Double
    double xAn;// As Double
    double yAn;// As Double
    double zAn;// As Double
    double m,n,p,Angle;
    double Straightness;
    double MinSt,MaxSt;

};

struct tagVector
{
    double a,b,c;
};

struct tagPlane
{
    double x,y,z;     //The distance from the origin to the centroid, as measured along the x-axis.
    double ax,by,cz,d;//Z + A*x + B*y + C =0  z's coefficient is just 1
    double Angle;
    double xAn,yAn,zAn;
    double Flat,MinFlat,MaxFlat;
    double MinZ,MaxZ;
};

tagPoint *listToPoint(double *x,double *y,double *z,int length);

double Intersect(tagVector v1,tagVector v2, long LinePlane = 0);
double PointToPlane(tagPoint dataRaw,tagPlane Plane,double& rtnDistance, bool AbsDist = false);
long PlaneSet(tagPoint dataRaw[],tagPlane& Plane,int AMT); // z+Ax+BY+C=0



#endif
