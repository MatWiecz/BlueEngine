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
        class CoordinateSystemClass : public BaseObjectClass
        {
            public:
    
            BaseObjectClassRetVal Create(BaseObjectClass *parentObject,
                                         std::string objectName,
                                         float xPos, float yPos, float zPos,
                                         float xAngle, float yAngle,
                                         float zAngle);
    
            BaseObjectClassRetVal Destroy();
            
        };
    };
}

#endif //BLUEENGINE_COORDINATESYSTEM_H
