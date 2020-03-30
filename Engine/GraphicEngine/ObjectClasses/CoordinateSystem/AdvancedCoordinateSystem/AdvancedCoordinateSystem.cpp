//
// Created by Mateusz on 2019-09-26.
//

#include "AdvancedCoordinateSystem.h"


namespace MatWiecz
{
    namespace BlueEngine
    {
        AdvancedCoordinateSystemClass::AdvancedCoordinateSystemClass()
        {
        }
        
        AdvancedCoordinateSystem &
        AdvancedCoordinateSystemClass::CreateAdvancedCoordinateSystem(
            BaseObjectClass *parentObject, std::string objectName)
        {
            CreateCoordinateSystem(parentObject, objectName);
            objectFunction = AdvancedCoordinateSystem::DrawFunction;
            showValues = false;
            return *this;
        }
        
        AdvancedCoordinateSystem &AdvancedCoordinateSystem::ShowValues(bool on)
        {
            showValues = on;
            return *this;
        }
        
        void AdvancedCoordinateSystemClass::DrawFunction(
            const BaseObjectClass &object)
        {
            const auto &coordinateSystem = (AdvancedCoordinateSystem &) object;
            CoordinateSystem::DrawFunction(object);
            
        }
    }
}