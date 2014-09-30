; Auto-generated. Do not edit!


(cl:in-package slam_makin-srv)


;//! \htmlinclude SetLandmark-request.msg.html

(cl:defclass <SetLandmark-request> (roslisp-msg-protocol:ros-message)
  ((landmark
    :reader landmark
    :initarg :landmark
    :type geometry_msgs-msg:PoseWithCovariance
    :initform (cl:make-instance 'geometry_msgs-msg:PoseWithCovariance))
   (topic_name
    :reader topic_name
    :initarg :topic_name
    :type cl:string
    :initform ""))
)

(cl:defclass SetLandmark-request (<SetLandmark-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetLandmark-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetLandmark-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name slam_makin-srv:<SetLandmark-request> is deprecated: use slam_makin-srv:SetLandmark-request instead.")))

(cl:ensure-generic-function 'landmark-val :lambda-list '(m))
(cl:defmethod landmark-val ((m <SetLandmark-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader slam_makin-srv:landmark-val is deprecated.  Use slam_makin-srv:landmark instead.")
  (landmark m))

(cl:ensure-generic-function 'topic_name-val :lambda-list '(m))
(cl:defmethod topic_name-val ((m <SetLandmark-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader slam_makin-srv:topic_name-val is deprecated.  Use slam_makin-srv:topic_name instead.")
  (topic_name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetLandmark-request>) ostream)
  "Serializes a message object of type '<SetLandmark-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'landmark) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'topic_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'topic_name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetLandmark-request>) istream)
  "Deserializes a message object of type '<SetLandmark-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'landmark) istream)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'topic_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'topic_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetLandmark-request>)))
  "Returns string type for a service object of type '<SetLandmark-request>"
  "slam_makin/SetLandmarkRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetLandmark-request)))
  "Returns string type for a service object of type 'SetLandmark-request"
  "slam_makin/SetLandmarkRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetLandmark-request>)))
  "Returns md5sum for a message object of type '<SetLandmark-request>"
  "3a728969e9be1948ad1516696bacf677")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetLandmark-request)))
  "Returns md5sum for a message object of type 'SetLandmark-request"
  "3a728969e9be1948ad1516696bacf677")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetLandmark-request>)))
  "Returns full string definition for message of type '<SetLandmark-request>"
  (cl:format cl:nil "geometry_msgs/PoseWithCovariance landmark~%string topic_name~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetLandmark-request)))
  "Returns full string definition for message of type 'SetLandmark-request"
  (cl:format cl:nil "geometry_msgs/PoseWithCovariance landmark~%string topic_name~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetLandmark-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'landmark))
     4 (cl:length (cl:slot-value msg 'topic_name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetLandmark-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetLandmark-request
    (cl:cons ':landmark (landmark msg))
    (cl:cons ':topic_name (topic_name msg))
))
;//! \htmlinclude SetLandmark-response.msg.html

(cl:defclass <SetLandmark-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass SetLandmark-response (<SetLandmark-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetLandmark-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetLandmark-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name slam_makin-srv:<SetLandmark-response> is deprecated: use slam_makin-srv:SetLandmark-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetLandmark-response>) ostream)
  "Serializes a message object of type '<SetLandmark-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetLandmark-response>) istream)
  "Deserializes a message object of type '<SetLandmark-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetLandmark-response>)))
  "Returns string type for a service object of type '<SetLandmark-response>"
  "slam_makin/SetLandmarkResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetLandmark-response)))
  "Returns string type for a service object of type 'SetLandmark-response"
  "slam_makin/SetLandmarkResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetLandmark-response>)))
  "Returns md5sum for a message object of type '<SetLandmark-response>"
  "3a728969e9be1948ad1516696bacf677")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetLandmark-response)))
  "Returns md5sum for a message object of type 'SetLandmark-response"
  "3a728969e9be1948ad1516696bacf677")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetLandmark-response>)))
  "Returns full string definition for message of type '<SetLandmark-response>"
  (cl:format cl:nil "~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetLandmark-response)))
  "Returns full string definition for message of type 'SetLandmark-response"
  (cl:format cl:nil "~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetLandmark-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetLandmark-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetLandmark-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetLandmark)))
  'SetLandmark-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetLandmark)))
  'SetLandmark-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetLandmark)))
  "Returns string type for a service object of type '<SetLandmark>"
  "slam_makin/SetLandmark")