cmake_minimum_required(VERSION 3.6)

project(BlueEngine)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES BlueEngineHeader.h Engine/Engine.cpp Engine/Engine.h)

add_compile_options("-static-libstdc++")
add_compile_options("-static-libgcc")

add_library(BlueEngine SHARED ${SOURCE_FILES})
target_link_libraries(BlueEngine opengl32 glu32 freeglut)