#pragma once


#define BULLET_COUNT 100

enum BulletType {PlayerBullet,EnemyBullet};

struct Bullet
{
	UINT posX;
	UINT posY;
	BulletType type;
	bool isAlive;
};

void BulletMove();
void CheckBulletHitEnemy(UINT bulletNum);
void CheckBulletHitPlayer(UINT bulletNum);
