
(cl:in-package :asdf)

(defsystem "slam_makin-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Landmark_msg" :depends-on ("_package_Landmark_msg"))
    (:file "_package_Landmark_msg" :depends-on ("_package"))
    (:file "Robot_position_msg" :depends-on ("_package_Robot_position_msg"))
    (:file "_package_Robot_position_msg" :depends-on ("_package"))
    (:file "Map" :depends-on ("_package_Map"))
    (:file "_package_Map" :depends-on ("_package"))
    (:file "Landmark" :depends-on ("_package_Landmark"))
    (:file "_package_Landmark" :depends-on ("_package"))
  ))