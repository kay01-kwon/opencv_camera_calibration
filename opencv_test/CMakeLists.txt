cmake_minimum_required(VERSION 2.8.11)
project(opencv_circle_detect)

find_package(OpenCV 3.3.1 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})


# Executables for practice
add_executable (circle_detect src/circle_detect.cpp)
target_link_libraries (circle_detect ${OpenCV_LIBRARIES})

add_executable (blob_test src/blob_test.cpp)
target_link_libraries (blob_test ${OpenCV_LIBRARIES})

add_executable (color_detect src/color_detect.cpp)
target_link_libraries (color_detect ${OpenCV_LIBRARIES})

add_executable (pose_from_homography src/pose_from_homography.cpp)
target_link_libraries (pose_from_homography ${OpenCV_LIBRARIES})

add_executable (camera_calibration src/camera_calibration.cpp)
target_link_libraries (camera_calibration ${OpenCV_LIBRARIES})