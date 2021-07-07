cmake_minimum_required(VERSION 3.0.0)
project(extract_data)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

add_compile_options(-Wall -Wextra)
