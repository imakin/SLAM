#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <boost/foreach.hpp>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

void callback(const PointCloud::ConstPtr& msg)
{
	printf ("Cloud: width = %d, height = %d\n", msg->width, msg->height);
	BOOST_FOREACH (const pcl::PointXYZ& pt, msg->points)
		printf ("\t(%f, %f, %f)\n", pt.x, pt.y, pt.z);
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "sub_pcl");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe<PointCloud>("points2", 1, callback);
	ros::spin();
}

/* FAIL
 * 
 * #include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt32.h"
#include "std_msgs/UInt8.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"

int Arr[9000];
void arrayCallback(const std_msgs::Int32MultiArray::ConstPtr& array);
 

void makinCallback(const std_msgs::UInt32::ConstPtr& msg);

int main(int argc, char **argv)
{
	ros::init(argc, argv, "mkn_depth");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("camera/depth/image", 10000, arrayCallback);

	//~ ros::Subscriber sub3 = n.subscribe("array", 100, arrayCallback);
	 
	ros::spin();
	 
	//~ for(int j = 1; j < 9000; j++)
	//~ {
		//~ printf("%d, ", Arr[j]);
	//~ }
	 
	printf("\n");
	return 0;
}


void makinCallback(const std_msgs::UInt32::ConstPtr& msg)
{
	ROS_INFO("MAN! ");
}
void arrayCallback(const std_msgs::Int32MultiArray::ConstPtr& array)
{ 
	int i = 0;
	// print all the remaining numbers
	printf("array->data.begin()");
	for(std::vector<int>::const_iterator it = array->data.begin(); it != array->data.end(); ++it)
	{
		Arr[i] = *it;
		i++;
	}
	return;
}
*/
