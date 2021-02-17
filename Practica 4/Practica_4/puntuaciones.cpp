//PRACTICA 4: TORTUGAS ROBOTICAS
//Hecho por: Richard Junior Mercado Correa y Maryny Zara Castada Collado

#include <iostream>
#include <fstream>
#include "Puntuaciones.h"
#include "Juego.h"
#include "checkML.h"
using namespace std;

void añadirjugador(tPuntuaciones &puntos, int pos, string nombre, int nuevos);
void ordenarCopia(tPuntuaciones &clasificacion);
bool mayorPuntuacion(int opIzq, int opDer);

//sugerencia de main para probar el modulo 
//int main() {
//	tPuntuaciones puntos;
//
//	inicializar(puntos);
//
//	if (cargarPuntuaciones(puntos)) { // cargando puntuaciones.txt (queda hueco para uno)
//		mostrarPuntuaciones(puntos);
//		cout << "<---------------------------------->\n";
//		actualizarPuntuacion(puntos, "pepe", 6); // actualizará pepe
//		mostrarPuntuaciones(puntos);
//		cout << "<---------------------------------->\n";
//		actualizarPuntuacion(puntos, "mercedes", 4); // actualizará mercedes
//		mostrarPuntuaciones(puntos);
//		cout << "<---------------------------------->\n";
//		actualizarPuntuacion(puntos, "isabel", 9);  // actualizará isabel
//		mostrarPuntuaciones(puntos);
//		cout << "<---------------------------------->\n";
//		actualizarPuntuacion(puntos, "ultimo", 16);  // incorpora a ultimo al final
//		mostrarPuntuaciones(puntos);
//		cout << "<---------------------------------->\n";
//		 en este momento la lista ya está llena: pepe 6, mercedes 4, isabel 8, ultimo 16
//		actualizarPuntuacion(puntos, "pepe2", 40); // sustituirá a pepe
//		mostrarPuntuaciones(puntos);
//		cout << "<---------------------------------->\n";
//		actualizarPuntuacion(puntos, "mercedes2", 40); // sustituirá a mercedes
//		mostrarPuntuaciones(puntos);
//		cout << "<---------------------------------->\n";
//		actualizarPuntuacion(puntos, "isabel2", 40);  // sustituirá a isabel
//		mostrarPuntuaciones(puntos);
//		cout << "<---------------------------------->\n";
//		actualizarPuntuacion(puntos, "ultimo2", 40);  // sustituirá a ultimo 
//		mostrarPuntuaciones(puntos);
//		cout << "<---------------------------------->\n";
//		actualizarPuntuacion(puntos, "no_entro", 10);  //  no entra porque nadie tiene menos que él
//		mostrarPuntuaciones(puntos);
//
//		for (int i = 0; i < puntos.num_jugadores; i ++)
//			cout << puntos.copia[i].nombre << " " << puntos.copia[i].puntuacion << endl;
//
//	}
//
//	cout << endl << endl << "Capacidad final: " << puntos.capacidad << endl;
//
//	liberar(puntos);
//
//	system("pause");
//	return 0;
//}

// implementaciones

bool cargarPuntuaciones(tPuntuaciones & puntos) {
	ifstream archivo;
	bool cargado;

	archivo.open("puntuaciones.txt");
	if (archivo.is_open()) {		//obtenemos las puntuaciones de archivo externo 'puntuaciones.txt'

		puntos.num_jugadores = 0;
		archivo >> puntos.puntuaciones[puntos.num_jugadores].nombre >> puntos.puntuaciones[puntos.num_jugadores].puntuacion;

		while (!archivo.eof()) {
			puntos.num_jugadores++;
			archivo >> puntos.puntuaciones[puntos.num_jugadores].nombre >> puntos.puntuaciones[puntos.num_jugadores].puntuacion;
		}

		cargado = true;
		ordenarCopia(puntos);
		archivo.close();
	}

	else
		cargado = false;

	return cargado;
}

bool guardarPuntuaciones(const tPuntuaciones & puntos) {
	ofstream archivo;
	bool cargado;

	archivo.open("puntuaciones.txt");
	if (archivo.is_open()) {
		for (int i = 0; i < puntos.num_jugadores; i++)
			archivo << puntos.puntuaciones[i].nombre << " " << puntos.puntuaciones[i].puntuacion << endl;


		cargado = true;
		archivo.close();
	}

	else
		cargado = false;

	return cargado;
}

//void mostrarPuntuaciones(const tPuntuaciones & puntos, int visualizacion) {
//
//	if (visualizacion == 1)
//		for (int i = 0; i < puntos.num_jugadores; i++)
//			cout << "Nombre: " << puntos.puntuaciones[i].nombre << " " << "Puntos: " << puntos.puntuaciones[i].puntuacion << endl;
//	else
//		for (int i = 0; i < puntos.num_jugadores; i++)
//			cout << "Nombre: " << puntos.copia[i].nombre << " " << "Puntos: " << puntos.copia[i].puntuacion << endl;
//}

void actualizarPuntuacion(tPuntuaciones & puntos, const string & nombre, int nuevos) {
	bool encontrado = false;
	int i = 0;
	tPuntuacionJugador jugador;

	while (i < puntos.num_jugadores && !encontrado) { //buscamos jugador en la lista
		encontrado = puntos.puntuaciones[i].nombre == nombre;
		i++;
	}

	if (encontrado) {													//si lo encontramos,
		eliminarJugador(puntos, i - 1);									//eliminamos el jugador
		añadirjugador(puntos, puntos.num_jugadores, nombre, nuevos);	//para luego añadirlo de nuevo con la puntuacion actualizada																	
																		//y reordenamos la lista de puntuaciones (orden por defecto)
	}

	else if (puntos.num_jugadores < puntos.capacidad && !encontrado) 	//si no lo encontramos y hay hueco, lo añadimos en la lista
		añadirjugador(puntos, i, nombre, nuevos);						//y reordenamos la lista de puntuaciones (orden por defecto)


	else {																// si la lista esta llena
		redimensionar(puntos);											//redimensionamos la lista (capacidad + MAX_JUGADORES_HISTORIAL)
		añadirjugador(puntos, i, nombre, nuevos);						//y reordenamos la lista de puntuaciones (orden por defecto)
	}

	jugador.nombre = nombre;
	jugador.puntuacion = nuevos;
	insertarOrdenado(puntos, jugador);
	ordenarCopia(puntos);
}

void inicializar(tPuntuaciones &clasificacion) {
	clasificacion.num_jugadores = 0;
	clasificacion.capacidad = MAX_JUGADORES_HISTORIAL;
	clasificacion.puntuaciones = new tPuntuacionJugador[MAX_JUGADORES_HISTORIAL];
}

void redimensionar(tPuntuaciones &clasificacion) {

	clasificacion.capacidad = clasificacion.capacidad + MAX_JUGADORES_HISTORIAL;
	tPuntuacionJugador *aux = new tPuntuacionJugador[clasificacion.capacidad];

	for (int i = 0; i < clasificacion.num_jugadores; i++)
		aux[i] = clasificacion.puntuaciones[i];

	delete[] clasificacion.puntuaciones;

	clasificacion.puntuaciones = aux;
}

void liberar(tPuntuaciones &clasificacion) {
	delete[] clasificacion.puntuaciones;

	clasificacion.capacidad = 0;
	clasificacion.num_jugadores = 0;
	clasificacion.puntuaciones = NULL;

}

void añadirjugador(tPuntuaciones &puntos, int pos, string nombre, int nuevos) {

	puntos.puntuaciones[pos].nombre = nombre;
	puntos.puntuaciones[pos].puntuacion = nuevos;

	puntos.num_jugadores++;
}

//*****************************
void insertarOrdenado(tPuntuaciones & clasificacion, const tPuntuacionJugador &jugador) {
	int pos;

	posicionInsercion(clasificacion, jugador, pos);
	desplazarDcha(clasificacion, pos);
	clasificacion.puntuaciones[pos] = jugador;
}

void posicionInsercion(const tPuntuaciones & clasificacion, const tPuntuacionJugador &jugador, int & pos) {
	bool mayor = false;

	int ini = 0, fin = clasificacion.num_jugadores - 1, mitad;

	pos = 0;

	while (ini <= fin && !mayor) { //buscamos posicion de insercion

		mitad = (ini + fin) / 2;

		if (clasificacion.puntuaciones[mitad].puntuacion == jugador.puntuacion)
			mayor = true;

		else if (clasificacion.puntuaciones[mitad].puntuacion < jugador.puntuacion)
			ini = mitad + 1;

		else
			fin = mitad - 1;

		mayor = mayorPuntuacion(clasificacion.puntuaciones[mitad].puntuacion, jugador.puntuacion);
		pos++;
	}

}

void desplazarDcha(tPuntuaciones & clasificacion, int pos) {
	for (int j = clasificacion.num_jugadores - 1; j > pos; j--)
		clasificacion.puntuaciones[j] = clasificacion.puntuaciones[j - 1];
}

bool mayorPuntuacion(int opIzq, int opDer) {
	bool ok;

	if (opIzq >= opDer)
		ok = false;
	else
		ok = true;

	return ok;
}

void eliminarJugador(tPuntuaciones & puntos, int posicion) {

	for (int i = posicion; i < puntos.num_jugadores; i++) {
		puntos.puntuaciones[i] = puntos.puntuaciones[i + 1];
	}

	puntos.num_jugadores--;
}

void ordenarCopia(tPuntuaciones &clasificacion) {
	clasificacion.copia = new tPuntuacionJugador[clasificacion.capacidad];

	for (int i = 0; i < clasificacion.num_jugadores; i++)
		clasificacion.copia[i] = clasificacion.puntuaciones[i];

	bool inter = true;
	int i = 0;

	while (i < clasificacion.num_jugadores - 1 && inter) {
		inter = false;

		for (int j = clasificacion.num_jugadores - 1; j > i; j--)

			//ordenamos si las puntuaciones son iguales
			if (clasificacion.copia[j].nombre < clasificacion.copia[j - 1].nombre &&
				clasificacion.copia[j].puntuacion == clasificacion.copia[j - 1].puntuacion) {
				int tmp1;
				string tmp2;

				tmp1 = clasificacion.copia[j].puntuacion;
				tmp2 = clasificacion.copia[j].nombre;
				clasificacion.copia[j] = clasificacion.copia[j - 1];

				clasificacion.copia[j - 1].puntuacion = tmp1;
				clasificacion.copia[j - 1].nombre = tmp2;
				inter = true;
			}
		if (inter)
			i++;
	}
}