//
// Created by Mateusz on 2019-08-26.
//

#include "GraphicsEngine.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        GraphicsEngineClass::GraphicsEngineClass(): status(0),
                                                    origin(nullptr),
                                                    viewManager(nullptr)
        {
        }
    
        GraphicsEngineClass::~GraphicsEngineClass()
        {
            Destroy();
        }
    
        GraphicsEngineRetVal GraphicsEngineClass::Create()
        {
            if(int(status & GraphicsEngineCreated))
                return GraphicsEngineRetVal::InvalidOperation;
            origin = new CoordinateSystem();
            origin->Create(nullptr, "Root object", 0.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 0.0f);
            status |= GraphicsEngineCreated;
            return GraphicsEngineRetVal::Success;
        }
    
        GraphicsEngineRetVal GraphicsEngineClass::SetViewManager(
            ViewManager *newViewManager)
        {
            if(int(~status & GraphicsEngineCreated))
                return GraphicsEngineRetVal::InvalidOperation;
            if(newViewManager != nullptr && !newViewManager->IsCreated())
                return GraphicsEngineRetVal::InvalidArgument;
            viewManager = newViewManager;
            if(viewManager == nullptr)
                status &= ~GraphicsEngineInitiated;
            else
                status |= GraphicsEngineInitiated;
            return GraphicsEngineRetVal::Success;
        }
    
        CoordinateSystem* GraphicsEngineClass::GetOrigin()
        {
            return origin;
        }
    
        GraphicsEngineRetVal GraphicsEngineClass::DrawScene()
        {
            if(int(~status & GraphicsEngineInitiated))
                return GraphicsEngineRetVal::InvalidOperation;
            viewManager->PerformViewTransformation();
            origin->Execute();
            return GraphicsEngineRetVal::Success;
        }
    
        GraphicsEngineRetVal GraphicsEngineClass::Destroy()
        {
            if(int(~status & GraphicsEngineCreated))
                return GraphicsEngineRetVal::InvalidOperation;
            SetViewManager(nullptr);
            origin->Destroy();
            delete origin;
            origin = nullptr;
            status &= ~GraphicsEngineCreated;
            return GraphicsEngineRetVal::Success;
        }
    }
}