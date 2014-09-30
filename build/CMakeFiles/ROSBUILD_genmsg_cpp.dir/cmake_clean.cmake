FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/slam_makin/msg"
  "../src/slam_makin/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/slam_makin/Landmark_msg.h"
  "../msg_gen/cpp/include/slam_makin/Robot_position_msg.h"
  "../msg_gen/cpp/include/slam_makin/Map.h"
  "../msg_gen/cpp/include/slam_makin/Landmark.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
