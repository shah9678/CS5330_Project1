cmake_minimum_required(VERSION 3.10)
project(imgDisplay)
find_package(OpenCV REQUIRED)
add_executable(imgDisplay imgDisplay.cpp)
target_link_libraries(imgDisplay ${OpenCV_LIBS})

