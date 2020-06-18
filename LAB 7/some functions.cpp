#ifndef INC
#define INC
#include "Header.h"
#endif

using namespace std;

void PrintNotifyInfo(PFILE_NOTIFY_INFORMATION pNotify)
{
    WCHAR szwFileName[MAX_PATH];
    ULONG ulCount = min(pNotify->FileNameLength / 2, MAX_PATH - 1);
    wcsncpy_s(szwFileName, pNotify->FileName, ulCount);
    szwFileName[ulCount] = L'\0';
    switch (pNotify->Action)
    {
    case FILE_ACTION_ADDED:
    {
        wcout << L"Created \"" << szwFileName << "\"" << endl;
        break;
    }
    case FILE_ACTION_REMOVED:
    {
        wcout << L"Removed \"" << szwFileName << "\"" << endl;
        break;
    }
    case FILE_ACTION_MODIFIED:
    {
        wcout << L"Modified \"" << szwFileName << "\"" << endl;
        break;
    }
    case FILE_ACTION_RENAMED_OLD_NAME:
    {
        wcout << L"Old Name \"" << szwFileName << "\"" << endl;
        break;
    }
    case FILE_ACTION_RENAMED_NEW_NAME:
    {
        wcout << L"New name \"" << szwFileName << "\"" << endl;
        break;
    }
    }
}

void doSnapshot(char* directory)
{
    WIN32_FIND_DATAA FindFileData;
    FILETIME filetime;
    SYSTEMTIME systime;
	HANDLE hf;
    int pos = strlen(directory);
    directory[pos] = '\\';
    directory[pos+1] = '*';
    directory[pos + 2] = '\0';

	hf = FindFirstFileA(directory, &FindFileData);

    if (hf != INVALID_HANDLE_VALUE)
    {
        do
        {
            FileTimeToSystemTime(&FindFileData.ftLastWriteTime, &systime);
            //FileTimeToLocalFileTime(FindFileData.ftLastWriteTime, &)
            cout << FindFileData.cFileName << " " << FindFileData.nFileSizeLow << " bytes, last access: " <<systime.wHour << ":" << systime.wMinute << ":" << systime.wSecond << endl;

        } while (FindNextFileA(hf, &FindFileData) != 0);
        FindClose(hf);
    }
    else cout << "An error has accured" << GetLastError() << endl;

    directory[pos] = '\0';
}

char* FindCurrentDirectory(char* argv, char* directory)
{
    int i = strlen(argv) - 1;
    while (argv[i] != '\\')
        i--;
    directory = new char[i];
    for (int j = 0; j < i + 1; j++)
        directory[j] = argv[j];
    directory[i] = '\0';

    return directory;
}