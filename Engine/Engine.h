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
            InvalidArgument
        } EngineRetVal;
        
        typedef class EngineClass Engine;
    }
}

#include "../Common/Basics/BitField.hpp"

namespace MatWiecz
{
    namespace BlueEngine
    {
        struct EngineStatusStruct {};
        typedef BitField <EngineStatusStruct> EngineStatus;
        const EngineStatus EngineCreated;
        const EngineStatus EngineInitiated;
        
        struct EngineOperationModeStruct {};
        typedef BitField <EngineOperationModeStruct> EngineOperationMode;
        const EngineOperationMode EngineUserMode;
        const EngineOperationMode EngineDeveloperMode;
        const EngineOperationMode EngineDebugMode;
        
        class EngineClass
        {
            private:
            
            EngineStatus status;
            
            
            public:
            EngineClass();
            
            ~EngineClass();
            
            EngineRetVal SetOperationMode(
                const EngineOperationMode &mode);
            
            EngineRetVal Start();
            
            EngineRetVal Stop();
        };
        
    }
}

#endif //BLUEENGINE_ENGINE_H
