//
// Created by Mateusz on 2019-09-01.
//

#include "CoordinateSystem.h"
#include "../../../../Common/Graphic/Colours.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        
        void CoordinateSystemClass::SetLineColor(BaseObjectClassFlags flags,
                                                 GLfloat red, GLfloat green,
                                                 GLfloat blue)
        {
            if (int(flags & ObjectTextured))
                glColor3f(red, green, blue);
            else
                glColor3f(1.0f, 1.0f, 1.0f);
        }
        
        CoordinateSystemClass::CoordinateSystemClass()
        {
        }
        
        CoordinateSystem &CoordinateSystemClass::CreateCoordinateSystem(
            BaseObjectClass *parentObject, std::string objectName)
        {
            Create(parentObject, objectName);
            length = 1000000.0f;
            objectFunction = CoordinateSystem::DrawFunction;
            return *this;
        }
        
        CoordinateSystem &CoordinateSystemClass::SetAxisLength(float axisLength)
        {
            length = axisLength;
            return *this;
        }
        
        void CoordinateSystemClass::DrawFunction(const BaseObjectClass &object)
        {
            const auto &coordinateSystem = (CoordinateSystem &) object;
            if (int(coordinateSystem.flags & ObjectShowEdges))
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