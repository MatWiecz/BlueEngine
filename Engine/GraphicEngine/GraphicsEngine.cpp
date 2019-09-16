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
                                                    viewManager(nullptr),
                                                    defaultColorValues({0.0f})
        {
        }
        
        GraphicsEngineClass::~GraphicsEngineClass()
        {
            Destroy();
        }
        
        GraphicsEngineRetVal GraphicsEngineClass::Create()
        {
            if (int(status & GraphicsEngineCreated))
                return GraphicsEngineRetVal::InvalidOperation;
            status |= GraphicsEngineCreated;
            return GraphicsEngineRetVal::Success;
        }
        
        bool GraphicsEngineClass::IsCreated()
        {
            return bool(int(status & GraphicsEngineCreated));
        }
    
        GraphicsEngineRetVal GraphicsEngineClass::SetVideoOutputWindow(
            VideoOutputWindow *newVideoOutputWindow)
        {
            if (int(~status & GraphicsEngineCreated) ||
                int(status & GraphicsEngineWorking))
                return GraphicsEngineRetVal::InvalidOperation;
            if (newVideoOutputWindow != nullptr &&
                !newVideoOutputWindow->IsCreated())
                return GraphicsEngineRetVal::InvalidArgument;
            videoOutputWindow = newVideoOutputWindow;
            if (videoOutputWindow == nullptr || viewManager == nullptr)
                status &= ~GraphicsEngineInitiated;
            else
                status |= GraphicsEngineInitiated;
            return GraphicsEngineRetVal::Success;
        }
        
        GraphicsEngineRetVal GraphicsEngineClass::SetViewManager(
            ViewManager *newViewManager)
        {
            if (int(~status & GraphicsEngineCreated) ||
                int(status & GraphicsEngineWorking))
                return GraphicsEngineRetVal::InvalidOperation;
            if (newViewManager != nullptr && !newViewManager->IsCreated())
                return GraphicsEngineRetVal::InvalidArgument;
            viewManager = newViewManager;
            if (videoOutputWindow == nullptr || viewManager == nullptr)
                status &= ~GraphicsEngineInitiated;
            else
                status |= GraphicsEngineInitiated;
            return GraphicsEngineRetVal::Success;
        }
        
        GraphicsEngineRetVal GraphicsEngineClass::SetDefaultColorValues(
            GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
        {
            if (int(~status & GraphicsEngineCreated) ||
                int(status & GraphicsEngineWorking))
                return GraphicsEngineRetVal::InvalidOperation;
            defaultColorValues[0] = red;
            defaultColorValues[1] = green;
            defaultColorValues[2] = blue;
            defaultColorValues[3] = alpha;
            return GraphicsEngineRetVal::Success;
        }
        
        GraphicsEngineRetVal GraphicsEngineClass::Start()
        {
            if (int(~status & GraphicsEngineInitiated) ||
                int(status & GraphicsEngineWorking))
                return GraphicsEngineRetVal::InvalidOperation;
            glClearColor(defaultColorValues[0], defaultColorValues[1],
                         defaultColorValues[2], defaultColorValues[3]);
            glEnable(GL_DEPTH_TEST);
            origin = new CoordinateSystem();
            origin->CreateOrigin("Root object");
            status |= GraphicsEngineWorking;
            return GraphicsEngineRetVal::Success;
        }
        
        CoordinateSystem *GraphicsEngineClass::GetOrigin()
        {
            return origin;
        }
        
        GraphicsEngineRetVal GraphicsEngineClass::DrawScene()
        {
            if (int(~status & GraphicsEngineInitiated))
                return GraphicsEngineRetVal::InvalidOperation;
            viewManager->UpdateProjection(
                videoOutputWindow->GetAspectRatio());
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
            viewManager->PerformViewTransformation();
            origin->Execute();
            videoOutputWindow->UpdateFrame();
            return GraphicsEngineRetVal::Success;
        }
        
        GraphicsEngineRetVal GraphicsEngineClass::Stop()
        {
            if (int(~status & GraphicsEngineWorking))
                return GraphicsEngineRetVal::InvalidOperation;
            status &= ~GraphicsEngineWorking;
            origin->Destroy();
            delete origin;
            origin = nullptr;
            return GraphicsEngineRetVal::Success;
        }
        
        GraphicsEngineRetVal GraphicsEngineClass::Destroy()
        {
            if (int(~status & GraphicsEngineCreated))
                return GraphicsEngineRetVal::InvalidOperation;
            SetViewManager(nullptr);
            status &= ~GraphicsEngineCreated;
            return GraphicsEngineRetVal::Success;
        }
    }
}