#include"Header.h"

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void field(int x, int y, num* field_num, COORD cPos, num* track, int* track_s)
{
	int n = 0;
	for (int i = 0; i < x * 4; i++)
	{
		std::cout << "_";
	}
	for (int j = 0; j < y; j++)
	{
		std::cout << std::endl;
		for (int i = 0; i < x; i++)
		{
			if (cPos.Y == field_num[n].c.y && cPos.X == field_num[n].c.x)
			{
				std::cout << "| ";
				SetColor(Green, Black);
				std::cout << field_num[n].s << " ";
				track[*track_s].s = field_num[n].s;
				track[*track_s].c.x = field_num[n].c.x;
				track[*track_s].c.y = field_num[n].c.y;
				*track_s = *track_s + 1;
				SetColor(White, Black);
			}
			else
			{
				int point = 0;
				for (int i1 = 0; i1 < *track_s; i1++)
				{
					if (track[i1].c.x == (n % x) * 4 + 3 && track[i1].c.y == (n / x) * 2 + 2)
					{
						std::cout << "| ";
						SetColor(Blue, Black);
						std::cout << field_num[n].s << " ";
						SetColor(White, Black);
						point++;
						break;
					}
				}
				if (point == 0)
				{
					std::cout << "| " << field_num[n].s << " ";
				}
			}
			n++;
		}
		std::cout << "|" << std::endl;
		for (int i = 0; i < x * 4; i++)
		{
			std::cout << "-";
		}
	}
}

void minimum(num* field_num, int x, int y, num* finish)
{
	num* min_way = new num[x * y];
	min_way[0] = field_num[0];
	for (int i = 1; i < x * y; i++)
	{
		min_way[i] = field_num[i];
		if (i < x)
		{
			min_way[i].s = min_way[i - 1].s + field_num[i].s;
		}
		else if (i % x == 0)
		{
			min_way[i].s = min_way[i - x].s + field_num[i].s;
		}
		else
		{
			if (min_way[i - 1].s <= min_way[i - x].s)
			{
				min_way[i].s = min_way[i - 1].s + field_num[i].s;
			}
			else
			{
				min_way[i].s = min_way[i - x].s + field_num[i].s;
			}
		}
	}

	finish[0] = min_way[x * y - 1];
	for (int i = 1, i1 = x * y - 1; i < x + y - 1; i++)
	{
		if (min_way[i1].c.x == 3)
		{
			i1 = i1 - x;
			finish[i] = min_way[i1];
		}
		else if (min_way[i1].c.y == 2)
		{
			i1 = i1 - 1;
			finish[i] = min_way[i1];
		}
		else if (min_way[i1 - 1].s <= min_way[i1 - x].s)
		{
			i1 = i1 - 1;
			finish[i] = min_way[i1];
		}
		else
		{
			i1 = i1 - x;
			finish[i] = min_way[i1];
		}
	}
}