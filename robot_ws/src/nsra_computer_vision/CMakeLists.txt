cmake_minimum_required(VERSION 2.8.3)
project(nsra_computer_vision)

set(OpenCV_DIR /usr/share/OpenCV/)


find_package(catkin REQUIRED COMPONENTS
  rospy
  roscpp
  roslib
  std_msgs
  OpenCV 
)

catkin_package(
  LIBRARIES
  INCLUDE_DIRS
  CATKIN_DEPENDS roslib roscpp std_msgs
)

include_directories(
 ${catkin_INCLUDE_DIRS}
 ${OpenCV_INCLUDE_DIRS}
)


add_executable(single_cam_callibration src/single_cam_callibration.cpp)

target_link_libraries(single_cam_callibration
  ${OpenCV_LIBS}
  ${catkin_LIBRARIES}
)

add_executable(calibrate src/calib_intrinsic.cpp src/popt_pp.h)
target_link_libraries(calibrate ${OpenCV_LIBS} "-lpopt")

add_executable(read src/read_images.cpp)
target_link_libraries(read ${catkin_LIBRARIES} ${OpenCV_LIBS} "-lpopt" -lpthread)

add_executable(calibrate_stereo src/calib_stereo.cpp)
target_link_libraries(calibrate_stereo ${catkin_LIBRARIES} ${OpenCV_LIBS} "-lpopt")

add_executable(undistort_rectify src/undistort_rectify.cpp)
target_link_libraries(undistort_rectify ${catkin_LIBRARIES} ${OpenCV_LIBS} "-lpopt")

install(PROGRAMS
  src/blob_detection_left
  src/blob_detection_right
  src/cbc_detection
  src/stereo_callibration
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(TARGETS
  single_cam_callibration
  calibrate
  read
  calibrate_stereo
  undistort_rectify
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(FILES
  config/camera1.xml
  config/camera2.xml
  config/camera1_conf.xml
  config/camera2_conf.xml
  src/popt_pp.h
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
