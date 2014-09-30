#!/usr/bin/env python

#makin Agustus 2014
import roslib
roslib.load_manifest('slam_makin')
import rospy
from geometry_msgs.msg import PoseWithCovarianceStamped
from visualization_msgs.msg import Marker
from slam_makin.msg import Landmark, Map
#~ from pose_ekf_slam.msg import Landmark, Map
import tf

class visualizeMap:
	
	def __init__(self, uniqueid):
		self.name = uniqueid
		rospy.Subscriber("/pose_ekf_slam/map", Map, self.mapCallback)
		rospy.Subscriber("/pose_ekf_slam/pose_update", PoseWithCovarianceStamped, self.posisiCallback)
		self.pub_Viz = rospy.Publisher("/mkn_map_viz",Marker)
		self.mapData = Marker()

	
	def posisiCallback(self,data):
		#gambar posisi robot
		self.buatTanda(100 ,data.pose.pose.position.x,data.pose.pose.position.y,data.pose.pose.position.z,0.4, 0.1,  0.8,0,0)
		
	def mapCallback(self,data):
		#tanda koordinat 0,0
		self.buatTanda(101 ,0,0,0,0.1, 0.2   ,1,1,1)
		
		for i in range (len(data.landmark)):
			print "generate marker untuk index "+str(i+1) + " di ("+str(data.landmark[i].position.x)+","+str(data.landmark[i].position.y)+")"
			#~ self.mapData.header.frame_id = "/landmark_"+str(i+1)
			self.mapData.header.frame_id = (data.landmark[i].landmark_id[ data.landmark[i].landmark_id.rfind("/"):]) #nama frame id di tf diambil landmarknya aja
			self.mapData.ns = "map"
			#~ self.mapData.id = i+1
			self.mapData.id = int(data.landmark[i].landmark_id[ data.landmark[i].landmark_id.rfind("_")+1:]) #nama frame id di tf diambil bilangan nya saja
			self.mapData.action = self.mapData.ADD
			self.mapData.header.stamp = rospy.Time.now()
			self.mapData.type = Marker.CYLINDER
			self.mapData.pose.position.x = 0 #posisi x,y,z ditransformasikan kenilai TF yang sudah di publish dr node pose_ekf_slam, di isi 0 sebagai ofset
			self.mapData.pose.position.y = 0
			self.mapData.pose.position.z = 0.9
			
			print self.mapData.pose.position.x
			print self.mapData.pose.position.y
			self.mapData.pose.orientation.x = 0
			self.mapData.pose.orientation.y = 0
			self.mapData.pose.orientation.z = 0
			self.mapData.pose.orientation.w = 1
			self.mapData.scale.x = 0.1
			self.mapData.scale.y = 0.1
			self.mapData.scale.z = 1.8 #tinggi gawang 180cm
			self.mapData.color.a = 1.0
			self.mapData.color.r = 0.8
			self.mapData.color.g = 0.8
			self.mapData.color.b = 0.0
			self.pub_Viz.publish(self.mapData)
			
		
	
	def buatTanda(self,_id,xx,yy,zz,h,w, r,g,b):
		self.mapData.header.frame_id = "tanda"+str(_id)
		self.mapData.ns = "map"
		self.mapData.id = _id
		self.mapData.action = self.mapData.ADD
		self.mapData.header.stamp = rospy.Time.now()
		self.mapData.type = Marker.CYLINDER
		self.mapData.pose.position.x = xx
		self.mapData.pose.position.y = yy
		self.mapData.pose.position.z = zz+(h/2)
		self.mapData.pose.orientation.x = 0
		self.mapData.pose.orientation.y = 0
		self.mapData.pose.orientation.z = 0
		self.mapData.pose.orientation.w = 1
		self.mapData.scale.x = w
		self.mapData.scale.y = w
		self.mapData.scale.z = h 
		self.mapData.color.a = 1.0
		self.mapData.color.r = r
		self.mapData.color.g = g
		self.mapData.color.b = b
		
		vel_tf = tf.TransformBroadcaster()
		o = tf.transformations.quaternion_from_euler(0.0, 0.0, 0.0, 'sxyz')
		vel_tf.sendTransform((0.0, 0.0, 0.0), o, self.mapData.header.stamp, 
							 self.mapData.header.frame_id, 'robot')      
                             
		self.pub_Viz.publish(self.mapData)
	
if __name__ == '__main__':
	
	try:
		rospy.init_node('python_rviz')		
		maprunner = visualizeMap(rospy.get_name())
		rospy.spin()
	except rospy.ROSInterruptException: 
		pass
	
