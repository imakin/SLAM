FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/slam_makin/msg"
  "../src/slam_makin/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_cpp"
  "../srv_gen/cpp/include/slam_makin/SetPosition.h"
  "../srv_gen/cpp/include/slam_makin/Landmark_srv.h"
  "../srv_gen/cpp/include/slam_makin/SetLandmark.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
