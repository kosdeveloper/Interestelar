#include<iostream>
#include<windows.h> //juego para windows: necesario para GetStdHandle, SetConsoleCursorPosition...
#include<conio.h> //para detectar pulsación de teclado
#include <fstream> //para manejo de ficheros
#include <iomanip>

using namespace std;

#pragma once

//codigo de teclas para _getch
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE_BAR 32

static void gotoxy(int x, int y) { //static para evitar definicion doble
	HANDLE Ventana;
	Ventana = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cord;
	cord.X = x;
	cord.Y = y;
	SetConsoleCursorPosition(Ventana, cord);
}

static void ocultarCursor() {
	HANDLE Ventana;
	Ventana = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci; //creamos estructura de este tipo
//https://docs.microsoft.com/en-us/windows/console/console-cursor-info-str
	cci.dwSize = 1; //accedemos al atributo sobre el estilo del cursor (grosor 1 a 100)
	cci.bVisible = FALSE; //atributo de visibilidad del cursor: FALSE -> invisible
	SetConsoleCursorInfo(Ventana, &cci); //cci se pasa por referencia
	//Arg1: Handle
	//Arg2: Estructura de datos CONSOLE_CURSOR_INFO
}

static void listaASCII() {
	for (int i = 0; i < 255; i++) {
		cout << i<<": "<<(char)i<<endl;
	}
}

static void color(string color) {
	HANDLE Ventana; //creo manejador
	Ventana = GetStdHandle(STD_OUTPUT_HANDLE);

	int k = 15;
	if (color == "marron") k = 6;
	else if (color == "gris") k = 8;
	else if (color == "azul") k = 9;
	else if (color == "verde") k = 10;
	else if (color == "cyan") k = 11;
	else if (color == "rojo") k = 12;
	else if (color == "rosa") k = 13;
	else if (color == "amarillo") k = 14;
	else if (color == "blanco") k = 15;
	else if (color == "todoblanco") k = 255;

	SetConsoleTextAttribute(Ventana, k);
}

static void dibujar_limites() {
	color("gris");
	//limites horizontales
	for (int i = 3; i < 98; i++) {
		gotoxy(i, 3); cout << (char)205;
		gotoxy(i, 38); cout << (char)205;
	}
	//limites verticales
	for (int i = 4; i < 38; i++) {
		gotoxy(2, i); cout << (char)186;
		gotoxy(98, i); cout << (char)186;
	}
	//esquinas
	gotoxy(2, 3); cout << (char)201; //arriba izquierda
	gotoxy(2, 38); cout << (char)200; //abajo izquierda
	gotoxy(98, 3); cout << (char)187; //arriba derecha
	gotoxy(98, 38); cout << (char)188; //abajo derecha
}

static void dibuja_titulo(int x, int y) {
	color("azul");
	//link: http://patorjk.com/software/taag/#p=display&h=2&v=0&f=Modular&t=Interestelar
	gotoxy(x, y);     cout << " ___ __    _ _______ _______ _____   _______ _______ _______ _______ ___     _______ _____";
	gotoxy(x, y + 1); cout << "|   |  |  | |       |       |   _ | |       |       |       |       |   |   |   _   |   _ |";
	gotoxy(x, y + 2); cout << "|   |   |_| |_     _|    ___|  | || |    ___|  _____|_     _|    ___|   |   |  |_|  |  | ||";
	gotoxy(x, y + 3); cout << "|   |       | |   | |   |___|  |_||_|   |___| |_____  |   | |   |___|   |   |       |  |_||_";
	gotoxy(x, y + 4); cout << "|   |  _    | |   | |    ___|   __  |    ___|_____  | |   | |    ___|   |___|       |   __  |";
	gotoxy(x, y + 5); cout << "|   | | |   | |   | |   |___|  |  | |   |___ _____| | |   | |   |___|       |   _   |  |  | |";
	gotoxy(x, y + 6); cout << "|___|_|  |__| |___| |_______|__|  |_|_______|_______| |___| |_______|_______|__| |__|__|  |_|";
}


static void dibuja_gameover(int x, int y) {
	color("rojo");
	gotoxy(x, y);     cout << " _______ _______ __   __ _______    _______ __   __ _______ _____ ";
	gotoxy(x, y + 1); cout << "|       |   _   |  |_|  |       |  |       |  | |  |       |   _ |";
	gotoxy(x, y + 2); cout << "|    ___|  |_|  |       |    ___|  |   _   |  |_|  |    ___|  | ||";
	gotoxy(x, y + 3); cout << "|   | __|       |       |   |___   |  | |  |       |   |___|  |_||_";
	gotoxy(x, y + 4); cout << "|   ||  |       |       |    ___|  |  |_|  |       |    ___|   __  |";
	gotoxy(x, y + 5); cout << "|   |_| |   _   | ||_|| |   |___   |       ||     ||   |___|  |  | |";
	gotoxy(x, y + 6); cout << "|_______|__| |__|_|   |_|_______|  |_______| |___| |_______|__|  |_|";
}

static void dibuja_agujeronegro(int x, int y) {
	color("blanco");
	gotoxy(x, y);     cout << "       "<<(char)219<<(char)219<<(char)219 << (char)219 << (char)219 << (char)219 << "       ";
	gotoxy(x, y + 1); cout << "     "<<(char)219<<(char)219<<"      " << (char)219 << (char)219 << "     ";
	gotoxy(x, y + 2); cout <<(char)220<<(char)220<< (char)220 << (char)220<<(char)219<<(char)219<<(char)220<<(char)220<< (char)220 << (char)220<<(char)220<<(char)220<< (char)220 << (char)220<< (char)220 << (char)219<<(char)219<< (char)220 << (char)220 << (char)220 << (char)220;
	gotoxy(x, y + 3); cout << "     "<<(char)219<<(char)219<<"      "<<(char)219<<(char)219<<"     ";
	gotoxy(x, y + 4); cout << "       " << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << "       ";
	gotoxy(x+10, y + 5); cout << (char)254;
}

static void dibujo_youwin(int x, int y) {
	gotoxy(x, y);     cout << " __   __  _______  __   __    _     _  ___   __    _ ";
	gotoxy(x, y + 1); cout << "|  | |  ||       ||  | |  |  | | _ | ||   | |  |  | |";
	gotoxy(x, y + 2); cout << "|  |_|  ||   _   ||  | |  |  | || || ||   | |   |_| |";
	gotoxy(x, y + 3); cout << "|       ||  | |  ||  |_|  |  |       ||   | |       |";
	gotoxy(x, y + 4); cout << "|_     _||  |_|  ||       |  |       ||   | |  _    |";
	gotoxy(x, y + 5); cout << "  |   |  |       ||       |  |   _   ||   | | | |   |";
	gotoxy(x, y + 6); cout << "  |___|  |_______||_______|  |__| |__||___| |_|  |__|";
}

static void dibuja_youwin(int x, int y) {
	color("azul");
	dibujo_youwin(x, y);
	Sleep(500);
	color("blanco");
	dibujo_youwin(x, y);
	Sleep(500);
}

static void leer_fichero() {
	char cadena[128];
	ifstream fe("highscore.txt"); //abre fichero de entrada: input file stream

	// Leeremos mediante getline, si lo hiciéramos 
   // mediante el operador << sólo leeríamos 
   // parte de la cadena:
	for (int i = 0; i < 3; i++) { //lee tres lineas y enumara posiciones
		fe.getline(cadena, 128); //lee hasta salto de linea
		gotoxy(45, 21+i); cout << i+1<< ". " << cadena << endl;
	}

	fe.close(); //cierra fichero
}

static void escribir_fichero(string nickname, int puntos) {
	//ofstream fs("highscore.txt");  //abre fichero de salida: output file stream
	ofstream fs("highscore.txt", ios::app);	//ios::app => inserta al final del fichero
	fs << setw(10) << nickname << " " << setw(4) << puntos << endl;
	fs.close(); //cierra fichero
}
