
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include "GameScene.h"
#include "TitleScene.h"
#include "EndScene.h"

using namespace std;
int currentScene = 0;

int main()
{
	// 99개의 문자 + 끝에 null 문자 -> 버퍼는 가로를 100으로, 콘솔창 가로 길이는 99로 설정
	// 콘솔창의 세로 사이즈는 45로 설정, but 실제 스크린 렌더는 40까지만 활용
	system("mode con lines=45 cols=99");

	// 콘솔 커서가 보이지 않도록 설정
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	// 시간 해상도 설정
	timeBeginPeriod(1);

	while (true)
	{
		switch (currentScene)
		{
		case 0:
			RunTitleScene();
			break;
		case 1:
			RunGameScene();
			break;
		default:
			break;
		}

		if (currentScene == 2)
		{
			RunEndScene();
			break;
		}
	}

	timeEndPeriod(1);

	return 0;
}



