// gamesnake.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
// Dev  The Young 
//se integran las librerias para la compilacion de juego
#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
//variables del juego para integrar la funcionalidad
bool gameOver;
bool print;
const int width = 30; //se agrega el ancho de la interfaz en la ventana
const int height = 30; //se agrega la altura de la interfaz 
int tailX[100], tailY[100];
int ntail;
int x, y, frutitaX, frutitaY, puntaje;
// se agrega los movimientos de la serpiente 
enum Directon
{
	STOP = 0, LEFT, RIGHT, UP, DOWN
};
//juego para aplicacion de consola 
Directon dir; //coloco las direcciones para el movimiento de la figura
// se agrega las funcion incial de la configuracion del juego Serpiente 
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
// se crea la funcion dibujo, donde tendra la interfaz del juego y la figura serpiente
void Draw() {
	system("cls"); //metodo para limpiar una nueva partida.
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	//bucles de movimientos de la serpiente con forme  a la interfaz de la terminal 
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
	// se aplica el puntaje del usuario en el juego
	for (int i = 0; i < width + 2; i++) {
		cout << "#";
		cout << endl;
		cout << "Puntaje :" << puntaje << endl;
	}
}
// se agrega la funcion de input para el movimiento de la serpiente en el teclado
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
// se agrega la funcion logica para los movimientos de la serpiente 
//donde se graban en memoria los movimientos que realiza el usuario en el juego
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
	//se inserta un switch para las instrucciones del juego y la movilidad de la serpiente en la consola 
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
	//coordenadas del movimiento de juego de la serpiente, en la ventana del terminal
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
// Funcion principal donde se llaman las demas funciones con sus respectivas operaciones 
int main()
{	// la configuracion inicial
	Setup();
	while (!gameOver)
	{
		//coloco las funciones que tienen el proposito de activar las funciones de cada bloque
		Draw();
		input();
		Logic();
		//metodo sleep para suspender una ejecucion por un determinado tiempo asignado en el codigo
		Sleep(10);
	}
	return 0;
}