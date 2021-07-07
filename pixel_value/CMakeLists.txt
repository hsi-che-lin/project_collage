cmake_minimum_required(VERSION 3.21.0)
project(pixel_value)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

add_compile_options(-Wall -Wextra)