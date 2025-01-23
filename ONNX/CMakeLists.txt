cmake_minimum_required(VERSION 3.0)
project(ONNX)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(/opt/homebrew/Cellar/onnxruntime/1.20.1_2/include/onnxruntime)
link_directories(/opt/homebrew/Cellar/onnxruntime/1.20.1_2/lib)

set(DA2_EXAMPLE_FILES
    da2-example.cpp
    DA2Network.hpp
)

set(DA2_VIDEO_FILES
    da2-video.cpp
    DA2Network.hpp
)

add_executable(da2-example ${DA2_EXAMPLE_FILES})
add_executable(da2-video ${DA2_VIDEO_FILES})

target_link_libraries(da2-example ${OpenCV_LIBS} -lonnxruntime)
target_link_libraries(da2-video ${OpenCV_LIBS} -lonnxruntime)
