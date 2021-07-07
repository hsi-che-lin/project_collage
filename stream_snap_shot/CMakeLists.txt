cmake_minimum_required(VERSION 3.0.0)
project(stream_snapshot VERSION 0.1.0)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(stream_snapshot stream_snapshot.cpp)

target_link_libraries(stream_snapshot ${OpenCV_LIBS})