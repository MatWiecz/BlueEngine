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
        
        typedef enum class UpdateFlagsModeEnum
        {
            SetFlags,
            UnsetFlags,
            ToggleFlags
        } UpdateFlagsMode;
        
        typedef enum class TransformationOrderModeEnum
        {
            TRS,
            TSR,
            RTS,
            RST,
            STR,
            SRT
        } TransformationOrderMode;
        
        typedef class BaseObjectClassClass BaseObjectClass;
    }
}

#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <GL/glu.h>

#include "../../../Common/Basics/BitField.hpp"

namespace MatWiecz
{
    namespace BlueEngine
    {
        struct BaseObjectClassFlagsStruct {};
        typedef BitField <BaseObjectClassFlagsStruct> BaseObjectClassFlags;
        const BaseObjectClassFlags ObjectCreated(BitFieldSymbols::Reset);
        const BaseObjectClassFlags ObjectVisible;
        const BaseObjectClassFlags ObjectShowPoints;
        const BaseObjectClassFlags ObjectShowEdges;
        const BaseObjectClassFlags ObjectShowFaces;
        const BaseObjectClassFlags ObjectTextured;
        
        typedef void (*PosFunction)(float [3]);
        
        typedef void (*AngleFunction)(float [3]);
        
        typedef void (*ScaleFunction)(float [3]);
        
        typedef void (*ObjectFunction)(const BaseObjectClass &);
        
        class BaseObjectClassClass
        {
            private:
            void PerformTranslation();
            
            void PerformRotation();
            
            void PerformScaling();
            
            void PerformReversedTranslation();
            
            void PerformReversedRotation();
            
            void PerformReversedScaling();
            
            protected:
            static unsigned int nextId;
            unsigned int id;
            BaseObjectClassFlags flags;
            BaseObjectClass *parent;
            std::string name;
            float pos[3];
            float angle[3];
            float scale[3];
            TransformationOrderMode transOrderMode;
            ObjectFunction objectFunction;
            PosFunction posFunction;
            AngleFunction angleFunction;
            ScaleFunction scaleFunction;
            std::map <unsigned int, BaseObjectClass *> children;
            
            public:
            BaseObjectClassClass();
            
            ~BaseObjectClassClass();
            
            virtual BaseObjectClass & Create(BaseObjectClass *parentObject,
                                                 std::string objectName);
            
            bool IsCreated();
            
            unsigned int GetObjectId();
            
            BaseObjectClass *GetParent();
            
            const std::map <unsigned int, BaseObjectClass *> &GetChildren();
    
            BaseObjectClass &
            UpdateFlags(UpdateFlagsMode mode,
                        BaseObjectClassFlags flagsMask,
                        bool recursively = false);
    
            BaseObjectClass & SetObjectFunction(ObjectFunction
                                                    newObjectFunction);
    
            BaseObjectClass & SetPos(float xPos, float yPos, float zPos);
    
            BaseObjectClass & SetXPos(float xPos);
    
            BaseObjectClass & SetYPos(float yPos);
    
            BaseObjectClass & SetZPos(float zPos);
    
            BaseObjectClass & SetPosFunction(PosFunction newPosFunction);
    
            BaseObjectClass & SetAngle(float xAngle, float yAngle,
                                           float zAngle);
    
            BaseObjectClass & SetXAngle(float xAngle);
    
            BaseObjectClass & SetYAngle(float yAngle);
    
            BaseObjectClass & SetZAngle(float zAngle);
    
            BaseObjectClass & SetAngleFunction(AngleFunction
                                                   newAngleFunction);
    
            BaseObjectClass & SetScale(float xScale, float yScale,
                                           float zScale);
    
            BaseObjectClass & SetXScale(float xScale);
    
            BaseObjectClass & SetYScale(float yScale);
    
            BaseObjectClass & SetZScale(float zScale);
    
            BaseObjectClass & SetScaleFunction(
                ScaleFunction newScaleFunction);
            
            BaseObjectClassRetVal PerformTransformation(
                bool reverse = false);
            
            BaseObjectClassRetVal Execute();
            
            BaseObjectClassRetVal Destroy();
        };
    }
}


#endif //BLUEENGINE_BASEOBJECTCLASS_H
