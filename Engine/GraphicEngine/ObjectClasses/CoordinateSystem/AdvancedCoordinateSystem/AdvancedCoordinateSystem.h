//
// Created by Mateusz on 2019-09-26.
//

#ifndef BLUEENGINE_ADVANCEDCOORDINATESYSTEM_H
#define BLUEENGINE_ADVANCEDCOORDINATESYSTEM_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef class AdvancedCoordinateSystemClass AdvancedCoordinateSystem;
    }
}

#include "../CoordinateSystem.h"
#include "../../../Managers/ViewManager/ViewManager.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        class AdvancedCoordinateSystemClass: public CoordinateSystem
        {
            protected:
            bool showValues;
            
            public:
            AdvancedCoordinateSystemClass();
    
            AdvancedCoordinateSystem & CreateAdvancedCoordinateSystem(
                BaseObjectClass *parentObject, std::string objectName);
    
            AdvancedCoordinateSystem & SetShowValuesMode(bool on);
    
            static void DrawFunction(const BaseObjectClass & object);
        };
    };
}

#endif //BLUEENGINE_ADVANCEDCOORDINATESYSTEM_H
