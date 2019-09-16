//
// Created by Mateusz on 2019-08-26.
//

#ifndef BLUEENGINE_GRAPHICSENGINE_H
#define BLUEENGINE_GRAPHICSENGINE_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef enum class GraphicsEngineRetValEnum
        {
            Success,
            InvalidArgument,
            InvalidOperation
        } GraphicsEngineRetVal;
        
        typedef class GraphicsEngineClass GraphicsEngine;
    }
}

#include "../../Common/Basics/BitField.hpp"
#include "Managers/ViewManager/ViewManager.h"
#include "ObjectClasses/CoordinateSystem/CoordinateSystem.h"
#include "../../VideoOutputWindow/VideoOutputWindow.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        struct GraphicsEngineStatusStruct {};
        typedef BitField <GraphicsEngineStatusStruct> GraphicsEngineStatus;
        const GraphicsEngineStatus GraphicsEngineCreated(
            BitFieldSymbols::Reset);
        const GraphicsEngineStatus GraphicsEngineInitiated;
        const GraphicsEngineStatus GraphicsEngineWorking;
        
        class GraphicsEngineClass
        {
            private:
            GraphicsEngineStatus status;
            VideoOutputWindow * videoOutputWindow;
            ViewManager *viewManager;
            CoordinateSystem *origin;
            GLclampf defaultColorValues [4];
            
            
            public:
            GraphicsEngineClass();
            
            ~GraphicsEngineClass();
            
            GraphicsEngineRetVal Create();
            
            bool IsCreated();
    
            GraphicsEngineRetVal SetVideoOutputWindow(
                VideoOutputWindow *newVideoOutputWindow);
            
            GraphicsEngineRetVal SetViewManager(ViewManager *newViewManager);
    
            GraphicsEngineRetVal SetDefaultColorValues(GLclampf red,
                                                       GLclampf green,
                                                       GLclampf blue,
                                                       GLclampf alpha);
    
            GraphicsEngineRetVal Start();
            
            CoordinateSystem *GetOrigin();
            
            GraphicsEngineRetVal DrawScene();
    
            GraphicsEngineRetVal Stop();
            
            GraphicsEngineRetVal Destroy();
        };
    };
}

#endif //BLUEENGINE_GRAPHICSENGINE_H
