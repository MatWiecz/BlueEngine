cmake_minimum_required(VERSION 3.6)

project(Research)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

add_compile_options("-static-libstdc++")
add_compile_options("-static-libgcc")

add_executable(Research ${SOURCE_FILES})
target_link_libraries(Research ../../cmake-build-debug/libBlueEngine.dll)