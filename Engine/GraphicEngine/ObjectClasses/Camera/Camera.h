//
// Created by Mateusz on 2019-08-26.
//

#ifndef BLUEENGINE_CAMERA_H
#define BLUEENGINE_CAMERA_H

#include "../BaseObjectClass.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef enum CameraModeEnum
        {
            Perspective,
            Ortographic
        } CameraMode;
        
        typedef class CameraClass : public BaseObjectClass
        {
            protected:
            CameraMode mode;
            double shootingAngleParam;
            double widthParam;
            double zNearParam;
            double zFarParam;
            
            public:
            CameraClass();
    
            BaseObjectClassRetVal SetUpPerspectiveCamera(
                double shootingAngle, double zNear, double zFar);
    
            BaseObjectClassRetVal SetUpOrtographicCamera(
                double width, double zNear, double zFar);
            
        } Camera;
    };
}

#endif //BLUEENGINE_CAMERA_H
