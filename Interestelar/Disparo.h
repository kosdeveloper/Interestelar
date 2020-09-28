#pragma once
class Disparo
{
private:
	int x;
	int y;
public:
	Disparo(int, int);
	int getX();
	int getY();
	void mover();
	void borrar(); //borro fotograma
	void eliminar(); //envio disparo fuera
	bool fuera();
};

