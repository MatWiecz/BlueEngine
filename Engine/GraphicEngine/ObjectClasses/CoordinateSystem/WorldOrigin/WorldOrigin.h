//
// Created by Mateusz on 30.03.2020.
//

#ifndef BLUEENGINE_WORLDORIGIN_H
#define BLUEENGINE_WORLDORIGIN_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef class WorldOriginClass WorldOrigin;
    }
}

#include "../CoordinateSystem.h"
#include "../../../Managers/ViewManager/ViewManager.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        class WorldOriginClass: public CoordinateSystem
        {
            protected:
            
            public:
            WorldOriginClass();
            
            WorldOrigin & CreateWorldOrigin(std::string objectName);
            
            static void DrawFunction(const BaseObjectClass & object);
        };
    }
}

#endif //BLUEENGINE_WORLDORIGIN_H
