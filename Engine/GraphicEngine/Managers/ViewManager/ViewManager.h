//
// Created by Mateusz on 2019-08-26.
//

#ifndef BLUEENGINE_VIEWMANAGER_H
#define BLUEENGINE_VIEWMANAGER_H

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
        
        typedef enum ViewManagerRetValEnum
        {
            Success,
            InvalidArgument
        
        } ViewManagerRetVal;
        
        typedef class ViewManagerClass
        {
            private:
            VideoManagerStatus status;
            std::vector <std::pair<unsigned int, Camera *>> cameras;
            unsigned int activeCamera;
            unsigned int nextCameraId;
            
            public:
            ViewManagerClass();
            ~ViewManagerClass() = default;
            ViewManagerRetVal Create();
            ViewManagerRetVal Destroy();
            ViewManagerRetVal AddCamera ();
            ViewManagerRetVal ActivateCamera();
            ViewManagerRetVal DeleteCamera ();
            ViewManagerRetVal UpdateProjection();
            
        } ViewManager;
    };
}

#endif //BLUEENGINE_VIEWMANAGER_H
