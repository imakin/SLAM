#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>// <depend package="sensor_msgs" /> <!-- supaya bisa pake sensor msgs --> di manifest.xml
#include "std_msgs/Float32.h" 
#include <iostream>
using namespace std;

#define max_landmark 100


float depth_minimal_jarak;
int depth_minimal_jarak_index;

sensor_msgs::LaserScan depth;
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}


void Callback_depth(const sensor_msgs::LaserScan::ConstPtr& scan_depth)
{
	int ii,a,b;
	//~ int a[max_landmark], b[max_landmark]
	depth_minimal_jarak = 12;
    for (ii=0;ii<360;ii++)
    {
		/// ROS_INFO("For [%d] I heard: [%f]", ii, scan_depth->ranges[ii]);
			
		if (scan_depth->ranges[ii]<depth_minimal_jarak)
		{
			depth_minimal_jarak = scan_depth->ranges[ii];
			depth_minimal_jarak_index = ii;
		}
	}
	ii = depth_minimal_jarak_index-1;
	while (abs(scan_depth->ranges[ii]-depth_minimal_jarak)<0.1)
		ii--;
	a=ii+1;
	ii = depth_minimal_jarak_index+1;
	while (abs(scan_depth->ranges[ii]-depth_minimal_jarak)<0.1)
		ii++;
	b=ii-1;
	
	for (ii=a;ii<b;ii++){
		cout<<scan_depth->ranges[ii]<<' ';
	}
	cout<<endl;
	cout<<endl;
	cout<<endl;
}
//~ void AutoExp::processLaserScan(const sensor_msgs::LaserScan::ConstPtr& scan){
	//~ ROS_INFO("I heard: [%f]", scan->ranges[2]);
//~ }

int main(int argc, char **argv)
{
	ros::init(argc, argv, "listener");

	/**
	* NodeHandle is the main access point to communications with the ROS system.
	* The first NodeHandle constructed will fully initialize this node, and the last
	* NodeHandle destructed will close down the node.
	*/
	ros::NodeHandle n;
	ros::Subscriber scanSub;

	//~ scanSub=n.subscribe<sensor_msgs::LaserScan>("/narrow_scan",10,&AutoExp::processLaserScan,this);
	scanSub=n.subscribe<sensor_msgs::LaserScan>("/narrow_scan", 100, Callback_depth);


	//~ ros::Subscriber sub = n.subscribe("narrow_scan", 1000, chatterCallback);

	ros::spin();

  return 0;
}

