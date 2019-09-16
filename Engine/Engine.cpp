//
// Created by Mateusz on 2019-08-25.
//

#include "Engine.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        EngineClass::EngineClass(): status(0),
                                    engineOperationMode(0),
                                    graphicsEngine(nullptr)
        {
        }
    
        EngineClass::~EngineClass()
        {
            Destroy();
        }
    
        EngineRetVal EngineClass::Create()
        {
            if(int(status & EngineCreated))
                return EngineRetVal::InvalidOperation;
            engineOperationMode = EngineDeveloperMode;
            status |= EngineCreated;
            return EngineRetVal::Success;
        }
    
        EngineRetVal EngineClass::SetOperationMode(
            const EngineOperationMode &mode)
        {
            if(int(~status & EngineCreated) || int(status & EngineWorking))
                return EngineRetVal::InvalidOperation;
            engineOperationMode = mode;
            return EngineRetVal::Success;
        }
    
        EngineRetVal EngineClass::SetGraphicsEngine(
            GraphicsEngine *newGraphicsEngine)
        {
            if(int(~status & EngineCreated) || int(status & EngineWorking))
                return EngineRetVal::InvalidOperation;
            if(newGraphicsEngine != nullptr && !newGraphicsEngine->IsCreated())
                return EngineRetVal::InvalidArgument;
            graphicsEngine = newGraphicsEngine;
            if(graphicsEngine == nullptr)
                status &= ~EngineInitiated;
            else
                status |= EngineInitiated;
            return EngineRetVal::Success;
        }
    
        EngineRetVal EngineClass::Start()
        {
            if(int(~status & EngineInitiated) || int(status & EngineWorking))
                return EngineRetVal::InvalidOperation;
            graphicsEngine->Start();
            status |= EngineWorking;
            return EngineRetVal::Success;
        }
    
        EngineRetVal EngineClass::MessageProcessingLoop()
        {
            if(int(~status & EngineWorking))
                return EngineRetVal::InvalidOperation;
            graphicsEngine->DrawScene();
            return EngineRetVal::Success;
        }
    
        EngineRetVal EngineClass::Stop()
        {
            if(int(~status & EngineWorking))
                return EngineRetVal::InvalidOperation;
            status &= ~EngineWorking;
            graphicsEngine->Stop();
            return EngineRetVal::Success;
        }
    
        EngineRetVal EngineClass::Destroy()
        {
            if(int(~status & EngineCreated))
                return EngineRetVal::InvalidOperation;
            Stop();
            SetGraphicsEngine(nullptr);
            status &= ~EngineCreated;
            engineOperationMode = EngineOperationMode(0);
            return EngineRetVal::Success;
        }
    }
}
