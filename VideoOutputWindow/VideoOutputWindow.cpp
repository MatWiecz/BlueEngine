//
// Created by Mateusz on 2019-08-25.
//

#include "VideoOutputWindow.h"

namespace MatWiecz
{
    namespace BlueEngine
    {
        VideoOutputWindowClass::VideoOutputWindowClass()
        {
            static PIXELFORMATDESCRIPTOR tempPixelFormatDescriptor {
                sizeof(PIXELFORMATDESCRIPTOR),
                1,
                PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                PFD_TYPE_RGBA,
                32,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,
                16,
                0,
                0,
                PFD_MAIN_PLANE,
                0, 0, 0, 0};
            pfd = tempPixelFormatDescriptor;
            foundPixelFormat = 0;
        }
        
        VideoOutputWindowClass::~VideoOutputWindowClass()
        {
            Destroy();
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::SetUpWindowResolution(
            VideoOutputWindowResolution newResolution)
        {
            if (int(status & VideoOutputWindowCreated))
                return VideoOutputWindowRetVal::InvalidOperation;
            resolution = newResolution;
            return VideoOutputWindowRetVal::Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::SetUpColorBuffer(
            unsigned char bitsPerPixel)
        {
            if (int(status & VideoOutputWindowCreated))
                return VideoOutputWindowRetVal::InvalidOperation;
            if (bitsPerPixel != 8 &&
                bitsPerPixel != 16 &&
                bitsPerPixel != 24 &&
                bitsPerPixel != 32)
                return VideoOutputWindowRetVal::InvalidArgument;
            pfd.cColorBits = bitsPerPixel;
            if (pfd.cAccumBits != 0)
                pfd.cAccumBits = bitsPerPixel;
            return VideoOutputWindowRetVal::Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::SetUpAccumulationBuffer(
            bool use)
        {
            if (int(status & VideoOutputWindowCreated))
                return VideoOutputWindowRetVal::InvalidOperation;
            if (use)
                pfd.cAccumBits =
                    pfd.cColorBits;
            else
                pfd.cAccumBits = 0;
            return VideoOutputWindowRetVal::Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::SetUpZBuffer(
            unsigned char bitsPerPixel)
        {
            if (int(status & VideoOutputWindowCreated))
                return VideoOutputWindowRetVal::InvalidOperation;
            if (bitsPerPixel != 0 &&
                bitsPerPixel != 8 &&
                bitsPerPixel != 16 &&
                bitsPerPixel != 32)
                return VideoOutputWindowRetVal::InvalidArgument;
            pfd.cDepthBits = bitsPerPixel;
            return VideoOutputWindowRetVal::Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::SetUpStencilBuffer(
            unsigned char bitsPerPixel)
        {
            if (int(status & VideoOutputWindowCreated))
                return VideoOutputWindowRetVal::InvalidOperation;
            if (bitsPerPixel != 0 &&
                bitsPerPixel != 8 &&
                bitsPerPixel != 16 &&
                bitsPerPixel != 32)
                return VideoOutputWindowRetVal::InvalidArgument;
            pfd.cStencilBits = bitsPerPixel;
            return VideoOutputWindowRetVal::Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::Create(
            HDC handleToDeviceContext)
        {
            if (int(status & VideoOutputWindowCreated))
                return VideoOutputWindowRetVal::InvalidOperation;
            if (handleToDeviceContext == NULL)
                return VideoOutputWindowRetVal::InvalidArgument;
            hDC = handleToDeviceContext;
            foundPixelFormat = ChoosePixelFormat(hDC, &pfd);
            if (!SetPixelFormat(hDC, foundPixelFormat, &pfd))
                return VideoOutputWindowRetVal::InvalidPixelFormat;
            if ((hRC = wglCreateContext(hDC)) == NULL)
                VideoOutputWindowRetVal::OpenGLInitiationFailed;
            if (!wglMakeCurrent(hDC, hRC))
                return VideoOutputWindowRetVal::OpenGLContextSwitchFailed;
            status |= VideoOutputWindowCreated;
            return VideoOutputWindowRetVal::Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::ResizeWindow(
            int newWidth, int newHeight)
        {
            if (int(~status & VideoOutputWindowCreated))
                return VideoOutputWindowRetVal::InvalidOperation;
            if (newWidth == 0 || newHeight == 0)
                return VideoOutputWindowRetVal::InvalidArgument;
            width = newWidth;
            height = newHeight;
            int xUnits = 16;
            int yUnits = 9;
            switch (resolution)
            {
                case VideoOutputWindowResolution::Res4x3:
                    xUnits = 4;
                    yUnits = 3;
                    break;
                case VideoOutputWindowResolution::Res16x10:
                    xUnits = 16;
                    yUnits = 10;
                    break;
                default:
                    break;
            }
            int tempHeight = width * yUnits / xUnits;
            if (tempHeight <= height)
                glViewport(0, (height - tempHeight)/2, width, tempHeight);
            else
            {
                int tempWidth = height * xUnits / yUnits;
                glViewport((width - tempWidth)/2, 0, tempWidth, height);
            }
            
            return VideoOutputWindowRetVal::Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::Destroy()
        {
            if (int(~status & VideoOutputWindowCreated))
                return VideoOutputWindowRetVal::InvalidOperation;
            status = VideoOutputWindowStatus(0);
            if (!wglMakeCurrent(hDC, NULL))
                return VideoOutputWindowRetVal::OpenGLContextSwitchFailed;
            if (!wglDeleteContext(hRC))
                return VideoOutputWindowRetVal::OpenGLDestructionFailed;
            return VideoOutputWindowRetVal::Success;
        }
    }
}
