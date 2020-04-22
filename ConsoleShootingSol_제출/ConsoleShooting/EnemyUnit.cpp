
#include "EnemyUnit.h"
#include <iostream>
#include "Bullet.h"

EnemyUnit enemyArr[ENEMY_COUNT];
extern Bullet bulletArr[BULLET_COUNT];

void SetEnemyPos(EnemyUnit& enemy, UINT x, UINT y)
{
	enemy.posX = x;
	enemy.posY = y;
}

void EnemyMoveRight()
{
	for (size_t i = 0; i < ENEMY_COUNT; i++)
	{
		enemyArr[i].posX++;
	}
}

void EnemyMoveLeft()
{
	for (size_t i = 0; i < ENEMY_COUNT; i++)
	{
		enemyArr[i].posX--;
	}
}

void EnemyShoot(UINT enemyNum)
{
	// 안쓰이는 총알을 찾아 발사한다
	for (size_t i = 0; i < BULLET_COUNT; i++)
	{
		if (bulletArr[i].isAlive == false)
		{
			bulletArr[i].isAlive = true;
			bulletArr[i].type = EnemyBullet;
			bulletArr[i].posX = enemyArr[enemyNum].posX;
			bulletArr[i].posY = enemyArr[enemyNum].posY;
			return;
		}
	}
}