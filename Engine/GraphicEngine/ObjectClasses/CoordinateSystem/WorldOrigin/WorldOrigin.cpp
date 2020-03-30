//
// Created by Mateusz on 30.03.2020.
//

#include "WorldOrigin.h"


namespace MatWiecz
{
    namespace BlueEngine
    {
        WorldOriginClass::WorldOriginClass()
        {
        }
        
        WorldOrigin &
        WorldOriginClass::CreateWorldOrigin(std::string objectName)
        {
            if (int(flags & ObjectCreated))
                return *this;
            id = nextId++;
            parent = nullptr;
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
            flags |= ObjectCreated;
            objectFunction = WorldOrigin::DrawFunction;
            length = 1000000.0f;
            return *this;
        }
        
        void WorldOriginClass::DrawFunction(
            const BaseObjectClass &object)
        {
            const auto &coordinateSystem = (WorldOrigin &) object;
            CoordinateSystem::DrawFunction(object);
            
        }
    }
}
