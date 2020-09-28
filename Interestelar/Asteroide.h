#include "Endurance.h"
#pragma once
class Asteroide
{
protected: //cambiamos la protecci�n de los atributos a protegidos para ser accesibles por sus hijos
	int x;
	int y;
	int dureza; //cuantos disparos hacen falta para destruirlo
public:
	Asteroide(int, int, int);
	int getX();
	int getY();
	int getDureza();
	void setDureza(int);
	void dibujar();
	void mover();
	void borrar(); //borro fotograma
	void eliminar(); //env�o asteroide a posicion aleatoria
	bool colision(Endurance&); //pasarlo por referencia 
};								//para que los cambios realizados en los par�metros
								//dentro del objetp se conserven al retornar de la llamada

class Asteroide_m : public Asteroide
{
public:
	Asteroide_m(int, int, int); //hereda sus coordenadas de la clase padre Asteroide
	void dibujar(); //cambia, ahora ser� m�s grande
	void mover(); //cambia, habr� que ocultar m�s dibujo
	void borrar(); //cambia, borramos m�s tama�o
	void eliminar(); //cambia, debido a cambio de tama�o
	bool colision(Endurance&); //cambia, debido a cambio de tama�o
};

class Asteroide_g : public Asteroide
{
public:
	Asteroide_g(int, int, int); //hereda sus coordenadas de la clase padre Asteroide
	void dibujar(); //cambia, ahora ser� m�s grande
	void mover(); //cambia, habr� que ocultar m�s dibujo
	void borrar(); //cambia, borramos m�s tama�o
	void eliminar(); //cambia, debido a cambio de tama�o
	bool colision(Endurance&); //cambia, debido a cambio de tama�o
};