#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/Image.h>// <depend package="sensor_msgs" /> <!-- supaya bisa pake sensor msgs --> di manifest.xml
#include "std_msgs/Float32.h" 
#include "std_msgs/Float64.h"
#include <iostream>
#include "makinRGB_HSV.hpp"
#include "makinLandmark.hpp"
#include "slam_makin/Landmark_msg.h"
#include "slam_makin/Robot_position_msg.h"


#define SPIKE_EDGE 100
#define CALIBRATE_STEP_TO_PIXEL 2.25 ///Dari Hasil Kalibrasi, besar geser pixel kekanan setiap 1 derajat servo kekiri (1 step servo ke derajat 300/1024 = 0.29296875 derajat) 
#define CALIBRATE_DEG_TO_PIXEL 2.25 ///Dari Hasil Kalibrasi, besar geser pixel kekanan setiap 1 derajat servo kekiri (1 step servo ke derajat 300/1024 = 0.29296875 derajat) 

using namespace std;

float depth_minimal_jarak;
int depth_minimal_jarak_index;

int global_what_to_write=0;
int point_r,point_g,point_b;
int review_x0,review_x1;

sensor_msgs::Image imgpub;
sensor_msgs::Image imgMap;
slam_makin::Landmark_msg landmarkpub;



landmark landmarks;
void Callback_rgb(const sensor_msgs::Image::ConstPtr& img);
void Callback_depth(const sensor_msgs::Image::ConstPtr& img);
void Callback_servoBearing(const std_msgs::Float64::ConstPtr& sudut);
void Callback_robotBearing(const slam_makin::Robot_position_msg ::ConstPtr& robot);

int getSensorMsgsIndex(int x, int y, int max_width, int max_height, int step);

int global_robot_bearing;
int global_x_robot;
int global_y_robot;
int global_servo_bearing;
//~ Landmark_msg lm;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "mkn_data");
	ros::Subscriber rgbSub;
	ros::Subscriber depthSub;
	ros::Subscriber servoBearingSub;
	ros::Subscriber robotBearingSub;
	
	
	/*
	///MAP ------- MULAI
	imgMap.header.seq = 0; ///http://docs.ros.org/api/std_msgs/html/msg/Header.html
	imgMap.header.stamp.sec = 0;
	imgMap.header.stamp.nsec = 0;
	imgMap.header.frame_id = "a";
	imgMap.height = 57;
	imgMap.width = 102;
	imgMap.encoding = "rgb24"; ///https://code.ros.org/trac/ros-pkg/browser/stacks/common_msgs/trunk/sensor_msgs/include/sensor_msgs/image_encodings.h
	imgMap.is_bigendian = 0;
	imgMap.step = 102*3;
	//~ cout<<(sizeof(imgMap.data)/sizeof(*imgMap.data));
	//~ imgMap.data[1024*576*3]
	
	for (int ix=1;ix<10;ix++)
	for (int iy=1;iy<5;iy++)
	{
		imgMap.data[getSensorMsgsIndex(ix,iy,imgMap.width,imgMap.height,imgMap.step)] = 255;//r
		imgMap.data[getSensorMsgsIndex(ix,iy,imgMap.width,imgMap.height,imgMap.step)+1]=255;//g
		imgMap.data[getSensorMsgsIndex(ix,iy,imgMap.width,imgMap.height,imgMap.step)+2]=255;//b
	}
	///MAP----- release */
	
	
	ros::NodeHandle n;
	
	depthSub	=	n.subscribe<sensor_msgs::Image>("/camera/depth/image_raw", 100, Callback_depth);
	rgbSub		=	n.subscribe<sensor_msgs::Image>("/camera/rgb/image_color", 100, Callback_rgb);
	servoBearingSub=n.subscribe<std_msgs::Float64>("/head_pan_joint/command", 100, Callback_servoBearing); 
	robotBearingSub=n.subscribe<slam_makin::Robot_position_msg>("/mkn_robotPos", 100, Callback_robotBearing);
	
	
	ros::Publisher imgrepublish = n.advertise<sensor_msgs::Image>("mkn_data", 100);
	ros::Publisher landmarkpublish = n.advertise<slam_makin::Landmark_msg>("mkn_landmarks",100);
	ros::Publisher mappublish = n.advertise<sensor_msgs::Image>("mkn_map",100);
	
	
	global_robot_bearing = 0;
	global_x_robot = 0;
	global_y_robot = 0;
	global_servo_bearing = 0;
	
	while (ros::ok())
	{
		ros::spinOnce();
		imgrepublish.publish(imgpub);
		landmarkpub.landmark_count = landmarks.landmark_count;
		for (int _i=1;_i<=landmarks.landmark_count;_i++)
		{
			landmarkpub.x[_i] = landmarks.landmarks[_i].x;
			landmarkpub.y[_i] = landmarks.landmarks[_i].y;
			landmarkpub.range[_i] = landmarks.landmarks[_i].r;
			landmarkpub.bearing[_i]=landmarks.landmarks[_i].bearing;
			landmarkpub.id[_i]=landmarks.landmarks[_i].id;
		}
		
		landmarkpublish.publish(landmarkpub);
		mappublish.publish(imgMap);
	}
	return 0;
}

void Callback_depth(const sensor_msgs::Image::ConstPtr& img)
{
	int mid,p;
	mid = getSensorMsgsIndex( (img->width/2), (img->height/2), img->width, img->height, img->step );
	
	
	///RECHECK LANDMARKS HERE
	int i,depth_p1, depth_p2,sweep_1,sweep_2,edge_1,edge_2;
	for (i=1;i<=landmarks.prelandmark_count;i++)
	{
		int spiking=0;
		for (sweep_1=0;sweep_1<10;sweep_1++)
		{
			p = getSensorMsgsIndex(landmarks.prelandmarks[i].x0-sweep_1, (img->height/2), img->width, img->height, img->step);
			depth_p1 = (int(img->data[p]))+(int(img->data[p+1])<<8);
			p = getSensorMsgsIndex(landmarks.prelandmarks[i].x0-sweep_1-1, (img->height/2), img->width, img->height, img->step);
			depth_p2 = (int(img->data[p]))+(int(img->data[p+1])<<8);
			
			if (abs(depth_p1-depth_p2)>SPIKE_EDGE)
			{
				spiking = 1;
				break;
			}
		}
		for (sweep_2=0;sweep_2<10;sweep_2++)
		{
			p = getSensorMsgsIndex(landmarks.prelandmarks[i].x1+sweep_1, (img->height/2), img->width, img->height, img->step);
			depth_p1 = (int(img->data[p]))+(int(img->data[p+1])<<8);
			p = getSensorMsgsIndex(landmarks.prelandmarks[i].x1+sweep_1+1, (img->height/2), img->width, img->height, img->step);
			depth_p2 = (int(img->data[p]))+(int(img->data[p+1])<<8);
			
			if (abs(depth_p1-depth_p2)>SPIKE_EDGE)
			{
				spiking = 1;
				break;
			}
		}
		if (spiking)
		{
			///landmark localization
			int titik_tengah_landmark = (landmarks.prelandmarks[i].x0+landmarks.prelandmarks[i].x1)/2;
			
				/*
				 * 	x0 = 
				 * 	jarak_titik_tengah_ke_tengah_frame
				 * 	jarak = ((x1-x0)/2)-(img->width/2)
				 * 	berapa step dynamixel harus muter ke kiri/kanan untuk objek sampe tengah????
				 * 	step = jarak/CALIBRATE_STEP_TO_PIXEL;
				 * 	bearing = (sudut_servo)+(step*(sudut_per_step));
				 * 
				 * 	degree = jarak/CALIBRATE_DEG_TO_PIX;
				 * 	
				 */
			int landmark_di_frame_relativ = titik_tengah_landmark - (img->width/2); 
			int bearing_relativ = landmark_di_frame_relativ/CALIBRATE_DEG_TO_PIXEL;   ///KALO landmark tepat ditengah frame, servo posisinnya harus berapa?
			int landmark_bearing = global_servo_bearing-bearing_relativ;
			
			p = getSensorMsgsIndex(titik_tengah_landmark, (img->height/2), img->width, img->height, img->step);
			int landmark_range = (int(img->data[p]))+(int(img->data[p+1])<<8);
			
			float x,y;
			x = global_x_robot + landmark_range* cos(0.0174532925*(landmark_bearing+global_robot_bearing));///DARI degree ke radian
			y = global_y_robot + landmark_range* -sin(0.0174532925*(landmark_bearing+global_robot_bearing));
			
			///DATA ASSOSIATION sebelum add
			int aaa;
			for (aaa=1;aaa<=landmarks.landmark_count;aaa++)
			{
				if (	(abs(landmarks.landmarks[aaa].x-x)<MAX_SAME_LANDMARK_RANGE) && (abs(landmarks.landmarks[aaa].y-y)<MAX_SAME_LANDMARK_RANGE)	)
				{
					//~ aaa= (-100);
					break;
				}
			}
			if (aaa>landmarks.landmark_count)
			{
				landmarks.addLandmark(landmark_range,landmark_bearing,x,y); ///x,y data matang di peta coordinat cartesian, DONE! 
			}
			else
			{
				landmarks.resetLandmark(aaa, landmark_range, landmark_bearing,x,y);
			}
			landmarks.removeDuplicateLandmark();
			
			
			
			
		}
		landmarks.deletePreLandmark(i);
		
	}
	
	if (global_what_to_write==1)
	{
		cout<<
			(int(img->data[mid]))+(int(img->data[mid+1])<<8)<<"   "<<endl;
	}
	global_what_to_write = 0;
	cout<<"[[["<<landmarks.landmark_count<<"]]]]"<<endl;
	for (int bbb=1;bbb<=landmarks.landmark_count;bbb++)
	{
		cout<<landmarks.landmarks[bbb].r<<":"<<landmarks.landmarks[bbb].bearing;
		cout<<"["<<landmarks.landmarks[bbb].x<<","<<landmarks.landmarks[bbb].y<<"]"<<"\t";
	}
	cout<<endl;
}
void Callback_rgb(const sensor_msgs::Image::ConstPtr& img)
{
	imgpub.header = img->header;
	imgpub.height = img->height;
	imgpub.width = img->width;
	imgpub.encoding = img->encoding;
	imgpub.is_bigendian = img->is_bigendian;
	imgpub.step = img->step;
	imgpub.data = img->data;
	
	int r,g,b,h,s,v;
	#define THRESHOLD_H_MIN 60-40
	#define THRESHOLD_H_MAX 60+40
	#define THRESHOLD_S_MIN 30
	#define THRESHOLD_S_MAX 100
	#define THRESHOLD_V_MIN 30
	#define THRESHOLD_V_MAX 100
	int mid,p;
	
	int baristengah_x=0;
	int baristengah_y=0;
	baristengah_y = img->height/2;
	
	int samplingmatch=0;
	int alreadyset=0;
	
	for (baristengah_x=0;baristengah_x<img->width;baristengah_x++)
	{
		
		p = getSensorMsgsIndex( (baristengah_x), (baristengah_y), img->width, img->height, img->step );
		r = int(img->data[p]);
		g = int(img->data[p+1]);
		b = int(img->data[p+2]);
		
		rgbToHsv(r,g,b,&h,&s,&v);
		
		samplingmatch = 0;
		if (h>=THRESHOLD_H_MIN && h<THRESHOLD_H_MAX && s>THRESHOLD_S_MIN && s<THRESHOLD_S_MAX && v>THRESHOLD_V_MIN && v<THRESHOLD_V_MAX)
		{
			if (!alreadyset)
			{
				review_x0 = baristengah_x;
				alreadyset = 1;
			}
			while (samplingmatch<5 && baristengah_x<img->width)
			{
				p = getSensorMsgsIndex( (baristengah_x), (baristengah_y), img->width, img->height, img->step );
				r = int(img->data[p]);
				g = int(img->data[p+1]);
				b = int(img->data[p+2]);
				rgbToHsv(r,g,b,&h,&s,&v);
				imgpub.data[p]=255;
				imgpub.data[p+1]=0;
				imgpub.data[p+2]=0;
				baristengah_x++;
				if (!(h>=THRESHOLD_H_MIN && h<THRESHOLD_H_MAX && s>THRESHOLD_S_MIN && s<THRESHOLD_S_MAX && v>THRESHOLD_V_MIN && v<THRESHOLD_V_MAX))
				{
					samplingmatch++;
				}
				else
				{
					samplingmatch=0;
				}
			}
			review_x1 = baristengah_x;
			if ((review_x1-review_x0)<10)
			{
				alreadyset=0;
				review_x0 = 0;
				review_x1 = 0;
				imgpub.data = img->data;
			}
			else
			{
				/// save now so we can check its depth later on depth kolbek
				//~ landmarks.addLandmark(review_x0,review_x1,baristengah_y,baristengah_y,0);
				
				/** re map pos **/
				
				///Data asosiasi landmark satu frame
				int i;
				for (i=1; i<=landmarks.prelandmark_count;i++)
				{
					if (abs(landmarks.prelandmarks[i].x0-review_x0)<LANDMARK_ASOSIASI_DATA_SELISIH_MAX) //landmark yg sama
					{
						landmarks.resetPreLandmark(i,review_x0,review_x1,DEFAULT,DEFAULT,DEFAULT);
						break;
					}
				}
				if (i>landmarks.prelandmark_count)
				{
					landmarks.addPreLandmark(review_x0,review_x1,baristengah_y,baristengah_y,0);
				}
				alreadyset=0;
			}
		}
		//~ cout<<review_x0<<" sampai "<<review_x1<<endl;
	}
	
	review_x0=0;
	review_x1=0;
	if (global_what_to_write ==0)
	{
		cout<<h<<" "<<s<<" "<<v<<"\t\t";
		cout<<r<<" "<<g<<" "<<b<<"\t\t";
	}
	global_what_to_write = 1;
	
}

void Callback_servoBearing(const std_msgs::Float64::ConstPtr& sudut)
{
	double s = sudut->data;
	global_servo_bearing = (int(s / 0.0174532925))* (1);
}
void Callback_robotBearing(const slam_makin::Robot_position_msg ::ConstPtr& robot)
{
	double s = robot->bearing;
	global_x_robot = robot->x;
	global_y_robot = robot->y;
	global_robot_bearing = int(s / 0.0174532925);
}

int getSensorMsgsIndex(int x, int y, int max_width, int max_height, int step)
{
	//~ return x*step*y;
	return ((y-1)*step + (x* (step/max_width)) );
	
}
