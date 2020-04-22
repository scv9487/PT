
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
	// 기존 스크린 버퍼의 내용 지우기======================================
	ClearScreenBuf();
	strcpy(&screenBuf[20][45], gameEnd);

	// 스크린 버퍼의 내용을 화면에 출력=====================================
	DisplayScreenBuf();
	Sleep(2000);
}