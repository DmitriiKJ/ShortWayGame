#pragma once

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

struct coord
{
	int x;
	int y;
};

struct num
{
	int s;
	coord c;
};

void SetColor(ConsoleColor text, ConsoleColor background);

void field(int x, int y, num* field_num, COORD cPos, num* track, int* track_s);

void minimum(num* field_num, int x, int y, num* finish);