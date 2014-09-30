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
	
	cout<<int(img->data[0])<<int(img->data[1])<<int(img->data[2])<<endl;
	cout<<img->step<<endl;
	cout<<img->encoding<<endl;
	

	
	cout<<endl;
	cout<<endl;
	cout<<endl;
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "mkn_data_RGB");
	ros::NodeHandle n;
	ros::Subscriber scanSub;

	scanSub=n.subscribe<sensor_msgs::Image>("/camera/rgb/image_color", 100, Callback_depth);

	ros::spin();

  return 0;
}

