#include "Agujeronegro.h"
#include "funciones.h"

Agujeronegro::Agujeronegro(int x, int y, char direccion)
{
	this->x = x;
	this->y = y;
	this->direccion = direccion;
}

int Agujeronegro::getX()
{
	return x;
}

int Agujeronegro::getY()
{
	return y;
}

void Agujeronegro::dibujar()
{
	dibuja_agujeronegro(x, y);
}

void Agujeronegro::borrar()
{
	gotoxy(x, y);     cout << "                     ";
	gotoxy(x, y + 1); cout << "                     ";
	gotoxy(x, y + 2); cout << "                     ";
	gotoxy(x, y + 3); cout << "                     ";
	gotoxy(x, y + 4); cout << "                     ";
	gotoxy(x+10, y + 5); cout << " ";
}

void Agujeronegro::mover()
{
	borrar();
	if (direccion == 'd') {
		x++;
		if (x == 75) direccion = 'i';
	}
	else if (direccion == 'i') {
		x--;
		if (x == 4) direccion = 'd';
	}
	dibujar();
}
