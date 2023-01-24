// gamesnake.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
// Dev  The Young 

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
bool gameOver;
bool print;
const int width = 30;
const int height = 30;
int tailX[100], tailY[100];
int ntail;
int x, y, frutitaX, frutitaY, puntaje;
enum Directon
{
	STOP = 0, LEFT, RIGHT, UP, DOWN
};

Directon dir; //coloco las direcciones para el movimiento de la figura
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	frutitaX = rand() % width;
	frutitaY = rand() % height;
	puntaje = 0;
}

void Draw() {
	system("cls"); //metodo para limpiar una nueva partida.
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == frutitaY && j == frutitaX)
				cout << "F";
			else {
				for (int k = 0; k < ntail; k++)
				{
					print = false;
					if (tailX[k] == j && tailY[k] == i) {
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
	for (int i = 0; i < width + 2; i++) {
		cout << "#";
		cout << endl;
		cout << "Puntaje :" << puntaje << endl;
	}
}
void input() {
	if (_kbhit())
	{
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
		default:
			break;
		}
	}
}
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < ntail; i++) {
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
		gameOver = true;
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) x = height - 1;
	for (int i = 0; i < ntail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	if (x == frutitaX && y == frutitaY) {
		puntaje += 10;
		frutitaX = rand() % width;
		frutitaY = rand() % height;
		ntail++;
	}

}
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		input();
		Logic();
		Sleep(10);
	}
	return 0;
}
