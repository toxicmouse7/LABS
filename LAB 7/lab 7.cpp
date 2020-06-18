#ifndef INC
#define INC
#include "Header.h"
#endif

using namespace std;

int main(int argc, char* argv[])
{
    char* directory = nullptr;
    setlocale(LC_ALL, "Russian");
	DWORD dwWaitStatus;
    if (argc < 2)
       directory = FindCurrentDirectory(argv[0], directory);
    else directory = argv[1];
    doSnapshot(directory);
    HANDLE hDir = CreateFileA((LPCSTR)directory, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);

    if (hDir == INVALID_HANDLE_VALUE)
    {
        cout << "Directory you are searching for doesn't exists" << endl;
        exit(1);
    }

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
                Sleep(1000);
                system("cls");
                doSnapshot(directory);

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
    return 0;
}