//PRACTICA 3: TORTUGAS ROBOTICAS
//Hecho por: Richard Junior Mercado Correa y Maryny Zara Castada Collado

#include <iostream>
#include <string>
#include "Secuencia.h"
#include "Puntuaciones.h"
#include "Juego.h"
using namespace std;

void menu(int &opcion);

int main() {
	tPuntuaciones puntos;
	string nombre;
	tJuego juego;
	bool cargado, creado, actualizado, guardado, hayGanador = false;
	int nuevos, opcion = -1;

	cargado = cargarPuntuaciones(puntos); // cargamos las puntuaciones 

	if (cargado) { //si cargado... ejecutamos menu

		while (opcion != 0) { //mientras la opcion no sea salir...
			menu(opcion);

			if (opcion == 1) {
				creado = crearJuego(juego); //creamos juego

				if (creado) {

					jugadores(juego);
					mostrarJuego(juego);

					while (!hayGanador) //mientras que no haya ganador ejecutar el juego
						hayGanador = ejecutarTurno(juego);

					cout << "Ha ganado " << juego.jugadores[juego.turno].nombre << "!" << endl << endl; //mostramos el ganador
					nombre = juego.jugadores[juego.turno].nombre;

					int pos = 0; bool encontrado = false;
					while (pos < puntos.num_jugadores && !encontrado) { //buscamos el nombre en la lista para ver que puntos recibe (si no esta, recibira 'juego.nJugadores' puntos; si esta, se suman los puntos)
						encontrado = nombre == puntos.puntuaciones[pos].nombre;
						pos++;
					}

					if (encontrado) //si esta en la lista, sumamos los puntos
						nuevos = puntos.puntuaciones[pos - 1].puntuacion + juego.nJugadores;

					else
						nuevos = juego.nJugadores; // si no esta en la lista, el jugador se llevara tantos puntos como jugadores haya

					actualizado = actualizarPuntuacion(puntos, nombre, nuevos);
					cout << nombre << " ha obtenido: " << juego.nJugadores << " punto(s)." << endl; //mostramos puntos que se lleva el jugador

					if (actualizado)
						hayGanador = false; //reiniciamos el juego

					else
						cout << "Error de actualizacion de puntos!" << endl;
				}

				else
					cout << "Error al crear el juego" << endl << endl;
			}

			else if (opcion == 2) { // mostramos puntos de la lista
				cout << "PUNTUACIONES: " << endl << endl;
				cout << "**********************************" << endl;
				mostrarPuntuaciones(puntos);
				cout << "**********************************" << endl << endl;
			}
		}

		guardado = guardarPuntuaciones(puntos); //guardamos las puntuaciones
		if (!guardado)
			cout << "Error de guardado!";

		cout << "Se han actualizado los puntos" << endl;
		cout << "FIN DEL JUEGO" << endl << endl;
	}

	else
		cout << "CARGA INCORRECTA!";

	system("pause");

	return 0;
}

void menu(int &opcion) { //mostrar menu
	do {
		cout << "Bienvenido a TORTUGAS ROBOTICAS!" << endl << endl;
		cout << "	1 - JUGAR" << endl;
		cout << "	2 - MOSTRAR PUNTOS" << endl;
		cout << "	0 - SALIR" << endl << endl;
		cout << "Introduzca su opcion: ";
		cin >> opcion;

		if (opcion < 0 || opcion > 2)
			cout << "Opcion no valida." << endl;

		cout << endl;
	} while (opcion < 0 || opcion > 2); //mientras la opcion no se valida
}