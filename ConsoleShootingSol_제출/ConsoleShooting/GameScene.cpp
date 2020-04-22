
#include <Windows.h>
#include <iostream>
#include "GameScene.h"
#include "ScreenRender.h"
#include "PlayerUnit.h"
#include "EnemyUnit.h"
#include "StageMap.h"
#include "Bullet.h"
#include "ControlQueue.h"
#define ENEMY_MOVE_TICK 500 // �� ������
#define ENEMY_SHOOT_TICK 500 // �� �߻�
#define ENEMY_SHOOT_PERCENT 10 // ���� 10%�� Ȯ���θ� �߻�
#define PLAYER_MOVE_TICK 30 // �÷��̾� ������
#define PLAYER_SHOOT_TICK 150 // �÷��̾� �߻�
#define BULLET_MOVE_TICK 50 // �Ѿ� �̵�

using namespace std;

extern char screenBuf[CONSOLE_HEIGHT][CONSOLE_WIDTH + 1];
extern EnemyUnit enemyArr[ENEMY_COUNT];
extern PlayerUnit player;
extern Bullet bulletArr[BULLET_COUNT];
extern int currentScene;
extern int enemyKillCount;

void RunGameScene()
{
	int initialTick = timeGetTime(); // initialTick �� �������� �ð� ó��

	while (true)
	{
		// ���� ��ũ�� ������ ���� �����======================================
		ClearScreenBuf();

		// ����==============================================================
		int currentTick = timeGetTime();

		// �� ������
		static int enemyMoveCount;
		if (currentTick - initialTick > ENEMY_MOVE_TICK * enemyMoveCount)
		{
			if ((enemyMoveCount / 5) % 2 == 0) // 5������ �¿�� �����̴� ����
			{
				EnemyMoveRight();
			}
			else
			{
				EnemyMoveLeft();
			}
			enemyMoveCount++;
		}

		// �� �߻�
		static int enemyShootCount;
		if (currentTick - initialTick > ENEMY_SHOOT_TICK * enemyShootCount)
		{
		// ������ Ȯ��(ENEMY_SHOOT_PERCENT)��� �Ѿ� �߻�
			for (size_t i = 0; i < ENEMY_COUNT; i++)
			{
				if (enemyArr[i].isAlive == true && (rand() % 100) < ENEMY_SHOOT_PERCENT)
				{
					EnemyShoot(i);
				}
			}
			enemyShootCount++;
		}

		// �÷��̾� ������
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

		// �÷��̾� �߻�
		static int playerShootCount;
		if (currentTick - initialTick > PLAYER_SHOOT_TICK * playerShootCount) 
		{
			if (GetAsyncKeyState(0x58) & 0x8000) // Ű���� X��ư
			{
				Enqueue(InputShoot);
			}
			playerShootCount++;
		}

		// ��Ʈ�� ť�� ���� �÷��̾� �Է¿� ���� ���� ó��
		EmptyControlQueue();

		// �Ѿ� ������ (������ �ٸ� ���ֵ��� ��� ������ �� ����)
		static int bulletMoveCount;
		if (currentTick - initialTick > BULLET_MOVE_TICK * bulletMoveCount)
		{
			BulletMove(); // �� �Լ����� �Ѿ��� ������ �� �浹 ó��
			if (player.hp == 0) // ���� �÷��̾ �׾��ٸ�, currentScene�� �����ϰ� break
			{
				printf("�÷��̾� HP : %d", player.hp);
				currentScene = 2; // end
				break;
			}
			else if (enemyKillCount >= ENEMY_COUNT) // ���� ��� �� ������ �׾��ٸ�, currentScene�� �����ϰ� break
			{
				currentScene = 2; // end
				break;
			}
			bulletMoveCount++;
		}

		// ��ũ�� ���ۿ� �� ���� ä��� (����)=============================

		// �� ���� �迭�� ��ȸ�ϸ� ��������Ʈ ���
		for (size_t i = 0; i < ENEMY_COUNT; i++)
		{
			if (enemyArr[i].isAlive == true)
			{
				DrawSprite('V', enemyArr[i].posX, enemyArr[i].posY);
			}
		}

		// �Ѿ� �迭�� ��ȸ�ϸ� ����ִ� �Ѿ˸� ���
		for (size_t i = 0; i < BULLET_COUNT; i++)
		{
			if (bulletArr[i].isAlive == true)
			{
				DrawSprite('!', bulletArr[i].posX, bulletArr[i].posY);
			}
		}

		// �÷��̾� ������ ��ġ ���
		DrawSprite('#', player.posX, player.posY);

		// �÷��̾� hp ���
		printf("�÷��̾� HP : %d", player.hp);

		// ��ũ�� ������ ������ ȭ�鿡 ���=====================================
		DisplayScreenBuf();
	}
}
