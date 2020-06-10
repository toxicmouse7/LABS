#include "snake.h"

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main()
{
	system("title Snake");
	FILE* f, * temp;
	Snake* snake = (Snake*)malloc(sizeof(Snake));
	Snake* snake_go;
	Snake* tmp;
	Apple* apple = (Apple*)malloc(sizeof(Apple));
	int score = 0;
	snake->next = NULL;
	snake->previous = NULL;
	snake->x = 20;
	snake->y = 10;
	char ch = 'm', ch1 = 'm';
	int time = 270;
	char Nickname[20];
	char buffer[50];

	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);


	printf("Write your nickname(max 20 symbols): ");
	gets_s(Nickname, 20);
	system("cls");

	create_game_field();
	Add_Random_Apple(apple);
	Output_Apple(apple);

	while (1)
	{
		if (_kbhit())
			ch = _getch();
		if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')
			ch1 = ch;

		switch (ch1)
		{
		case 'w':
		{
			Remove_Snakes_Tail(snake);
			pullup_snake(snake);
			snake->y--;
			Output_Snake(snake);
			Sleep(time);
			break;
		}
		case 'a':
		{
			Remove_Snakes_Tail(snake);
			pullup_snake(snake);
			snake->x--;
			Output_Snake(snake);
			Sleep(time);
			break;
		}
		case 's':
		{
			Remove_Snakes_Tail(snake);
			pullup_snake(snake);
			snake->y++;
			Output_Snake(snake);
			Sleep(time);
			break;
		}
		case 'd':
		{
			Remove_Snakes_Tail(snake);
			pullup_snake(snake);
			snake->x++;
			Output_Snake(snake);
			Sleep(time);
			break;
		}
		}

		if (snake->x > 39 || snake->x < 1 || snake->y < 1 || snake->y > 19)
		{
			system("cls");
			printf("Game Over, your score is: %d\n", score);
			goto end;
		}

		if (snake->x == apple->x && snake->y == apple->y)
		{
			increase_snake(snake);
			Add_Random_Apple(apple);
			Apple_Collision(apple, snake);
			Output_Apple(apple);
			score++;
			if (time > 49)
				time -= 10;
		}

		snake_go = snake;
		while (snake_go->next != NULL)
		{
			snake_go = snake_go->next;
			if (snake->x == snake_go->x && snake->y == snake_go->y)
			{
				system("cls");
				printf("Game Over, your score is: %d\n", score);
				goto end;
			}
		}

	}
end:

	fopen_s(&f, "scorelist.txt", "r+");
	int count = 0;
	while (!feof(f))
	{
		fgets(buffer, 50, f);
		count++;
	}
	fseek(f, 0, SEEK_SET);
	if (count < 11)
	{
		fprintf(f, "%s - %d\n", Nickname, score);
		fclose(f);
	}
	else
	{
		fopen_s(&temp, "temp.txt", "w");
		fprintf(f, "%s - %d\n", Nickname, score);
		for (int i = 0; i < 10; i++)
		{
			fgets(buffer, 50, f);
			fputs(buffer, temp);
		}
		fclose(temp);
		fclose(f);
		remove("scorelist.txt");
		rename("temp.txt", "scorelist.txt");
	}
	
	free_snake(snake);
	free(apple);

	system("pause");
	return 0;
}