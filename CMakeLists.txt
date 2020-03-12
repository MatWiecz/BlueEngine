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
        Engine/GraphicEngine/ObjectClasses/CoordinateSystem/CoordinateSystem.h Engine/GraphicEngine/ObjectClasses/CoordinateSystem/AdvancedCoordinateSystem/AdvancedCoordinateSystem.cpp Engine/GraphicEngine/ObjectClasses/CoordinateSystem/AdvancedCoordinateSystem/AdvancedCoordinateSystem.h Common/Graphic/Colours.cpp Common/Graphic/Colours.h Common/Maths/Matrices/Matrix.hpp Common/Maths/AnalyticGeometry/Point.cpp Common/Maths/AnalyticGeometry/Point.h Common/Maths/AnalyticGeometry/Plane.cpp Common/Maths/AnalyticGeometry/Plane.h Common/Maths/AnalyticGeometry/Vector.cpp Common/Maths/AnalyticGeometry/Vector.h Common/Maths/AnalyticGeometry/StraightLine.cpp Common/Maths/AnalyticGeometry/StraightLine.h Common/Maths/AnalyticGeometry/Calculations.cpp Common/Maths/AnalyticGeometry/Calculations.h Common/Maths/AnalyticGeometry/Triangle.cpp Common/Maths/AnalyticGeometry/Triangle.h Common/Maths/AnalyticGeometry/Common.h)

add_compile_options("-static-libstdc++")
add_compile_options("-static-libgcc")

add_library(BlueEngine SHARED ${SOURCE_FILES})
target_link_libraries(BlueEngine opengl32 glu32 freeglut)

add_subdirectory(Tests)