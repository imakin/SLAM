#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "slam_makin/Landmark.h"
#include "slam_makin/Map.h"
#include "slam_makin/Landmark_msg.h"
#include <geometry_msgs/PoseWithCovarianceStamped.h>

#include <iostream>
#include <sstream>
using namespace std;

void Callback_mapSubsribe(const slam_makin::Map ::ConstPtr& map);
void Callback_lSubsribe(const geometry_msgs::PoseWithCovarianceStamped ::ConstPtr& lm);

slam_makin::Map globalMap;

int main( int argc, char** argv )
{
	ros::init(argc, argv, "basic_shapes");
	ros::NodeHandle n;
	ros::Rate r(1);
	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
	
	ros::Subscriber mapSubscriber;
	ros::Subscriber lSubscriber;
	mapSubscriber=n.subscribe<slam_makin::Map>("/pose_ekf_slam/map", 100, Callback_mapSubsribe);
	lSubscriber=n.subscribe<geometry_msgs::PoseWithCovarianceStamped>("/pose_ekf_slam/landmark_update/landmark_0", 100, Callback_lSubsribe);
	
	
	uint32_t shape = visualization_msgs::Marker::CUBE;

	while (ros::ok())
	{
		//~ visualization_msgs::Marker marker;
		//~ marker.header.frame_id = "/my_frame";
		//~ marker.header.stamp = ros::Time::now();
//~ 
		//~ /// Set the namespace and id for this marker.  This serves to create a unique ID
		//~ /// Any marker sent with the same namespace and id will overwrite the old one
		//~ marker.ns = "basic_shapes";
		//~ marker.id = 0;
//~ 
		//~ marker.type = shape;
//~ 
		//~ /// Set the marker action.  Options are ADD and DELETE
		//~ marker.action = visualization_msgs::Marker::ADD;
//~ 
		//~ /// Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
		//~ marker.pose.position.x = 0;
		//~ marker.pose.position.y = 0;
		//~ marker.pose.position.z = 0;
		//~ marker.pose.orientation.x = 0.0;
		//~ marker.pose.orientation.y = 0.0;
		//~ marker.pose.orientation.z = 0.0;
		//~ marker.pose.orientation.w = 1;
//~ 
		//~ /// Set the scale of the marker -- 1x1x1 here means 1m on a side
		//~ marker.scale.x = 1.0;
		//~ marker.scale.y = 1.0;
		//~ marker.scale.z = 1.0;
//~ 
		//~ /// Set the color -- be sure to set alpha to something non-zero!
		//~ marker.color.r = 0.0f;
		//~ marker.color.g = 1.0f;
		//~ marker.color.b = 0.0f;
		//~ marker.color.a = 1.0;
//~ 
		//~ marker.lifetime = ros::Duration();
//~ 
		//~ /// Publish the marker
		//~ marker_pub.publish(marker);

		ros::spinOnce();
		//~ r.sleep();
		//~ cout<< "masuk2";
	}
}


void Callback_mapSubsribe(const slam_makin::Map ::ConstPtr& map)
{
	//~ globalMap = map;
	//~ cout << sizeof (map)/sizeof(*map);
	cout<< "masuk map subscribe";
}

void Callback_lSubsribe(const geometry_msgs::PoseWithCovarianceStamped ::ConstPtr& lm)
{
	//~ cout<<lm->pose->pose->position->x;
}
