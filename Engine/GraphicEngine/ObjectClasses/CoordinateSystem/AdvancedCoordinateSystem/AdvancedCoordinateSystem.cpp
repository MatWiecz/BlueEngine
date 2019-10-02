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
        
        BaseObjectClassRetVal
        AdvancedCoordinateSystemClass::CreateAdvancedCoordinateSystem(
            BaseObjectClass *parentObject, std::string objectName, float xPos,
            float yPos, float zPos, float xAngle, float yAngle, float zAngle,
            GLfloat axisLength, bool showValues)
        {
            BaseObjectClassRetVal retVal = CreateCoordinateSystem
                (parentObject, objectName, xPos, yPos, zPos, xAngle, yAngle,
                 zAngle, axisLength);
            if(retVal != BaseObjectClassRetVal::Success)
                return retVal;
            objectFunction = AdvancedCoordinateSystem::DrawFunction;
            showValuesFlag = showValues;
            return retVal;
        }
    
        void AdvancedCoordinateSystemClass::DrawFunction(
            const BaseObjectClass &object)
        {
            const auto & coordinateSystem = (AdvancedCoordinateSystem &) object;
            CoordinateSystem::DrawFunction(object);
            
        }
    }
}