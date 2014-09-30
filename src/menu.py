#!/usr/bin/env python

import roslib
roslib.load_manifest('slam_makin')
import rospy
from geometry_msgs.msg import PoseWithCovarianceStamped
import tf

from slam_makin.msg import Robot_position_msg
from std_msgs.msg import Int32


def menu():
	pub = rospy.Publisher('mkn_global_run', Int32)
	pubposisi = rospy.Publisher('mkn_robotPos', Robot_position_msg)
	r = rospy.Rate(10) # 10hz
	while not rospy.is_shutdown():
		print "Menu:"
		print " s: jalan\t\t\t p:pause"
		print " d: kirim data posisi"
		pilih = raw_input()
		if (pilih=="s"):
			pub.publish(1)
		elif (pilih=="p"):
			pub.publish(0)
		elif (pilih=="d"):
			pos = Robot_position_msg()
			print "masukkan posisi x: "
			pos.x = input()
			
			print "masukkan posisi y: "
			pos.y = input()
			
			print "masukkan bearing (derajat): "
			pos.bearing = input()*0.0174532925
			pubposisi.publish(pos)
		r.sleep()

if __name__ == '__main__':
	try:
		rospy.init_node('slam_menu')		
		menu()
	except rospy.ROSInterruptException: 
		pass

