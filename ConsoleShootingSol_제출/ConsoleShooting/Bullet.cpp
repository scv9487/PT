
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

void BulletMove() // 총알 움직임
{
	for (size_t i = 0; i < BULLET_COUNT; i++)
	{
		if (bulletArr[i].isAlive) // 죽은 총알은 성능상 연산에서 제외
		{
			switch (bulletArr[i].type)
			{
			case PlayerBullet:
				if (bulletArr[i].posY == 0)// 아군 총알인 경우 y 포즈가 0이면 총알이 사라진다
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
				if (bulletArr[i].posY == CONSOLE_HEIGHT-1)// 적군 총알인 경우 y 포즈가 0이면 총알이 사라진다
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

