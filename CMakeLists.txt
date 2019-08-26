cmake_minimum_required(VERSION 3.6)

project(BlueEngine)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES BlueEngineHeader.h

        Engine/Engine.h
        Engine/Engine.cpp

        VideoOutputWindow/VideoOutputWindow.h
        VideoOutputWindow/VideoOutputWindow.cpp

        Logger/Logger.h
        Logger/Logger.cpp

        Common/Basics/BitField.hpp
        )

add_compile_options("-static-libstdc++")
add_compile_options("-static-libgcc")

add_library(BlueEngine SHARED ${SOURCE_FILES})
target_link_libraries(BlueEngine opengl32 glu32 freeglut)

add_subdirectory(Tests)