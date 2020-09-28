#include<iostream>
#include<windows.h> 
#include<conio.h> 
#include "Endurance.h"
#include"funciones.h"

using namespace std;

Endurance::Endurance(int x, int y, int salud, int vidas)
{
	this->x = x;
	this->y = y;
	this->salud = salud;
	this->vidas = vidas;
}

int Endurance::getX()
{
	return x;
}

int Endurance::getY()
{
	return y;
}

int Endurance::getSalud()
{
	return salud;
}

int Endurance::getVidas()
{
	return vidas;
}

void Endurance::setXY(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Endurance::setSalud(int salud)
{
	this->salud = salud;
}

void Endurance::setKeys(int key_up, int key_down, int key_left, int key_right)
{
	this->key_up = key_up;
	this->key_down = key_down;
	this->key_left = key_left;
	this->key_right = key_right;
}

void Endurance::dibujar() 
{ //tamaño 7x5
	color("azul");
	gotoxy(x, y); cout << "   " << (char) 254;
	gotoxy(x, y + 1); cout << " " << (char)47<<"   "<< (char)92;
	gotoxy(x, y + 2); cout << (char)254 << "  "<< (char)176 <<"--" << (char)254;
	gotoxy(x, y + 3); cout << " " << (char)92<< "   "<< (char)47;
	gotoxy(x, y + 4); cout << "   " << (char)254;
}

void Endurance::borrar()
{
	gotoxy(x, y);		cout << "       ";
	gotoxy(x, y + 1);	cout << "       ";
	gotoxy(x, y + 2);	cout << "       ";
	gotoxy(x, y + 3);	cout << "       ";
	gotoxy(x, y + 4);	cout << "       ";
}

void Endurance::mover()
{
	if ((GetKeyState(VK_UP) < 0) || (GetKeyState(VK_DOWN) < 0) ||
		(GetKeyState(VK_LEFT) < 0) || (GetKeyState(VK_RIGHT) < 0)) {
		borrar();
		if (GetKeyState(VK_UP) < 0) if (y > 5) y--;
		if (GetKeyState(VK_DOWN) < 0) if (y < 33) y++;
		if (GetKeyState(VK_LEFT) < 0) if (x > 3) x--;
		if (GetKeyState(VK_RIGHT) < 0) if (x < 91) x++;
		dibujar();
		dibujar_salud();
	}

	//if (_kbhit()) { //_kbhit (keyboardhit) detecta la presión de teclas 
	//		//guarda tecla pulsada
	//	char tecla = _getch();
	//	//borramos nave
	//	borrar();
	//	//determinamos tecla pulsada
	//	switch (tecla) {
	//	case KEY_UP: if (y > 5) y--; break;
	//	case KEY_DOWN: if (y < 33) y++; break;
	//	case KEY_LEFT: if (x > 3) x--; break;
	//	case KEY_RIGHT: if (x < 91) x++; break;
	//	default: break;
	//	}
	//	//para eliminar el parpadeo
	//	dibujar();
	//	dibujar_salud();
	//}
}

void Endurance::mover_aleatorio()
{
	if (_kbhit()) { //_kbhit (keyboardhit) detecta la presión de teclas 
			//guarda tecla pulsada
		char tecla = _getch();
		//borramos nave
		borrar();
		//determinamos tecla pulsada
		if (tecla == key_up)  if (y > 5) y--; 
		if (tecla == key_down) if (y < 33) y++; 
		if (tecla == key_left)  if (x > 3) x--; 
		if (tecla == key_right)  if (x < 91) x++; 
		//para eliminar el parpadeo
		dibujar();
		dibujar_salud();
	}
}

void Endurance::dibujar_salud()
{
	//imprimir vidas
	color("gris");
	gotoxy(70, 2); cout << "Vidas";
	gotoxy(76, 2); cout << "         ";
	color("rojo");
	for (int i = 0; i < vidas; i++) { //dibujo corazones de vida
		gotoxy(76 + i, 2); cout << (char)3;
	}
	//imprimir salud
	color("gris");
	gotoxy(82, 2); cout << "Salud";
	gotoxy(89, 2); cout << "         "; //borramos la salud para redibujar
	color("amarillo");
	int j = 0; //dibujo barra de salud
	for (int i = 0; i < salud; i++) { 
		if (i % 3 == 0)j++;
		gotoxy(89+i, 2); 
		cout << (char)(175+j);
	}
}

void Endurance::morir()
{
	color("rojo");
	if (salud <= 0) {
		//PlaySound(TEXT("sonido//explosion_asteroide_m.wav"), NULL, SND_ASYNC);
		borrar();//explosión 1er fotograma
		gotoxy(x, y + 1);	cout << "   *   ";
		gotoxy(x, y + 2);	cout << "  ***  ";
		gotoxy(x, y + 3);	cout << "   *   ";
		Sleep(200);
		borrar();//explosión 2do fotograma
		gotoxy(x, y);		cout << "   *   ";
		gotoxy(x, y + 1);	cout << " *   * ";
		gotoxy(x, y + 2);	cout << "*     *";
		gotoxy(x, y + 3);	cout << " *   * ";
		gotoxy(x, y + 4);	cout << "   *   ";
		Sleep(200);

		vidas--;//elimino una vida
		salud = 9; //relleno salud
		dibujar_salud();
		dibujar();
	}
}
