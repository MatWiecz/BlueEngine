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
                return InvalidOperation;
            resolution = newResolution;
            return Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::SetUpColorBuffer(
            unsigned char bitsPerPixel)
        {
            if (int(status & VideoOutputWindowCreated))
                return InvalidOperation;
            if (bitsPerPixel != 8 &&
                bitsPerPixel != 16 &&
                bitsPerPixel != 24 &&
                bitsPerPixel != 32)
                return InvalidArgument;
            pfd.cColorBits = bitsPerPixel;
            if (pfd.cAccumBits != 0)
                pfd.cAccumBits = bitsPerPixel;
            return Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::SetUpAccumulationBuffer(
            bool use)
        {
            if (int(status & VideoOutputWindowCreated))
                return InvalidOperation;
            if (use)
                pfd.cAccumBits =
                    pfd.cColorBits;
            else
                pfd.cAccumBits = 0;
            return Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::SetUpZBuffer(
            unsigned char bitsPerPixel)
        {
            if (int(status & VideoOutputWindowCreated))
                return InvalidOperation;
            if (bitsPerPixel != 0 &&
                bitsPerPixel != 8 &&
                bitsPerPixel != 16 &&
                bitsPerPixel != 32)
                return InvalidArgument;
            pfd.cDepthBits = bitsPerPixel;
            return Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::SetUpStencilBuffer(
            unsigned char bitsPerPixel)
        {
            if (int(status & VideoOutputWindowCreated))
                return InvalidOperation;
            if (bitsPerPixel != 0 &&
                bitsPerPixel != 8 &&
                bitsPerPixel != 16 &&
                bitsPerPixel != 32)
                return InvalidArgument;
            pfd.cStencilBits = bitsPerPixel;
            return Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::Create(
            HDC handleToDeviceContext)
        {
            if (int(status & VideoOutputWindowCreated))
                return InvalidOperation;
            if (handleToDeviceContext == NULL)
                return InvalidArgument;
            hDC = handleToDeviceContext;
            foundPixelFormat = ChoosePixelFormat(hDC, &pfd);
            if (!SetPixelFormat(hDC, foundPixelFormat, &pfd))
                return InvalidPixelFormat;
            if ((hRC = wglCreateContext(hDC)) == NULL)
                OpenGLInitiationFailed;
            if (!wglMakeCurrent(hDC, hRC))
                return OpenGLContextSwitchFailed;
            status &= VideoOutputWindowCreated;
            return Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::ResizeWindow(
            int newWidth, int newHeight)
        {
            if (int(~status & VideoOutputWindowCreated))
                return InvalidOperation;
            if (newWidth == 0 || newHeight == 0)
                return InvalidArgument;
            width = newWidth;
            height = newHeight;
            int xUnits = 16;
            int yUnits = 9;
            switch (resolution)
            {
                case Res4x3:
                    xUnits = 4;
                    yUnits = 3;
                    break;
                case Res16x10:
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
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            return Success;
        }
        
        VideoOutputWindowRetVal VideoOutputWindowClass::Destroy()
        {
            if (int(~status & VideoOutputWindowCreated))
                return InvalidOperation;
            status &= ~VideoOutputWindowCreated;
            if (!wglMakeCurrent(hDC, NULL))
                return OpenGLContextSwitchFailed;
            if (!wglDeleteContext(hRC))
                return OpenGLDestructionFailed;
            return Success;
        }
    }
}
