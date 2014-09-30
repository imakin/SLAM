///Makin 5 Juli 2014
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/Image.h>// <depend package="sensor_msgs" /> <!-- supaya bisa pake sensor msgs --> di manifest.xml
#include "std_msgs/Float32.h" 
#include "std_msgs/Float64.h"
#include <iostream>
#include "makinLandmark.hpp"
#include "slam_makin/Landmark_msg.h"
#include "slam_makin/Robot_position_msg.h"

#define X_INDEX_ROBOT_x 0
#define X_INDEX_ROBOT_y 1
#define X_INDEX_ROBOT_bearing 2
#define X_INDEX_LANDMARK_x(landmark_num) ((3+landmark_num-1)*2) 
#define X_INDEX_LANDMARK_y(landmark_num) ((3+landmark_num-1)*2) 

landmark landmarks;
int global_robot_bearing;
int global_x_robot;
int global_y_robot;
int global_last_x_robot;
int global_last_y_robot;




/// MAtrik - matrik EKF 
int matrix_X[3+2*MAX_LANDMARK]; //The system state matrix 

int matrix_A [3][3]; //Jaqobian of the prediction model matrix 


void update_X(void);
void update_current_state(void);

void Callback_robotBearing(const slam_makin::Robot_position_msg ::ConstPtr& robot);
void Callback_landmarks(const slam_makin::Landmark_msg ::ConstPtr& landmark_ptr);

int main(int argc, char **argv)
{
	ros::init(argc, argv, "mkn_EKF_SLAM");
	ros::Subscriber landmarksub;
	ros::Subscriber robotBearingSub;
	
	ros::NodeHandle n;
	
	robotBearingSub	=	n.subscribe<slam_makin::Robot_position_msg>("/mkn_robotPos", 100, Callback_robotBearing);
	landmarksub		=	n.subscribe<slam_makin::Landmark_msg>("/mkn_landmarks", 100, Callback_landmarks);
	
	global_robot_bearing = 0;
	global_x_robot = 0;
	global_y_robot = 0;
	
	while (ros::ok())
	{
		ros::spinOnce();
		update_X();
	}
	return 0;
}

void update_current_state(void)
{
	update_X();
	update_A();
}

void update_X(void)
{
	matrix_X[X_INDEX_ROBOT_x] 			= global_x_robot;
	matrix_X[X_INDEX_ROBOT_y] 			= global_y_robot;
	matrix_X[X_INDEX_ROBOT_bearing]	= global_robot_bearing;
	for (int i=1;i<=landmarks.landmark_count;i++)
	{
		matrix_X[X_INDEX_LANDMARK_x(i)] = landmarks.landmarks[i].x;
		matrix_X[X_INDEX_LANDMARK_y(i)] = landmarks.landmarks[i].y;
	}
}

void update_A(void)
{
	/* jaqobian of prediction model
	 * 
	 * [	1	0	-Dy	] (delta y)
	 * [	0	1	-Dx	]
	 * [	0	0	1	]
	 */
	 matrix_A[0][0] = 1; matrix_A[0][1] = 0; matrix_A[0][2] = (global_last_y_robot - global_y_robot);
	 matrix_A[1][0] = 0; matrix_A[1][1] = 1; matrix_A[1][2] = (global_x_robot - global_last_x_robot);
	 matrix_A[2][0] = 0; matrix_A[2][1] = 0; matrix_A[2][2] = 1;
}

void Callback_robotBearing(const slam_makin::Robot_position_msg ::ConstPtr& robot)
{
	double s = robot->bearing;
	global_last_x_robot = global_x_robot;
	global_last_y_robot = global_y_robot;
	global_x_robot = robot->x;
	global_y_robot = robot->y;
	global_robot_bearing = int(s / 0.0174532925);
}

void Callback_landmarks(const slam_makin::Landmark_msg ::ConstPtr& landmark_ptr)
{
	landmarks.landmark_count = landmark_ptr->landmark_count;
	for (int i=1;i<=landmarks.landmark_count;i++)
	{
		landmarks.landmarks[i].x = landmark_ptr->x[i];
		landmarks.landmarks[i].y = landmark_ptr->y[i];
		landmarks.landmarks[i].r = landmark_ptr->range[i];
		landmarks.landmarks[i].bearing = landmark_ptr->bearing[i];
		landmarks.landmarks[i].id = landmark_ptr->id[i];
	}
}


