//
// Created by Mateusz on 2019-09-01.
//

#include "CoordinateSystem.h"
#include "../../../../Common/Graphic/Colours.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        CoordinateSystemClass::CoordinateSystemClass()
        {
        }
        
        BaseObjectClassRetVal CoordinateSystemClass::CreateOrigin(
            std::string objectName)
        {
            if (int(flags & ObjectCreated))
                return BaseObjectClassRetVal::InvalidOperation;
            id = nextId++;
            name = objectName;
            pos[0] = 0.0f;
            pos[1] = 0.0f;
            pos[2] = 0.0f;
            angle[0] = 0.0f;
            angle[2] = 0.0f;
            angle[2] = 0.0f;
            scale[0] = 1.0f;
            scale[1] = 1.0f;
            scale[2] = 1.0f;
            posFunction = nullptr;
            angleFunction = nullptr;
            scaleFunction = nullptr;
            objectFunction = CoordinateSystem::DrawFunction;
            flags |= ObjectCreated | ObjectVisible | ObjectShowPoints |
                     ObjectShowEdges | ObjectShowFaces;
            length = 1000000.0f;
            return BaseObjectClassRetVal::Success;
        }
    
        BaseObjectClassRetVal CoordinateSystemClass::CreateCoordinateSystem(
            BaseObjectClass *parentObject, std::string objectName, float xPos,
            float yPos, float zPos, float xAngle, float yAngle, float zAngle,
            GLfloat axisLength)
        {
            if(axisLength<= 0.0f)
                return BaseObjectClassRetVal::InvalidArgument;
            BaseObjectClassRetVal retVal = Create(parentObject, objectName,
                                                  xPos, yPos, zPos,
                                                  xAngle, yAngle, zAngle,
                                                  1.0f, 1.0f, 1.0f);
            if(retVal != BaseObjectClassRetVal::Success)
                return retVal;
            objectFunction = CoordinateSystem::DrawFunction;
            length = axisLength;
            return retVal;
            
        }
    
        void CoordinateSystemClass::SetLineColor(BaseObjectClassFlags flags,
                                                 GLfloat red, GLfloat green,
                                                 GLfloat blue)
        {
            if(int(flags&ObjectTextured))
                glColor3f(red, green, blue);
            else
                glColor3f(1.0f, 1.0f, 1.0f);
        }
    
        void CoordinateSystemClass::DrawFunction(const BaseObjectClass & object)
        {
            const auto & coordinateSystem = (CoordinateSystem &) object;
            if(int(coordinateSystem.flags&ObjectShowEdges))
            {
                glBegin(GL_LINES);
                {
                    SetLineColor(coordinateSystem.flags, 1.0f, 0.0f, 0.0f);
                    glVertex3f(-coordinateSystem.length, 0.0f, 0.0f);
                    glVertex3f(coordinateSystem.length, 0.0f, 0.0f);
                    SetLineColor(coordinateSystem.flags, 0.0f, 1.0f, 0.0f);
                    glVertex3f(0.0f, -coordinateSystem.length, 0.0f);
                    glVertex3f(0.0f, coordinateSystem.length, 0.0f);
                    SetLineColor(coordinateSystem.flags, 0.0f, 0.0f, 1.0f);
                    glVertex3f(0.0f, 0.0f, -coordinateSystem.length);
                    glVertex3f(0.0f, 0.0f, coordinateSystem.length);
                }
                glEnd();
            }
        }
    }
}