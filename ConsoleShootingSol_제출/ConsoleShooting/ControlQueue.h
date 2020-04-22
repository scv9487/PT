#pragma once

#define ARR_SIZE 6 // ��Ʈ�� ť�� ������. �迭�� ũ��� 6������, �����δ� 5�� ���� Ȱ�� ����
enum ControlInput { InputUp, InputDown, InputLeft, InputRight, InputShoot };

bool IsControlQueueEmpty();
bool IsControlQueueFull();
bool Enqueue(ControlInput input);
bool Dequeue(ControlInput& input);
void EmptyControlQueue();