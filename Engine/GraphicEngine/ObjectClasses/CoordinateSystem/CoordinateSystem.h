//
// Created by Mateusz on 2019-09-01.
//

#ifndef BLUEENGINE_COORDINATESYSTEM_H
#define BLUEENGINE_COORDINATESYSTEM_H

#include "../BaseObjectClass.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef class CoordinateSystemClass CoordinateSystem;
    }
}

namespace MatWiecz
{
    namespace BlueEngine
    {
        class CoordinateSystemClass: public BaseObjectClass
        {
            protected:
            GLfloat length;
            
            static void SetLineColor(BaseObjectClassFlags flags,
                              GLfloat red, GLfloat green, GLfloat blue);
            
            public:
            
            CoordinateSystemClass();
            
            BaseObjectClassRetVal CreateOrigin(std::string objectName);
    
            BaseObjectClassRetVal CreateCoordinateSystem(
                BaseObjectClass *parentObject, std::string objectName,
                float xPos, float yPos, float zPos,
                float xAngle, float yAngle, float zAngle,
                GLfloat axisLength = 1000000.0f);
    
            static void DrawFunction(const BaseObjectClass & object);
        };
    };
}

#endif //BLUEENGINE_COORDINATESYSTEM_H
