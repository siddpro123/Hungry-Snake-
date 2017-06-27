// SnakeGame.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
// checkes whether game is over or not
bool gameOver;

//game screen size
const int width = 20;
const int height = 20;

//snake head position 
int headPostion_x, headPostion_y;

//baite/fruit position
int fruitPosition_x, fruitPosition_y;

//score counter
int score;

//creating tail of the snake
int tailX[100], tailY[100];
int nTail;

//direction of the snake
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

//setting the componenets of the game
void Setup()
{
	gameOver = false;
	dir = STOP;

	//genrating snake head at the middle of the display window
	headPostion_x = width / 2;
	headPostion_y = height / 2;

	//creating random position for the fruit 
	fruitPosition_x = rand() % width;
	fruitPosition_y = rand() % height;
	score = 0;
}

//creating the graphical componenets of the game on the screen
void Draw()
{
	//clearing consloe window 
	system("cls");

	//printing the top wall of the window
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			//printing the head of the snake
			if (i == headPostion_y && j == headPostion_x)
				cout << "O";
			else if (i == fruitPosition_y && j == fruitPosition_x)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
}

//taking keyboard input from user
void Input()
{
	//_kbhit returns a nonzero value if a key has been pressed. 
	//Otherwise, it returns 0.
	if (_kbhit())
	{
		// _getch() Returns the character read.
		// switch is used to take the input from the keyboard for directions of the 
		// snake i.t a,s,w,d ( std keys used in games ).
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = headPostion_x;
	tailY[0] = headPostion_y;

	//loop to increase the tail of the snake which will increase after eating the fruit
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		headPostion_x--;
		break;
	case RIGHT:
		headPostion_x++;
		break;
	case UP:
		headPostion_y--;
		break;
	case DOWN:
		headPostion_y++;
		break;
	default:
		break;
	}
	//if (x > width || x < 0 || y > height || y < 0)
	//gameOver = true;

	if (headPostion_x >= width) headPostion_x = 0; else if (headPostion_x < 0) headPostion_x = width - 1;
	if (headPostion_y >= height) headPostion_y = 0; else if (headPostion_y < 0) headPostion_y = height - 1;

	//if snake touches it own snake then the game will terminate 
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == headPostion_x && tailY[i] == headPostion_y)
			gameOver = true;

	//score will incerese if snake eats the fruit.
	if (headPostion_x == fruitPosition_x && headPostion_y == fruitPosition_y)
	{
		score += 10;
		//genrate fruit at the random position on the screen 
		fruitPosition_x = rand() % width;
		fruitPosition_y = rand() % height;
		nTail++;
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

		// sleep is not required but it slows the game which reduces the flickering of the screen
		Sleep(10);
	}
	return 0;
}



