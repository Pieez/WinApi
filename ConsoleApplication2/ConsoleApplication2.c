#include <Windows.h>
#include <stdio.h>
#include <string.h>

#define SIZE_BUFFER 260
#define PATH L"C:/TestAPI/text.txt"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	
	HANDLE hFile = CreateFile(PATH,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL

	);
		
	
	OVERLAPPED olf = { 0 };

	LARGE_INTEGER li = { 0 };

	li.QuadPart = 1;
	olf.Offset = li.LowPart;
	olf.OffsetHigh = li.HighPart;

	LPSTR buffer = (CHAR*)calloc(SIZE_BUFFER + 1, sizeof(CHAR));
	DWORD iNumRead = 0;

	if (!ReadFile(hFile, buffer, SIZE_BUFFER, &iNumRead, &olf))
		return 1;
	if (olf.Internal == -1 && GetLastError())
		return 2;

	olf.Offset += iNumRead;

	LPCSTR str = " test message...\r\n";
	DWORD iNumWrite = 0;
	if (!WriteFile(hFile, str, strlen(str), &iNumWrite, &olf))
		return 3;
	if (olf.Internal == -1 && GetLastError())
		return 4;


	CloseHandle(hFile);
	return 0;
}

void SaveData(LPSTR args) {




}