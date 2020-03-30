//
// Created by Mateusz on 2019-08-25.
//

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "../../BlueEngineHeader.h"
#include "../../Engine/GraphicEngine/ObjectClasses/CoordinateSystem/AdvancedCoordinateSystem/AdvancedCoordinateSystem.h"
#include "../../Common/Maths/Matrices/Matrix.hpp"

using namespace MatWiecz::BlueEngine;

Engine blueEngine;
GraphicsEngine graphicsEngine;
VideoOutputWindow videoOutputWindow;
ViewManager viewManager;
Camera camera;
Camera tempCamera;
unsigned int cameraId;
CoordinateSystem *worldOrigin;
AdvancedCoordinateSystem extraCoordinateSystem;
Matrix <float, 4, 2> aMatrix;
Matrix <float, 2, 3> bMatrix;
Matrix <float, 4, 3> cMatrix;

void CameraAngleFunction(float angle[3])
{
    angle[1] += 0.1f;
    (aMatrix * bMatrix) + -cMatrix;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hDC;
    int width, height;
    switch (message)
    {
        case WM_CREATE:
            hDC = GetDC(hwnd);
            videoOutputWindow.Create(hDC);
            viewManager.Create();
            graphicsEngine.Create();
            graphicsEngine.SetVideoOutputWindow(&videoOutputWindow);
            graphicsEngine.SetViewManager(&viewManager);
            graphicsEngine.SetDefaultColorValues(0.0f, 0.0f, 0.0f, 0.0f);
            blueEngine.Create();
            blueEngine.SetGraphicsEngine(&graphicsEngine);
            blueEngine.Start();
            worldOrigin = graphicsEngine.GetOrigin();
            //worldOrigin->UpdateFlags(BaseObjectClassUpdateFlagsMode::SetFlags,
            //                         ObjectTextured);
            camera.CreateCamera(worldOrigin, "Main camera").SetXPos(10)
                  .SetYPos(10).SetZPos(100).SetAngleFunction(CameraAngleFunction);
            //camera.SetUpPerspectiveCamera(45.0, 1.0, 1000000.0f);
            tempCamera.CreateCamera(worldOrigin, "Temp camera").SetXPos(10)
                      .SetYPos(10).SetZPos(10);
            viewManager.RegisterCamera(&camera, &cameraId);
            viewManager.ActivateCamera(cameraId);
            extraCoordinateSystem.CreateAdvancedCoordinateSystem(
                worldOrigin, "Extra");
            return 0;
        
        case WM_CLOSE:
            viewManager.UnregisterCamera(cameraId);
            tempCamera.Destroy();
            camera.Destroy();
            blueEngine.Stop();
            blueEngine.Destroy();
            graphicsEngine.Destroy();
            viewManager.Destroy();
            videoOutputWindow.Destroy();
            PostQuitMessage(0);
            return 0;
        
        case WM_SIZE:
            width = LOWORD(lParam);
            height = HIWORD(lParam);
            videoOutputWindow.ResizeWindow(width, height);
            return 0;
        
        default:
            break;
    }
    return DefWindowProcA(hwnd, message, wParam, lParam);
}


// punkt, w którym rozpoczyna się wykonywanie aplikacji
int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
        int nShowCmd)
{
    WNDCLASSEX windowClass;        // klasa okna
    HWND hwnd;            // uchwyt okna
    MSG msg;                // komunikat
    bool done;            // znacznik zakończenia aplikacji
    DWORD dwExStyle;                        // rozszerzony styl okna
    DWORD dwStyle;                        // styl okna
    RECT windowRect;
    
    // zmienne pomocnicze
    int width = 800;
    int height = 600;
    int bits = 32;
    
    //fullScreen = TRUE;
    
    windowRect.left =
        (long) 0;                        // struktura określająca rozmiary okna
    windowRect.right = (long) width;
    windowRect.top = (long) 0;
    windowRect.bottom = (long) height;
    
    // definicja klasy okna
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);    // domyślna ikona
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);        // domyślny kursor
    windowClass.hbrBackground = NULL;                                // bez tła
    windowClass.lpszMenuName = NULL;                                // bez menu
    windowClass.lpszClassName = "MojaKlasa";
    windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);        // logo Windows
    
    // rejestruje klasę okna
    if (!RegisterClassEx(&windowClass))
        return 0;
    
    
    dwExStyle =
        WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;            // definicja klasy okna
    dwStyle = WS_OVERLAPPEDWINDOW;                    // styl okna
    
    AdjustWindowRectEx(&windowRect, dwStyle, FALSE,
                       dwExStyle);        // koryguje rozmiar okna
    
    // tworzy okno
    hwnd = CreateWindowEx(
        NULL,                                    // rozszerzony styl okna
        "MojaKlasa",                            // nazwa klasy
        "Research",        // nazwa aplikacji
        dwStyle | WS_CLIPCHILDREN |
        WS_CLIPSIBLINGS,
        0, 0,                                // współrzędne x,y
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top, // szerokość, wysokość
        NULL,                                    // uchwyt okna nadrzędnego
        NULL,                                    // uchwyt menu
        hInstance,                            // instancja aplikacji
        NULL);                                // bez dodatkowych parametrów
    
    // sprawdza, czy utworzenie okna nie powiodło się (wtedy wartość hwnd równa NULL)
    if (!hwnd)
        return 0;
    
    ShowWindow(hwnd, SW_SHOW);            // wyświetla okno
    UpdateWindow(hwnd);                    // aktualizuje okno
    
    done = false;                        // inicjuje zmienną warunku pętli
    
    // pętla przetwarzania komunikatów
    while (!done)
    {
        PeekMessage(&msg, hwnd, NULL, NULL, PM_REMOVE);
        
        if (msg.message ==
            WM_QUIT)        // aplikacja otrzymała komunikat WM_QUIT?
        {
            done = true;                // jeśli tak, to kończy działanie
        }
        else
        {
            blueEngine.MessageProcessingLoop();
            
            TranslateMessage(
                &msg);        // tłumaczy komunikat i wysyła do systemu
            DispatchMessage(&msg);
        }
    }
    
    return msg.wParam;
}