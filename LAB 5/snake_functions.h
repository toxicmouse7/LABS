#ifndef INC_GUR
#include <stdio.h>
#include <stdlib.h>
#endif

typedef struct
{
	int x;
	int y;
	struct Snake* next;
	struct Snake* previous;
} Snake;

void gotoxy(int x, int y);
void create_game_field();
void Output_Snake(Snake* snake);
void Remove_Snakes_Tail(Snake* snake);
void increase_snake(Snake* snake);
void pullup_snake(Snake* snake);
void free_snake(Snake* snake);