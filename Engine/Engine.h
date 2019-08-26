//
// Created by Mateusz on 2019-08-25.
//

#ifndef BLUEENGINE_ENGINE_H
#define BLUEENGINE_ENGINE_H

#include "../Common/Basics/BitField.hpp"

namespace MatWiecz
{
    namespace BlueEngine
    {
        struct EngineStatusStruct
        {
        };
        typedef BitField <EngineStatusStruct> EngineStatus;
        const EngineStatus EngineCreated;
        const EngineStatus EngineInitiated;
        
        typedef enum EngineRetValEnum
        {
            Success,
            InvalidArgument
            
        } EngineRetVal;
        
        struct EngineOperationModeStruct
        {
        };
        typedef BitField <EngineOperationModeStruct> EngineOperationMode;
        const EngineOperationMode EngineUserMode;
        const EngineOperationMode EngineDeveloperMode;
        const EngineOperationMode EngineDebugMode;
        
        typedef class EngineClass
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
        } Engine;
        
    }
}

#endif //BLUEENGINE_ENGINE_H
