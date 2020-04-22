
#include <Windows.h>
#include <iostream>
#include "GameScene.h"
#include "ScreenRender.h"
#include "PlayerUnit.h"
#include "EnemyUnit.h"
#include "StageMap.h"
#include "Bullet.h"
#include "ControlQueue.h"
#define ENEMY_MOVE_TICK 500 // 적 움직임
#define ENEMY_SHOOT_TICK 500 // 적 발사
#define ENEMY_SHOOT_PERCENT 10 // 적은 10%의 확률로만 발사
#define PLAYER_MOVE_TICK 30 // 플레이어 움직임
#define PLAYER_SHOOT_TICK 150 // 플레이어 발사
#define BULLET_MOVE_TICK 50 // 총알 이동

using namespace std;

extern char screenBuf[CONSOLE_HEIGHT][CONSOLE_WIDTH + 1];
extern EnemyUnit enemyArr[ENEMY_COUNT];
extern PlayerUnit player;
extern Bullet bulletArr[BULLET_COUNT];
extern int currentScene;
extern int enemyKillCount;

void RunGameScene()
{
	int initialTick = timeGetTime(); // initialTick 을 기준으로 시간 처리

	while (true)
	{
		// 기존 스크린 버퍼의 내용 지우기======================================
		ClearScreenBuf();

		// 로직==============================================================
		int currentTick = timeGetTime();

		// 적 움직임
		static int enemyMoveCount;
		if (currentTick - initialTick > ENEMY_MOVE_TICK * enemyMoveCount)
		{
			if ((enemyMoveCount / 5) % 2 == 0) // 5번씩만 좌우로 움직이는 로직
			{
				EnemyMoveRight();
			}
			else
			{
				EnemyMoveLeft();
			}
			enemyMoveCount++;
		}

		// 적 발사
		static int enemyShootCount;
		if (currentTick - initialTick > ENEMY_SHOOT_TICK * enemyShootCount)
		{
		// 정해진 확률(ENEMY_SHOOT_PERCENT)대로 총알 발사
			for (size_t i = 0; i < ENEMY_COUNT; i++)
			{
				if (enemyArr[i].isAlive == true && (rand() % 100) < ENEMY_SHOOT_PERCENT)
				{
					EnemyShoot(i);
				}
			}
			enemyShootCount++;
		}

		// 플레이어 움직임
		static int playerMoveCount;
		if (currentTick - initialTick > PLAYER_MOVE_TICK * playerMoveCount)
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				Enqueue(InputUp);
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				Enqueue(InputDown);
			}
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				Enqueue(InputLeft);
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				Enqueue(InputRight);
			}
			playerMoveCount++;
		}

		// 플레이어 발사
		static int playerShootCount;
		if (currentTick - initialTick > PLAYER_SHOOT_TICK * playerShootCount) 
		{
			if (GetAsyncKeyState(0x58) & 0x8000) // 키보드 X버튼
			{
				Enqueue(InputShoot);
			}
			playerShootCount++;
		}

		// 컨트롤 큐를 비우며 플레이어 입력에 대한 로직 처리
		EmptyControlQueue();

		// 총알 움직임 (순서상 다른 유닛들이 모두 움직인 후 수행)
		static int bulletMoveCount;
		if (currentTick - initialTick > BULLET_MOVE_TICK * bulletMoveCount)
		{
			BulletMove(); // 이 함수에서 총알을 움직인 후 충돌 처리
			if (player.hp == 0) // 만약 플레이어가 죽었다면, currentScene을 변경하고 break
			{
				printf("플레이어 HP : %d", player.hp);
				currentScene = 2; // end
				break;
			}
			else if (enemyKillCount >= ENEMY_COUNT) // 만약 모든 적 유닛이 죽었다면, currentScene을 변경하고 break
			{
				currentScene = 2; // end
				break;
			}
			bulletMoveCount++;
		}

		// 스크린 버퍼에 들어갈 내용 채우기 (렌더)=============================

		// 적 유닛 배열을 순회하며 스프라이트 출력
		for (size_t i = 0; i < ENEMY_COUNT; i++)
		{
			if (enemyArr[i].isAlive == true)
			{
				DrawSprite('V', enemyArr[i].posX, enemyArr[i].posY);
			}
		}

		// 총알 배열을 순회하며 살아있는 총알만 출력
		for (size_t i = 0; i < BULLET_COUNT; i++)
		{
			if (bulletArr[i].isAlive == true)
			{
				DrawSprite('!', bulletArr[i].posX, bulletArr[i].posY);
			}
		}

		// 플레이어 유닛의 위치 출력
		DrawSprite('#', player.posX, player.posY);

		// 플레이어 hp 출력
		printf("플레이어 HP : %d", player.hp);

		// 스크린 버퍼의 내용을 화면에 출력=====================================
		DisplayScreenBuf();
	}
}
