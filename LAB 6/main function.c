#include <Windows.h>
#include "variables.h"

int CheckNewPosistion(COORD* pos)
{
	if (pos->X == -1 || pos->X == a)
	{
		return 1;
	}
	if (pos->Y == -1 || pos->Y == a)
	{
		return 1;
	}
	return 0;
}


void changPos(COORD* Pos, int step)
{
	if (step == 1)
	{
		Pos->X += 0;
		Pos->Y -= 1;
	}
	if (step == 2)
	{
		Pos->X -= 1;
		Pos->Y += 0;
	}
	if (step == 3)
	{
		Pos->X += 0;
		Pos->Y += 1;
	}
	if (step == 4)
	{
		Pos->X += 1;
		Pos->Y += 0;
	}

	if (CheckNewPosistion(Pos))
	{
		if (step == 1)
		{
			Pos->X += 0;
			Pos->Y += 1;
		}
		if (step == 2)
		{
			Pos->X += 1;
			Pos->Y += 0;
		}
		if (step == 3)
		{
			Pos->X += 0;
			Pos->Y -= 1;
		}
		if (step == 4)
		{
			Pos->X -= 1;
			Pos->Y += 0;
		}
	}
}