#pragma once

#include <Windows.h> // ���� ���� �־����ϴ�.
#define PLAYER_HP 3

struct PlayerUnit
{
	UINT posX;
	UINT posY;
	UINT hp;
};

void SetPlayerPos(UINT x, UINT y);
void PlayerShoot();