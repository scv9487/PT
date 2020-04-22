
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include "GameScene.h"
#include "TitleScene.h"
#include "EndScene.h"

using namespace std;
int currentScene = 0;

int main()
{
	// 99���� ���� + ���� null ���� -> ���۴� ���θ� 100����, �ܼ�â ���� ���̴� 99�� ����
	// �ܼ�â�� ���� ������� 45�� ����, but ���� ��ũ�� ������ 40������ Ȱ��
	system("mode con lines=45 cols=99");

	// �ܼ� Ŀ���� ������ �ʵ��� ����
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	// �ð� �ػ� ����
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



