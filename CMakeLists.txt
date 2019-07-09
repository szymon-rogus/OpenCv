cmake_minimum_required(VERSION 3.14)
project(Object_detection)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

add_executable(Object_detection main.cpp Colors.hpp My_Exeption.hpp Picture.hpp Picture.cpp Video.hpp Video.cpp Colors.cpp My_Exeption.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Object_detection ${OpenCV_LIBS})