//
// Created by Mateusz on 2019-08-26.
//

#ifndef BLUEENGINE_VIEWMANAGER_H
#define BLUEENGINE_VIEWMANAGER_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef enum class ViewManagerRetValEnum
        {
            Success,
            InvalidArgument,
            InvalidOperation,
            CameraAlreadyRegistered,
            CameraAlreadyInUse
        } ViewManagerRetVal;
        
        typedef class ViewManagerClass ViewManager;
    }
}

#include "../../../../Common/Basics/BitField.hpp"
#include "../../ObjectClasses/Camera/Camera.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        struct VideoManagerStatusStruct {};
        typedef BitField <VideoManagerStatusStruct> VideoManagerStatus;
        const VideoManagerStatus ViewManagerCreated;
        const VideoManagerStatus VideoManagerInUse;
        
        class ViewManagerClass
        {
            private:
            VideoManagerStatus status;
            std::vector <std::pair <unsigned int, Camera *>> cameras;
            Camera *activeCamera;
            unsigned int nextCameraId;
            bool toUpdate;
            //TODO: What if the Camera's object will be destroyed suddenly?
            
            public:
            ViewManagerClass();
            
            ~ViewManagerClass();
            
            ViewManagerRetVal Create();
            
            bool IsCreated ();
            
            ViewManagerRetVal RegisterCamera(Camera *camera,
                                             unsigned int *retCameraId);
            
            ViewManagerRetVal ActivateCamera(unsigned int retCameraId);
            
            ViewManagerRetVal UnregisterCamera(unsigned int retCameraId);
            
            ViewManagerRetVal UpdateProjection(double aspect);
    
            ViewManagerRetVal PerformViewTransformation();
            
            ViewManagerRetVal Destroy();
            
        };
    };
}

#endif //BLUEENGINE_VIEWMANAGER_H
