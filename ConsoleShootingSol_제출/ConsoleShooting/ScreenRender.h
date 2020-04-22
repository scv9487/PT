#pragma once

#define CONSOLE_WIDTH 99
#define CONSOLE_HEIGHT 40

typedef unsigned int UINT;

void MoveCursor(int x, int y);
void ClearScreenBuf();
void DisplayScreenBuf();
void DrawSprite(char, UINT, UINT);