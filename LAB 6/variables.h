#pragma once
int a;
static int x = 85;

int CheckNewPosition(COORD* pos);
void changPos(COORD* Pos, int step);
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam);
