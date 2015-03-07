// PCL_Library_Dll.cpp : 定义 DLL 应用程序的导出函数。
//

//#include "StdAfx.h"
#include <iostream>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>

#ifndef PCL_LIBRARY_DLL_H_
#define PCL_LIBRARY_DLL_H_
#ifdef PCLLIBRARYDLL
#define PCLLIBRARYDLL extern "C" _declspec(dllimport) 
#else
#define PCLLIBRARYDLL extern "C" _declspec(dllexport) 
#endif

#define MESSAGE_OK 1
#define MESSAGE_ERROR -1
using namespace Eigen;
//简单类型定义
typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;

	   /** \brief 将坐标存入点云，
	     * \param[in] 输入点X坐标
		 * \param[in] 输入点Y坐标
		 * \param[in] 输入点Z坐标  
		 * \param[in] 输入点I坐标
		 * \param[in] 输入列数
		 * \param[in] 输入行数 
		 * \param[out] 返回的点云 
	     */
PCLLIBRARYDLL void Transfer2Cloud(double* X,double* Y,double* Z,unsigned short* I,const int col,const int row,PointCloud::Ptr inCloud);
	  	
		/** \brief 计算点到平面的距离
		 * \param[in] 输入点
		 * \param[in] 输入平面方程
		 * \param[out] 输出点到平面的距离
		 * \param[return] 成功返回1 
		 */
PCLLIBRARYDLL int Dis_point2plane(PointT &point,Vector4f &normal_vec,double &_result);

		/** \brief 计算平面度
		 * \param[in] 返回的点云
		 * \param[out] 返回平面度
		 * \param[return] 成功返回1 
	     */
PCLLIBRARYDLL int CalculateFlatness(PointCloud::Ptr &inCloud, double &_result);

//You can also write like this:
//extern "C" {
//_declspec(dllexport) int Add(int plus1, int plus2);
//};
#endif
