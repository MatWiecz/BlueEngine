//
// Created by Mateusz on 2019-08-26.
//

#ifndef BLUEENGINE_CAMERA_H
#define BLUEENGINE_CAMERA_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef enum class CameraModeEnum
        {
            Perspective,
            Orthographic
        } CameraMode;
        
        typedef class CameraClass Camera;
    }
}

#include "../BaseObjectClass.h"
#include "../../Managers/ViewManager/ViewManager.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        class CameraClass: public BaseObjectClass
        {
            protected:
            CameraMode mode;
            float shootingAngleParam;
            float widthParam;
            float zNearParam;
            float zFarParam;
            
            public:
            CameraClass();
    
            BaseObjectClassRetVal CreateCamera(
                BaseObjectClass *parentObject, std::string objectName,
                float xPos, float yPos, float zPos,
                float xAngle, float yAngle, float zAngle);
            
            BaseObjectClassRetVal SetUpPerspectiveCamera(
                float shootingAngle, float zNear, float zFar);
            
            BaseObjectClassRetVal SetUpOrtographicCamera(
                float width, float zNear, float zFar);
            
            BaseObjectClassRetVal UpdateProjection(float aspect);
            
            BaseObjectClassRetVal PerformViewTransformation();
            
            static void DrawFunction(const BaseObjectClass & object);
            
        };
    };
}

#endif //BLUEENGINE_CAMERA_H
