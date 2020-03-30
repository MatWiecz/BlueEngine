//
// Created by Mateusz on 2019-08-26.
//

#include "BaseObjectClass.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        void BaseObjectClassClass::PerformTranslation()
        {
            glTranslatef(pos[0], pos[1], pos[2]);
        }
        
        void BaseObjectClassClass::PerformReversedTranslation()
        {
            glTranslatef(-pos[0], -pos[1], -pos[2]);
        }
        
        void BaseObjectClassClass::PerformRotation()
        {
            glRotatef(angle[0], 1.0f, 0.0f, 0.0f);
            glRotatef(angle[1], 0.0f, 1.0f, 0.0f);
            glRotatef(angle[2], 0.0f, 0.0f, 1.0f);
        }
        
        void BaseObjectClassClass::PerformReversedRotation()
        {
            glRotatef(-angle[2], 0.0f, 0.0f, 1.0f);
            glRotatef(-angle[1], 0.0f, 1.0f, 0.0f);
            glRotatef(-angle[0], 1.0f, 0.0f, 0.0f);
        }
        
        void BaseObjectClassClass::PerformScaling()
        {
            glScalef(scale[0], scale[1], scale[2]);
        }
        
        void BaseObjectClassClass::PerformReversedScaling()
        {
            glScalef(1.0f / scale[0], 1.0f / scale[1], 1.0f / scale[2]);
        }
        
        unsigned int BaseObjectClassClass::nextId = 1;
        
        BaseObjectClassClass::BaseObjectClassClass(): id(0),
                                                      flags(0),
                                                      parent(nullptr)
        {
        }
        
        BaseObjectClassClass::~BaseObjectClassClass()
        {
            Destroy();
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::Create(
            BaseObjectClass *parentObject, std::string objectName,
            float xPos, float yPos, float zPos,
            float xAngle, float yAngle, float zAngle,
            float xScale, float yScale, float zScale,
            TransformationOrderMode transformationOrderMode)
        {
            if (int(flags & ObjectCreated))
                return BaseObjectClassRetVal::InvalidOperation;
            if (parentObject == nullptr || !parentObject->IsCreated() ||
                objectName.empty())
                return BaseObjectClassRetVal::InvalidArgument;
            id = nextId++;
            parent = parentObject;
            parent->children[id] = this;
            name = objectName;
            pos[0] = xPos;
            pos[1] = yPos;
            pos[2] = zPos;
            angle[0] = xAngle;
            angle[1] = yAngle;
            angle[2] = zAngle;
            scale[0] = xScale;
            scale[1] = yScale;
            scale[2] = zScale;
            transOrderMode = transformationOrderMode;
            posFunction = nullptr;
            angleFunction = nullptr;
            scaleFunction = nullptr;
            objectFunction = nullptr;
            flags |= ObjectCreated | ObjectVisible | ObjectShowPoints |
                     ObjectShowEdges | ObjectShowFaces;
            return BaseObjectClassRetVal::Success;
        }
        
        bool BaseObjectClassClass::IsCreated()
        {
            return bool(int(flags & ObjectCreated));
        }
        
        unsigned int BaseObjectClassClass::GetObjectId()
        {
            return id;
        }
        
        BaseObjectClass *BaseObjectClassClass::GetParent()
        {
            return parent;
        }
        
        const std::map <unsigned int, BaseObjectClass *> &
        BaseObjectClassClass::GetChildren()
        {
            return children;
        }
        
        BaseObjectClassRetVal
        BaseObjectClassClass::UpdateFlags(BaseObjectClassUpdateFlagsMode mode,
                                          BaseObjectClassFlags flagsMask,
                                          bool recursively)
        {
            if (int(~flags & ObjectCreated))
                return BaseObjectClassRetVal::InvalidOperation;
            flagsMask &= ~ObjectCreated;
            switch (mode)
            {
                case BaseObjectClassUpdateFlagsMode::SetFlags:
                    flags |= flagsMask;
                    break;
                case BaseObjectClassUpdateFlagsMode::UnsetFlags:
                    flags &= ~flagsMask;
                    break;
                case BaseObjectClassUpdateFlagsMode::ToggleFlags:
                    flags ^= flagsMask;
                    break;
            }
            if (recursively)
                for (auto &child : children)
                    child.second->UpdateFlags(mode, flagsMask, true);
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::SetObjectFunction(
            ObjectFunction newObjectFunction)
        {
            if (int(~flags & ObjectCreated))
                return BaseObjectClassRetVal::InvalidOperation;
            objectFunction = newObjectFunction;
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::SetPos(
            float xPos, float yPos, float zPos)
        {
            pos[0] = xPos;
            pos[1] = yPos;
            pos[2] = zPos;
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::SetPosFunction(
            PosFunction newPosFunction)
        {
            if (int(~flags & ObjectCreated))
                return BaseObjectClassRetVal::InvalidOperation;
            posFunction = newPosFunction;
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::SetAngle(
            float xAngle, float yAngle, float zAngle)
        {
            angle[0] = xAngle;
            angle[2] = yAngle;
            angle[2] = zAngle;
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::SetAngleFunction(
            AngleFunction newAngleFunction)
        {
            if (int(~flags & ObjectCreated))
                return BaseObjectClassRetVal::InvalidOperation;
            angleFunction = newAngleFunction;
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::SetScale
            (float xScale, float yScale, float zScale)
        {
            scale[0] = xScale;
            scale[1] = yScale;
            scale[2] = zScale;
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::SetScaleFunction(
            ScaleFunction newScaleFunction)
        {
            if (int(~flags & ObjectCreated))
                return BaseObjectClassRetVal::InvalidOperation;
            scaleFunction = newScaleFunction;
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal
        BaseObjectClassClass::PerformTranslationAndRotation(
            bool reverse)
        {
            if (int(~flags & ObjectCreated))
                return BaseObjectClassRetVal::InvalidOperation;
            if (posFunction != nullptr)
                posFunction(pos);
            if (angleFunction != nullptr)
                angleFunction(angle);
            if (scaleFunction != nullptr)
                scaleFunction(scale);
            switch (transOrderMode)
            {
                case TransformationOrderMode::TRS:
                    if (!reverse)
                    {
                        PerformTranslation();
                        PerformRotation();
                        PerformScaling();
                    }
                    else
                    {
                        PerformReversedScaling();
                        PerformReversedRotation();
                        PerformReversedTranslation();
                    }
                    break;
                case TransformationOrderMode::TSR:
                    if (!reverse)
                    {
                        PerformTranslation();
                        PerformScaling();
                        PerformRotation();
                    }
                    else
                    {
                        PerformReversedRotation();
                        PerformReversedScaling();
                        PerformReversedTranslation();
                    }
                    break;
                case TransformationOrderMode::RTS:
                    if (!reverse)
                    {
                        PerformRotation();
                        PerformTranslation();
                        PerformScaling();
                    }
                    else
                    {
                        PerformReversedScaling();
                        PerformReversedTranslation();
                        PerformReversedRotation();
                    }
                    break;
                case TransformationOrderMode::RST:
                    if (!reverse)
                    {
                        PerformRotation();
                        PerformScaling();
                        PerformTranslation();
                    }
                    else
                    {
                        PerformReversedTranslation();
                        PerformReversedScaling();
                        PerformReversedRotation();
                    }
                    break;
                case TransformationOrderMode::STR:
                    if (!reverse)
                    {
                        PerformScaling();
                        PerformTranslation();
                        PerformRotation();
                    }
                    else
                    {
                        PerformReversedRotation();
                        PerformReversedTranslation();
                        PerformReversedScaling();
                    }
                    break;
                case TransformationOrderMode::SRT:
                    if (!reverse)
                    {
                        PerformScaling();
                        PerformRotation();
                        PerformTranslation();
                    }
                    else
                    {
                        PerformReversedTranslation();
                        PerformReversedRotation();
                        PerformReversedScaling();
                    }
                    break;
            }
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::Execute()
        {
            if (int(~flags & ObjectCreated))
                return BaseObjectClassRetVal::InvalidOperation;
            glPushMatrix();
            PerformTranslationAndRotation();
            if (objectFunction != nullptr && int(flags & ObjectVisible))
            {
                glPushMatrix();
                objectFunction(*this);
                glPopMatrix();
            }
            for (auto &child : children)
                child.second->Execute();
            glPopMatrix();
            return BaseObjectClassRetVal::Success;
        }
        
        BaseObjectClassRetVal BaseObjectClassClass::Destroy()
        {
            if (int(~flags & ObjectCreated))
                return BaseObjectClassRetVal::InvalidOperation;
            auto tempChildren(children);
            for (auto &child : tempChildren)
                child.second->Destroy();
            flags = BaseObjectClassFlags(0);
            if (parent != nullptr)
                parent->children.erase(id);
            parent = nullptr;
            id = 0;
            return BaseObjectClassRetVal::Success;
        }
    }
}