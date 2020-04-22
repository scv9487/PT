#pragma once

#define PLAYER_HP 3

typedef unsigned int UINT;

struct PlayerUnit
{
	UINT posX;
	UINT posY;
	UINT hp;
};

void SetPlayerPos(UINT x, UINT y);
void PlayerShoot();