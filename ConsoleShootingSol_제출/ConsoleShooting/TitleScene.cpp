
#include <Windows.h>
#include <conio.h> // console input and output
#include <iostream>
#include "TitleScene.h"
#include "ScreenRender.h"
#include "StageMap.h"
#include "PlayerUnit.h"
#include "Bullet.h"

using namespace std;

#define SHOW_INTERVAL_TICK 500 // ������ �ð� �ֱ�� ���ڰ� �ϳ��� ��Ÿ������ ����
char pressButton[] = "Please Select Stage Map (1,2,3)";
static int lettersDisplayed = 1;

extern char screenBuf[CONSOLE_HEIGHT][CONSOLE_WIDTH + 1];
extern int currentScene;
extern PlayerUnit player;
extern Bullet bulletArr[BULLET_COUNT];

void RunTitleScene()
{	
	// �� ������ ���� ������ tick�� �������� �ð� ó��
	int initialTick = timeGetTime();

	while (true)
	{
		// ���� ��ũ�� ������ ���� �����======================================
		ClearScreenBuf();

		// ��ũ�� ���ۿ� �� ���� ä��� (����)=============================
		int currentTick = timeGetTime();
		if (currentTick - initialTick > SHOW_INTERVAL_TICK*lettersDisplayed)
		{
			lettersDisplayed++;
		}

		switch (lettersDisplayed)
		{
		case 1:
			DrawSprite('G', 35, 20);
			break;
		case 2:
			DrawSprite('G', 35, 20);
			DrawSprite('A', 45, 20);
			break;
		case 3:
			DrawSprite('G', 35, 20);
			DrawSprite('A', 45, 20);
			DrawSprite('M', 55, 20);
			break;
		case 4:
			DrawSprite('G', 35, 20);
			DrawSprite('A', 45, 20);
			DrawSprite('M', 55, 20);
			DrawSprite('E', 65, 20);
			break;
		default:
			// Ư�� ��ǥ�� �����Ͽ� ���� ���
			strcpy(&screenBuf[20][35], pressButton);
			break;
		}

		if (_kbhit())
		{
			char keyPressed = getch();
			if (keyPressed - '0' < 4 && keyPressed - '0' >=0) // �Է� ������ ���� 1~3���� ����
			{
				// ���� �ʱ�ȭ : �� �ҷ�����(�� ����), �Ѿ� ����, �÷��̾� ����
				currentScene = 1; // GameScene
				LoadStageMap(keyPressed - '0');
				for (size_t i = 0; i < BULLET_COUNT; i++)
				{
					bulletArr[i].isAlive = false;
				}
				SetPlayerPos(43, 30);
				player.hp = PLAYER_HP;
				break;
			}
		}
		// ��ũ�� ������ ������ ȭ�鿡 ���=====================================
		DisplayScreenBuf();

	}
}
