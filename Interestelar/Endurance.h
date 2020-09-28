#pragma once
class Endurance
{
private:
	int x, y;
	int salud;
	int vidas;
	int key_up = 72;
	int key_down = 80;
	int key_left = 75;
	int key_right = 77;
public:
	Endurance(int,int,int,int);
	int getX();
	int getY();
	int getSalud();
	int getVidas();
	void setXY(int, int);
	void setSalud(int);
	void setKeys(int, int, int, int);
	void dibujar();
	void borrar();
	void mover();
	void mover_aleatorio();
	void dibujar_salud();
	void morir();
};