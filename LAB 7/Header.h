#pragma once
#include <iostream>
#include <Windows.h>

typedef bool cyberbool;

void PrintNotifyInfo(PFILE_NOTIFY_INFORMATION pNotify);
char* FindCurrentDirectory(char* argv, char* directory);
void doSnapshot(char* directory);