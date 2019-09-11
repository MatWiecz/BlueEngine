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

namespace MatWiecz
{
    namespace BlueEngine
    {
        struct GraphicsEngineStatusStruct {};
        typedef BitField <GraphicsEngineStatusStruct> GraphicsEngineStatus;
        const GraphicsEngineStatus GraphicsEngineCreated;
        const GraphicsEngineStatus GraphicsEngineInitiated;
        
        class GraphicsEngineClass
        {
            private:
            GraphicsEngineStatus status;
            ViewManager *viewManager;
            CoordinateSystem *origin;
            
            
            public:
            GraphicsEngineClass();
            
            ~GraphicsEngineClass();
            
            GraphicsEngineRetVal Create();
            
            GraphicsEngineRetVal SetViewManager(ViewManager *newViewManager);
            
            CoordinateSystem * GetOrigin();
            
            GraphicsEngineRetVal DrawScene();
            
            GraphicsEngineRetVal Destroy();
        };
    };
}

#endif //BLUEENGINE_GRAPHICSENGINE_H
