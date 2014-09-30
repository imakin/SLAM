FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/slam_makin/msg"
  "../src/slam_makin/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/Landmark_msg.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_Landmark_msg.lisp"
  "../msg_gen/lisp/Robot_position_msg.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_Robot_position_msg.lisp"
  "../msg_gen/lisp/Map.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_Map.lisp"
  "../msg_gen/lisp/Landmark.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_Landmark.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
