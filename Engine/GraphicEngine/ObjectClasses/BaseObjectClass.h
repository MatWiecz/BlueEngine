//
// Created by Mateusz on 2019-08-26.
//

#ifndef BLUEENGINE_BASEOBJECTCLASS_H
#define BLUEENGINE_BASEOBJECTCLASS_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef enum class BasObjectClassRetValEnum
        {
            Success,
            InvalidArgument,
            InvalidOperation
        } BaseObjectClassRetVal;
        
        typedef enum class BaseObjectClassUpdateFlagsModeEnum
        {
            SetFlags,
            UnsetFlags,
            ToggleFlags
        } BaseObjectClassUpdateFlagsMode;
        
        typedef class BaseObjectClassClass BaseObjectClass;
    }
}

#include <stdlib.h>
#include <string>
#include <vector>
#include <GL/glu.h>

#include "../../../Common/Basics/BitField.hpp"

namespace MatWiecz
{
    namespace BlueEngine
    {
        struct BaseObjectClassFlagsStruct {};
        typedef BitField <BaseObjectClassFlagsStruct> BaseObjectClassFlags;
        const BaseObjectClassFlags ObjectCreated;
        const BaseObjectClassFlags ObjectVisible;
        const BaseObjectClassFlags ObjectShowPoints;
        const BaseObjectClassFlags ObjectShowEdges;
        const BaseObjectClassFlags ObjectShowFaces;
        const BaseObjectClassFlags ObjectTextured;
    
        typedef void (*PosFunction)(float [3]);
    
        typedef void (*AngleFunction)(float [3]);
    
        typedef void (*ObjectFunction)(BaseObjectClassFlags);
        
        class BaseObjectClassClass
        {
            protected:
            static unsigned int nextId;
            unsigned int id;
            BaseObjectClassFlags flags;
            BaseObjectClassClass *parent;
            unsigned int parentChildNo;
            std::string name;
            float pos[3];
            float angle[3];
            ObjectFunction objectFunction;
            PosFunction posFunction;
            AngleFunction angleFunction;
            std::vector <BaseObjectClassClass *> children;
            
            public:
            BaseObjectClassClass();
            
            ~BaseObjectClassClass() = default;
    
            BaseObjectClassRetVal Create(BaseObjectClassClass *parentObject,
                                         std::string &objectName,
                                         float xPos, float yPos, float zPos,
                                         float xAngle, float yAngle,
                                         float zAngle);
    
            bool IsCreated ();
            
            unsigned int GetObjectId ();
            
            BaseObjectClassRetVal UpdateFlags(BaseObjectClassUpdateFlagsMode mode, BaseObjectClassFlags flagsMask,
                                                          bool recursively);
            
            BaseObjectClassRetVal SetObjectFunction(ObjectFunction
                                                    newObjectFunction);
    
            BaseObjectClassRetVal SetPos (float xPos, float yPos, float zPos);
            
            BaseObjectClassRetVal SetPosFunction(PosFunction newPosFunction);
    
            BaseObjectClassRetVal SetAngle (float xAngle, float yAngle,
                                          float zAngle);
            
            BaseObjectClassRetVal SetAngleFunction(AngleFunction
                                                   newAngleFunction);
            
            BaseObjectClassRetVal Execute();
            
            BaseObjectClassRetVal Destroy();
        };
    }
}


#endif //BLUEENGINE_BASEOBJECTCLASS_H
