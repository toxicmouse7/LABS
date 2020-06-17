#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "variables.h"
#include <time.h>

HWND hEdit; // дискриптор для дочернего окна

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
    MoveToEx(hdc, x1, y1, NULL); //сделать текущими координаты x1, y1
    return LineTo(hdc, x2, y2);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    srand(time(NULL));
    HWND hwnd;
    HWND hButton;
    HMENU hMenu = 1;
    MSG msg;
    WNDCLASS w;
    memset(&w, 0, sizeof(WNDCLASS));
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance;
    w.hbrBackground = CreateSolidBrush(0x00FFFFFF);
    w.lpszClassName = L"MyClass";
    RegisterClass(&w);

    hwnd = CreateWindow(L"MyClass", L"LAB 6", WS_OVERLAPPEDWINDOW, 500, 300, 500, 500, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    hEdit = CreateWindow(L"Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 110, 1, 60, 20, hwnd, NULL, hInstance, 0); // создние дочернего окна
    ShowWindow(hEdit, SW_SHOWNORMAL);
    UpdateWindow(hEdit);// отображение окна 

    hButton = CreateWindow(L"Button", L"Draw field", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 2, 25, 120, 30, hwnd, hMenu, hInstance, NULL);


    // бесконечный цикл обработки событий	
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
    HDC hdc;
    PAINTSTRUCT ps;
switch (Message)
{
case WM_CREATE:
{

    break;
}
case WM_COMMAND:
{
    if (LOWORD(wparam) == 1)
    {
        const RECT ReRect = { 100, 100, 200, 200 };
        InvalidateRect(hwnd, &ReRect, FALSE);
        UpdateWindow(hwnd);
    }
    break;
}
case WM_PAINT:
{
    hdc = BeginPaint(hwnd, &ps);
    TextOut(hdc, 5, 3, L"Type number: ", 14);
    TextOut(hdc, 5, 80, L"Result: ", 9);
    HPEN hPen; //Объявляется кисть
    hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); //Создаётся объект
    SelectObject(hdc, hPen); //Объект делается текущим
    Line(hdc, 100, 100, 200, 200);
    hdc = EndPaint(hwnd, &ps);
    break;
}
case WM_DESTROY: // закрытие окна
{
    PostQuitMessage(0);
    break;
}
default: // обработка сообщения по умолчанию
    return DefWindowProc(hwnd, Message, wparam, lparam);
}
return 0;
}