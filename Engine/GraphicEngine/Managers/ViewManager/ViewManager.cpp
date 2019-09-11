//
// Created by Mateusz on 2019-08-26.
//

#include "ViewManager.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        ViewManagerClass::ViewManagerClass(): status(0),
                                              activeCamera(nullptr),
                                              nextCameraId(1),
                                              toUpdate(false)
        {
        }
    
        ViewManagerClass::~ViewManagerClass()
        {
            Destroy();
        }
        
        ViewManagerRetVal ViewManagerClass::Create()
        {
            status |= ViewManagerCreated;
            return ViewManagerRetVal::Success;
        }
    
        bool ViewManagerClass::IsCreated()
        {
            return bool(int(status & ViewManagerCreated));
        }
        
        ViewManagerRetVal ViewManagerClass::RegisterCamera(Camera *camera,
                                                           unsigned int *retCameraId)
        {
            if (int(~status & ViewManagerCreated))
                return ViewManagerRetVal::InvalidOperation;
            if (camera == nullptr || retCameraId == nullptr
                || camera->IsCreated())
                return ViewManagerRetVal::InvalidArgument;
            for (auto &record : cameras)
                if (record.second->GetObjectId() == camera->GetObjectId())
                    return ViewManagerRetVal::CameraAlreadyRegistered;
            cameras.push_back(std::pair <unsigned int, Camera *>(nextCameraId,
                                                                 camera));
            *retCameraId = nextCameraId++;
            return ViewManagerRetVal::Success;
        }
        
        ViewManagerRetVal ViewManagerClass::ActivateCamera(
            unsigned int retCameraId)
        {
            if (int(~status & ViewManagerCreated))
                return ViewManagerRetVal::InvalidOperation;
            for (auto &record : cameras)
                if (record.first == retCameraId)
                {
                    activeCamera = record.second;
                    return ViewManagerRetVal::Success;
                }
            toUpdate = true;
            return ViewManagerRetVal::InvalidArgument;
        }
        
        ViewManagerRetVal ViewManagerClass::UnregisterCamera(
            unsigned int retCameraId)
        {
            if (int(~status & ViewManagerCreated))
                return ViewManagerRetVal::InvalidOperation;
            auto recordIter = std::begin(cameras);
            while (recordIter != std::end(cameras))
            {
                if (recordIter->first == retCameraId)
                {
                    if (recordIter->second == activeCamera)
                        return ViewManagerRetVal::CameraAlreadyInUse;
                    cameras.erase(recordIter);
                    return ViewManagerRetVal::Success;
                }
                recordIter++;
            }
            return ViewManagerRetVal::InvalidArgument;
        }
        
        ViewManagerRetVal ViewManagerClass::UpdateProjection(
            double aspect)
        {
            if (int(~status & ViewManagerCreated) || activeCamera == nullptr)
                return ViewManagerRetVal::InvalidOperation;
            if(toUpdate)
            {
                activeCamera->UpdateProjection(aspect);
                toUpdate = false;
            }
            return ViewManagerRetVal::Success;
        }
    
        ViewManagerRetVal ViewManagerClass::PerformViewTransformation()
        {
            if (int(~status & ViewManagerCreated) || activeCamera == nullptr)
                return ViewManagerRetVal::InvalidOperation;
            activeCamera->PerformViewTransformation();
            return ViewManagerRetVal::Success;
        }
        
        ViewManagerRetVal ViewManagerClass::Destroy()
        {
            if (int(~status & ViewManagerCreated))
                return ViewManagerRetVal::InvalidOperation;
            status = VideoManagerStatus(0);
            cameras.clear();
            activeCamera = nullptr;
            nextCameraId = 1;
            toUpdate = false;
            return ViewManagerRetVal::Success;
        }
    }
}
