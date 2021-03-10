cmake_minimum_required(VERSION 3.17)
project(kdtree_search)

set(CMAKE_CXX_STANDARD 14)
find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable(kdtree_search kdtree_search可视化复现.cpp)
target_link_libraries (kdtree_search ${PCL_LIBRARIES})