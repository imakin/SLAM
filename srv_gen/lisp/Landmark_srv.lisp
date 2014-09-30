; Auto-generated. Do not edit!


(cl:in-package slam_makin-srv)


;//! \htmlinclude Landmark_srv-request.msg.html

(cl:defclass <Landmark_srv-request> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (y
    :reader y
    :initarg :y
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass Landmark_srv-request (<Landmark_srv-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Landmark_srv-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Landmark_srv-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name slam_makin-srv:<Landmark_srv-request> is deprecated: use slam_makin-srv:Landmark_srv-request instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <Landmark_srv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader slam_makin-srv:x-val is deprecated.  Use slam_makin-srv:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <Landmark_srv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader slam_makin-srv:y-val is deprecated.  Use slam_makin-srv:y instead.")
  (y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Landmark_srv-request>) ostream)
  "Serializes a message object of type '<Landmark_srv-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'x))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'y))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Landmark_srv-request>) istream)
  "Deserializes a message object of type '<Landmark_srv-request>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'x) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'x)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'y) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'y)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Landmark_srv-request>)))
  "Returns string type for a service object of type '<Landmark_srv-request>"
  "slam_makin/Landmark_srvRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Landmark_srv-request)))
  "Returns string type for a service object of type 'Landmark_srv-request"
  "slam_makin/Landmark_srvRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Landmark_srv-request>)))
  "Returns md5sum for a message object of type '<Landmark_srv-request>"
  "796182af49bd48aa8ba60ed21519725c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Landmark_srv-request)))
  "Returns md5sum for a message object of type 'Landmark_srv-request"
  "796182af49bd48aa8ba60ed21519725c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Landmark_srv-request>)))
  "Returns full string definition for message of type '<Landmark_srv-request>"
  (cl:format cl:nil "float64[] x~%float64[] y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Landmark_srv-request)))
  "Returns full string definition for message of type 'Landmark_srv-request"
  (cl:format cl:nil "float64[] x~%float64[] y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Landmark_srv-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'x) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'y) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Landmark_srv-request>))
  "Converts a ROS message object to a list"
  (cl:list 'Landmark_srv-request
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
))
;//! \htmlinclude Landmark_srv-response.msg.html

(cl:defclass <Landmark_srv-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass Landmark_srv-response (<Landmark_srv-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Landmark_srv-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Landmark_srv-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name slam_makin-srv:<Landmark_srv-response> is deprecated: use slam_makin-srv:Landmark_srv-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Landmark_srv-response>) ostream)
  "Serializes a message object of type '<Landmark_srv-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Landmark_srv-response>) istream)
  "Deserializes a message object of type '<Landmark_srv-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Landmark_srv-response>)))
  "Returns string type for a service object of type '<Landmark_srv-response>"
  "slam_makin/Landmark_srvResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Landmark_srv-response)))
  "Returns string type for a service object of type 'Landmark_srv-response"
  "slam_makin/Landmark_srvResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Landmark_srv-response>)))
  "Returns md5sum for a message object of type '<Landmark_srv-response>"
  "796182af49bd48aa8ba60ed21519725c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Landmark_srv-response)))
  "Returns md5sum for a message object of type 'Landmark_srv-response"
  "796182af49bd48aa8ba60ed21519725c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Landmark_srv-response>)))
  "Returns full string definition for message of type '<Landmark_srv-response>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Landmark_srv-response)))
  "Returns full string definition for message of type 'Landmark_srv-response"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Landmark_srv-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Landmark_srv-response>))
  "Converts a ROS message object to a list"
  (cl:list 'Landmark_srv-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'Landmark_srv)))
  'Landmark_srv-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'Landmark_srv)))
  'Landmark_srv-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Landmark_srv)))
  "Returns string type for a service object of type '<Landmark_srv>"
  "slam_makin/Landmark_srv")