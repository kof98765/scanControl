#include "PCL_Library_Dll.h"


void Transfer2Cloud(double* X,double* Y,double* Z,unsigned short* I,const int col,const int row,PointCloud::Ptr inCloud)
{
	pcl::PointXYZ cloud;
	for (int i=0;i<row;++i)
	{
		for (int j=0;j<col;++j)
		{
			cloud.x=(float)*X++;
			cloud.y=(float)*Y++;
			cloud.z=(float)*Z++;
			inCloud->push_back(cloud);
		}
	}
}

int Dis_point2plane(PointT &point,Vector4f &normal_vec,double &_result)
{
	if (normal_vec[0]==0&&normal_vec[1]==0&&normal_vec[2]==0)
	{
		return MESSAGE_ERROR;
	}
	_result=(normal_vec[0]*point.x+normal_vec[1]*point.y+normal_vec[2]*point.z+normal_vec[3])/sqrt(normal_vec[0]*normal_vec[0]+normal_vec[1]*normal_vec[1]+normal_vec[2]*normal_vec[2]);
	return MESSAGE_OK;
}

int CalculateFlatness(PointCloud::Ptr &inCloud, double &_result)
{
	vector<double> D_length;
	Eigen::Vector4f normal_vec(0,0,0,0);
	float curvature = std::numeric_limits<float>::quiet_NaN ();
	pcl::computePointNormal(*inCloud,normal_vec,curvature);
	for (int i=0;i<inCloud->size();i++)
	{
		double L;
		Dis_point2plane((*inCloud)[i],normal_vec,L);
		D_length.push_back(L);
	}
	sort(D_length.begin(),D_length.end());
	_result=D_length[inCloud->size()-1]-D_length[0];
	return MESSAGE_OK;
}