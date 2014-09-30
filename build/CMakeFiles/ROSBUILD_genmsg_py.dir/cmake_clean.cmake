FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/slam_makin/msg"
  "../src/slam_makin/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/slam_makin/msg/__init__.py"
  "../src/slam_makin/msg/_Landmark_msg.py"
  "../src/slam_makin/msg/_Robot_position_msg.py"
  "../src/slam_makin/msg/_Map.py"
  "../src/slam_makin/msg/_Landmark.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
