cmake_minimum_required(VERSION 3.6)
set(CMAKE_VERBOSE_MAKEFILE 1)

project(Research)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

add_compile_options("-static-libstdc++")
add_compile_options("-static-libgcc")

link_directories("${PROJECT_SOURCE_DIR}/../../cmake-build-debug")


add_executable(Research ${SOURCE_FILES})
target_link_libraries(Research libgcc_s_seh-1 libBlueEngine)