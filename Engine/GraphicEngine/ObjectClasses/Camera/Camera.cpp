//
// Created by Mateusz on 2019-08-26.
//

#include "Camera.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        CameraClass::CameraClass(): mode(CameraMode::Perspective),
                                    shootingAngleParam(90.0f),
                                    widthParam(0.0f),
                                    zNearParam(1.0f),
                                    zFarParam(1000.0f)
        {
        }
    
        BaseObjectClassRetVal CameraClass::CreateCamera(
            BaseObjectClass *parentObject, std::string objectName, float xPos,
            float yPos, float zPos, float xAngle, float yAngle, float zAngle)
        {
            BaseObjectClassRetVal retVal = Create(parentObject, objectName,
                                                  xPos, yPos, zPos,
                                                  xAngle, yAngle, zAngle,
                                                  1.0f, 1.0f, 1.0f);
            if(retVal == BaseObjectClassRetVal::Success)
                objectFunction = Camera::DrawFunction;
            return retVal;
        
        }
        
        BaseObjectClassRetVal CameraClass::SetUpPerspectiveCamera(
            float shootingAngle, float zNear, float zFar)
        {
            if (!IsCreated())
                return BaseObjectClassRetVal::InvalidOperation;
            if (shootingAngle >= 180.0f || shootingAngle <= 0.0f
                || zNear <= 0.0f || zNear >= zFar)
                return BaseObjectClassRetVal::InvalidArgument;
            shootingAngleParam = shootingAngle;
            zNearParam = zNear;
            zFarParam = zFar;
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal CameraClass::SetUpOrtographicCamera(
            float width, float zNear, float zFar)
        {
            if (!IsCreated())
                return BaseObjectClassRetVal::InvalidOperation;
            if (width <= 0.0f || zNear <= 0.0f || zNear >= zFar)
                return BaseObjectClassRetVal::InvalidArgument;
            widthParam = width;
            zNearParam = zNear;
            zFarParam = zFar;
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal CameraClass::UpdateProjection(
            float aspect)
        {
            if (!IsCreated())
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
                    float tempWidth = widthParam / 2.0f;
                    float tempHeight = (widthParam / aspect) / 2.0f;
                    glOrtho(-tempWidth, tempWidth, -tempHeight, tempHeight,
                            zNearParam, zFarParam);
                    break;
            }
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal CameraClass::PerformViewTransformation()
        {
            if (!IsCreated())
                return BaseObjectClassRetVal::InvalidOperation;
            BaseObjectClass * currentObject = this;
            while(currentObject != nullptr)
            {
                currentObject->PerformTranslationAndRotation(true);
                currentObject = currentObject->GetParent();
            }
            return BaseObjectClassRetVal::Success;
        }
        
        void CameraClass::DrawFunction(const BaseObjectClass & object)
        {
            //const float length = 1000000.0f;
            //glBegin(GL_LINES);
            //{
            //    glColor3f(1.0f, 0.0f, 0.0f);
            //    glVertex3f(-length, 0.0f, 0.0f);
            //    glVertex3f(length, 0.0f, 0.0f);
            //    glColor3f(0.0f, 1.0f, 0.0f);
            //    glVertex3f(0.0f, -length, 0.0f);
            //    glVertex3f(0.0f, length, 0.0f);
            //    glColor3f(0.0f, 0.0f, 1.0f);
            //    glVertex3f(0.0f, 0.0f, -length);
            //    glVertex3f(0.0f, 0.0f, length);
            //}
            //glEnd();
        }
    }
}