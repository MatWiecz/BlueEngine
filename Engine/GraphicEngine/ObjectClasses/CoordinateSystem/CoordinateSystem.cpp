//
// Created by Mateusz on 2019-09-01.
//

#include "CoordinateSystem.h"

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
            posFunction = nullptr;
            angleFunction = nullptr;
            objectFunction = CoordinateSystem::DrawFunction;
            flags |= ObjectCreated | ObjectVisible | ObjectShowPoints |
                     ObjectShowEdges | ObjectShowFaces;
            return BaseObjectClassRetVal::Success;
        }
    
        BaseObjectClassRetVal CoordinateSystemClass::CreateCoordinateSystem(
            BaseObjectClass *parentObject, std::string objectName, float xPos,
            float yPos, float zPos, float xAngle, float yAngle, float zAngle)
        {
            BaseObjectClassRetVal retVal = Create(parentObject, objectName,
                                                  xPos, yPos, zPos,
                                                  xAngle, yAngle, zAngle);
            if(retVal == BaseObjectClassRetVal::Success)
                objectFunction = CoordinateSystem::DrawFunction;
            return retVal;
            
        }
    
        void CoordinateSystemClass::DrawFunction(BaseObjectClassFlags flags)
        {
            const float axisLength = 1000000.0f;
            glBegin(GL_LINES);
            {
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(-axisLength, 0.0f, 0.0f);
                glVertex3f(axisLength, 0.0f, 0.0f);
                glColor3f(0.0f, 1.0f, 0.0f);
                glVertex3f(0.0f, -axisLength, 0.0f);
                glVertex3f(0.0f, axisLength, 0.0f);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex3f(0.0f, 0.0f, -axisLength);
                glVertex3f(0.0f, 0.0f, axisLength);
            }
            glEnd();
        }
    };
}