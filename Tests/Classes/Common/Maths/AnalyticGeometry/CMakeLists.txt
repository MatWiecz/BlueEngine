cmake_minimum_required(VERSION 3.6)
set(CMAKE_VERBOSE_MAKEFILE 1)

project(AnalyticGeometryTests)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

add_compile_options("-static-libstdc++")
add_compile_options("-static-libgcc")

link_directories("${PROJECT_SOURCE_DIR}/../../../../../cmake-build-debug")


add_executable(AnalyticGeometryTests ${SOURCE_FILES})
target_link_libraries(AnalyticGeometryTests libgcc_s_seh-1 libBlueEngine)