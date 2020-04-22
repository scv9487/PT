
#include "ControlQueue.h"
#include <iostream>
#include "PlayerUnit.h"
#include "ScreenRender.h"

extern PlayerUnit player;
// 'ControlInput' enum형을 넣어둘 수 있는 큐 -> 배열의 크기를 6으로 두면 최대 5개 까지 활용 가능
ControlInput inputArr[ARR_SIZE];
ControlInput input; // dequeue 에서 값을 받아주는 역할
int front;
int back;

bool IsControlQueueEmpty()
{
	if (front == back)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsControlQueueFull()
{
	if ((back + 1) % ARR_SIZE == front)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Enqueue(ControlInput input)
{
	if (IsControlQueueFull() == false)
	{
		inputArr[back] = input;
		back = (back + 1) % ARR_SIZE;
		return true;
	}
	else
	{
		return false;
	}
}

bool Dequeue(ControlInput& input)
{
	if (IsControlQueueEmpty() == false)
	{
		input = inputArr[front];
		front = (front + 1) % ARR_SIZE;
		return true;
	}
	else
	{
		return false;
	}
}

void EmptyControlQueue()
{
	while (IsControlQueueEmpty() == false) // 큐에 아무것도 남지 않을 때 까지 dequeue해서 로직 처리
	{
		if (Dequeue(input) == false) // 만약 dequeue할 수 없다면 바로 리턴
		{
			return;
		}

		switch (input) // 큐에서 빼낸 값에 따라 로직을 처리
		{
		case InputUp:
			if (player.posY == 0) // 화면 밖으로 못나가도록 조건 체크
			{
				break;
			}
			SetPlayerPos(player.posX, player.posY - 1);
			break;
		case InputDown:
			if (player.posY == CONSOLE_HEIGHT-1)
			{
				break;
			}
			SetPlayerPos(player.posX, player.posY + 1);
			break;
		case InputLeft:
			if (player.posX == 0)
			{
				break;
			}
			SetPlayerPos(player.posX - 1, player.posY);
			break;
		case InputRight:
			if (player.posX == CONSOLE_WIDTH-1)
			{
				break;
			}
			SetPlayerPos(player.posX + 1, player.posY);
			break;
		case InputShoot:
			PlayerShoot();
			break;
		default:
			break;
		}
	}
}
