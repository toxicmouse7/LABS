#include <iostream>
#include <Windows.h>

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
    //wcout << pNotify->Action << ". " << szwFileName << endl;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
	DWORD dwWaitStatus;
    HANDLE hDir = CreateFileA(argv[1], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);
    OVERLAPPED o = {};
    o.hEvent = CreateEvent(0, FALSE, FALSE, 0);
    DWORD nBufferLength = 60 * 1024;
    BYTE* lpBuffer = new BYTE[nBufferLength];

	while (true)
	{
        DWORD returnedBytes = 0;
        ReadDirectoryChangesW(hDir, lpBuffer, nBufferLength, FALSE,
            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_SIZE,
            &returnedBytes, &o, 0);
        dwWaitStatus = WaitForSingleObject(o.hEvent, INFINITE);

        switch (dwWaitStatus)
        {
        case WAIT_OBJECT_0:
        {
            DWORD seek = 0;
            while (seek < nBufferLength)
            {
                PFILE_NOTIFY_INFORMATION pNotify = PFILE_NOTIFY_INFORMATION(lpBuffer + seek);
                seek += pNotify->NextEntryOffset;

                PrintNotifyInfo(pNotify);

                if (pNotify->NextEntryOffset == 0)
                    break;
            }
            break;
        }
        case WAIT_TIMEOUT:
        {
            printf("\nNo changes in the timeout period.\n");
            break;
        }
        default: break;
        }
	}

    CloseHandle(o.hEvent);
    delete[] lpBuffer;
}