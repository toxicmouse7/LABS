#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "variables.h"

HWND hEdit; // дискриптор для дочернего окна
HWND** m;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
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
    hButton = CreateWindow(L"Button", L"Draw field", WS_CHILD | WS_VISIBLE | WS_BORDER, 2, 25, 120, 30, hwnd, hMenu, hInstance, NULL);

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
    switch (LOWORD(wparam))
    {
    case 1:
    {
        int Len;
        wchar_t StrA[20];
        Len = GetWindowText(hEdit, StrA, 20);
        a = _wtoi(StrA);

        m = (HWND**)malloc(a * sizeof(HWND*));
        for (int i = 0; i < a; i++)
            m[i] = (HWND*)malloc(a * sizeof(HWND));

        for (int i = 0; i < a; i++)
        {
            for (int j = 0; j < a; j++)
                m[i][j] = CreateWindow(L"Static", NULL, WS_EX_CLIENTEDGE | WS_CHILD | WS_VISIBLE,
                    x + 10 * i, 78 + 13 * j, 10, 13, hwnd, 0, hwnd, NULL);
        }

        HBRUSH WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        SetClassLongW(hwnd, GCLP_HBRBACKGROUND, (LONG)WhiteBrush);

        COORD StartPos;

        int ans = a * a + 1;
        int kol = 0;
        for (int i = 0; i < a; i++)
            for (int j = 0; j < a; j++)
               // SetWindowText(m[i][j], L"*");
        StartPos.X = rand() % a;
        StartPos.Y = rand() % a;
        SetWindowText(m[StartPos.X][StartPos.Y], L" ");
        while (kol < ans)
        {
            int step = rand() % 4 + 1;
            changPos(&StartPos, step);
            SetWindowText(m[StartPos.X][StartPos.Y], L" ");

            kol++;
        }
        MessageBox(hwnd, L"Reset fild", L"Task", MB_OK);


        for (int i = 0; i < a; i++)
            free(m[i]);
        free(m);
        
        break;
    }
    }
    break;
}
case WM_PAINT:
{
    hdc = BeginPaint(hwnd, &ps);
    TextOut(hdc, 5, 3, L"Type number: ", 14);
    TextOut(hdc, 5, 80, L"Result: ", 9);
    EndPaint(hwnd, &ps);
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