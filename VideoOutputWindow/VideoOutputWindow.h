//
// Created by Mateusz on 2019-08-25.
//

#ifndef BLUEENGINE_VIDEOOUTPUTWINDOW_H
#define BLUEENGINE_VIDEOOUTPUTWINDOW_H

namespace MatWiecz
{
    namespace BlueEngine
    {
        typedef enum class VideoOutputWindowRetValEnum
        {
            Success,
            InvalidArgument,
            InvalidOperation,
            InvalidPixelFormat,
            OpenGLInitiationFailed,
            OpenGLContextSwitchFailed,
            OpenGLDestructionFailed
        } VideoOutputWindowRetVal;
        
        typedef enum class VideoOutputWindowAspectRatioEnum
        {
            Ratio16x9,
            Ratio4x3,
            Ratio16x10
        } VideoOutputWindowAspectRatio;
        
        typedef class VideoOutputWindowClass VideoOutputWindow;
    }
}

#include <windows.h>
#include <GL/gl.h>
#include "../Common/Basics/BitField.hpp"

namespace MatWiecz
{
    namespace BlueEngine
    {
        struct VideoOutputWindowStatusStruct {};
        typedef BitField <VideoOutputWindowStatusStruct>
            VideoOutputWindowStatus;
        const VideoOutputWindowStatus VideoOutputWindowCreated(
            BitFieldSymbols::Reset);
        
        
        class VideoOutputWindowClass
        {
            private:
            VideoOutputWindowStatus status;
            PIXELFORMATDESCRIPTOR pfd;
            HDC hDC;
            HGLRC hRC;
            int foundPixelFormat;
            VideoOutputWindowAspectRatio aspectRatio;
            int width;
            int height;
            
            public:
            
            VideoOutputWindowClass();
            
            ~VideoOutputWindowClass();
            
            VideoOutputWindowRetVal SetUpWindowAspectRatio(
                VideoOutputWindowAspectRatio newAspectRatio);
            
            VideoOutputWindowRetVal
            SetUpColorBuffer(unsigned char bitsPerPixel);
            
            VideoOutputWindowRetVal SetUpAccumulationBuffer(bool use);
            
            VideoOutputWindowRetVal
            SetUpZBuffer(unsigned char bitsPerPixel);
            
            VideoOutputWindowRetVal
            SetUpStencilBuffer(unsigned char bitsPerPixel);
            
            VideoOutputWindowRetVal Create(HDC handleToDeviceContext);
    
            bool IsCreated();
            
            double GetAspectRatio();
            
            VideoOutputWindowRetVal ResizeWindow(int newWidth, int newHeight);
    
            VideoOutputWindowRetVal UpdateFrame();
            
            VideoOutputWindowRetVal Destroy();
            
        };
    }
}

#endif //BLUEENGINE_VIDEOOUTPUTWINDOW_H
