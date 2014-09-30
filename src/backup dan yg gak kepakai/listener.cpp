#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>// <depend package="sensor_msgs" /> <!-- supaya bisa pake sensor msgs --> di manifest.xml
#include "std_msgs/Float32.h" 
#include <iostream>
using namespace std;

#define MAX_LANDMARK 100
#define MAX_DEPTH	11 		/**meter**/
#define EXTREMA_BATAS 0.5 	/**batas extrim jarak dianggap 1 objek, meter**/

float depth_landmark_terdeteksi;
float depth_terjauh;
int depth_landmark_terdeteksi_index;
int landmark_count;

sensor_msgs::LaserScan depth;


void Callback_depth(const sensor_msgs::LaserScan::ConstPtr& scan_depth)
{
	int ii;
	int a[MAX_LANDMARK], b[MAX_LANDMARK]; /** untuk setiap landmark, a batas poin index kecil, b batas poin index gedhe **/
	landmark_count = 0;
	ii=0;
	depth_terjauh = 0;
	depth_landmark_terdeteksi = scan_depth->ranges[ii];
	depth_landmark_terdeteksi_index = ii;
	while (ii<360)
	{
		if (scan_depth->ranges[ii]<10)
		{
			if (scan_depth->ranges[ii]>depth_terjauh)
				depth_terjauh=scan_depth->ranges[ii];
			
			/** Cari extrema **/
			a[landmark_count] = ii;
			while (abs(scan_depth->ranges[ii]-depth_landmark_terdeteksi)<EXTREMA_BATAS)
			{
				ii=ii+5;
			}
			/** Sudah dapat titik ekstrema cari mana yang lebih dekat **/
			if (scan_depth->ranges[ii-5]>depth_landmark_terdeteksi)
			{
				a[landmark_count]=ii;/** lebih dekat yang tengah (landmark yang itu) **/
				
				depth_landmark_terdeteksi_index = ii-5;
				depth_landmark_terdeteksi = scan_depth->ranges[depth_landmark_terdeteksi_index];
				
				/** scan lagi untuk titik poin index gedhe (b) **/
				while (abs(scan_depth->ranges[ii]-depth_landmark_terdeteksi)<EXTREMA_BATAS)
				{
					ii=ii+5;
				}
				b[landmark_count] = ii-5;
				if (a[landmark_count]<b[landmark_count])
					landmark_count++;
			}
			else
			{
				depth_landmark_terdeteksi_index = a[landmark_count];
				depth_landmark_terdeteksi = scan_depth->ranges[depth_landmark_terdeteksi_index];
				
				a[landmark_count] = a[landmark_count]; /** di baris atas sudah diisi, kalau lebih dekat yang pinggir, landmark yang itu **/
				b[landmark_count] = ii-5;
				if (a[landmark_count]<b[landmark_count])
					landmark_count++;
			} 															/// end if (scan_depth->ranges[ii-5]>depth_landmark_terdeteksi)
		} 																/// end if (scan_depth->ranges[ii]<11)
		ii++;
	}
	cout<<landmark_count;
	cout<<"   range terjauh: "<<depth_terjauh<<endl;
	for (ii=0;ii<landmark_count;ii++)
	{
		if (abs(depth_terjauh-scan_depth->ranges[a[ii]])<EXTREMA_BATAS)
			continue;
		cout<<"Landmark #"<<ii<<" points: "<<endl;
		int jj;
		for (jj=a[ii];jj<b[ii];jj++)
		{
			//~ cout<<scan_depth->ranges[jj]<<" ";
			cout<<jj<<" ";
		}
		cout<<endl;
	}
	cout<<endl;cout<<endl;cout<<endl;
}
//~ void AutoExp::processLaserScan(const sensor_msgs::LaserScan::ConstPtr& scan){
	//~ ROS_INFO("I heard: [%f]", scan->ranges[2]);
//~ }

int main(int argc, char **argv)
{
	ros::init(argc, argv, "mkn_data_depth");

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

