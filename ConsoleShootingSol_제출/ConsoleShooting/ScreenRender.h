#pragma once

#include <Windows.h>
#define CONSOLE_WIDTH 99
#define CONSOLE_HEIGHT 40

void MoveCursor(int x, int y);
void ClearScreenBuf();
void DisplayScreenBuf();
void DrawSprite(char, UINT, UINT);