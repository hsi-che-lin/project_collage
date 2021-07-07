cmake_minimum_required(VERSION 3.0.0)
project(calculator VERSION 0.1.0)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_PATH}})

add_executable(calculator calculator.cpp)

target_link_libraries(calculator ${OpenCV_LIBS})