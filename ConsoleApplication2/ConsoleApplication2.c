#include <Windows.h>
#include <stdio.h>
#include <string.h>

#define SIZE_BUFFER 260
#define PATH L"C:/TestAPI/text.txt"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	int bool = 0;
	int counter = 0;
	int counter_spase = 0;
	float a, b, c;



	
	HANDLE hFile = CreateFile(PATH,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
		
	
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

	QuaEquation(a, b, c);
}

void QuaEquation(float a, float b , float c) {

	HANDLE hFile = CreateFile(PATH,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	char answer_text[300];
	DWORD bytes;
	int size = 0;

	float x1, x2, discriminant;
	discriminant = powf(b, 2.0) - 4 * a * c;
	if (discriminant <0 || a == 0) {

		WriteFile(hFile, "Решения нет", 11, &bytes, NULL);
		return 1;

	}

	if (discriminant == 0) {

		x1 = (-b) / (2 * a);
		sprintf(answer_text, "Дискриминант равен %f\nx1 = %f", discriminant, x1);
		while (answer_text[size] != 0) {

			size++;

		}

		WriteFile(hFile, answer_text, size, &bytes, NULL);

	}
	if (discriminant > 0) {

		x1 = ((-b) - sqrt(discriminant) / (2 * a));
		x2 = ((-b) + sqrt(discriminant) / (2 * a));

		sprintf(answer_text, "Дискриминант равен %f\nx1 = %f\nx2 = %f");
		while (answer_text[size] != 0) {

			size++;
		}
		WriteFile(hFile, answer_text, size, &bytes, NULL);

	}

}