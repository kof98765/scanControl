// PCL_Library_Dll.cpp : 定义 DLL 应用程序的导出函数。
//

//#include "StdAfx.h"
#include <iostream>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>
#include "CPP/HalconCpp.h"

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
using namespace Halcon;
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
	  	
		/** \brief 计算平面方程
		* \param[in] 输入点云
		 * \param[out] 输出平面方程
		 * \param[out] 输出曲率
		 * \param[return] 成功返回1 
		 */
PCLLIBRARYDLL int ComputePointNormal(PointCloud::Ptr &cloud,Vector4f &normal_vec,float &curvature);

		/** \brief 计算平面方程向量A B C
		* \param[in] 输入点云
		* \param[out] 输出平面方程 
		* \param[return] 成功返回1 
		*/
PCLLIBRARYDLL int ComputePointNormal2 (PointCloud::Ptr &cloud, Vector4f &normal_vec);

		/** \brief 计算点到平面的距离
		 * \param[in] 输入点
		 * \param[in] 输入平面方程
		 * \param[out] 输出点到平面的距离
		 * \param[return] 成功返回1 
		 */
PCLLIBRARYDLL int Dis_point2plane(PointT &point,Vector4f &normal_vec,double &_result);

		/** \brief 计算平面度
		 * \param[in] 输入的点云
		 * \param[out] 返回平面度
		 * \param[return] 成功返回1 
	     */
PCLLIBRARYDLL int CalculateFlatness(PointCloud::Ptr &inCloud, double &_result);

		/** \brief 计算平面度
		 * \param[in] 输入的点云
		 * \param[out] 返回平面度
		 * \param[return] 成功返回1 
	     */
PCLLIBRARYDLL int CalculateFlatness2(PointCloud::Ptr &inCloud, double &_result);

		/** \brief 从点云中选取新的区域点云
		 * \param[in] 输入的原始点云
		 * \param[in] 输入的左上角坐标point
		 * \param[in] 输入的右下角坐标point
		 * \param[in] 输入每行多少个点
		 * \param[out] 返回的新的点云
		 * \param[return] 成功返回1 
	     */
PCLLIBRARYDLL int GetChildCloud(PointCloud::Ptr &inCloud, POINT point1,POINT point2,int width,PointCloud::Ptr outCloud);

		/** \brief 从区域点云中获取点（剔除点云中Z轴的最大值和最小值后返回平均值）
		 * \param[in] 输入的原始点云
		 * \param[in] 输入2D的原始图片
		 * \param[in] 输入的左上角坐标row
		 * \param[in] 输入的左上角坐标col
		 * \param[in] 输入的右下角坐标row
		 * \param[in] 输入的右下角坐标col
		 * \param[out] 返回的新的点云
		 * \param[return] 成功返回1 
	     */
PCLLIBRARYDLL int GetChildPoint(PointCloud::Ptr &inCloud,Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,PointCloud::Ptr outCloud);

		/** \brief 创建区域模板
		 * \param[in] 输入2D的原始图片
		 * \param[in] 输入的左上角坐标row
		 * \param[in] 输入的左上角坐标col
		 * \param[in] 输入的右下角坐标row
		 * \param[in] 输入的右下角坐标col
		 * \param[out] 返回的模板编号
		 * \param[return] 成功返回1 
	     */
PCLLIBRARYDLL int Create_template(Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,HTuple *hv_TemplateID);

		/** \brief 搜索模板区域
		 * \param[in] 输入2D的原始图片
		 * \param[in] 输入的左上角坐标row
		 * \param[in] 输入的左上角坐标col
		 * \param[in] 输入的右下角坐标row
		 * \param[in] 输入的右下角坐标col
		 * \param[in] 输入的模板编号
		 * \param[out] 返回的目标行坐标
		 * \param[out] 返回的目标列坐标
		 * \param[out] 返回的角度
		 * \param[return] 成功返回1 
	     */
PCLLIBRARYDLL int Match_template(Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,HTuple hv_TemplateID,HTuple* hv_Row, HTuple *hv_Column,HTuple *hv_Angle);


		/** \brief 从区域点云中获取点(高通，低通，中通),只能在halcon12下使用
		 * \param[in] 输入的原始点云
		 * \param[in] 输入2D的原始图片
		 * \param[in] 输入的左上角坐标row
		 * \param[in] 输入的左上角坐标col
		 * \param[in] 输入的右下角坐标row
		 * \param[in] 输入的右下角坐标col
		 * \param[in] 输入的滤波通过百分比（0~100）
		 * \param[in] 输入滤波类型（1高通，2低通，其他数字是中通）
		 * \param[out] 返回的新的点云
		 * \param[return] 成功返回1 
	     */

//PCLLIBRARYDLL int GetChildPoint2(PointCloud::Ptr &inCloud,Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,float Percent,int f_type,PointCloud::Ptr outCloud);

//You can also write like this:
//extern "C" {
//_declspec(dllexport) int Add(int plus1, int plus2);
//};
#endif