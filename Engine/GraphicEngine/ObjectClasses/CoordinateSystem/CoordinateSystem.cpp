//
// Created by Mateusz on 2019-09-01.
//

#include "CoordinateSystem.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        BaseObjectClassRetVal CoordinateSystemClass::Create(
            BaseObjectClass *parentObject, std::string objectName,
            float xPos, float yPos, float zPos,
            float xAngle, float yAngle, float zAngle)
        {
            if (int(flags & ObjectCreated))
                return BaseObjectClassRetVal::InvalidOperation;
            if (parentObject != nullptr && !parentObject->IsCreated())
                return BaseObjectClassRetVal::InvalidArgument;
            id = nextId++;
            parent = parentObject;
            if(parent != nullptr)
            {
                parentChildNo = (unsigned int) parent->children.size();
                parent->children.push_back(this);
            }
            name = objectName;
            pos[0] = xPos;
            pos[1] = yPos;
            pos[2] = zPos;
            angle[0] = xAngle;
            angle[2] = yAngle;
            angle[2] = zAngle;
            posFunction = nullptr;
            angleFunction = nullptr;
            objectFunction = nullptr;
            flags |= ObjectCreated | ObjectVisible | ObjectShowPoints |
                     ObjectShowEdges | ObjectShowFaces;
            return BaseObjectClassRetVal::Success;
        }
    
        BaseObjectClassRetVal BaseObjectClassClass::Destroy()
        {
            if (int(~(flags & ObjectCreated)))
                return BaseObjectClassRetVal::InvalidOperation;
            for (auto &child : children)
                child->Destroy();
            flags = BaseObjectClassFlags(0);
            if (parent != nullptr)
                parent->children.erase(parent->children.begin() + parentChildNo);
            id = 0;
            return BaseObjectClassRetVal::Success;
        }
    };
}