#include "Endurance.h"
#pragma once
class Asteroide
{
protected: //cambiamos la protección de los atributos a protegidos para ser accesibles por sus hijos
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
	void eliminar(); //envío asteroide a posicion aleatoria
	bool colision(Endurance&); //pasarlo por referencia 
};								//para que los cambios realizados en los parámetros
								//dentro del objetp se conserven al retornar de la llamada

class Asteroide_m : public Asteroide
{
public:
	Asteroide_m(int, int, int); //hereda sus coordenadas de la clase padre Asteroide
	void dibujar(); //cambia, ahora será más grande
	void mover(); //cambia, habrá que ocultar más dibujo
	void borrar(); //cambia, borramos más tamaño
	void eliminar(); //cambia, debido a cambio de tamaño
	bool colision(Endurance&); //cambia, debido a cambio de tamaño
};

class Asteroide_g : public Asteroide
{
public:
	Asteroide_g(int, int, int); //hereda sus coordenadas de la clase padre Asteroide
	void dibujar(); //cambia, ahora será más grande
	void mover(); //cambia, habrá que ocultar más dibujo
	void borrar(); //cambia, borramos más tamaño
	void eliminar(); //cambia, debido a cambio de tamaño
	bool colision(Endurance&); //cambia, debido a cambio de tamaño
};