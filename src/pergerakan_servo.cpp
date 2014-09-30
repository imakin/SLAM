#include "ros/ros.h"
#include "std_msgs/Float64.h"

#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pergerakan_servo");
  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::Float64>("head_pan_joint/command", 1000);
  ros::Rate loop_rate(10);

   int mode_main=0;
   cout<<"mode \n\t0: baca masukan \n\t1:sweep\n";
   cin>>mode_main;
   
   
  int count = 0;
  double nilai=0;
  int naik=1;
  while (ros::ok())
  {
	std_msgs::Float64 sudut;
	sudut.data = nilai*0.0174532925;
    chatter_pub.publish(sudut);
    cout<<"sending: "<<nilai<<endl;

    ros::spinOnce();

    //~ loop_rate.sleep();
    if (nilai>=50)
    {
		naik=0;
		
	}
	if (nilai<=-50)
	{
		naik=1;
	}
    ++count;
    if (mode_main)
    {
		ros::Duration(4.8).sleep();
		if (naik)
			nilai = nilai + 26;
		else
			nilai = nilai - 26;
		
	}
	else
	{
		cout<<"masukkan nilai sudut (derajat): ";
		cin>>nilai;
		//~ nilai = nilai * 0.0174532925;
	}
  }


  return 0;
}

