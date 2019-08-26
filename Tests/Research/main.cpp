//
// Created by Mateusz on 2019-08-25.
//

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   return DefWindowProcA(hwnd, message, wParam, lParam);
}

int main()
{
    return 0;
}