#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define SIZE_BUFFER 260
#define PATH L"1.txt"
#define PATH_OUT L"2.txt"


int QuaEquation(float a, float b, float c, float* discriminant, float* x1, float* x2) {
	*discriminant = b * b - 4 * a * c;
	float aa = a + a;
	if (*discriminant == 0) {
		*x2 = *x1 = (-b) / aa;
		return 0;
	}
	if (*discriminant > 0) {
		float sqrtdiscr = sqrt(*discriminant);
		*x1 = ((-b) - sqrtdiscr) / aa;
		*x2 = ((-b) + sqrtdiscr) / aa;
		return 1;
	}
	return -1;
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

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

	char* buffer = (char*)calloc(SIZE_BUFFER + 1, sizeof(char));
	DWORD iNumRead = 0;

	SetFilePointer(hFile, 0, 0, FILE_BEGIN);

	if (!ReadFile(hFile, buffer, SIZE_BUFFER, &iNumRead, &olf))
		return 1;
	if (olf.Internal == -1 && GetLastError())
		return 2;

	olf.Offset += iNumRead;

	CloseHandle(hFile);

	hFile = CreateFile(PATH_OUT,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS | TRUNCATE_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	char answer_text[300];
	DWORD bytes;
	int size = 0;

	int q = sscanf(buffer, "%f %f %f", &a, &b, &c);
	if (q == 3) {
		float x1, x2, d;
		int r = QuaEquation(a, b, c, &d, &x1, &x2);
		switch (r) {
		case 0:
			sprintf(answer_text, "Дискриминант равен %f\nx1 = %f", d, x1);
			while (answer_text[size] != 0) {
				size++;
			}
			WriteFile(hFile, answer_text, size, &bytes, NULL);
			break;
		case 1:
			sprintf(answer_text, "Дискриминант равен %f\r\nx1 = %f\r\nx2 = %f", d, x1, x2);
			while (answer_text[size] != 0) {

				size++;
			}
			WriteFile(hFile, answer_text, size, &bytes, NULL);
			break;
		case -1:
			WriteFile(hFile, "Решения нет", 11, &bytes, NULL);
			break;
		}
	}
	else {
		WriteFile(hFile, "Введены некорректные данные.", 28, &bytes, NULL);
	}
	CloseHandle(hFile);

	return 0;
}
