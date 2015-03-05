// PCL_Library_Dll.cpp : ���� DLL Ӧ�ó���ĵ���������
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
//�����Ͷ���
typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;

	   /** \brief �����������ƣ�
	     * \param[in] �����X����
		 * \param[in] �����Y����
		 * \param[in] �����Z����  
		 * \param[in] �����I����
		 * \param[in] ��������
		 * \param[in] �������� 
		 * \param[out] ���صĵ��� 
	     */
PCLLIBRARYDLL void Transfer2Cloud(double* X,double* Y,double* Z,unsigned short* I,const int col,const int row,PointCloud::Ptr inCloud);
	  	
		/** \brief ����㵽ƽ��ľ���
		 * \param[in] �����
		 * \param[in] ����ƽ�淽��
		 * \param[out] ����㵽ƽ��ľ���
		 * \param[return] �ɹ�����1 
		 */
PCLLIBRARYDLL int Dis_point2plane(PointT &point,Vector4f &normal_vec,double &_result);

		/** \brief ����ƽ���
		 * \param[in] ���صĵ���
		 * \param[out] ����ƽ���
		 * \param[return] �ɹ�����1 
	     */
PCLLIBRARYDLL int CalculateFlatness(PointCloud::Ptr &inCloud, double &_result);

//You can also write like this:
//extern "C" {
//_declspec(dllexport) int Add(int plus1, int plus2);
//};
#endif