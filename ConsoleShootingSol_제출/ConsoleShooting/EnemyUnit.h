#pragma once

#define ENEMY_COUNT 15
#define ENEMY_HP 1 // 테스트를 위해 쉽게 죽도록 적 HP는 1로 설정

typedef unsigned int UINT;

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