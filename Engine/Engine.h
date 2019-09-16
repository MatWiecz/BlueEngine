//
// Created by Mateusz on 2019-08-25.
//

#ifndef BLUEENGINE_ENGINE_H
#define BLUEENGINE_ENGINE_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef enum class EngineRetValEnum
        {
            Success,
            InvalidArgument,
            InvalidOperation
        } EngineRetVal;
        
        typedef class EngineClass Engine;
    }
}

#include "../Common/Basics/BitField.hpp"
#include "GraphicEngine/GraphicsEngine.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        struct EngineStatusStruct {};
        typedef BitField <EngineStatusStruct> EngineStatus;
        const EngineStatus EngineCreated(BitFieldSymbols::Reset);
        const EngineStatus EngineInitiated;
        const EngineStatus EngineWorking;
        
        struct EngineOperationModeStruct {};
        typedef BitField <EngineOperationModeStruct> EngineOperationMode;
        const EngineOperationMode EngineUserMode(BitFieldSymbols::Reset);
        const EngineOperationMode EngineDeveloperMode;
        const EngineOperationMode EngineDebugMode;
        
        class EngineClass
        {
            private:
            EngineStatus status;
            EngineOperationMode engineOperationMode;
            GraphicsEngine * graphicsEngine;
            
            
            public:
            EngineClass();
            
            ~EngineClass();
    
            EngineRetVal Create();
            
            EngineRetVal SetOperationMode(
                const EngineOperationMode &mode);
    
            EngineRetVal SetGraphicsEngine (GraphicsEngine * newGraphicsEngine);
            
            EngineRetVal Start();
    
            EngineRetVal MessageProcessingLoop();
            
            EngineRetVal Stop();
    
            EngineRetVal Destroy();
        };
        
    }
}

#endif //BLUEENGINE_ENGINE_H
