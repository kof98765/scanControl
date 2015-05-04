// PCL_Library_Dll.cpp : 定义 DLL 应用程序的导出函数。
//

//#include "StdAfx.h"
#include <iostream>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>
#include "CPP/HalconCpp.h"
#include "CPP/HIOStream.h"

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
		 * \param[in] 输入旋转框的旋转角度
		 * \param[in] 输入旋转框 W/2
		 * \param[in] 输入旋转框 H/2
		 * \param[in] 输入是否转换为255图像 1转换 其他不转换
		 * \param[in] 第七个参数为1 时 有效  被映射的最小值
		 * \param[in] 第七个参数为1 时 有效  被映射的最大值
		 * \param[out] 返回的模板编号
		 * \param[return] 成功返回1 
	     */
PCLLIBRARYDLL int Create_template(Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,HTuple hv_mode,HTuple hv__min,HTuple hv__max,HTuple *hv_TemplateID);

		/** \brief 搜索模板区域
		 * \param[in] 输入2D的原始图片
		 * \param[in] 输入的左上角坐标row
		 * \param[in] 输入的左上角坐标col
		 * \param[in] 输入旋转框的旋转角度
		 * \param[in] 输入旋转框 W/2
		 * \param[in] 输入旋转框 H/2
		 * \param[in] 输入是否转换为255图像 1转换 其他不转换
		 * \param[in] 第七个参数为1 时 有效  被映射的最小值
		 * \param[in] 第七个参数为1 时 有效  被映射的最大值
		 * \param[in] 输入的模板编号
		 * \param[out] 返回的目标行坐标
		 * \param[out] 返回的目标列坐标
		 * \param[out] 返回的角度
		 * \param[return] 成功返回1 
	     */
PCLLIBRARYDLL int Match_template(Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,HTuple hv_mode,HTuple hv__min,HTuple hv__max,HTuple hv_TemplateID,HTuple* hv_Row, HTuple *hv_Column,HTuple *hv_Angle,HTuple *hv_Score);
		
		/** \brief 输入一个可旋转矩阵，返回你需要的轮廓
		 * \param[in] 输入2D的原始图片
		 * \param[out] 返回轮廓
		 * \param[in] 输入旋转框中心点的row坐标
		 * \param[in] 输入旋转框中心点的Colum坐标
		 * \param[in] 输入旋转框的旋转角度
		 * \param[in] 输入旋转框 W/2
		 * \param[in] 输入旋转框 H/2
		 * \param[in] 输入需要检测的轮廓 “line” or “circle”
		 * \param[in] 输入阈值模式 0~7 表示8个检测的方向（方向指由0~255 黑到白） 其他数字表示不限制梯度的角度
		 * \param[in] 输入轮廓框的旋转HomMat2D
		 * \param[return] 成功返回1 失败返回-1
	     */
PCLLIBRARYDLL int gen_region2xld (Halcon::Hobject ho_Image, Halcon::Hobject *ho_Select_xld, Halcon::HTuple hv_Row, 
	Halcon::HTuple hv_Column, Halcon::HTuple hv_Phi, Halcon::HTuple hv_Width_2, Halcon::HTuple hv_Height_2, 
	Halcon::HTuple hv_itype, Halcon::HTuple hv_ithresholdmode, Halcon::HTuple hv_HomMat2D);

		/** \brief 输入一个可旋转矩阵，返回你需要的轮廓
		* \param[in] 输入2D的原始图片
		* \param[in] 输入旋转框中心点的row坐标
		* \param[in] 输入旋转框中心点的Colum坐标
		* \param[in] 输入旋转框的旋转角度
		* \param[in] 输入旋转框 W/2
		* \param[in] 输入旋转框 H/2
		* \param[in] 输入需要检测的轮廓 “line” or “circle”
		* \param[in] 输入阈值模式 0~7 表示8个检测的方向（方向指由0~255 黑到白） 其他数字表示不限制梯度的角度
		* \param[in] 输入轮廓框的旋转HomMat2D
		 * \param[out] 返回直线的起始行坐标
		 * \param[out] 返回直线的起始列坐标
		 * \param[out] 返回直线的终点行坐标
		 * \param[out] 返回直线的终点列坐标
		 * \param[out] 返回直线的行法向量坐标
		 * \param[out] 返回直线的列法向量坐标
		 * \param[out] 返回直线的法向量距离
		 * \param[return] 成功返回1 失败返回-1
	     */
PCLLIBRARYDLL int fit_line(Halcon::Hobject ho_Image, Halcon::HTuple hv_Row, 
	Halcon::HTuple hv_Column, Halcon::HTuple hv_Phi, Halcon::HTuple hv_Width_2, Halcon::HTuple hv_Height_2, 
	Halcon::HTuple hv_itype, Halcon::HTuple hv_ithresholdmode, Halcon::HTuple hv_HomMat2D,Halcon::HTuple		*hv_RowBegin, Halcon::HTuple *hv_ColBegin, Halcon::HTuple *hv_RowEnd, Halcon::HTuple *hv_ColEnd,			Halcon::HTuple *hv_Nr, Halcon::HTuple *hv_Nc, Halcon::HTuple *hv_Dist);

		/** \brief 输入一个可旋转矩阵，返回你需要的轮廓
		* \param[in] 输入包含X轴的数组
		* \param[in] 输入包含Y轴的数组
		* \param[in] 输入包含Z轴的数组
		* \param[in] 数组长度
		* \param[out] 返回点云
		* \param[return] 成功返回1 失败返回-1
		*/
PCLLIBRARYDLL int Points2Cloud3(float* iX,float* iY,float* iZ,int iLength,PointCloud::Ptr inCloud);
		
		/** \brief 将一个非byte类型的图片映射为byte类型
		* \param[in] 输入图片
		* \param[out] 输出图片
		* \param[in] 被映射的最小值
		* \param[in] 被映射的最大值
		* \param[return] 成功返回1 失败返回-1
		*/
PCLLIBRARYDLL int byteMapperTable(Halcon::Hobject ho_inImage,Halcon::Hobject* ho_outImage,HTuple hv__min,HTuple hv__max);


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
