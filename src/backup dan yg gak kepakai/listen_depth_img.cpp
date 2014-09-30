#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/Image.h>// <depend package="sensor_msgs" /> <!-- supaya bisa pake sensor msgs --> di manifest.xml
#include "std_msgs/Float32.h" 
#include <iostream>
using namespace std;


float depth_minimal_jarak;
int depth_minimal_jarak_index;

void Callback_depth(const sensor_msgs::Image::ConstPtr& img)
{
	//~ ROS_INFO("For [%d] I heard: [%f]", ii, scan_depth->ranges[ii]);
	cout<<img->height<<endl;
	cout<<img->width<<endl;
	int mid;
	mid = (img->step*(img->height-1))/2;/** msh aneh **/
	cout<<
		(int(img->data[mid]))+(int(img->data[mid+1])<<8)<<"   "<<endl;
	cout<<img->step<<endl;
	cout<<img->encoding<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "mkn_data_depth");
	ros::NodeHandle n;
	ros::Subscriber scanSub;

	scanSub=n.subscribe<sensor_msgs::Image>("/camera/depth/image_raw", 100, Callback_depth);

	ros::spin();

  return 0;
}

