#include "Header.h"

int main()
{
	srand(time(0));
	const int startCoordX = 3;
	const int startCoordY = 2;
	const int moveRight = 4;
	const int moveDown = 2;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cPos = { startCoordX, startCoordY };

	std::cout << "At the beginning you set the size of the field, then you can move down or to the right.\nGoal: go from the upper left corner to the lower right corner with as few points as possible." << std::endl;

	int x, y;
	do
	{
		std::cout << "Enter the number of rows (Minimum 1): ";
		std::cin >> y;
	} while (y < 1);
	do
	{
		std::cout << "Enter the number of columns (Minimum 1): ";
		std::cin >> x;
	} while (x < 1);
	num* field_num = new num[x * y];
	num* track = new num[x + y - 1];
	int track_s = 0;
	for (int i = 0; i < x * y; i++)
	{
		field_num[i].s = 1 + rand() % 9;
		field_num[i].c.x = (i % x) * 4 + cPos.X;
		field_num[i].c.y = (i / x) * 2 + cPos.Y;
	}
	system("cls");

	field(x, y, field_num, cPos, track, &track_s);
	SetConsoleCursorPosition(hCon, cPos);

	for (; cPos.X != (x - 1) * 4 + startCoordX || cPos.Y != (y - 1) * 2 + startCoordY; )
	{
		int code = _getch();
		if (code == 224)
		{
			code = _getch();
		}
		else
		{
			std::cout << cPos.X << " " << cPos.Y;
		}

		switch (code)
		{
		case 77:
			if (cPos.X < (x - 1) * 4 + startCoordX)
			{
				cPos.X += moveRight;
				system("cls");
				field(x, y, field_num, cPos, track, &track_s);
			}
			break;
		case 80:
			if (cPos.Y < (y - 1) * 2 + startCoordY)
			{
				cPos.Y += moveDown;
				system("cls");
				field(x, y, field_num, cPos, track, &track_s);
			}
			break;
		}
		SetConsoleCursorPosition(hCon, cPos);

	}

	cPos.X = 0;
	cPos.Y = 2 * y + 1;
	SetConsoleCursorPosition(hCon, cPos);
	int summ = 0;
	num* finish = new num[x + y - 1];
	for (int i = 0; i < x + y - 1; i++)
	{
		summ += track[i].s;
	}
	std::cout << "Sum of all cells passed: " << summ << std::endl;

	minimum(field_num, x, y, finish);
	cPos.X = finish[0].c.x;
	cPos.Y = finish[0].c.y + 100;
	int z = x + y - 1;
	int* t = &z;
	std::cout << "Minimum amount: " << finish[0].s << std::endl;
	if (finish[0].s == summ)
	{
		std::cout << "You managed to score the minimum value!" << std::endl;
	}
	else
	{
		std::cout << "You failed to reach the minimum value!" << std::endl;
	}
	std::cout << "One of the possible options: " << std::endl;
	field(x, y, field_num, cPos, finish, t);

	system("pause");
	return 0;
}