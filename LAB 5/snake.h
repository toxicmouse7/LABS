#ifndef INC_GUR
#define INC_GUR
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#endif

struct snake
{
	int x;
	int y;
	struct snake* next;
	struct snake* previous;
};

typedef struct snake Snake;

struct apple
{
	int x;
	int y;
};

typedef struct apple Apple;

void gotoxy(int x, int y);
void Add_Random_Apple(Apple* apple);
void Output_Apple(Apple* apple);
void create_game_field();
void Output_Snake(Snake* snake);
void Remove_Snakes_Tail(Snake* snake);
void increase_snake(Snake* snake);
void pullup_snake(Snake* snake);
void free_snake(Snake* snake);
void Apple_Collision(Apple* apple, Snake* snake);
