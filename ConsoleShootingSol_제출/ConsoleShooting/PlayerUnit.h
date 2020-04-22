#pragma once

#include <Windows.h> // 원래 여기 있었습니다.
#define PLAYER_HP 3

struct PlayerUnit
{
	UINT posX;
	UINT posY;
	UINT hp;
};

void SetPlayerPos(UINT x, UINT y);
void PlayerShoot();