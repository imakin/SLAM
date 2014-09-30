#include <ros/ros.h>
#include <iostream>

#include <std_msgs/String.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/TwistWithCovarianceStamped.h>


#include <tf/transform_broadcaster.h>
#include "makinRGB_HSV.hpp"
#include "makinLandmark.hpp"
#include "slam_makin/Landmark_msg.h"
#include "slam_makin/Robot_position_msg.h"
#include "slam_makin/SetPosition.h"


#include <sstream>

#define to_string(____x) static_cast<std::ostringstream*>( &(std::ostringstream() << ____x) )->str()



//~ #define CALIBRATE_DEG_TO_PIXEL 2.25 ///Dari Hasil Kalibrasi, besar geser pixel kekanan setiap 1 derajat servo kekiri (1 step servo ke derajat 300/1024 = 0.29296875 derajat) 
//~ #define CALIBRATE_DEG_TO_PIXEL 2.1584 ///Dari Hasil Kalibrasi, besar geser pixel kekanan setiap 1 derajat servo kekiri (1 step servo ke derajat 300/1024 = 0.29296875 derajat) 
float CALIBRATE_DEG_TO_PIXEL = (160.0/62.0); /// 1 frame, width x = 160px, init 160

using namespace std;

float depth_minimal_jarak;
int depth_minimal_jarak_index;

int global_what_to_write=0;
int point_r,point_g,point_b;
int review_x0,review_x1;

sensor_msgs::Image imgpub;
sensor_msgs::Image imgMap;
slam_makin::Landmark_msg landmarkpub;
int GLOBAL_RUN;



landmark landmarks;
void Callback_globalRun(const std_msgs::Int32::ConstPtr& _run);
void Callback_rgb(const sensor_msgs::Image::ConstPtr& img);
void Callback_depth(const sensor_msgs::Image::ConstPtr& img);
void Callback_servoBearing(const std_msgs::Float64::ConstPtr& sudut);
void Callback_robotBearing(const slam_makin::Robot_position_msg ::ConstPtr& robot);
void landmarkPublishtoEKF(int ii);

int getSensorMsgsIndex(int x, int y, int max_width, int max_height, int step);

double global_robot_bearing;
float global_x_robot;
float global_y_robot;
geometry_msgs::PoseWithCovarianceStamped global_pose_robot;


void posePublishtoEKF(void);
void imuPublishtoEKF(void);
void velPublishtoEKF(void);
ros::Publisher posepublish;
ros::Publisher imupublish;
ros::Publisher velpublish;


double global_servo_bearing;
int global_servo_updated=0;
//~ Landmark_msg lm;


ros::Publisher global_landmarkpub_to_EKF;

double global_runStart;
int global_oncestarted=0;
int main(int argc, char **argv)
{
	GLOBAL_RUN = 1;
	ros::init(argc, argv, "mkn_data");
	ros::Subscriber rgbSub;
	ros::Subscriber depthSub;
	ros::Subscriber servoBearingSub;
	ros::Subscriber robotBearingSub;
	ros::Subscriber isRunningSub;
	
	global_robot_bearing = 0.0;
	global_x_robot = 0.0;///meter
	global_y_robot = 0.0;
	global_servo_bearing = 0.0;
	
	
	
	ros::NodeHandle n;
	
	depthSub	=	n.subscribe<sensor_msgs::Image>("/camera/depth/image_raw", 100, Callback_depth);
	rgbSub		=	n.subscribe<sensor_msgs::Image>("/camera/rgb/image_color", 100, Callback_rgb);
	servoBearingSub=n.subscribe<std_msgs::Float64>("/head_pan_joint/command", 1, Callback_servoBearing); 
	robotBearingSub=n.subscribe<slam_makin::Robot_position_msg>("/mkn_robotPos", 100, Callback_robotBearing);
	
	isRunningSub=n.subscribe<std_msgs::Int32>("/mkn_global_run", 100, Callback_globalRun);
	
	
	ros::Publisher imgrepublish = n.advertise<sensor_msgs::Image>("mkn_data", 100);
	ros::Publisher landmarkpublish = n.advertise<slam_makin::Landmark_msg>("mkn_landmarks",100);
	ros::Publisher mappublish = n.advertise<sensor_msgs::Image>("mkn_map",100);
	posepublish = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("/pose_ekf_slam/pose_update",2000);
	imupublish = n.advertise<sensor_msgs::Imu>("/pose_ekf_slam/imu_input",2000);
	velpublish = n.advertise<geometry_msgs::TwistWithCovarianceStamped>("/pose_ekf_slam/velocity_update",2000);
	
	
	///init EKF dgn request posisi dgn service
	ros::ServiceClient client = n.serviceClient<slam_makin::SetPosition>("pose_ekf_slam/set_position");
	slam_makin::SetPosition setpos_req;
	setpos_req.request.position.x = global_x_robot;
	setpos_req.request.position.y = global_y_robot;
	setpos_req.request.position.z = 0.0;
	if (client.call(setpos_req))
	{
		cout<<"EKF init, posisi request terkirim\n";
	}
	else
	{
		cout<<"init failed\n";
	}
	
	
	double last_publish_landmark_time = ros::Time::now().toSec();
	double last_publish_pose_time = ros::Time::now().toSec();
	int index_landmark_publish = 1;
	
	while (ros::ok())
	{
		ros::spinOnce();
		imgrepublish.publish(imgpub);
		if (!GLOBAL_RUN)
			continue;
		
		
		if (global_servo_updated==0)
		{
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
			
			if (landmarks.landmark_count>0)
			{
				static string landmark_topicname;
				landmark_topicname = "pose_ekf_slam/landmark_update/landmark_";
				landmark_topicname += to_string(landmarks.landmarks[index_landmark_publish].id);
				
				global_landmarkpub_to_EKF = n.advertise<geometry_msgs::PoseWithCovarianceStamped>(landmark_topicname,20);
					
				if (((ros::Time::now().toSec() - last_publish_landmark_time)>2.0) && landmarks.landmark_count>0)
				{
					landmarkPublishtoEKF(index_landmark_publish);
					last_publish_landmark_time = ros::Time::now().toSec();
					index_landmark_publish++;
					if (index_landmark_publish>landmarks.landmark_count)
						index_landmark_publish = 1;
				}
			}
		} /**end if (global_servo_updated==0)**/
		else
		{
			global_servo_updated-=1;
		}
		if ((ros::Time::now().toSec() - last_publish_pose_time) > 2.0)
		{
			posePublishtoEKF();
			velPublishtoEKF();
			imuPublishtoEKF();
			last_publish_pose_time = ros::Time::now().toSec();
		}
	}
	return 0;
}

///untuk spesifik landmark index ii
void landmarkPublishtoEKF(int ii) 
{
	
		static tf::TransformBroadcaster br;
		  tf::Transform transform;
		  transform.setOrigin( tf::Vector3( landmarks.landmarks[ii].x, landmarks.landmarks[ii].y, 0.0) );
		  tf::Quaternion q;
		  q.setRPY(/**msg->theta**/0, 0, 0); ///zero puteran
		  transform.setRotation(q);
		  
		  static string landmark_fullnameID;
		  landmark_fullnameID = "landmark_";
		  landmark_fullnameID += to_string(landmarks.landmarks[ii].id);
		
		  
		  geometry_msgs::PoseWithCovarianceStamped p;
			p.header.stamp = ros::Time::now();
			p.header.frame_id = landmark_fullnameID;
			///Matrix diagonal diisi nilai variance (seberapa besar nilai bisa menyebar /ketidak telitian
			p.pose.covariance[0] = 0.0005; ///error 0.5 mm (skala terkecil posisi 1 mm) 
			p.pose.covariance[7] = 0.0005; ///nilai statis , cant be zero (result in singular matrix calculation) 
			p.pose.covariance[14] = 0.0005;///nilai statis
			p.pose.pose.position.x = 0; //0 dari diri sendiri, jarak di frame di post di tf 
			p.pose.pose.position.y = 0;
			p.pose.pose.position.z = 0;
			p.pose.pose.orientation.x =0;
			p.pose.pose.orientation.y =0;
			p.pose.pose.orientation.z =0;
			p.pose.pose.orientation.w =0;
		  
		  br.sendTransform(tf::StampedTransform(transform, p.header.stamp,"robot", p.header.frame_id)); ///parent sikik, njut child (kuwalik karo sing piton)
			  
			///kyne keluar loop uwis destroy
			global_landmarkpub_to_EKF.publish(p);
			cout<<"publish landmark_"<<landmarks.landmarks[ii].id<<endl;
}


void posePublishtoEKF(void)
{
	///Publish posisi robot untuk slam
		global_pose_robot.header.stamp = ros::Time::now();
		global_pose_robot.header.frame_id = "pose";
		global_pose_robot.pose.covariance[0] = 0.001; 
		global_pose_robot.pose.covariance[7] = 0.001; 
		global_pose_robot.pose.covariance[14] = 9999;///z tidak dimodif
		global_pose_robot.pose.pose.position.x = global_x_robot; 
		global_pose_robot.pose.pose.position.y = global_y_robot;
		global_pose_robot.pose.pose.position.z = 0;
		global_pose_robot.pose.pose.orientation.x =0;
		global_pose_robot.pose.pose.orientation.y =0;
		global_pose_robot.pose.pose.orientation.z =0;
		global_pose_robot.pose.pose.orientation.w =0;
		posepublish.publish(global_pose_robot);
		
		static tf::TransformBroadcaster posetf;
		  tf::Transform transform;
		  transform.setOrigin( tf::Vector3( global_pose_robot.pose.pose.position.x, global_pose_robot.pose.pose.position.y, 0.0) );
		  tf::Quaternion q;
		  q.setRPY(/**msg->theta**/0, 0, 0); ///zero puteran
		  transform.setRotation(q);
		  posetf.sendTransform(tf::StampedTransform(transform, global_pose_robot.header.stamp,"robot", global_pose_robot.header.frame_id)); ///parent sikik "robot", njut child (kuwalik karo sing piton)
}


void imuPublishtoEKF(void)
{
	sensor_msgs::Imu imu;
	imu.header.stamp = ros::Time::now();
	imu.header.frame_id = "imu";
	imu.orientation.x = 0.0;
	imu.orientation.y = 0.0;
	imu.orientation.z = 0.0;
	imu.orientation.w = 1.0;
	imu.linear_acceleration.x = 0.00;
	imupublish.publish(imu);
	
	//# Publish TF
	static tf::TransformBroadcaster publishtf;
	tf::Transform transform;
	transform.setOrigin( tf::Vector3( 0, 0, 0.0) );
	tf::Quaternion q;
	q.setRPY(/**msg->theta**/0, 0, 0);
	transform.setRotation(q);
	publishtf.sendTransform(tf::StampedTransform(transform, imu.header.stamp,"robot", imu.header.frame_id)); ///parent sikik "robot", njut child (kuwalik karo sing piton)


}

void velPublishtoEKF(void)
{
	geometry_msgs::TwistWithCovarianceStamped v;
	v.header.stamp = ros::Time::now();
	v.header.frame_id = "vel";
	
	//# create a new velocity
	v.twist.twist.linear.x = 0.0;
	v.twist.twist.linear.y = 0.0;
	v.twist.twist.linear.z = 0.0;
	
	//# Only the number in the covariance matrix diagonal 
	//# are used for the updates!
	v.twist.covariance[0] = 0.01;
	v.twist.covariance[7] = 0.01;
	v.twist.covariance[14] = 0.01;
	
	velpublish.publish(v);
	///publish TF
	static tf::TransformBroadcaster publishtf;
	tf::Transform transform;
	transform.setOrigin( tf::Vector3( 0, 0, 0.0) );
	tf::Quaternion q;
	q.setRPY(/**msg->theta**/0, 0, 0);
	transform.setRotation(q);
	publishtf.sendTransform(tf::StampedTransform(transform, v.header.stamp,"robot", v.header.frame_id)); ///parent sikik "robot", njut child (kuwalik karo sing piton)

	
        
}


void Callback_depth(const sensor_msgs::Image::ConstPtr& img)
{
	if (!GLOBAL_RUN)
		return;
	if (global_servo_updated!=0)
	{
		cout<<endl<<"bearing kamera (Servo) berubah. menunggu "<<global_servo_updated<<" sample"<<endl;
		return;
		
	}
	int mid,p;
	mid = getSensorMsgsIndex( (img->width/2), (img->height/2), img->width, img->height, img->step );
	
	
	///RECHECK LANDMARKS HERE (YG DIDAPAT DR COLOR THRESHOLD DISIMPEN DI PRELANDMARK)
	int i,depth_p1, depth_p2,depth_p3,sweep_1,sweep_2,edge_1,edge_2;
	for (i=1;i<=landmarks.prelandmark_count;i++)
	{
		int spiking=0;
		for (sweep_1=0;sweep_1<10;sweep_1++)
		{
			p = getSensorMsgsIndex((landmarks.prelandmarks[i].x0+landmarks.prelandmarks[i].x1)/2, (img->height/2), img->width, img->height, img->step);
			depth_p1 = (int(img->data[p]))+(int(img->data[p+1])<<8);
			p = getSensorMsgsIndex(landmarks.prelandmarks[i].x0-sweep_1, (img->height/2), img->width, img->height, img->step);
			depth_p2 = (int(img->data[p]))+(int(img->data[p+1])<<8);
			
			if ((depth_p2-depth_p1)>SPIKE_EDGE)
			{
				spiking = 1;
				break;
			}
		}
		for (sweep_2=0;sweep_2<10;sweep_2++)
		{
			p = getSensorMsgsIndex((landmarks.prelandmarks[i].x0+landmarks.prelandmarks[i].x1)/2, (img->height/2), img->width, img->height, img->step);
			depth_p1 = (int(img->data[p]))+(int(img->data[p+1])<<8);
			p = getSensorMsgsIndex(landmarks.prelandmarks[i].x1+sweep_2, (img->height/2), img->width, img->height, img->step);
			depth_p2 = (int(img->data[p]))+(int(img->data[p+1])<<8);
			
			if ((depth_p2-depth_p1)>SPIKE_EDGE)
			{
				spiking += 1;
				break;
			}
		}
		if (spiking>1)
		{
			///landmark localization
			int titik_tengah_landmark = (landmarks.prelandmarks[i].x0+landmarks.prelandmarks[i].x1)/2;	
			///8 Agustus 2014, coba kalkulasi baru
			/**
			 * Semua disesuaikan arah sudut positifnya supaya sama, sesuai bentuk standar sistem koordinat polar, arah sudut positif berlawanan jarum jam
			 * 			0
			 * 		90		270
			 * 			180
			 */
			 
			int landmark_di_frame_relativ = (img->width/2) - titik_tengah_landmark; /** nilai positif ketika landmark dikiri frame,  nilai positif ketika landmark dikiri frame **/
			double bearing_di_frame_relativ = double(landmark_di_frame_relativ)/double(CALIBRATE_DEG_TO_PIXEL);
			double landmark_bearing = global_robot_bearing + global_servo_bearing + bearing_di_frame_relativ;
			
			p = getSensorMsgsIndex(titik_tengah_landmark, (img->height/2), img->width, img->height, img->step);
			int landmark_range = (int(img->data[p]))+(int(img->data[p+1])<<8);
			
			///~ KALAU range kurang dr 40cm gak dhitung
			if (landmark_range<400)
				continue;
			
			float x,y;
			///hitung koordinat dari robot
			x = float(landmark_range) *  sin(0.0174532925*float(landmark_bearing));///DARI degree ke radian
			y = float(landmark_range) *  cos(0.0174532925*float(landmark_bearing));
			
			/// mm to meter
			x=x/1000;
			y=y/1000;
			///global_x dalam meter, hitung koordinat dari world frame
			x = global_x_robot - x;
			y = global_y_robot + y;
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
			if (aaa>landmarks.landmark_count) ///Kalo udah ada reset ( update posisi), kalo blm ada nambah baru
			{
				landmarks.addLandmark(landmark_range,landmark_bearing,x,y); ///x,y data matang di peta coordinat cartesian, DONE! 
			}
			else
			{
				landmarks.resetLandmark(aaa, landmark_range, landmark_bearing,x,y);
				landmarks.landmarks[aaa].spike = abs(depth_p1-depth_p2);
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
	cout<<"[[["<<landmarks.landmark_count<<"]]]]" << " posisi robot:"<<global_x_robot<<","<<global_y_robot<<endl;
	for (int bbb=1;bbb<=landmarks.landmark_count;bbb++)
	{
		cout<<landmarks.landmarks[bbb].id<<". ";
		cout<<landmarks.landmarks[bbb].r<<":"<<landmarks.landmarks[bbb].bearing;
		cout<<"["<<landmarks.landmarks[bbb].x<<","<<landmarks.landmarks[bbb].y<<"]"<<landmarks.landmarks[bbb].spike<<"\t";
	}
	cout<<endl;
	
	cout<<ros::Time::now().toSec()-global_runStart<<endl;
	if (landmarks.landmark_count>1)
		ros::shutdown();
}
void Callback_rgb(const sensor_msgs::Image::ConstPtr& img)
{
	if (!global_oncestarted)
	{
		global_runStart = ros::Time::now().toSec();
		global_oncestarted = 1;
	}
	if (!GLOBAL_RUN)
		return;
	
	CALIBRATE_DEG_TO_PIXEL = img->width/62.0; //hitung ulang 
	if (global_servo_updated!=0)
	{
		cout<<endl<<"bearing kamera (Servo) berubah. menunggu "<<global_servo_updated<<" sample"<<endl;
		return;
		
	}
	imgpub.header = img->header;
	imgpub.height = img->height;
	imgpub.width = img->width;
	imgpub.encoding = img->encoding;
	imgpub.is_bigendian = img->is_bigendian;
	imgpub.step = img->step;
	imgpub.data = img->data;
	
	int r,g,b,h,s,v;
	#define THRESHOLD_H_MIN 60-20
	#define THRESHOLD_H_MAX 60+20
	#define THRESHOLD_S_MIN 30
	#define THRESHOLD_S_MAX 100
	#define THRESHOLD_V_MIN 30
	#define THRESHOLD_V_MAX 100
	#define MINIMUM_TERTANGKAP_BESAR_LEBAR_PIXEL 4 //10
	int mid,p;
	
	int baristengah_x=0;
	int baristengah_y=0;
	baristengah_y = img->height/2;
	
	int samplingmatch=0;
	int alreadyset=0;
	
	for (baristengah_x=20;baristengah_x<img->width-20;baristengah_x++)
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
			while (samplingmatch<3 && baristengah_x<img->width)
			{
				p = getSensorMsgsIndex( (baristengah_x), (baristengah_y), img->width, img->height, img->step );
				r = int(img->data[p]);
				g = int(img->data[p+1]);
				b = int(img->data[p+2]);
				rgbToHsv(r,g,b,&h,&s,&v);
				if (samplingmatch==0)
				{
					imgpub.data[p]=255;
					imgpub.data[p+1]=0;
					imgpub.data[p+2]=0;
				}
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
			review_x1 = baristengah_x-3;
			if ((review_x1+3-review_x0)<MINIMUM_TERTANGKAP_BESAR_LEBAR_PIXEL)
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
	
}

void Callback_servoBearing(const std_msgs::Float64::ConstPtr& sudut)
{
	double s = sudut->data;
	global_servo_bearing = (double(s / 0.0174532925))* (1.0);
	//~ global_servo_bearing = (2.158*global_servo_bearing)/CALIBRATE_DEG_TO_PIXEL;
	
	global_servo_updated = 2500;
}
void Callback_robotBearing(const slam_makin::Robot_position_msg ::ConstPtr& robot)
{
	double s = robot->bearing;
	global_x_robot = robot->x;
	global_y_robot = robot->y;
	global_robot_bearing = double(s / 0.0174532925);
}

int getSensorMsgsIndex(int x, int y, int max_width, int max_height, int step)
{
	//~ return x*step*y;
	return ((y-1)*step + (x* (step/max_width)) );
	
}


void Callback_globalRun(const std_msgs::Int32::ConstPtr& _run)
{
	GLOBAL_RUN = _run->data;
	if (GLOBAL_RUN==1)
		cout<<"Bismillah jalan!\n";
	else
		cout<<"Paused\n";
	cout<<"("<<global_x_robot<<","<<global_y_robot<<"):"<<global_robot_bearing<<"\n";
}
