import roslib
from geometry_msgs.msg import PoseWithCovarianceStamped


def sss(l):
	print 
	
	

if __name__ == '__main__':
	rospy.init_node('python_rviz')		
	rospy.Subscriber("/pose_ekf_slam/landmark_update/landmark_0", PoseWithCovarianceStamped, sss)
	rospy.spin()
	
	
