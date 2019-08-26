//
// Created by Mateusz on 2019-08-26.
//

#include "Camera.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        CameraClass::CameraClass(): mode(Perspective), shootingAngleParam(90.0),
                                    widthParam(0), zNearParam(1.0),
                                    zFarParam (1000.0)
        {
        }
        
        BaseObjectClassRetVal CameraClass::SetUpPerspectiveCamera(
            double shootingAngle, double zNear, double zFar)
        {
            if (int(~(flags & ObjectCreated)))
                return InvalidOperation;
            if(shootingAngle >= 180.0 || shootingAngle <= 0.0 || zNear <= 0.0
               || zNear >= zFar)
                return InvalidArgument;
            shootingAngleParam = shootingAngle;
            zNearParam = zNear;
            zFarParam = zFar;
            return Success;
        }
        
        BaseObjectClassRetVal CameraClass::SetUpOrtographicCamera(
            double width, double zNear, double zFar)
        {
            if (int(~(flags & ObjectCreated)))
                return InvalidOperation;
            if(width <= 0.0 || zNear <= 0.0 || zNear >= zFar)
                return InvalidArgument;
            widthParam = width;
            zNearParam = zNear;
            zFarParam = zFar;
            return Success;
        }
    }
}