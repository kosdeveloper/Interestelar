#include "Asteroide.h"
#include"funciones.h"
#include "Endurance.h"

Asteroide::Asteroide(int x, int y, int dureza)
{
	this->x = x;
	this->y = y;
	this->dureza = dureza;
}

int Asteroide::getX()
{
	return x;
}

int Asteroide::getY()
{
	return y;
}

int Asteroide::getDureza()
{
	return dureza;
}

void Asteroide::setDureza(int dureza)
{
	this->dureza=dureza;
}

void Asteroide::dibujar()
{
	color("marron");
	gotoxy(x, y); cout << "O";
}

void Asteroide::mover()
{
	borrar();
	y++;
	if (y > 37) {
		eliminar();
	}
	dibujar();
	//Sleep(200);//velocidad asteroide:
			//0-muy rápido / 50-rápido / 100-medio / 150-lento /200-muy lento
}

void Asteroide::borrar()
{
	gotoxy(x, y); cout << " ";
}

void Asteroide::eliminar()
{
	x = rand() % 94 + 4;//número aleatorio entre 4 y 97
	y = 4;
}

bool Asteroide::colision(Endurance& E)
{	//si las coordenadas del asteroide coinciden el rango de coordenadas de la nave
		if ((x >= (E.getX())) && (x < (E.getX() + 7)) && (y >= E.getY()) && (y < (E.getY() + 5))) {
			E.setSalud(E.getSalud() - 1);
			E.borrar();
			E.dibujar();
			E.dibujar_salud();
			eliminar(); //elimina asteroide enviandolo a posición aleatoria
			//PlaySound(TEXT("sonido//alerta1.wav"), NULL, SND_LOOP | SND_ASYNC);
			return true;
		}
		else return false;
}

//CLASE HIJA: ASTEROIDE MEDIANO
Asteroide_m::Asteroide_m(int x, int y, int dureza):Asteroide(x,y,dureza)
{

}

void Asteroide_m::dibujar()
{
	color("gris");
	if (dureza == 2) {
		gotoxy(x, y);   cout << " __ ";
		gotoxy(x, y + 1); cout << "(__)";
	}
	else {
		gotoxy(x, y);   cout << " __ ";
		gotoxy(x, y + 1); cout << "(XX)";
	}
}

void Asteroide_m::mover()
{
	borrar();
	y++;
	if (y > 36) {
		eliminar();
	}
	dibujar();
}

void Asteroide_m::borrar()
{
	gotoxy(x, y); cout << "    ";
	gotoxy(x, y + 1); cout << "    ";
}

void Asteroide_m::eliminar()
{
	x = rand() % 91 + 4;//número aleatorio entre 4 y 94
	y = 4;
}

bool Asteroide_m::colision(Endurance& E)
{	//si las coordenadas del asteroide coinciden el rango de coordenadas de la nave
	if (
		(
			(x >= (E.getX())) && (x < (E.getX() + 7)) &&
			(y >= E.getY()) && (y < (E.getY() + 5))
			) ||
		(
			(x + 3 >= (E.getX())) && (x + 3 < (E.getX() + 7)) &&  //coordenadas otro expremo del asteroide
			(y + 1 >= E.getY()) && (y + 1 < (E.getY() + 5))
			)
		) {
		E.setSalud(E.getSalud() - 2); //genera más daño
		borrar(); //borramos asteroide
		eliminar(); //elimina asteroide enviandolo a posición aleatoria
		E.borrar();
		E.dibujar();
		E.dibujar_salud();
		//PlaySound(TEXT("sonido//alerta1.wav"), NULL, SND_LOOP | SND_ASYNC);
		return true;
	}
	else return false;
}

//CLASE HIJA: ASTEROIDE GRANDE
Asteroide_g::Asteroide_g(int x, int y, int dureza) :Asteroide(x, y, dureza)
{

}

void Asteroide_g::dibujar()
{
	color("rojo");
	if (dureza == 4) {
		gotoxy(x, y);     cout << (char)218<<(char)196 << (char)196 << (char)196 << (char)196 << (char)191;
		gotoxy(x, y + 1); cout << (char)179<<"    " << (char)179;
		gotoxy(x, y + 2); cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217;
	}
	else if (dureza == 3){
		gotoxy(x, y);     cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191;
		gotoxy(x, y + 1); cout << (char)179 << "X   " << (char)179;
		gotoxy(x, y + 2); cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217;
	}
	else if (dureza == 2) {
		gotoxy(x, y);     cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191;
		gotoxy(x, y + 1); cout << (char)179 << "X  X" << (char)179;
		gotoxy(x, y + 2); cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217;
	}
	else {
		gotoxy(x, y);     cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191;
		gotoxy(x, y + 1); cout << (char)179 << "XXXX" << (char)179;
		gotoxy(x, y + 2); cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217;
	}
}

void Asteroide_g::mover()
{
	borrar();
	y++;
	if (y > 35) {
		eliminar();
	}
	dibujar();
}

void Asteroide_g::borrar()
{
	gotoxy(x, y); cout << "      ";
	gotoxy(x, y + 1); cout << "      ";
	gotoxy(x, y + 2); cout << "      ";
}

void Asteroide_g::eliminar()
{
	x = rand() % 89 + 4;//número aleatorio entre 4 y 92
	y = 4;
}

bool Asteroide_g::colision(Endurance& E)
{	//si las coordenadas del asteroide coinciden el rango de coordenadas de la nave
	if (
		(
			(x >= (E.getX())) && (x < (E.getX() + 7)) &&
			(y >= E.getY()) && (y < (E.getY() + 5))
			) ||
		(
			(x + 3 >= (E.getX())) && (x + 3 < (E.getX() + 7)) &&  //coordenadas otro expremo del asteroide
			(y + 1 >= E.getY()) && (y + 1 < (E.getY() + 5))
			)
		) {
		E.setSalud(E.getSalud() - 4); //genera más daño
		borrar(); //borramos asteroide
		eliminar(); //elimina asteroide enviandolo a posición aleatoria
		E.borrar();
		E.dibujar();
		E.dibujar_salud();
		//PlaySound(TEXT("sonido//alerta2.wav"), NULL, SND_LOOP | SND_ASYNC);
		return true;
	}
	else return false;
}
