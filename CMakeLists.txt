cmake_minimum_required(VERSION 3.6)

project(BlueEngine)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES

        BlueEngineHeader.h

        Engine/Engine.cpp
        Engine/Engine.h

        VideoOutputWindow/VideoOutputWindow.cpp
        VideoOutputWindow/VideoOutputWindow.h

        Logger/Logger.cpp
        Logger/Logger.h

        Common/Basics/BitField.hpp

        Engine/GraphicEngine/GraphicsEngine.cpp
        Engine/GraphicEngine/GraphicsEngine.h

        Engine/GraphicEngine/ObjectClasses/BaseObjectClass.cpp
        Engine/GraphicEngine/ObjectClasses/BaseObjectClass.h

        Engine/GraphicEngine/ObjectClasses/Camera/Camera.cpp
        Engine/GraphicEngine/ObjectClasses/Camera/Camera.h

        Engine/GraphicEngine/Managers/ViewManager/ViewManager.cpp
        Engine/GraphicEngine/Managers/ViewManager/ViewManager.h

        Engine/GraphicEngine/ObjectClasses/CoordinateSystem/CoordinateSystem.cpp
        Engine/GraphicEngine/ObjectClasses/CoordinateSystem/CoordinateSystem.h Engine/GraphicEngine/ObjectClasses/CoordinateSystem/AdvancedCoordinateSystem/AdvancedCoordinateSystem.cpp Engine/GraphicEngine/ObjectClasses/CoordinateSystem/AdvancedCoordinateSystem/AdvancedCoordinateSystem.h)

add_compile_options("-static-libstdc++")
add_compile_options("-static-libgcc")

add_library(BlueEngine SHARED ${SOURCE_FILES})
target_link_libraries(BlueEngine opengl32 glu32 freeglut)

add_subdirectory(Tests)