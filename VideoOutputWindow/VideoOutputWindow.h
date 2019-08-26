//
// Created by Mateusz on 2019-08-25.
//

#ifndef BLUEENGINE_VIDEOOUTPUTWINDOW_H
#define BLUEENGINE_VIDEOOUTPUTWINDOW_H

#include <windows.h>
#include <GL/glu.h>
#include "../Common/Basics/BitField.hpp"

namespace MatWiecz
{
    namespace BlueEngine
    {
        struct VideoOutputWindowStatusStruct {};
        typedef BitField <VideoOutputWindowStatusStruct>
            VideoOutputWindowStatus;
        const VideoOutputWindowStatus VideoOutputWindowCreated;
        
        typedef enum VideoOutputWindowRetValEnum
        {
            Success,
            InvalidArgument,
            InvalidOperation,
            InvalidPixelFormat,
            OpenGLInitiationFailed,
            OpenGLContextSwitchFailed,
            OpenGLDestructionFailed
        } VideoOutputWindowRetVal;
        
        typedef enum VideoOutputWindowResolutionEnum
        {
            Res16x9,
            Res4x3,
            Res16x10
        } VideoOutputWindowResolution;
        
        typedef class VideoOutputWindowClass
        {
            private:
            VideoOutputWindowStatus status;
            PIXELFORMATDESCRIPTOR pfd;
            HDC hDC;
            HGLRC hRC;
            int foundPixelFormat;
            VideoOutputWindowResolution resolution;
            int width;
            int height;
            
            public:
            
            VideoOutputWindowClass();
            
            ~VideoOutputWindowClass();
            
            VideoOutputWindowRetVal SetUpWindowResolution (
                VideoOutputWindowResolution newResolution);
            
            VideoOutputWindowRetVal
            SetUpColorBuffer(unsigned char bitsPerPixel);
            
            VideoOutputWindowRetVal SetUpAccumulationBuffer(bool use);
            
            VideoOutputWindowRetVal
            SetUpZBuffer(unsigned char bitsPerPixel);
            
            VideoOutputWindowRetVal
            SetUpStencilBuffer(unsigned char bitsPerPixel);
            
            VideoOutputWindowRetVal Create(HDC handleToDeviceContext);
            
            VideoOutputWindowRetVal ResizeWindow (int newWidth, int newHeight);
            
            VideoOutputWindowRetVal Destroy();
            
        } VideoOutputWindow;
    }
}

#endif //BLUEENGINE_VIDEOOUTPUTWINDOW_H
