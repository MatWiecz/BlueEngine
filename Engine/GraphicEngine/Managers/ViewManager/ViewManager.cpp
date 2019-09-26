//
// Created by Mateusz on 2019-08-26.
//

#include "ViewManager.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        ViewManagerClass::ViewManagerClass(): status(0),
                                              activeCameraId(0),
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
                || !camera->IsCreated())
                return ViewManagerRetVal::InvalidArgument;
            for (auto &record : cameras)
                if (record.second->GetObjectId() == camera->GetObjectId())
                    return ViewManagerRetVal::CameraAlreadyRegistered;
            cameras[nextCameraId] = camera;
            *retCameraId = nextCameraId++;
            return ViewManagerRetVal::Success;
        }
        
        ViewManagerRetVal ViewManagerClass::ActivateCamera(
            unsigned int cameraId)
        {
            if (int(~status & ViewManagerCreated))
                return ViewManagerRetVal::InvalidOperation;
            if (cameraId == 0)
            {
                activeCameraId = 0;
                return ViewManagerRetVal::Success;
            }
            auto foundCameraRecord = cameras.find(cameraId);
            if (foundCameraRecord != cameras.end())
            {
                activeCameraId = cameraId;
                toUpdate = true;
                return ViewManagerRetVal::Success;
            }
            return ViewManagerRetVal::InvalidArgument;
        }
        
        ViewManagerRetVal ViewManagerClass::UnregisterCamera(
            unsigned int cameraId)
        {
            if (int(~status & ViewManagerCreated))
                return ViewManagerRetVal::InvalidOperation;
            if (cameraId == activeCameraId)
                return ViewManagerRetVal::CameraAlreadyInUse;
            auto foundCameraRecord = cameras.find(cameraId);
            if (foundCameraRecord != cameras.end())
            {
                cameras.erase(foundCameraRecord);
                return ViewManagerRetVal::Success;
            }
            return ViewManagerRetVal::InvalidArgument;
        }
        
        ViewManagerRetVal ViewManagerClass::UpdateProjection(
            double aspect)
        {
            if (int(~status & ViewManagerCreated) || activeCameraId == 0)
                return ViewManagerRetVal::InvalidOperation;
            if (toUpdate)
            {
                toUpdate = false;
                if (cameras[activeCameraId]->UpdateProjection(aspect) !=
                    BaseObjectClassRetVal::Success)
                {
                    unsigned int lastActiveCamera = activeCameraId;
                    activeCameraId = 0;
                    UnregisterCamera(lastActiveCamera);
                    return ViewManagerRetVal::InvalidOperation;
                }
            }
            return ViewManagerRetVal::Success;
        }
        
        ViewManagerRetVal ViewManagerClass::PerformViewTransformation()
        {
            if (int(~status & ViewManagerCreated) || activeCameraId == 0)
                return ViewManagerRetVal::InvalidOperation;
            if (cameras[activeCameraId]->PerformViewTransformation() !=
                BaseObjectClassRetVal::Success)
            {
                unsigned int lastActiveCamera = activeCameraId;
                activeCameraId = 0;
                UnregisterCamera(lastActiveCamera);
                return ViewManagerRetVal::InvalidOperation;
            }
            return ViewManagerRetVal::Success;
        }
        
        ViewManagerRetVal ViewManagerClass::Destroy()
        {
            if (int(~status & ViewManagerCreated))
                return ViewManagerRetVal::InvalidOperation;
            status = VideoManagerStatus(0);
            cameras.clear();
            activeCameraId = 0;
            nextCameraId = 1;
            toUpdate = false;
            return ViewManagerRetVal::Success;
        }
    }
}
