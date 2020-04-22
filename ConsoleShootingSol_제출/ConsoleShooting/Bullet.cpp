
#include <Windows.h>
#include "Bullet.h"
#include "EnemyUnit.h"
#include "PlayerUnit.h"
#include "ScreenRender.h"

Bullet bulletArr[BULLET_COUNT];

extern EnemyUnit enemyArr[ENEMY_COUNT];
extern PlayerUnit player;
int enemyKillCount;

void CheckBulletHitEnemy(UINT bulletNum)
{
	for (size_t i = 0; i < ENEMY_COUNT; i++)
	{
		if (enemyArr[i].posX == bulletArr[bulletNum].posX && enemyArr[i].posY == bulletArr[bulletNum].posY &&  enemyArr[i].isAlive == true)
		{
			if (enemyArr[i].hp == 1)
			{
				enemyArr[i].isAlive = false;
				enemyKillCount++;
			}
			else
			{
				enemyArr[i].hp--;
			}
			bulletArr[bulletNum].isAlive = false;
		}
	}
}

void CheckBulletHitPlayer(UINT bulletNum)
{
	if (player.posX == bulletArr[bulletNum].posX && player.posY == bulletArr[bulletNum].posY)
	{
			player.hp--;
			bulletArr[bulletNum].isAlive = false;
	}
}

void BulletMove() // �Ѿ� ������
{
	for (size_t i = 0; i < BULLET_COUNT; i++)
	{
		if (bulletArr[i].isAlive) // ���� �Ѿ��� ���ɻ� ���꿡�� ����
		{
			switch (bulletArr[i].type)
			{
			case PlayerBullet:
				if (bulletArr[i].posY == 0)// �Ʊ� �Ѿ��� ��� y ��� 0�̸� �Ѿ��� �������
				{
					bulletArr[i].isAlive = false;
				}
				else
				{
					bulletArr[i].posY--;
				}
				CheckBulletHitEnemy(i);
				break;
			case EnemyBullet:
				if (bulletArr[i].posY == CONSOLE_HEIGHT-1)// ���� �Ѿ��� ��� y ��� 0�̸� �Ѿ��� �������
				{
					bulletArr[i].isAlive = false;
				}
				else
				{
					bulletArr[i].posY++;
				}
				CheckBulletHitPlayer(i);
				break;
			default:
				break;
			}
		}
	}
}

