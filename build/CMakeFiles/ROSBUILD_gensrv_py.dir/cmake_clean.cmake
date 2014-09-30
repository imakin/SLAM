FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/slam_makin/msg"
  "../src/slam_makin/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/slam_makin/srv/__init__.py"
  "../src/slam_makin/srv/_SetPosition.py"
  "../src/slam_makin/srv/_Landmark_srv.py"
  "../src/slam_makin/srv/_SetLandmark.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
