#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection direction;
int bodyX[100], bodyY[100];
int nSegments;

void Setup()
{
	gameOver = false;
	direction = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;

}

void Draw()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << "#";
			}
			if (i == y && j == x)
			{
				cout << "O";
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "$";
			}
			else
			{
				bool print = false;

				for (int k = 0; k < nSegments; k++)
				{
					if (bodyX[k] == j && bodyY[k] == i)
					{
						cout << "o";
						print = true;
					}
			    }
				if (!print)
				{
					cout << " ";
				}
			}
			if (j == width -1)
			{
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a' :
			direction = LEFT;
			break;
		case 'd' :
			direction = RIGHT;
			break;
		case 'w' :
			direction = UP;
			break;
		case 's' :
			direction = DOWN;
			break;
		case 'q':
			gameOver = true;
			break;
		}
	}

}

void Logic()
{
	int lastLocX = bodyX[0];
	int lastLocY = bodyY[0];
	int lastLocX2, lastLocY2;
	bodyX[0] = x;
	bodyY[0] = y;
	for (int i = 1; i < nSegments; i++)
	{

		lastLocX2 = bodyX[i];
		lastLocY2 = bodyY[i];
		bodyX[i] = lastLocX;
		bodyY[i] = lastLocY;
		lastLocX = lastLocX2;
		lastLocY = lastLocY2;
	}


	switch (direction)
	{
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}

	if (x > width || x < 0 || y > height || y < 0)
	{
		gameOver = true;
	}
	for (int i = 0; i < nSegments; i++)
	{
		if (bodyX[i] == x && bodyY[i] == y)
		{
			gameOver = true;
		}
	}
	if (x == fruitX && y == fruitY)
	{
		score += 1;

		fruitX = rand() % width;
		fruitY = rand() % height;
		nSegments++;
	}

}

int main()
{
	Setup();

	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(150);
	}

	return 0;
}