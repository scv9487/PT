
#include <Windows.h>
#include <conio.h> // console input and output
#include <iostream>
#include "TitleScene.h"
#include "ScreenRender.h"
#include "StageMap.h"
#include "PlayerUnit.h"
#include "Bullet.h"

using namespace std;

#define SHOW_INTERVAL_TICK 500 // 정해진 시간 주기로 글자가 하나씩 나타나도록 설정
char pressButton[] = "Please Select Stage Map (1,2,3)";
static int lettersDisplayed = 1;

extern char screenBuf[CONSOLE_HEIGHT][CONSOLE_WIDTH + 1];
extern int currentScene;
extern PlayerUnit player;
extern Bullet bulletArr[BULLET_COUNT];

void RunTitleScene()
{	
	// 이 로직에 들어온 시점의 tick을 기준으로 시간 처리
	int initialTick = timeGetTime();

	while (true)
	{
		// 기존 스크린 버퍼의 내용 지우기======================================
		ClearScreenBuf();

		// 스크린 버퍼에 들어갈 내용 채우기 (렌더)=============================
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
			// 특정 좌표를 지정하여 문장 출력
			strcpy(&screenBuf[20][35], pressButton);
			break;
		}

		if (_kbhit())
		{
			char keyPressed = getch();
			if (keyPressed - '0' < 4 && keyPressed - '0' >=0) // 입력 가능한 값을 1~3으로 제한
			{
				// 게임 초기화 : 맵 불러오기(적 세팅), 총알 세팅, 플레이어 세팅
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
		// 스크린 버퍼의 내용을 화면에 출력=====================================
		DisplayScreenBuf();

	}
}
