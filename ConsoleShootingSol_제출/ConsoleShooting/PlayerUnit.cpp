
//#include <Windows.h> // PlayerUnit.h 에 있던 것을 이곳으로 옮겨왔습니다. 옮기기 전에는 잘 작동하였습니다.
#include "PlayerUnit.h"
#include "Bullet.h"

PlayerUnit player;
extern Bullet bulletArr[BULLET_COUNT];

void SetPlayerPos(UINT x, UINT y)
{
	player.posX = x;
	player.posY = y;
}

void PlayerShoot()
{
	// 안쓰이는 총알을 찾아 발사
	bool bfoundBullet = false;
	for (size_t i = 0; i < BULLET_COUNT; i++)
	{
		if (bulletArr[i].isAlive == false)
		{
			bfoundBullet = true;
			bulletArr[i].isAlive = true;
			bulletArr[i].type = PlayerBullet;			
			bulletArr[i].posX = player.posX;
			bulletArr[i].posY = player.posY;
			return;
		}
	}
}