#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>


int main(int argc, char** argv){
  ros::init(argc, argv, "mkn_test_tf");

  ros::NodeHandle node;
  //~ ros::Subscriber sub = node.subscribe(turtle_name+"/pose", 10, &poseCallback);
	
	
	ros::Publisher lpub = node.advertise<geometry_msgs::PoseWithCovarianceStamped>("/pose_ekf_slam/landmark_update/landmark_1",2000);
	
	ros::Time begin = ros::Time::now();
	
	while (ros::ok())
	{
		if ((ros::Time::now().toSec()- begin.toSec()) >= 2.0)
		{
			static tf::TransformBroadcaster br;
			tf::Transform transform;
			transform.setOrigin( tf::Vector3(1.0, 5.0, 0.0) ); ///X,Y,Z landmark
			tf::Quaternion q;
			q.setRPY(0, 0, 0);
			transform.setRotation(q);
			
			//~ 
			//~ p = PoseWithCovarianceStamped()
			//~ p.header.stamp = rospy.Time.now()
			//~ p.header.frame_id = 'landmark_0'
			//~ p.pose.covariance[0] = 0.05
			//~ p.pose.covariance[7] = 0.05
			//~ p.pose.covariance[14] = 0.05
			geometry_msgs::PoseWithCovarianceStamped p;
			p.header.stamp = ros::Time::now();
			p.header.frame_id = "landmark_1";
			p.pose.covariance[0] = 0.05;
			p.pose.covariance[7] = 0.05;
			p.pose.covariance[14] = 0.05;
			
			br.sendTransform(tf::StampedTransform(transform, p.header.stamp,"robot", p.header.frame_id)); ///parent sikik, njut child (kuwalik karo sing piton)
			//~ br.sendTransform(tf::TransformStamped>(p.header.stamp,  p.header.frame_id,transform));
			
			
			lpub.publish(p);
			
			begin = ros::Time::now();
		}
		ros::spinOnce();
	}
  return 0;
};
