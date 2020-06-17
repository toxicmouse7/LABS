#pragma once
#include <iostream>
#include <Windows.h>

void PrintNotifyInfo(PFILE_NOTIFY_INFORMATION pNotify);
char* FindCurrentDirectory(char* argv, char* directory);