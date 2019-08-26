//
// Created by Mateusz on 2019-08-26.
//

#include "BaseObjectClass.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        unsigned int BaseObjectClassClass::nextId = 1;
        
        BaseObjectClassClass::BaseObjectClassClass(): flags(0)
        {
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::Create(
            BaseObjectClassClass *parentObject, std::string &objectName,
            float xPos, float yPos, float zPos,
            float xAngle, float yAngle, float zAngle)
        {
            if (int(flags & ObjectCreated))
                return InvalidOperation;
            if (parentObject == nullptr || int(~parentObject->flags &
                                               ObjectCreated))
                return InvalidArgument;
            id = nextId++;
            parent = parentObject;
            parentChildNo = (unsigned int) parent->children.size();
            parent->children.push_back(this);
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
            return Success;
        }
        
        BaseObjectClassRetVal
        BaseObjectClassClass::UpdateFlags(BaseObjectClassUpdateFlagsMode mode,
                                          BaseObjectClassFlags flagsMask,
                                          bool recursively)
        {
            if (int(~(flags & ObjectCreated)))
                return InvalidOperation;
            flagsMask &= ~ObjectCreated;
            switch (mode)
            {
                case SetFlags:
                    flags |= flagsMask;
                    break;
                case UnsetFlags:
                    flags &= ~flagsMask;
                    break;
                case ToggleFlags:
                    flags ^= flagsMask;
                    break;
                default:
                    break;
            }
            if (recursively)
                for (auto &child : children)
                    child->UpdateFlags(mode, flagsMask, true);
            return Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::SetObjectFunction(
            ObjectFunction newObjectFunction)
        {
            if (int(~(flags & ObjectCreated)))
                return InvalidOperation;
            objectFunction = newObjectFunction;
            return Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::SetPos(
            float xPos, float yPos, float zPos)
        {
            pos[0] = xPos;
            pos[1] = yPos;
            pos[2] = zPos;
            return Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::SetPosFunction(
            PosFunction newPosFunction)
        {
            if (int(~(flags & ObjectCreated)))
                return InvalidOperation;
            posFunction = newPosFunction;
            return Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::SetAngle(
            float xAngle, float yAngle, float zAngle)
        {
            angle[0] = xAngle;
            angle[2] = yAngle;
            angle[2] = zAngle;
            return Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::SetAngleFunction(
            AngleFunction newAngleFunction)
        {
            if (int(~(flags & ObjectCreated)))
                return InvalidOperation;
            angleFunction = newAngleFunction;
            return Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::Execute()
        {
            if (int(~(flags & ObjectCreated)))
                return InvalidOperation;
            if(posFunction != nullptr)
                posFunction(pos);
            if(angleFunction != nullptr)
                angleFunction(angle);
            glPushMatrix();
            glTranslatef(pos[0], pos[1], pos[2]);
            glRotatef(angle[0], 1.0f, 0.0f, 0.0f);
            glRotatef(angle[1], 0.0f, 1.0f, 0.0f);
            glRotatef(angle[2], 0.0f, 0.0f, 1.0f);
            if(objectFunction != nullptr && int(flags & ObjectVisible))
            {
                glPushMatrix();
                objectFunction(flags);
                glPopMatrix();
            }
            for (auto &child : children)
                child->Execute();
            glPopMatrix();
            return Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::Destroy()
        {
            if (int(~(flags & ObjectCreated)))
                return InvalidOperation;
            for (auto &child : children)
                child->Destroy();
            flags &= ~ObjectCreated;
            parent->children.erase(parent->children.begin() + parentChildNo);
            return Success;
        }
    }
}