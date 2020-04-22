
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
	// 스크린 버퍼 비우기
	memset(screenBuf, ' ', (CONSOLE_HEIGHT*(CONSOLE_WIDTH + 1) * sizeof(char)));

	for (size_t h = 0; h < CONSOLE_HEIGHT; h++)
	{
		screenBuf[h][CONSOLE_WIDTH] = '\0'; // []는 0부터 시작하기 때문에, 실제로는 99번째가 아니라, 100번째 문자에 접근
	}
}

void DisplayScreenBuf()
{
	for (size_t h = 0; h < CONSOLE_HEIGHT; h++)
	{
		// 스크린 버퍼의 내용을 덮어씌우기 방식으로 출력
		MoveCursor(0, h);
		printf("%s", screenBuf[h]);
	}
}

void DrawSprite(char sprite, UINT x, UINT y)
{
	// 스크린 범위 밖의 위치라면 무시
	if (x <= CONSOLE_WIDTH || y <= CONSOLE_HEIGHT) 
	{
		screenBuf[y][x] = sprite;
	}
}
