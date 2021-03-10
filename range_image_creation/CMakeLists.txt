cmake_minimum_required(VERSION 3.17)
project(range_image_creation)

set(CMAKE_CXX_STANDARD 14)
find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable(range_image_creation main.cpp)
target_link_libraries (range_image_creation ${PCL_LIBRARIES})