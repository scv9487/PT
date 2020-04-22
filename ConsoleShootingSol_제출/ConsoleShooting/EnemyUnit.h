#pragma once

#define ENEMY_COUNT 15
#define ENEMY_HP 1

struct EnemyUnit
{
	UINT posX;
	UINT posY;
	UINT hp;
	bool isAlive;
};

void SetEnemyPos(EnemyUnit& enemy, UINT x, UINT y);
void EnemyMoveRight();
void EnemyMoveLeft();
void EnemyShoot(UINT enemyNum);