//
// Created by Mateusz on 2019-09-01.
//

#ifndef BLUEENGINE_COORDINATESYSTEM_H
#define BLUEENGINE_COORDINATESYSTEM_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef class CoordinateSystemClass CoordinateSystem;
    }
}

#include "../BaseObjectClass.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        class CoordinateSystemClass: public BaseObjectClass
        {
            protected:
            float length;
            
            static void SetLineColor(BaseObjectClassFlags flags,
                                     GLfloat red, GLfloat green, GLfloat blue);
            
            public:
            
            CoordinateSystemClass();
    
            CoordinateSystem & CreateOrigin(std::string objectName);
            
            CoordinateSystem &CreateCoordinateSystem(
                BaseObjectClass *parentObject, std::string objectName);
    
            CoordinateSystem & SetAxisLength(float axisLength);
            
            static void DrawFunction(const BaseObjectClass &object);
        };
    }
}

#endif //BLUEENGINE_COORDINATESYSTEM_H
