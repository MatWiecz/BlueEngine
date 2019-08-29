//
// Created by Mateusz on 2019-08-26.
//

#include "Camera.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        CameraClass::CameraClass(): mode(CameraMode::Perspective),
                                    shootingAngleParam(90.0),
                                    widthParam(0),
                                    zNearParam(1.0),
                                    zFarParam(1000.0)
        {
        }
        
        BaseObjectClassRetVal CameraClass::SetUpPerspectiveCamera(
            double shootingAngle, double zNear, double zFar)
        {
            if (int(~(flags & ObjectCreated)))
                return BaseObjectClassRetVal::InvalidOperation;
            if (shootingAngle >= 180.0 || shootingAngle <= 0.0 || zNear <= 0.0
                || zNear >= zFar)
                return BaseObjectClassRetVal::InvalidArgument;
            shootingAngleParam = shootingAngle;
            zNearParam = zNear;
            zFarParam = zFar;
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal CameraClass::SetUpOrtographicCamera(
            double width, double zNear, double zFar)
        {
            if (int(~(flags & ObjectCreated)))
                return BaseObjectClassRetVal::InvalidOperation;
            if (width <= 0.0 || zNear <= 0.0 || zNear >= zFar)
                return BaseObjectClassRetVal::InvalidArgument;
            widthParam = width;
            zNearParam = zNear;
            zFarParam = zFar;
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal CameraClass::UpdateProjection(
            double aspect)
        {
            if (int(~(flags & ObjectCreated)))
                return BaseObjectClassRetVal::InvalidOperation;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            switch (mode)
            {
                case CameraMode::Perspective:
                    gluPerspective(shootingAngleParam, aspect, zNearParam,
                                   zFarParam);
                    break;
                case CameraMode::Orthographic:
                    double tempWidth = widthParam / 2.0;
                    double tempHeight = (widthParam / aspect) / 2.0;
                    glOrtho(-tempWidth, tempWidth, -tempHeight, tempHeight,
                            zNearParam, zFarParam);
                    break;
            }
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            return BaseObjectClassRetVal::Success;
        }
    }
}