
#include <Windows.h>
#include <iostream>
#include "ScreenRender.h"

using namespace std;

char screenBuf[CONSOLE_HEIGHT][CONSOLE_WIDTH + 1];

void MoveCursor(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void ClearScreenBuf()
{
	// ��ũ�� ���� ����
	memset(screenBuf, ' ', (CONSOLE_HEIGHT*(CONSOLE_WIDTH + 1) * sizeof(char)));

	for (size_t h = 0; h < CONSOLE_HEIGHT; h++)
	{
		screenBuf[h][CONSOLE_WIDTH] = '\0'; // []�� 0���� �����ϱ� ������, �����δ� 99��°�� �ƴ϶�, 100��° ���ڿ� ����
	}
}

void DisplayScreenBuf()
{
	for (size_t h = 0; h < CONSOLE_HEIGHT; h++)
	{
		// ��ũ�� ������ ������ ������ ������� ���
		MoveCursor(0, h);
		printf("%s", screenBuf[h]);
	}
}

void DrawSprite(char sprite, UINT x, UINT y)
{
	// ��ũ�� ���� ���� ��ġ��� ����
	if (x <= CONSOLE_WIDTH || y <= CONSOLE_HEIGHT) 
	{
		screenBuf[y][x] = sprite;
	}
}
