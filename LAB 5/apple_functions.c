#include "apple_functions.h"

void Add_Random_Apple(Apple* apple)
{
	apple->x = (rand() % 39) + 1;
	apple->y = (rand() % 19) + 1;
}

void Apple_Collision(Apple* apple, Snake* snake)
{
	Snake* temp = snake;
	while (temp != NULL)
	{
		if (temp->x == apple->x && temp->y == apple->y)
		{
			Add_Random_Apple(apple);
			temp = snake;
		}
		temp = temp->next;
	}
}

//void Apple_Collision_Check(Apple* apple, Snake* snake);

void Output_Apple(Apple* apple)
{
	gotoxy(apple->x, apple->y);
	printf("@");
}