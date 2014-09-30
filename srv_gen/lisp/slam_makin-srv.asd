
(cl:in-package :asdf)

(defsystem "slam_makin-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "SetPosition" :depends-on ("_package_SetPosition"))
    (:file "_package_SetPosition" :depends-on ("_package"))
    (:file "Landmark_srv" :depends-on ("_package_Landmark_srv"))
    (:file "_package_Landmark_srv" :depends-on ("_package"))
    (:file "SetLandmark" :depends-on ("_package_SetLandmark"))
    (:file "_package_SetLandmark" :depends-on ("_package"))
  ))