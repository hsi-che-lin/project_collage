cmake_minimum_required(VERSION 3.0.0)
project(opencv_basic VERSION 0.1.0)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(opencv_basic main.cpp)

target_link_libraries(opencv_basic ${OpenCV_LIBS})