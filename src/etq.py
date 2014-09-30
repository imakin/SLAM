#!/usr/bin/env python

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

tf.transformations.quaternion_from_euler(90,0,0)
