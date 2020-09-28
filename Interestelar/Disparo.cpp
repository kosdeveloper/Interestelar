#include "Disparo.h"
#include "funciones.h"

Disparo::Disparo(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Disparo::getX()
{
	return x;
}

int Disparo::getY()
{
	return y;
}

void Disparo::mover()
{
	color("cyan");
	gotoxy(x, y); cout << " ";
	if (y > 4) y--;
	gotoxy(x, y); cout << "|";
}

void Disparo::borrar()
{
	gotoxy(x, y); cout << " ";
}

void Disparo::eliminar()
{
	y = 5;
}

bool Disparo::fuera()
{
	if (y <= 5) return true;
	else return false;
}
