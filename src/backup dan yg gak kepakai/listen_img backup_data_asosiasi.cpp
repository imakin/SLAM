#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/Image.h>// <depend package="sensor_msgs" /> <!-- supaya bisa pake sensor msgs --> di manifest.xml
#include "std_msgs/Float32.h" 
#include <iostream>
#include "makinRGB_HSV.hpp"
#include "makinLandmark.hpp"

#define SPIKE_EDGE 100
#define CALIBRATE_STEP_TO_PIXEL 4.5 ///Dari Hasil Kalibrasi, besar geser pixel kekanan setiap 1 derajat servo kekiri (1 step servo ke derajat 300/1024 = 0.29296875 derajat) 

using namespace std;

float depth_minimal_jarak;
int depth_minimal_jarak_index;

int global_what_to_write=0;
int point_r,point_g,point_b;
int review_x0,review_x1;
sensor_msgs::Image imgpub;
//~ landmark landmarks;	
//~ landmark* landmark::uniqueInstance = new landmark();
landmark landmarks;
void Callback_rgb(const sensor_msgs::Image::ConstPtr& img);
void Callback_depth(const sensor_msgs::Image::ConstPtr& img);
int getSensorMsgsIndex(int x, int y, int max_width, int max_height, int step);

int main(int argc, char **argv)
{
	ros::init(argc, argv, "mkn_data_RGB");
	ros::Subscriber rgbSub;
	ros::Subscriber depthSub;
	
	ros::NodeHandle n;
	
	depthSub	=	n.subscribe<sensor_msgs::Image>("/camera/depth/image_raw", 100, Callback_depth);
	rgbSub		=	n.subscribe<sensor_msgs::Image>("/camera/rgb/image_color", 100, Callback_rgb);
	
	ros::Publisher imgrepublish = n.advertise<sensor_msgs::Image>("mkn_data", 1000);
	
	
	
	while (ros::ok())
	{
		ros::spinOnce();
		imgrepublish.publish(imgpub);
	}
	return 0;
}

void Callback_depth(const sensor_msgs::Image::ConstPtr& img)
{
	int mid,p;
	mid = getSensorMsgsIndex( (img->width/2), (img->height/2), img->width, img->height, img->step );
	
	
	///RECHECK LANDMARKS HERE
	int i,depth_p1, depth_p2,sweep_1,sweep_2,edge_1,edge_2;
	for (i=1;i<=landmarks.landmark_count;i++)
	{
		int spiking=0;
		for (sweep_1=0;sweep_1<10;sweep_1++)
		{
			p = getSensorMsgsIndex(landmarks.landmarks_x0[landmarks.landmark_count]-sweep_1, (img->height/2), img->width, img->height, img->step);
			depth_p1 = (int(img->data[p]))+(int(img->data[p+1])<<8);
			p = getSensorMsgsIndex(landmarks.landmarks_x0[landmarks.landmark_count]-sweep_1-1, (img->height/2), img->width, img->height, img->step);
			depth_p2 = (int(img->data[p]))+(int(img->data[p+1])<<8);
			
			if (abs(depth_p1-depth_p2)>SPIKE_EDGE)
			{
				spiking = 1;
				break;
			}
		}
		for (sweep_2=0;sweep_2<10;sweep_2++)
		{
			p = getSensorMsgsIndex(landmarks.landmarks_x0[landmarks.landmark_count]+sweep_1, (img->height/2), img->width, img->height, img->step);
			depth_p1 = (int(img->data[p]))+(int(img->data[p+1])<<8);
			p = getSensorMsgsIndex(landmarks.landmarks_x0[landmarks.landmark_count]+sweep_1+1, (img->height/2), img->width, img->height, img->step);
			depth_p2 = (int(img->data[p]))+(int(img->data[p+1])<<8);
			
			if (abs(depth_p1-depth_p2)>SPIKE_EDGE)
			{
				spiking = 1;
				break;
			}
		}
		if (!spiking)
		{
			landmarks.deleteLandmark(i);
		}
	}
	
	if (global_what_to_write==1)
	{
		cout<<
			(int(img->data[mid]))+(int(img->data[mid+1])<<8)<<"   "<<endl;
	}
	global_what_to_write = 0;
	cout<<"[[["<<landmarks.landmark_count<<"]]]]"<<endl;;
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
	
	int samplingmatch=0;
	int alreadyset=0;
	baristengah_y = img->height/2;
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
				/*
				 * 	x0 = 
				 * 	jarak_titik_tengah_ke_tengah_frame
				 * 	jarak = ((x1-x0)/2)-(img->width/2)
				 * 	berapa step dynamixel harus muter ke kiri/kanan untuk objek sampe tengah????
				 * 	step = jarak/CALIBRATE_STEP_TO_PIXEL;
				 * 	bearing = (sudut_servo)+(step*(sudut_per_step));
				 * 
				 */
				
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

int getSensorMsgsIndex(int x, int y, int max_width, int max_height, int step)
{
	//~ return x*step*y;
	return ((y-1)*step + (x* (step/max_width)) );
	
}
