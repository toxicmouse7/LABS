#ifndef INC_GUR
#include <stdio.h>
#include <stdlib.h>
#endif

typedef struct
{
	int x;
	int y;
} Apple;

typedef struct
{
	int x;
	int y;
	struct Snake* next;
	struct Snake* previous;
} Snake;

void gotoxy(int x, int y);
void Add_Random_Apple(Apple* apple);
void Output_Apple(Apple* apple);
void Apple_Collision(Apple* apple, Snake* snake);