#include<iostream>
#include<windows.h> //juego para windows: necesario para GetStdHandle, SetConsoleCursorPosition...
#include<conio.h> //para detectar pulsación de teclado
#include<list> //para crear listas de objetos
#include<ctime> //para temporizar con clock
#include"funciones.h"
#include"Endurance.h"
#include"Asteroide.h"
#include"Disparo.h"
#include"Agujeronegro.h"
#include<algorithm> //para random_suffle
#include<iomanip>

//FMOD
#include "fmod.hpp"
#include "common.h"


using namespace std;


int FMOD_Main() { //hay q cambiar nombre del main() a FMOD_Main()

	/////FMOD///////////////////////////////////////////

	FMOD::System* sistema;
	FMOD::Sound* sound1, * sound2, * sound3, * sound4, * sound5, * sound6, * sound7, * sound8;
	FMOD::Channel* channel = 0;
	FMOD_RESULT       result;
	unsigned int      version;
	void* extradriverdata = 0;

	//Common_Init(&extradriverdata);

	result = FMOD::System_Create(&sistema);
	ERRCHECK(result);

	result = sistema->getVersion(&version);
	ERRCHECK(result);

	if (version < FMOD_VERSION)
	{
		Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
	}

	result = sistema->init(32, FMOD_INIT_NORMAL, extradriverdata);
	ERRCHECK(result);

	result = sistema->createSound(Common_MediaPath("sonido/musica.wav"), FMOD_DEFAULT, 0, &sound1);
	ERRCHECK(result);
	result = sound1->setMode(FMOD_LOOP_NORMAL);   // FMOD_LOOP_OFF o FMOD_LOOP_NORMAL
	ERRCHECK(result);                           

	result = sistema->createSound(Common_MediaPath("sonido/disparo.wav"), FMOD_DEFAULT, 0, &sound2);
	ERRCHECK(result);

	result = sistema->createSound(Common_MediaPath("sonido/alerta1.wav"), FMOD_DEFAULT, 0, &sound3);
	ERRCHECK(result);

	result = sistema->createSound(Common_MediaPath("sonido/explosion_asteroide_m.wav"), FMOD_DEFAULT, 0, &sound4);
	ERRCHECK(result);

	result = sistema->createSound(Common_MediaPath("sonido/alerta2.wav"), FMOD_DEFAULT, 0, &sound5);
	ERRCHECK(result);

	result = sistema->createSound(Common_MediaPath("sonido/inicio_nave.wav"), FMOD_DEFAULT, 0, &sound6);
	ERRCHECK(result);

	result = sistema->createSound(Common_MediaPath("sonido/game_over.wav"), FMOD_DEFAULT, 0, &sound7);
	ERRCHECK(result);

	result = sistema->createSound(Common_MediaPath("sonido/you_win.wav"), FMOD_DEFAULT, 0, &sound8);
	ERRCHECK(result);
	///////////////////////////////////////////////////

	//listaASCII();
	//exit(0);
menu:
	system("cls");
	ocultarCursor();
	dibujar_limites();
	dibuja_titulo(4, 5);
	//PlaySound(TEXT("sonido//musica.wav"), NULL, SND_LOOP | SND_ASYNC);
	result = sistema->playSound(sound1, 0, false, &channel);
	ERRCHECK(result);

	///MENU
	color("cyan");
	gotoxy(45, 20); cout << "1.Jugar";
	gotoxy(45, 22); cout << "2.Puntuaciones";
	gotoxy(45, 24); cout << "3.Salir";
	while (1) {
		if (_kbhit()) {
			char opcion = _getch();
			switch (opcion) {
			case('1'): //Jugar
				//gotoxy(45, 20); cout << "       ";
				//gotoxy(45, 22); cout << "       ";
				goto jugar;
				break;
			case('2'): ////muestra highscore
				system("cls");
				color("gris"); dibujar_limites();
				gotoxy(45, 19); cout << "HIGH SCORE";
				leer_fichero();
				Sleep(1000);
				while (GetKeyState(VK_RETURN)>0);
				goto menu;
				break;
			case('3'): //Salir
				///Finalizacion FMOD /////////////////
				result = sound1->release();
				ERRCHECK(result);
				result = sound2->release();
				ERRCHECK(result);
				result = sound3->release();
				ERRCHECK(result);
				result = sound4->release();
				ERRCHECK(result);
				result = sound5->release();
				ERRCHECK(result);
				result = sound6->release();
				ERRCHECK(result);
				result = sistema->close();
				ERRCHECK(result);
				result = sistema->release();
				ERRCHECK(result);

				Common_Close();
				///////////////////////////////////
				system("cls");
				exit(0);
				break;
			}
		}
	}
jugar:
	system("cls");
	color("gris"); dibujar_limites();
	srand(time(NULL));
	//creo lista de punteros a objetos de la clase asteroide 
	list<Asteroide*> l_ast;
	list<Asteroide*>::iterator it_ast;
	//creo lista de punteros a objetos de la clase asteroide mediano
	list<Asteroide_m*> l_astm;
	list<Asteroide_m*>::iterator it_astm;
	//creo lista de punteros a objetos de la clase asteroide grande
	list<Asteroide_g*> l_astg;
	list<Asteroide_g*>::iterator it_astg;
	//creo lista de punteros a objetos de la clase disparo
	list<Disparo*> l_disp;
	list<Disparo*>::iterator it;
	//creo lista de punteros a objetos de la clase agujeronegro
	list<Agujeronegro*> l_agu;
	list<Agujeronegro*>::iterator it_agu;

	Endurance endurance(45,30,9,3); //creamos la nave en esta posición
 					//con 3 vidas y salud llena (9)
	endurance.dibujar(); //dibujo la nave
	//PlaySound(TEXT("sonido//inicio_nave.wav"), NULL, SND_ASYNC);
	result = sistema->playSound(sound6, 0, false, &channel);
	ERRCHECK(result);

	endurance.dibujar_salud();

	bool game_over = false;
	int puntos=0;
	clock_t t0a, t0b, t1, t2, t3, t4;
	int tiempo; //tiempo general del juego
	float tiempo_ast = 0;//tiempo asteroides (seg)
	float tiempo_tecla_aleat = 0; //tiempo teclas aleatorias
	int cuenta_atras = 2; //contador de segundos cuenta atrás
	int tiempo_ini_count; //variable para almacenar el tiempo inicial
	t1 = clock(); //inicio tiempo asteroides
	t3 = clock(); //inicio tiempo teclas aleatorias
	int tiempo_disp; //tiempo disparo (seg)
	int tiempo_astm = 0;
	int tiempo_astg = 0;
	int sleep_x5=0; //flag para temporizar un sleep x 5veces
	int sleep_x8 = 0;
	int sleep_x2 = 0;
	t0a = clock(); //actualizacion tiempo general del juego
	int tmpSalud = 0;
	bool mov_aleat=false;

	while (!game_over) {
		t0b = clock(); //actualizacion tiempo general del juego
		tiempo = (int)(t0b - t0a) / CLOCKS_PER_SEC; //
		//imprimimos tiempo
		color("gris");
		gotoxy(20, 2); cout << "Tiempo: " << tiempo;
		if (tiempo < 30) { //si pasan de 3 minutos 
			//creo un nuevo asteroide cada segundo hasta un max de 20
			t2 = clock();//tiempo asteroides
			tiempo_ast = ((float)(t2 - t1) / CLOCKS_PER_SEC);
			if (tiempo_ast > 5 && l_ast.size() < 10) { //si pasaron 5seg creo un nuevo asteroide
				l_ast.push_back(new Asteroide(rand() % 94 + 4, 4, 1));
				tiempo_ast = 0;
				tiempo_astm++;
				t1 = clock();
			}
			if (tiempo_astm == 2 && l_astm.size() < 5) { //si pasaron 10seg creo un nuevo asteroide mediano
				l_astm.push_back(new Asteroide_m(rand() % 91 + 4, 4, 2));
				tiempo_astm = 0;
				tiempo_astg++;
			}
			if (tiempo_astg == 2 && l_astg.size() < 3) { //si pasaron 20seg creo un nuevo asteroide mediano
				l_astg.push_back(new Asteroide_g(rand() % 91 + 4, 4, 4));
				tiempo_astg = 0;
			}
		}
		else if (!l_ast.empty()) { //cuando pase el tiempo fijado (3 min) destruyo todos los asteroides
			//borrar imagen y objetos
			for (it_ast = l_ast.begin(); it_ast != l_ast.end(); it_ast++) {
				(*it_ast)->borrar();
				delete(*it_ast); //borro el objeto
			}
			for (it_astm = l_astm.begin(); it_astm != l_astm.end(); it_astm++) {
				(*it_astm)->borrar();
				delete(*it_astm); //borro el objeto
			}
			for (it_astg = l_astg.begin(); it_astg != l_astg.end(); it_astg++) {
				(*it_astg)->borrar();
				delete(*it_astg); //borro el objeto
			}
			//eliminar los elementos de la lista
			while (!l_ast.empty())
			{
				l_ast.pop_front(); //elimino primer elemento
			}
			while (!l_astm.empty())
			{
				l_astm.pop_front(); //elimino primer elemento
			}
			while (!l_astg.empty())
			{
				l_astg.pop_front(); //elimino primer elemento
			}
			//que aparezca agujero negro => lista ya no está vacía
			l_agu.push_back(new Agujeronegro(40, 5, 'd'));
			mov_aleat = true; //habilitamos teclas aleatorias
			//situamos nave en posición alejada del agujeronegro
			endurance.borrar();
			endurance.setXY(45, 30);
			endurance.dibujar();
			tiempo_ini_count=tiempo; //para calculo de tiempo inicial de la cuenta atrás 
			//PlaySound(TEXT("sonido//musica_agujeronegro.wav"), NULL, SND_ASYNC);
		}


		//imprimimos puntuación
		color("gris");
		gotoxy(4, 2); cout << "Puntos: ";
		color("verde");
		cout << puntos;

		//gotoxy(40, 2); cout << setw(4) << GetKeyState(VK_SPACE);
		//detectamos pulsación de la barra espaciadora
		if (sleep_x2 == 2) {
			if (GetKeyState(VK_SPACE) < 0) { //GetKeyState: devuelve estado tecla:
											//si devuelve 1 => pulsada (0000 0001)
											//si devuelve 0 => no pulsada
											//-127:(0111 1111)
											//-128:(1000 0000)
				l_disp.push_back(new Disparo(endurance.getX() + 3, endurance.getY() - 1));
				result = sistema->playSound(sound2, 0, false, &channel);
				ERRCHECK(result);
			}
		}
		
		//if (!mov_aleat) {
		//	if (_kbhit()) {
		//		char tecla = _getch();
		//		if (tecla == SPACE_BAR) { //si pulsamos tecla espacio añadimos
		//			 //disparo a la lista
		//			//el disparo se crea con las coordenadas de la endurance más ajuste
		//			//para centrar el disparo
		//			l_disp.push_back(new Disparo(endurance.getX() + 3, endurance.getY() - 1));
		//			//reproducir sonido de disparo laser
		//			//PlaySound(TEXT("sonido//disparo.wav"), NULL, SND_ASYNC);
		//			result = sistema->playSound(sound2, 0, false, &channel);
		//			ERRCHECK(result);
		//		}
		//	}
		//}

		//recorremos la lista de disparos desde principio a fin
		for (it = l_disp.begin(); it != l_disp.end(); it++) {
			(*it)->mover(); //de esta manera podemos acceder a los metodos
							//del objeto a los que apunta el puntero *it en esa
							//iteración. (*it) se llama desreferenciación
			if ((*it)->fuera()) { //si el disparo está fuera lo eliminamos
				(*it)->borrar();
				delete(*it); //borro el objeto
				l_disp.erase(it); //elimina enlace al elemento
				break;

				//no funciona
				//delete(*it); //borramos elemento de la lista
				//it = ldisp.erase(it); //enlace el iterador
			}
		}

		//movemos asteroides y comprobamos colisión
		//recorremos la lista de asteroides pequeños
		for (it_ast = l_ast.begin(); it_ast != l_ast.end(); it_ast++) {
			(*it_ast)->mover();
			//(*it_ast)->colision(endurance);
			if (((*it_ast)->colision(endurance))==true) {
				result = sistema->playSound(sound3, 0, false, &channel);
				ERRCHECK(result);
			}
		}
		//recorremos la lista de asteroides medianos
		if (sleep_x5 == 5) {
			for (it_astm = l_astm.begin(); it_astm != l_astm.end(); it_astm++) {
				(*it_astm)->mover();
				//(*it_astm)->colision(endurance);
				if (((*it_astm)->colision(endurance)) == true) {
					result = sistema->playSound(sound3, 0, false, &channel);
					ERRCHECK(result);
				}
			}

		}
		//recorremos la lista de asteroides grandes
		if (sleep_x8 == 8) {
			for (it_astg = l_astg.begin(); it_astg != l_astg.end(); it_astg++) {
				(*it_astg)->mover();
				//(*it_astg)->colision(endurance);
				if (((*it_astg)->colision(endurance)) == true) {
					result = sistema->playSound(sound3, 0, false, &channel);
					ERRCHECK(result);
				}
			}
		}
		//para comprobar colisión entre disparos y asteroides
		//recorremos la lista de esteroides miramos sus coordenadas
		//y las comparamos con las de los disparos

		for (it = l_disp.begin(); it != l_disp.end(); it++) {
			//asteroides pequeños
			for (it_ast = l_ast.begin(); it_ast != l_ast.end(); it_ast++) {
				//si sus coordenadas son coincidentes
				if (((*it)->getX() == (*it_ast)->getX()) &&
					(((*it)->getY() == (*it_ast)->getY()) ||
						((*it)->getY() + 1 == (*it_ast)->getY()) ||
						((*it)->getY() - 1 == (*it_ast)->getY())
						)) {
					(*it)->borrar(); //borro disparo
					(*it)->eliminar(); //elimino disparo enviandolo fuera
					(*it_ast)->borrar(); //borro asteroide
					(*it_ast)->eliminar(); //elimino asteroide enviandolo a otra posición
					cout << "."; //dejo rastro de humo
					puntos += 5; //incrementamos puntos al dar al asteroide
					//PlaySound(TEXT("sonido//explosion_asteroide_p.wav"), NULL, SND_ASYNC);
					result = sistema->playSound(sound4, 0, false, &channel);
					ERRCHECK(result);
				}
			}
			//asteroides medianos
			for (it_astm = l_astm.begin(); it_astm != l_astm.end(); it_astm++) {
				//si sus coordenadas son coincidentes
				if (
					(
						((*it)->getX() >= (*it_astm)->getX()) && ((*it)->getX() < (*it_astm)->getX() + 5)
						) && (
							((*it)->getY() >= (*it_astm)->getY()) && ((*it)->getY() < (*it_astm)->getY() + 2)
							)
					) {
					if ((*it_astm)->getDureza() == 1) {
						(*it)->borrar(); //borro disparo
						(*it)->eliminar(); //elimino disparo enviandolo fuera
						(*it_astm)->setDureza(2);
						(*it_astm)->borrar(); //borro asteroide
						(*it_astm)->eliminar(); //elimino asteroide enviandolo a otra posición
						cout << "..."; //dejo rastro de humo
						puntos += 10; //incrementamos puntos al dar al asteroide
						//PlaySound(TEXT("sonido//explosion_asteroide_m.wav"), NULL, SND_ASYNC);
						result = sistema->playSound(sound4, 0, false, &channel);
						ERRCHECK(result);
					}
					else {
						(*it_astm)->setDureza(1);
						(*it)->borrar(); //borro disparo
						(*it)->eliminar(); //elimino disparo enviandolo fuera
					}
				}
			}
			//asteroides grandes
			for (it_astg = l_astg.begin(); it_astg != l_astg.end(); it_astg++) {
				//si sus coordenadas son coincidentes
				if (
					(
						((*it)->getX() >= (*it_astg)->getX()) && ((*it)->getX() < (*it_astg)->getX() + 6)
						) && (
							((*it)->getY() >= (*it_astg)->getY()) && ((*it)->getY() < (*it_astg)->getY() + 3)
							)
					) {
					if ((*it_astg)->getDureza() == 1) {
						(*it)->borrar(); //borro disparo
						(*it)->eliminar(); //elimino disparo enviandolo fuera
						(*it_astg)->setDureza(4);
						(*it_astg)->borrar(); //borro asteroide
						(*it_astg)->eliminar(); //elimino asteroide enviandolo a otra posición
						cout << "..."; //dejo rastro de humo
						puntos += 20; //incrementamos puntos al dar al asteroide
						//PlaySound(TEXT("sonido//explosion_asteroide_m.wav"), NULL, SND_ASYNC);
						result = sistema->playSound(sound4, 0, false, &channel);
						ERRCHECK(result);
					}
					else {
						(*it_astg)->setDureza((*it_astg)->getDureza()-1);
						(*it)->borrar(); //borro disparo
						(*it)->eliminar(); //elimino disparo enviandolo fuera
					}
				}
			}
		}

		if(mov_aleat==false) endurance.mover(); //muevo la nave
		else {//fase del agujero negro
			endurance.mover_aleatorio(); //muevo la nave
			//muevo agujero negro
			if (sleep_x2 == 2) {
				//if (!l_agu.empty()) {
				it_agu = l_agu.begin();
				(*it_agu)->mover();
				//}
			}
			//cambio aleatorio de teclas
			t4 = clock();//tiempo teclas aleatorias
			tiempo_tecla_aleat = ((float)(t4 - t3) / CLOCKS_PER_SEC);//tiempo teclas aleatorias en seg
			if (tiempo_tecla_aleat > 1) { //si pasaron 1seg genero otras teclas aleatorias
				int KEY[] = { 72,80,75,77 };
				random_shuffle(begin(KEY), end(KEY));
				endurance.setKeys(KEY[1], KEY[2], KEY[3], KEY[0]);
				t3 = clock();
			}
			//entrada de la nave en el agujero negro
			//si coinciden sus coordenadas centrales
			it_agu = l_agu.begin();
			if (endurance.getX()+4 == (*it_agu)->getX()+11 &&
				endurance.getY()+2 == (*it_agu)->getY()+3
				) goto youwin;

			//cuenta atrá desde 30
			if (tiempo - tiempo_ini_count == 1) { //si hay un segundo de diferencia
				cuenta_atras--;
				tiempo_ini_count = tiempo;
				//Beep(1568, 200);
			}
			if(cuenta_atras==0) game_over = true;
			//imprimimos cuenta atrás
			color("gris");
			gotoxy(40, 2); cout << "Cuenta: ";
			color("rojo");
			gotoxy(48, 2); cout << setw(2) << cuenta_atras;
		}
		
		endurance.dibujar();
		endurance.morir(); //compruebo salud de la nave

		//copruebo game over
		if (endurance.getVidas() == 0) {
			gotoxy(89, 2); cout << "         "; //borramos la salud 
			game_over = true;
		}
		
		if ((tmpSalud==2) && (endurance.getSalud()==1)) {
				result = sistema->playSound(sound5, 0, false, &channel);
				ERRCHECK(result);
				tmpSalud = 1;
		}
		tmpSalud = endurance.getSalud();

		Sleep(40); 
		if (sleep_x8 == 8) sleep_x8 = 0;
		else sleep_x8++;

		if (sleep_x5 == 5) sleep_x5 = 0;
		else sleep_x5++;

		if (sleep_x2 == 2) sleep_x2 = 0;
		else sleep_x2++;
		//game_over = true;

		result = sistema->update();
		ERRCHECK(result);

	}
	//GAME OVER
	//gotoxy(45, 20); cout << "GAME OVER";
	//PlaySound(TEXT("sonido//game_over.wav"), NULL, SND_ASYNC);
	result = sistema->playSound(sound7, 0, false, &channel);
	ERRCHECK(result);
	dibuja_gameover(15, 15);
	Sleep(5000); //espera para que salga Game Over durante algo de tiempo
	while (!GetKeyState(VK_RETURN));
	//goto highscore;
	goto highscore;

youwin:
	//PlaySound(TEXT("sonido//you_win.wav"), NULL, SND_ASYNC);
	result = sistema->playSound(sound8, 0, false, &channel);
	ERRCHECK(result);
	for(int i=0; i<10; i++) dibuja_youwin(25, 15); //efecto color cambiante
	do{
		dibuja_youwin(25, 15);
	} while (!GetKeyState(VK_RETURN));
	//goto menu;

highscore:
	system("cls");
	color("gris"); dibujar_limites();
	//revisa si la puntación debe estar en highscore
	//nick: 10 letras
	//puntuación 4 cifras
	// LLLLLLLLLL CCCC
	char cadena[15];
	char c_nickname[10];
	char c_puntuacion[4];
	char nickname[10];
	int puntuacion[3];
	string nicknames[3];
	ifstream fe("highscore.txt"); //abre fichero de entrada: input file stream

	for (int i = 0; i < 3; i++) { //lee tres lineas y enumara posiciones
		fe.getline(cadena, 15); //lee hasta salto de linea
		c_nickname[0] = cadena[0];
		c_nickname[1] = cadena[1];
		c_nickname[2] = cadena[2];
		c_nickname[3] = cadena[3];
		c_nickname[4] = cadena[4];
		c_nickname[5] = cadena[5];
		c_nickname[7] = cadena[7];
		c_nickname[8] = cadena[8];
		c_nickname[9] = cadena[9];

		c_puntuacion[0] = cadena[11];
		c_puntuacion[1] = cadena[12];
		c_puntuacion[2] = cadena[13];
		c_puntuacion[3] = cadena[14];
		puntuacion[i] = atoi(c_puntuacion);
		nicknames[i] = c_nickname;
		//gotoxy(45, 21 + i); cout << i + 1 << ". " << puntuacion[i] << endl;
	}
	fe.close(); //cierra fichero

	if (puntos > puntuacion[2]) {
		////guarda puntuación
		gotoxy(45, 19); cout << "Introduce nombre: ";
		gotoxy(64, 19); cin >> nickname;
		escribir_fichero(nickname, puntos);
		escribir_fichero(nicknames[0], puntuacion[0]);
		escribir_fichero(nicknames[1], puntuacion[1]);
	}
	////muestra highscore
	system("cls");
	color("gris"); dibujar_limites();
	gotoxy(45, 19); cout << "HIGH SCORE";
	leer_fichero();

	Sleep(5000);
	//while (!_kbhit());
	while (!GetKeyState(VK_RETURN)); //GetKeyState: devuelve estado tecla: si devuelve 1 => pulsada
	goto menu;													//si devuelve 0 => no pulsada
	
	return 0;
}