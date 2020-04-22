
#include "ControlQueue.h"
#include <iostream>
#include "PlayerUnit.h"
#include "ScreenRender.h"

extern PlayerUnit player;
// 'ControlInput' enum���� �־�� �� �ִ� ť -> �迭�� ũ�⸦ 6���� �θ� �ִ� 5�� ���� Ȱ�� ����
ControlInput inputArr[ARR_SIZE];
ControlInput input; // dequeue ���� ���� �޾��ִ� ����
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
	while (IsControlQueueEmpty() == false) // ť�� �ƹ��͵� ���� ���� �� ���� dequeue�ؼ� ���� ó��
	{
		if (Dequeue(input) == false) // ���� dequeue�� �� ���ٸ� �ٷ� ����
		{
			return;
		}

		switch (input) // ť���� ���� ���� ���� ������ ó��
		{
		case InputUp:
			if (player.posY == 0) // ȭ�� ������ ���������� ���� üũ
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
