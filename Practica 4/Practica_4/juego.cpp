//PRACTICA 3: TORTUGAS ROBOTICAS
//Hecho por: Richard Junior Mercado Correa y Maryny Zara Castada Collado

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include "Juego.h"
#include "Secuencia.h"
#include "checkML.h"
using namespace std;

tEstadoCasilla conversorEstados(char pos, tCasilla &casilla);

void leerTecla(tTecla &teclita);
void colorFondo(int colorFondo);
void cambioColor(tCasilla casilla); //cambiamos color de las casillas
void num2carta(int num, tCarta &carta); //transformamos el numero recibido en una carta
void introducirSecuencia(tJuego &juego, tCarta carta); //introducimos la secuencia

void girarDerecha(tJuego &juego);
void girarIzquierda(tJuego &juego);
void avanzarTortuga(tJuego &juego);
void dispararLaser(tJuego &juego);

//*********** PRUEBAS ***********
//int main() {
//	bool cargado, ejecutado;
//	tJuego juego;
//	tJugador jugador;
//
//	cargado = crearJuego(juego);
//
//	
//	if (cargado) {
//			jugadores(juego);
//			mostrarJuego(juego);
//			ejecutarTurno(juego);
//	}
//	
//	system("pause");
//
//	return 0;
//}
//*******************************

bool crearJuego(tJuego &juego) { //iniciamos juego

	int numTab;
	bool encontrado = false, cargado;
	string fichero, aux;
	ifstream archivo;
	tCasilla casilla;

	typedef string tPosicion[NUM_FILAS];
	tPosicion posicion;

	cout << "Introduzca nombre del fichero: ";
	cin >> fichero;
	cout << endl;
	do {
		cout << "Introduzca numero de jugadores: ";
		cin >> juego.nJugadores;
	} while (juego.nJugadores > MAX_JUGADORES || juego.nJugadores < 1); //mientras el numero no sea valido...

	archivo.open(fichero);

	if (archivo.is_open()) { //obtenemos el tablero desde fichero

		archivo >> numTab;
		archivo.ignore();

		//buscamos el tablero
		encontrado = numTab == juego.nJugadores;
		while (!encontrado) {

			if (!encontrado) { //si no es el tablero que buscamos, saltamos de linea
				for (int i = 0; i < NUM_COLUMNAS; i++)
					getline(archivo, aux);

				archivo >> numTab;
				archivo.ignore();

				encontrado = numTab == juego.nJugadores;
			}
		}

		if (encontrado) { //si encontramos el tablero, extraemos el tablero y rellenamos la informacion correspondiente a cada casilla de dicho tablero

			int numTortuga = 0;
			int numJoya = 0;
			for (int i = 0; i < NUM_FILAS; i++) {
				getline(archivo, aux); //obtenemos linea por linea el tablero
				posicion[i] = aux;

				for (int j = 0; j < NUM_COLUMNAS; j++) {
					char pos;

					pos = posicion[i][j]; //extraemos los caracteres (casillas)
										  //rellenamos informacion correspondiente
					juego.tableroJuego[i][j].estado = conversorEstados(pos, casilla);

					if (juego.tableroJuego[i][j].estado == tortuga) { //si en la casilla hay tortuga rellenamos informacion
						juego.tableroJuego[i][j].tortuga.direccion = casilla.tortuga.direccion;
						juego.tableroJuego[i][j].tortuga.numero = numTortuga;
						juego.jugadores[numTortuga].posActual.fila = i;
						juego.jugadores[numTortuga].posActual.columna = j;
						numTortuga++;
					}

					else if (juego.tableroJuego[i][j].estado == joya) { //si en la casilla hay joya obtenemos su posicion
						juego.jugadores[numJoya].posJoya.fila = i;
						juego.jugadores[numJoya].posJoya.columna = j;
						numJoya++;
					}
				}
			}
			cargado = true;
		}
		else
			cout << "NO ENCONTRADO" << endl;
		archivo.close();
	}

	else {
		cout << "ERROR DE APERTURA!" << endl;
		cargado = false;
	}

	return cargado;
}

void jugadores(tJuego &juego) {
	tMazo mazo;
	tCarta carta;
	juego.turno = 0;

	for (int i = 0; i < juego.nJugadores; i++) {
		cout << "Introduzca nombre de jugador: ";
		cin >> juego.jugadores[i].nombre;

		//creamos el mazo...
		crearVacia(mazo);
		crearMazoAleatorio(mazo);
		juego.jugadores[i].numMano = 3; //numero de cartas inicial en la mano

		for (int j = 0; j < MAX_CARTAS_MAZO; j++) {
			juego.jugadores[i].mazo.lista[j] = mazo.lista[j];
			juego.jugadores[i].mazo.numcartas = mazo.numcartas;
		}


		//creamos la mano inicial...
		juego.jugadores[i].contadores.avanza = 0;
		juego.jugadores[i].contadores.derecha = 0;
		juego.jugadores[i].contadores.izquierda = 0;
		juego.jugadores[i].contadores.laser = 0;

		for (int k = 0; k < juego.jugadores[i].numMano; k++) { //contamos cuantas cartas de cada tipo hay
			bool sacado;

			sacado = sacar(mazo, carta);

			juego.jugadores[i].mazo.numcartas = mazo.numcartas;

			if (sacado) {
				juego.jugadores[i].mano[k] = carta;

				if (carta == avanzar)
					juego.jugadores[i].contadores.avanza++;
				else if (carta == giroDerecha)
					juego.jugadores[i].contadores.derecha++;
				else if (carta == giroIzquierda)
					juego.jugadores[i].contadores.izquierda++;
				else if (carta == laser)
					juego.jugadores[i].contadores.laser++;
			}

			else
				cout << "ERROR AL SACAR CARTA!";
		}

		for (int l = 0; l < mazo.numcartas; l++) //introducimos las cartas en la mano de cada jugador
			juego.jugadores[i].mazo.lista[l] = mazo.lista[l];
	}
}

void mostrarJuego(const tJuego & juego) {
	tCasilla casilla;

	system("cls");
	for (int i = 0; i < NUM_FILAS; i++) {
		for (int j = 0; j < NUM_COLUMNAS; j++) { //obtenemos la informacion del tablero para mostrar por pantalla
			casilla.estado = juego.tableroJuego[i][j].estado;
			if (casilla.estado == tortuga) { //si en la casilla hay una tortuga, extraemos su numero
				casilla.tortuga.numero = juego.tableroJuego[i][j].tortuga.numero;
			}
			casilla.tortuga.direccion = juego.tableroJuego[i][j].tortuga.direccion;
			cambioColor(casilla); //mostramos las casillas
		}
		cout << endl;
	}

	colorFondo(0);
	cout << endl << endl << "JUGADORES: " << endl << endl; //mostramos manos de jugadores

	for (int i = 0; i < juego.nJugadores; i++) {

		if (juego.turno == i) { //indicador de turno
			colorFondo(PALETA[i + 5]);
			cout << ">> ";
		}

		colorFondo(PALETA[i + 5]);

		cout << i + 1 << ". " << juego.jugadores[i].nombre << ":";

		//mostramos cartas
		colorFondo(0);
		cout << "	" << juego.jugadores[i].contadores.avanza << " ";
		colorFondo(PALETA[9]);
		cout << " ^ ";

		colorFondo(0);
		cout << "	" << juego.jugadores[i].contadores.derecha << " ";
		colorFondo(PALETA[9]);
		cout << " > ";

		colorFondo(0);
		cout << "	" << juego.jugadores[i].contadores.izquierda << " ";
		colorFondo(PALETA[9]);
		cout << " < ";

		colorFondo(0);
		cout << "	" << juego.jugadores[i].contadores.laser << " ";
		colorFondo(PALETA[9]);
		cout << " ~ ";

		colorFondo(0); // mostramos el mazo
		cout << "	Mazo: ";
		colorFondo(6);
		cout << " " << juego.jugadores[i].mazo.numcartas << " ";

		cout << endl;
	}
	colorFondo(0);

	cout << endl;
}

bool accionRobar(tJuego & juego) {
	bool robado;
	tMazo mazo;
	tCarta carta;

	mazo = juego.jugadores[juego.turno].mazo; //robamos carta
	robado = sacar(mazo, carta);

	//sumamos las cantidades de cartas de cada tipo
	if (carta == avanzar)
		juego.jugadores[juego.turno].contadores.avanza++;
	else if (carta == giroDerecha)
		juego.jugadores[juego.turno].contadores.derecha++;
	else if (carta == giroIzquierda)
		juego.jugadores[juego.turno].contadores.izquierda++;
	else
		juego.jugadores[juego.turno].contadores.laser++;

	//damos la mano y el mazo a cada jugador
	juego.jugadores[juego.turno].mazo = mazo;
	juego.jugadores[juego.turno].mano[juego.jugadores[juego.turno].numMano] = carta;
	juego.jugadores[juego.turno].numMano++;

	if (!robado)
		cout << "Error!";

	return robado;
}

bool ejecutarTurno(tJuego &juego) {
	bool ganador = false, robado;
	tMazo cartas;
	char opcion;

	while (juego.turno < juego.nJugadores && !ganador) { //mientras no haya ganador...
		mostrarJuego(juego);

		do {
			cout << "Es el turno de " << juego.jugadores[juego.turno].nombre << "!" << endl;;
			cout << "	R - ROBAR CARTA" << endl;
			cout << "	E - EJECUTAR SECUENCIA" << endl;
			cout << "Introduzca su proximo movimiento: ";
			cin >> opcion;

			opcion = toupper(opcion);

			cout << endl;
		} while ((opcion != 'R' && opcion != 'E') && juego.jugadores[juego.turno].mazo.numcartas == 0); //mientras la opcion no sea valida...

		if (opcion == 'E') { //obtenemos secuencia de cartas a jugar
			obtenerSecuencia(juego);
			ganador = accionSecuencia(juego, cartas);
		}

		else if (opcion == 'R') { //robamos carta
			if (juego.jugadores[juego.turno].mazo.numcartas > 0) {
				robado = accionRobar(juego);

				if (!robado)
					cout << "Error al robar carta!";
			}

			else
				cout << "No quedan cartas para robar";
		}

		if (!ganador) //si no hay ganador cambiamos el turno
			cambiarTurno(juego);

		mostrarJuego(juego);

		if (juego.turno == juego.nJugadores) //reiniciamos ciclo de turnos si todos los jugadores han hecho su jugada
			juego.turno = 0;
	}

	liberar(cartas); //eliminamos cartas de la secuencia

	return ganador;
}

void cambiarTurno(tJuego &juego) {
	juego.turno++;
}

void obtenerSecuencia(tJuego &juego) {
	tTecla tecla;
	bool encontrado = false;
	tCarta aux;

	juego.jugadores[juego.turno].secuencia.numcartas = 0; //iniciamos numero de cartas en la secuencia

	cout << "INSTRUCCIONES:" << endl
		<< endl
		<< "	FLECHA ARRIBA - avanzar" << endl
		<< "	FLECHA DERECHA - girar derecha" << endl
		<< "	FLECHA IZQUIERDA - girar izquierda" << endl
		<< "	ESPACIO - disparar laser" << endl
		<< endl
		<< "Introduzca secuencia: " << endl
		<< endl;
	do {

		cout << "Movimiento: "; //muestra nuestra secuencia de cartas
		leerTecla(tecla);

		if (juego.jugadores[juego.turno].numMano == 0) //si no hay cartas en la mano...
			cout << "No tienes cartas. Pasa de turno. ";

		//obtenemos la secuencia de cartas
		if ((tecla == AVANZA && juego.jugadores[juego.turno].contadores.avanza > 0) && juego.jugadores[juego.turno].numMano != 0) {
			cout << "^ " << endl;
			aux = avanzar;
			introducirSecuencia(juego, aux);
			juego.jugadores[juego.turno].contadores.avanza--;
		}

		else if ((tecla == DERECHA && juego.jugadores[juego.turno].contadores.derecha > 0) && juego.jugadores[juego.turno].numMano != 0) {
			cout << "> " << endl;
			aux = giroDerecha;
			introducirSecuencia(juego, aux);
			juego.jugadores[juego.turno].contadores.derecha--;
		}

		else if ((tecla == IZQUIERDA && juego.jugadores[juego.turno].contadores.izquierda > 0) && juego.jugadores[juego.turno].numMano != 0) {
			cout << "< " << endl;
			aux = giroIzquierda;
			introducirSecuencia(juego, aux);
			juego.jugadores[juego.turno].contadores.izquierda--;
		}

		else if ((tecla == LASER && juego.jugadores[juego.turno].contadores.laser > 0) && juego.jugadores[juego.turno].numMano != 0) {
			cout << "~ " << endl;
			aux = laser;
			introducirSecuencia(juego, aux);
			juego.jugadores[juego.turno].contadores.laser--;
		}

		else if (tecla == NADA)
			cout << "TECLA NO VALIDA! " << endl;

		else if (tecla == SALIR)
			cout << "HAS ELEGIDO SALIR!" << endl;

		else
			cout << "No te quedan cartas de este tipo! Introduce otro movimiento." << endl;

	} while (tecla != SALIR);
}

bool accionSecuencia(tJuego &juego, tMazo &cartas) {
	tCarta carta;
	bool ganador = false;

	for (int i = 0; i < juego.jugadores[juego.turno].secuencia.numcartas; i++) { //ejecutamos nuestra jugada mientras haya cartas en la secuencia
		carta = *juego.jugadores[juego.turno].secuencia.lista[0]; //utilizamos cartas (posteriormente seran eliminados por quitarCartaMano)

		if (carta == avanzar)
			avanzarTortuga(juego);

		else if (carta == giroDerecha)
			girarDerecha(juego);

		else if (carta == giroIzquierda)
			girarIzquierda(juego);

		else
			dispararLaser(juego);

		quitarCartaMano(juego, carta); //eliminamos cartas utilizadas y la ponemos al final del mazo


		int numjoya = 0;
		while (numjoya < juego.nJugadores && !ganador) { //comprobamos si la posicion de la tortuga corresponde con la posicion de la joya
			if (juego.jugadores[juego.turno].posActual.fila == juego.jugadores[numjoya].posJoya.fila &&
				juego.jugadores[juego.turno].posActual.columna == juego.jugadores[numjoya].posJoya.columna) {
				ganador = true;
			}
			numjoya++;
		}
	}


	return ganador;
}


//**********************auxiliares************************************

//transformamos caracteres por estados del tablero
tEstadoCasilla conversorEstados(char pos, tCasilla &casilla) {

	tEstadoCasilla estado;

	if (pos == 'D') {
		estado = tortuga;
		casilla.tortuga.direccion = sur;
	}
	else if (pos == 'R') {
		estado = tortuga;
		casilla.tortuga.direccion = este;
	}
	else if (pos == 'U') {
		estado = tortuga;
		casilla.tortuga.direccion = norte;
	}
	else if (pos == 'L') {
		estado = tortuga;
		casilla.tortuga.direccion = oeste;
	}
	else if (pos == 'C') estado = caja;
	else if (pos == ' ') estado = vacia;
	else if (pos == '#') estado = muro;
	else if (pos == '@') estado = hielo;
	else estado = joya;

	return estado;
}

void leerTecla(tTecla &teclita) {
	cin.sync(); int tecla = _getch();
	if (tecla == 0xe0) {// Tecla especial
		tecla = _getch();
		switch (tecla) {
		case 72: teclita = AVANZA; break;
		case 77: teclita = DERECHA; break;
		case 75: teclita = IZQUIERDA; break;
		default: teclita = NADA; break;
		}
	}
	else if (tecla == 32) teclita = LASER;
	else if (tecla == 13) teclita = SALIR;
	else teclita = NADA;
}

void cambioColor(tCasilla casilla) {
	switch (casilla.estado) {
	case vacia: colorFondo(PALETA[0]); cout << "  "; break;
	case tortuga:

		if (casilla.tortuga.numero == 0)
			colorFondo(PALETA[5]);
		else if (casilla.tortuga.numero == 1)
			colorFondo(PALETA[6]);
		else if (casilla.tortuga.numero == 2)
			colorFondo(PALETA[7]);
		else
			colorFondo(PALETA[8]);


		if (casilla.tortuga.direccion == norte)
			cout << "^^";
		else if (casilla.tortuga.direccion == oeste)
			cout << "<<";
		else if (casilla.tortuga.direccion == este)
			cout << ">>";
		else
			cout << "vv";

		break;

	case hielo: colorFondo(PALETA[1]); cout << "**"; break;
	case muro: colorFondo(PALETA[2]); cout << "||"; break;
	case caja: colorFondo(PALETA[3]); cout << "[]"; break;
	case joya: colorFondo(PALETA[4]); cout << "00"; break;
	}
}

void colorFondo(int colorFondo) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (colorFondo << 4));
}

void quitarCartaMano(tJuego &juego, tCarta carta) {
	bool encontrado = false;
	tMazo mazo;
	int aux;

	int posicion = 0;

	while (posicion < juego.jugadores[juego.turno].secuencia.numcartas && !encontrado) { //mientras no encontremos la carta a eliminar de la secuencia..
		encontrado = *juego.jugadores[juego.turno].secuencia.lista[posicion] == carta;
		posicion++;
	}

	if (encontrado) { //si encontramos la carta

		aux = *juego.jugadores[juego.turno].secuencia.lista[posicion - 1]; //transformamos numero en carta
		delete juego.jugadores[juego.turno].secuencia.lista[posicion - 1]; //borramos carta de la secuencia

		num2carta(aux, carta);

		mazo = juego.jugadores[juego.turno].mazo; //insertamos carta al fondo del mazo
		insertar(mazo, carta);
		juego.jugadores[juego.turno].mazo = mazo;

		for (int i = posicion; i < juego.jugadores[juego.turno].numMano; i++) //recolocamos la mano
			juego.jugadores[juego.turno].mano[i] = juego.jugadores[juego.turno].mano[i + 1];

		juego.jugadores[juego.turno].numMano--;
	}

	else
		cout << "No hay cartas de este tipo en tu mano!" << endl;
}

void num2carta(int num, tCarta &carta) {
	switch (num) {
	case 0: carta = avanzar; break;
	case 1: carta = giroIzquierda; break;
	case 2: carta = giroDerecha; break;
	case 3: carta = laser; break;
	}
}

//introducimos la carta en la secuencia
void introducirSecuencia(tJuego &juego, tCarta carta) {
	juego.jugadores[juego.turno].secuencia.lista[juego.jugadores[juego.turno].secuencia.numcartas] = new tCarta(carta);
	juego.jugadores[juego.turno].secuencia.numcartas++;
}


//********************ejecuciones de cartas***************************

void girarDerecha(tJuego &juego) {

	if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == norte)
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion = este;

	else if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == este)
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion = sur;

	else if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == sur)
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion = este;

	else
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion = norte;
}

void girarIzquierda(tJuego &juego) {

	if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == norte)
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion = oeste;

	else if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == este)
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion = norte;

	else if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == sur)
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion = oeste;

	else
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion = sur;

}

void avanzarTortuga(tJuego &juego) {
	if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == norte && juego.jugadores[juego.turno].posActual.fila > 0 &&
		(juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila - 1][juego.jugadores[juego.turno].posActual.columna].estado == vacia ||
			juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila - 1][juego.jugadores[juego.turno].posActual.columna].estado == joya ||
			(juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila - 1][juego.jugadores[juego.turno].posActual.columna].estado == caja &&
				juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila - 2][juego.jugadores[juego.turno].posActual.columna].estado == vacia))) {

		if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila - 1][juego.jugadores[juego.turno].posActual.columna].estado == caja)
			juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila - 2][juego.jugadores[juego.turno].posActual.columna].estado = caja;

		juego.jugadores[juego.turno].posActual.fila--;

		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].estado = tortuga;
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.numero = juego.turno;
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion = norte;
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila + 1][juego.jugadores[juego.turno].posActual.columna].estado = vacia;

	}

	else if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == este && juego.jugadores[juego.turno].posActual.columna < NUM_COLUMNAS - 1 &&
		(juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna + 1].estado == vacia ||
			juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna + 1].estado == joya ||
			(juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna + 1].estado == caja &&
				juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna + 2].estado == vacia))) {

		if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna + 1].estado == caja)
			juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna + 2].estado = caja;

		juego.jugadores[juego.turno].posActual.columna++;

		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].estado = tortuga;
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.numero = juego.turno;
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion = este;
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna - 1].estado = vacia;
	}

	else if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == sur && juego.jugadores[juego.turno].posActual.fila < NUM_FILAS - 1 &&
		(juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila + 1][juego.jugadores[juego.turno].posActual.columna].estado == vacia ||
			juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila + 1][juego.jugadores[juego.turno].posActual.columna].estado == joya ||
			(juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila + 1][juego.jugadores[juego.turno].posActual.columna].estado == caja &&
				juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila + 2][juego.jugadores[juego.turno].posActual.columna].estado == vacia))) {

		if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila + 1][juego.jugadores[juego.turno].posActual.columna].estado == caja)
			juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila + 2][juego.jugadores[juego.turno].posActual.columna].estado = caja;

		juego.jugadores[juego.turno].posActual.fila++;

		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].estado = tortuga;
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.numero = juego.turno;
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion = sur;
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila - 1][juego.jugadores[juego.turno].posActual.columna].estado = vacia;
	}

	else if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == oeste && juego.jugadores[juego.turno].posActual.columna > 0 &&
		(juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna - 1].estado == vacia ||
			juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna - 1].estado == joya ||
			(juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna - 1].estado == caja &&
				juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna - 2].estado == vacia))) {

		if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna - 1].estado == caja)
			juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna - 2].estado = caja;

		juego.jugadores[juego.turno].posActual.columna--;

		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].estado = tortuga;
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.numero = juego.turno;
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion = oeste;
		juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna + 1].estado = vacia;
	}
}

void dispararLaser(tJuego &juego) {

	if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == norte) {
		int pos = juego.jugadores[juego.turno].posActual.fila - 1;

		while (pos >= 0 && juego.tableroJuego[pos][juego.jugadores[juego.turno].posActual.columna].estado == vacia)
			pos--;

		if (juego.tableroJuego[pos][juego.jugadores[juego.turno].posActual.columna].estado == hielo)
			juego.tableroJuego[pos][juego.jugadores[juego.turno].posActual.columna].estado = vacia;
	}

	else if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == este) {
		int pos = juego.jugadores[juego.turno].posActual.columna + 1;

		while (pos <= NUM_COLUMNAS && juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][pos].estado == vacia)
			pos++;

		if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][pos].estado == hielo)
			juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][pos].estado = vacia;
	}

	else if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == sur) {
		int pos = juego.jugadores[juego.turno].posActual.fila + 1;

		while (pos <= NUM_FILAS && juego.tableroJuego[pos][juego.jugadores[juego.turno].posActual.columna].estado == vacia)
			pos++;

		if (juego.tableroJuego[pos][juego.jugadores[juego.turno].posActual.columna].estado == hielo)
			juego.tableroJuego[pos][juego.jugadores[juego.turno].posActual.columna].estado = vacia;

	}

	else if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][juego.jugadores[juego.turno].posActual.columna].tortuga.direccion == oeste) {
		int pos = juego.jugadores[juego.turno].posActual.columna - 1;

		while (pos >= 0 && juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][pos].estado == vacia)
			pos--;

		if (juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][pos].estado == hielo)
			juego.tableroJuego[juego.jugadores[juego.turno].posActual.fila][pos].estado = vacia;
	}
}