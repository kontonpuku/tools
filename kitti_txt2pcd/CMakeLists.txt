cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(pcl_tools)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable (txt2pcd  txt2pcd.cpp)
add_executable (bin2pcd bin2pcd.cpp)

target_link_libraries (txt2pcd ${PCL_LIBRARIES})
target_link_libraries (bin2pcd ${PCL_LIBRARIES})