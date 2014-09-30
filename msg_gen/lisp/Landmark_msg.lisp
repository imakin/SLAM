; Auto-generated. Do not edit!


(cl:in-package slam_makin-msg)


;//! \htmlinclude Landmark_msg.msg.html

(cl:defclass <Landmark_msg> (roslisp-msg-protocol:ros-message)
  ((landmark_count
    :reader landmark_count
    :initarg :landmark_count
    :type cl:integer
    :initform 0)
   (x
    :reader x
    :initarg :x
    :type (cl:vector cl:float)
   :initform (cl:make-array 100 :element-type 'cl:float :initial-element 0.0))
   (y
    :reader y
    :initarg :y
    :type (cl:vector cl:float)
   :initform (cl:make-array 100 :element-type 'cl:float :initial-element 0.0))
   (range
    :reader range
    :initarg :range
    :type (cl:vector cl:integer)
   :initform (cl:make-array 100 :element-type 'cl:integer :initial-element 0))
   (bearing
    :reader bearing
    :initarg :bearing
    :type (cl:vector cl:integer)
   :initform (cl:make-array 100 :element-type 'cl:integer :initial-element 0))
   (id
    :reader id
    :initarg :id
    :type (cl:vector cl:integer)
   :initform (cl:make-array 100 :element-type 'cl:integer :initial-element 0)))
)

(cl:defclass Landmark_msg (<Landmark_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Landmark_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Landmark_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name slam_makin-msg:<Landmark_msg> is deprecated: use slam_makin-msg:Landmark_msg instead.")))

(cl:ensure-generic-function 'landmark_count-val :lambda-list '(m))
(cl:defmethod landmark_count-val ((m <Landmark_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader slam_makin-msg:landmark_count-val is deprecated.  Use slam_makin-msg:landmark_count instead.")
  (landmark_count m))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <Landmark_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader slam_makin-msg:x-val is deprecated.  Use slam_makin-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <Landmark_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader slam_makin-msg:y-val is deprecated.  Use slam_makin-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'range-val :lambda-list '(m))
(cl:defmethod range-val ((m <Landmark_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader slam_makin-msg:range-val is deprecated.  Use slam_makin-msg:range instead.")
  (range m))

(cl:ensure-generic-function 'bearing-val :lambda-list '(m))
(cl:defmethod bearing-val ((m <Landmark_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader slam_makin-msg:bearing-val is deprecated.  Use slam_makin-msg:bearing instead.")
  (bearing m))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <Landmark_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader slam_makin-msg:id-val is deprecated.  Use slam_makin-msg:id instead.")
  (id m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Landmark_msg>) ostream)
  "Serializes a message object of type '<Landmark_msg>"
  (cl:let* ((signed (cl:slot-value msg 'landmark_count)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
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
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'range))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'bearing))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'id))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Landmark_msg>) istream)
  "Deserializes a message object of type '<Landmark_msg>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'landmark_count) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:setf (cl:slot-value msg 'x) (cl:make-array 100))
  (cl:let ((vals (cl:slot-value msg 'x)))
    (cl:dotimes (i 100)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'y) (cl:make-array 100))
  (cl:let ((vals (cl:slot-value msg 'y)))
    (cl:dotimes (i 100)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'range) (cl:make-array 100))
  (cl:let ((vals (cl:slot-value msg 'range)))
    (cl:dotimes (i 100)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
  (cl:setf (cl:slot-value msg 'bearing) (cl:make-array 100))
  (cl:let ((vals (cl:slot-value msg 'bearing)))
    (cl:dotimes (i 100)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
  (cl:setf (cl:slot-value msg 'id) (cl:make-array 100))
  (cl:let ((vals (cl:slot-value msg 'id)))
    (cl:dotimes (i 100)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Landmark_msg>)))
  "Returns string type for a message object of type '<Landmark_msg>"
  "slam_makin/Landmark_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Landmark_msg)))
  "Returns string type for a message object of type 'Landmark_msg"
  "slam_makin/Landmark_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Landmark_msg>)))
  "Returns md5sum for a message object of type '<Landmark_msg>"
  "f6754d2ed924c43b64bfcb2e0006aca3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Landmark_msg)))
  "Returns md5sum for a message object of type 'Landmark_msg"
  "f6754d2ed924c43b64bfcb2e0006aca3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Landmark_msg>)))
  "Returns full string definition for message of type '<Landmark_msg>"
  (cl:format cl:nil "int32 landmark_count~%~%float64[100] x~%float64[100] y~%int32[100] range~%int32[100] bearing~%int32[100] id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Landmark_msg)))
  "Returns full string definition for message of type 'Landmark_msg"
  (cl:format cl:nil "int32 landmark_count~%~%float64[100] x~%float64[100] y~%int32[100] range~%int32[100] bearing~%int32[100] id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Landmark_msg>))
  (cl:+ 0
     4
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'x) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'y) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'range) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'bearing) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'id) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Landmark_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'Landmark_msg
    (cl:cons ':landmark_count (landmark_count msg))
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':range (range msg))
    (cl:cons ':bearing (bearing msg))
    (cl:cons ':id (id msg))
))
