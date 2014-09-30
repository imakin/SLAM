#!/usr/bin/env python
#270814
# ROS imports
import roslib 
roslib.load_manifest('slam_makin')
import rospy
import tf
from tf.transformations import euler_from_quaternion
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseWithCovarianceStamped
from geometry_msgs.msg import TwistWithCovarianceStamped
from sensor_msgs.msg import Imu
# from geometry_msgs.msg import Point
from visualization_msgs.msg import Marker, MarkerArray

# Custom msgs
from slam_makin.srv import SetPosition, SetPositionResponse, SetPositionRequest
from slam_makin.srv import SetLandmark, SetLandmarkResponse
from slam_makin.msg import Landmark, Map

# More imports
from numpy import delete, dot, zeros, eye, cos, sin, array, diag, sqrt
# from numpy import linalg
from numpy import matrix, asarray, squeeze, mean, var
from collections import deque

import threading
import motion_transformations as mt
import PyKDL
import math


MAX_LANDMARK = 20
global_robot_x = 0.0
global_robot_y = 0.0
global_robot_b = 0.0
global_robot_x_last = 0.0
global_robot_y_last = 0.0
global_robot_b_last = 0.0
global_robot_x_delta = 0.0
global_robot_y_delta = 0.0
global_robot_b_delta =0.0
#~ global_delta_time = 0
t_now = 0 #waktu skrg
c = 1 #seberapa akurat? 1 untuk akurat


class ekfslam:
	def __init__(self, name, p_var, q_c_var):
		self.P = p_var #Matriks covariance #diagonal berisi uncertainty posisi
		
		self.Q_C = q_c_var #Matriks error, ketidaktepatan dari posisi robot nilai initial adalah nilai C, C nilai ketepatan posisi, diisi 1 untuk tepat, 3 elemen: untuk x, y, time
		self.Q = zeros(3)
		self.W = zeros(3).T #W = array([global_delta_time*cos(global_robot_b),	global_delta_time*sin(global_robot_b),	global_robot_b]).T
		
		self.last_prediction = rospy.Time.now()
		self.position = PyKDL.Vector(global_robot_x, global_robot_y, 0) #posisi robot xyz (z=0)
		self.X = array([self.position.x, self.position.y, global_robot_b]) #sistem state 
		
		
		self.A = eye(3) #Jacobian of the prediction model
		
		#measurement noise, hubungannya dgn ketidaktepatan posisi landmark
		self.Rc = eye(2)
		self.Rc[0][0] = 0.001 #ketidaktepatan jarak - 1mm ini nilai c, rc = range*c dengan huruf r kecil
		self.Rc[1][1] = 1 #ketidak tepatan posisi servo - 1 derajat ini nilai bd
		self.Jxr = zeros(2)
		self.Jz = zeros(2)
		self.V = eye(2)
		
		self.landmark_count = 1
		self.landmarkDB = zeros(MAX_LANDMARK*4).reshape(MAX_LANDMARK,4)
		self.landmarkDB[0][0] = 20.0
		self.landmarkDB[0][1] = 30.0
		self.landmarkDB[0][2] = 300.0
		self.landmarkDB[0][3] = 5.0
		self.landmarkDB[1][0] = -20.0
		self.landmarkDB[1][1] = 30.0
		self.landmarkDB[1][2] = 300.0
		self.landmarkDB[1][3] = -5.0
		
		#~ self.X[3] = 20
		#~ self.X[4] = 30
		
		self.velocityrange = 0
		self.velocitytetha = 0
	
		rospy.Timer(rospy.Duration(2.0), self.state_update_posisi)
		rospy.Timer(rospy.Duration(2.0), self.state_update_landmark(0))
		
		
	#ID dimulai dari 0
	def state_update_posisi(self):
		deltat = (rospy.Time.now() - self.last_prediction).to_sec()
		self.last_prediction = rospy.Time.now()
		
		#step 1 update current state
		self.X[0] = global_robot_x + global_robot_x_delta
		self.X[1] = global_robot_y + global_robot_y_delta
		self.X[2] = global_robot_b + global_robot_b_delta
		
		self.A[0][2] = -global_robot_y_delta
		self.A[1][2] = global_robot_x_delta
		
		
		self.Q[0][0] = self.Q_C[0][0]*global_robot_x_delta*global_robot_x_delta
		self.Q[1][1] = self.Q_C[1][1]*global_robot_y_delta*global_robot_y_delta
		self.Q[2][2] = self.Q_C[2][2]*deltat*deltat
		
		#update Prr dari P
		Prr = P[0:3, 0:3]
		Prr = dot(self.A, dot(Prr, self.A)) + self.Q
		P[0:3, 0:3] = Prr
		"""
			00 01 02 03 04
			10 11 12 13 14
			20 21 22 23 24
			30 31 32 33 34
			40 41 42 43 44
		"""
		#update covariance posisirobot-landmark
		i = 0
		while (i<self.landmark_count):
			Pri = P[0:3	, 	3+(2*i) : 5+(2*i)	]
			Pri = dot (self.A, Pri)
			P[0:3, 	3+(2*i) : 5+(2*i)] = Pri
			P[3+(2*i) : 5+(2*i), 0:3] = Pri.T
			i=i+1
	
	def state_update_landmark(self, landmark_id):
		#ir ib jarak landmark dr robot sekarang
		ix = self.landmarkDB[landmark_id][0]
		iy = self.landmarkDB[landmark_id][1]
		ir = self.landmarkDB[landmark_id][2]
		ib = self.landmarkDB[landmark_id][3]
		print ix
		print iy
		print ir
		print ib
		#isi Jacobian H - masing2 landmark pnya H berbeda
		H = zeros(2*	(3+	2*self.landmark_count)).reshape(2,(3+	2*self.landmark_count))
		print H
		print (global_robot_x - ix)/ir
		Habcd = array([ 
						[	(global_robot_x - ix)/ir,		(global_robot_y - iy)/ir		],
						[	(iy - global_robot_y)/(ir**2),	(ix - global_robot_x)/(ir**2)	]		])
		H[0:2,0:2] = Habcd
		H[0:2,2:3] = array([ [0][-1] ])
		H[0:2,3+landmark_id*2:3+landmark_id*2+2] = Habcd
		
		#
		R = eye(2)
		R[0][0] = ir * self.Rc[0][0]
		R[1][1] = self.Rc[1][1]
		#~ print Habcd
		#~ print H
		#formula untuk mengukur kalman gain
		#~ print "aaa"
		#~ print dot(dot(H,self.P),self.P.T)
		#~ print dot(dot(self.V,R),self.V.T)
		print "test"
		#~ KKK =  dot(dot(H,self.P),self.H.T)+ dot(dot(self.V,R),self.V.T) 
		
		#~ h = H
		#~ v = self.V
		#~ r = R
		#~ temp_K = dot(dot(h, self.P), h.T) + dot(dot(v, r), v.T)
		
		
		#~ print temp_K
		#~ print ( dot(dot(H,self.P),self.H.T)	+ dot(dot(self.V,R),self.V.T) ).I
		#~ print dot (self.P, H.T)
		s = squeeze(asarray(matrix(		( dot(dot(H,self.P),H.T)	+ dot(dot(self.V,R),self.V.T) )		)))
		K = dot(dot (self.P, H.T), 		s.I)
		
		#~ K = dot (self.P, self.H.T)
		#~ #sehingga dpt diukur X dengan kalman gain
		#~ X = X + dot(K, (z-		dot(self.H	))
		print "before"
		print X
		X = X + K
		print "after"
		print X
		print K
		
rospy.init_node('slam_makin')
ekfslam("slam_makin",
		array(
				[	
				[0.001,		0,		0,	0,	0], 
				[0,		0.001,		0,	0,	0], 
				[0,		0,		0.001,	0,	0], 
				[0,		0,		0.0,	0,	0], 
				[0,		0,		0.0,	0,	0] 
			])
			, eye(3))
rospy.spin()
