
#include <iostream>
#include <Windows.h>
#include "EndScene.h"
#include "TitleScene.h"
#include "ScreenRender.h"

using namespace std;

extern char screenBuf[CONSOLE_HEIGHT][CONSOLE_WIDTH + 1];
char gameEnd[] = "THE END";

void RunEndScene()
{
	// ���� ��ũ�� ������ ���� �����======================================
	ClearScreenBuf();
	strcpy(&screenBuf[20][45], gameEnd);

	// ��ũ�� ������ ������ ȭ�鿡 ���=====================================
	DisplayScreenBuf();
	Sleep(2000);
}