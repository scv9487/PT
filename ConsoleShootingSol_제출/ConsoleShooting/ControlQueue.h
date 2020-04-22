#pragma once

#define ARR_SIZE 6 // 컨트롤 큐의 사이즈. 배열의 크기는 6이지만, 실제로는 5개 까지 활용 가능
enum ControlInput { InputUp, InputDown, InputLeft, InputRight, InputShoot };

bool IsControlQueueEmpty();
bool IsControlQueueFull();
bool Enqueue(ControlInput input);
bool Dequeue(ControlInput& input);
void EmptyControlQueue();