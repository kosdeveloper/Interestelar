#pragma once
class Agujeronegro
{
private: //cambiamos la protección de los atributos a protegidos para ser accesibles por sus hijos
	int x;
	int y;
	char direccion; //d=derecha | i=izquierda
public:
	Agujeronegro(int, int, char);
	int getX();
	int getY();
	void dibujar();
	void borrar();
	void mover();
};

