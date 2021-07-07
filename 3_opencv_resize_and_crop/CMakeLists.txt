cmake_minimum_required(VERSION 3.0.0)
project(opencv_resize_and_crop VERSION 0.1.0)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(opencv_resize_and_crop main.cpp)

target_link_libraries(opencv_resize_and_crop ${OpenCV_LIBS})