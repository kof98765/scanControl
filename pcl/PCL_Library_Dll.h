// PCL_Library_Dll.cpp : ���� DLL Ӧ�ó���ĵ���������
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
	  	
		/** \brief ����ƽ�淽��
		* \param[in] �������
		 * \param[out] ���ƽ�淽��
		 * \param[out] �������
		 * \param[return] �ɹ�����1 
		 */
PCLLIBRARYDLL int ComputePointNormal(PointCloud::Ptr &cloud,Vector4f &normal_vec,float &curvature);

		/** \brief ����ƽ�淽������A B C
		* \param[in] �������
		* \param[out] ���ƽ�淽�� 
		* \param[return] �ɹ�����1 
		*/
PCLLIBRARYDLL int ComputePointNormal2 (PointCloud::Ptr &cloud, Vector4f &normal_vec);

		/** \brief ����㵽ƽ��ľ���
		 * \param[in] �����
		 * \param[in] ����ƽ�淽��
		 * \param[out] ����㵽ƽ��ľ���
		 * \param[return] �ɹ�����1 
		 */
PCLLIBRARYDLL int Dis_point2plane(PointT &point,Vector4f &normal_vec,double &_result);

		/** \brief ����ƽ���
		 * \param[in] ����ĵ���
		 * \param[out] ����ƽ���
		 * \param[return] �ɹ�����1 
	     */
PCLLIBRARYDLL int CalculateFlatness(PointCloud::Ptr &inCloud, double &_result);

		/** \brief ����ƽ���
		 * \param[in] ����ĵ���
		 * \param[out] ����ƽ���
		 * \param[return] �ɹ�����1 
	     */
PCLLIBRARYDLL int CalculateFlatness2(PointCloud::Ptr &inCloud, double &_result);

		/** \brief �ӵ�����ѡȡ�µ��������
		 * \param[in] �����ԭʼ����
		 * \param[in] ��������Ͻ�����point
		 * \param[in] ��������½�����point
		 * \param[in] ����ÿ�ж��ٸ���
		 * \param[out] ���ص��µĵ���
		 * \param[return] �ɹ�����1 
	     */
PCLLIBRARYDLL int GetChildCloud(PointCloud::Ptr &inCloud, POINT point1,POINT point2,int width,PointCloud::Ptr outCloud);

		/** \brief ����������л�ȡ�㣨�޳�������Z������ֵ����Сֵ�󷵻�ƽ��ֵ��
		 * \param[in] �����ԭʼ����
		 * \param[in] ����2D��ԭʼͼƬ
		 * \param[in] ��������Ͻ�����row
		 * \param[in] ��������Ͻ�����col
		 * \param[in] ��������½�����row
		 * \param[in] ��������½�����col
		 * \param[out] ���ص��µĵ���
		 * \param[return] �ɹ�����1 
	     */
PCLLIBRARYDLL int GetChildPoint(PointCloud::Ptr &inCloud,Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,PointCloud::Ptr outCloud);

		/** \brief ��������ģ��
		 * \param[in] ����2D��ԭʼͼƬ
		 * \param[in] ��������Ͻ�����row
		 * \param[in] ��������Ͻ�����col
		 * \param[in] ������ת�����ת�Ƕ�
		 * \param[in] ������ת�� W/2
		 * \param[in] ������ת�� H/2
		 * \param[in] �����Ƿ�ת��Ϊ255ͼ�� 1ת�� ������ת��
		 * \param[in] ���߸�����Ϊ1 ʱ ��Ч  ��ӳ�����Сֵ
		 * \param[in] ���߸�����Ϊ1 ʱ ��Ч  ��ӳ������ֵ
		 * \param[out] ���ص�ģ����
		 * \param[return] �ɹ�����1 
	     */
PCLLIBRARYDLL int Create_template(Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,HTuple hv_mode,HTuple hv__min,HTuple hv__max,HTuple *hv_TemplateID);

		/** \brief ����ģ������
		 * \param[in] ����2D��ԭʼͼƬ
		 * \param[in] ��������Ͻ�����row
		 * \param[in] ��������Ͻ�����col
		 * \param[in] ������ת�����ת�Ƕ�
		 * \param[in] ������ת�� W/2
		 * \param[in] ������ת�� H/2
		 * \param[in] �����Ƿ�ת��Ϊ255ͼ�� 1ת�� ������ת��
		 * \param[in] ���߸�����Ϊ1 ʱ ��Ч  ��ӳ�����Сֵ
		 * \param[in] ���߸�����Ϊ1 ʱ ��Ч  ��ӳ������ֵ
		 * \param[in] �����ģ����
		 * \param[out] ���ص�Ŀ��������
		 * \param[out] ���ص�Ŀ��������
		 * \param[out] ���صĽǶ�
		 * \param[return] �ɹ�����1 
	     */
PCLLIBRARYDLL int Match_template(Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,HTuple hv_mode,HTuple hv__min,HTuple hv__max,HTuple hv_TemplateID,HTuple* hv_Row, HTuple *hv_Column,HTuple *hv_Angle,HTuple *hv_Score);
		
		/** \brief ����һ������ת���󣬷�������Ҫ������
		 * \param[in] ����2D��ԭʼͼƬ
		 * \param[out] ��������
		 * \param[in] ������ת�����ĵ��row����
		 * \param[in] ������ת�����ĵ��Colum����
		 * \param[in] ������ת�����ת�Ƕ�
		 * \param[in] ������ת�� W/2
		 * \param[in] ������ת�� H/2
		 * \param[in] ������Ҫ�������� ��line�� or ��circle��
		 * \param[in] ������ֵģʽ 0~7 ��ʾ8�����ķ��򣨷���ָ��0~255 �ڵ��ף� �������ֱ�ʾ�������ݶȵĽǶ�
		 * \param[in] �������������תHomMat2D
		 * \param[return] �ɹ�����1 ʧ�ܷ���-1
	     */
PCLLIBRARYDLL int gen_region2xld (Halcon::Hobject ho_Image, Halcon::Hobject *ho_Select_xld, Halcon::HTuple hv_Row, 
	Halcon::HTuple hv_Column, Halcon::HTuple hv_Phi, Halcon::HTuple hv_Width_2, Halcon::HTuple hv_Height_2, 
	Halcon::HTuple hv_itype, Halcon::HTuple hv_ithresholdmode, Halcon::HTuple hv_HomMat2D);

		/** \brief ����һ������ת���󣬷�������Ҫ������
		* \param[in] ����2D��ԭʼͼƬ
		* \param[in] ������ת�����ĵ��row����
		* \param[in] ������ת�����ĵ��Colum����
		* \param[in] ������ת�����ת�Ƕ�
		* \param[in] ������ת�� W/2
		* \param[in] ������ת�� H/2
		* \param[in] ������Ҫ�������� ��line�� or ��circle��
		* \param[in] ������ֵģʽ 0~7 ��ʾ8�����ķ��򣨷���ָ��0~255 �ڵ��ף� �������ֱ�ʾ�������ݶȵĽǶ�
		* \param[in] �������������תHomMat2D
		 * \param[out] ����ֱ�ߵ���ʼ������
		 * \param[out] ����ֱ�ߵ���ʼ������
		 * \param[out] ����ֱ�ߵ��յ�������
		 * \param[out] ����ֱ�ߵ��յ�������
		 * \param[out] ����ֱ�ߵ��з���������
		 * \param[out] ����ֱ�ߵ��з���������
		 * \param[out] ����ֱ�ߵķ���������
		 * \param[return] �ɹ�����1 ʧ�ܷ���-1
	     */
PCLLIBRARYDLL int fit_line(Halcon::Hobject ho_Image, Halcon::HTuple hv_Row, 
	Halcon::HTuple hv_Column, Halcon::HTuple hv_Phi, Halcon::HTuple hv_Width_2, Halcon::HTuple hv_Height_2, 
	Halcon::HTuple hv_itype, Halcon::HTuple hv_ithresholdmode, Halcon::HTuple hv_HomMat2D,Halcon::HTuple		*hv_RowBegin, Halcon::HTuple *hv_ColBegin, Halcon::HTuple *hv_RowEnd, Halcon::HTuple *hv_ColEnd,			Halcon::HTuple *hv_Nr, Halcon::HTuple *hv_Nc, Halcon::HTuple *hv_Dist);

		/** \brief ����һ������ת���󣬷�������Ҫ������
		* \param[in] �������X�������
		* \param[in] �������Y�������
		* \param[in] �������Z�������
		* \param[in] ���鳤��
		* \param[out] ���ص���
		* \param[return] �ɹ�����1 ʧ�ܷ���-1
		*/
PCLLIBRARYDLL int Points2Cloud3(float* iX,float* iY,float* iZ,int iLength,PointCloud::Ptr inCloud);
		
		/** \brief ��һ����byte���͵�ͼƬӳ��Ϊbyte����
		* \param[in] ����ͼƬ
		* \param[out] ���ͼƬ
		* \param[in] ��ӳ�����Сֵ
		* \param[in] ��ӳ������ֵ
		* \param[return] �ɹ�����1 ʧ�ܷ���-1
		*/
PCLLIBRARYDLL int byteMapperTable(Halcon::Hobject ho_inImage,Halcon::Hobject* ho_outImage,HTuple hv__min,HTuple hv__max);


/** \brief ����������л�ȡ��(��ͨ����ͨ����ͨ),ֻ����halcon12��ʹ��
		 * \param[in] �����ԭʼ����
		 * \param[in] ����2D��ԭʼͼƬ
		 * \param[in] ��������Ͻ�����row
		 * \param[in] ��������Ͻ�����col
		 * \param[in] ��������½�����row
		 * \param[in] ��������½�����col
		 * \param[in] ������˲�ͨ���ٷֱȣ�0~100��
		 * \param[in] �����˲����ͣ�1��ͨ��2��ͨ��������������ͨ��
		 * \param[out] ���ص��µĵ���
		 * \param[return] �ɹ�����1 
	     */

//PCLLIBRARYDLL int GetChildPoint2(PointCloud::Ptr &inCloud,Hobject inImage,HTuple Row1,HTuple Column1,HTuple Row2,HTuple Column2,float Percent,int f_type,PointCloud::Ptr outCloud);

//You can also write like this:
//extern "C" {
//_declspec(dllexport) int Add(int plus1, int plus2);
//};
#endif
