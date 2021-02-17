//PRACTICA 3: TORTUGAS ROBOTICAS
//Hecho por: Richard Junior Mercado Correa y Maryny Zara Castada Collado

#include "Puntuaciones.h"
#include <iostream>
#include <fstream>
using namespace std;


// sugerencia de main para probar el modulo 
//int main(){
//	tPuntuaciones puntos;
//
//	if (cargarPuntuaciones(puntos)){ // cargando puntuaciones.txt (queda hueco para uno)
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
//		// en este momento la lista ya está llena: pepe 6, mercedes 4, isabel 8, ultimo 16
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
//		guardarPuntuaciones(puntos);
//	}
//
//	system("pause");
//	return 0;
//}

// implementaciones

bool cargarPuntuaciones(tPuntuaciones & puntos) {
	ifstream archivo;
	bool cargado;

	archivo.open("puntuaciones.txt");
	if (archivo.is_open()) { //obtenemos puntuaciones de archivo externo

		puntos.num_jugadores = 0;
		archivo >> puntos.puntuaciones[puntos.num_jugadores].nombre >> puntos.puntuaciones[puntos.num_jugadores].puntuacion;
		while (!archivo.eof()) {
			puntos.num_jugadores++;
			archivo >> puntos.puntuaciones[puntos.num_jugadores].nombre >> puntos.puntuaciones[puntos.num_jugadores].puntuacion;
		}

		cargado = true;

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
		for (int i = 0; i < puntos.num_jugadores; i++) {
			archivo << puntos.puntuaciones[i].nombre << " " << puntos.puntuaciones[i].puntuacion << endl;
		}

		cargado = true;
		archivo.close();
	}

	else
		cargado = false;

	return cargado;
}


void mostrarPuntuaciones(const tPuntuaciones & puntos) {
	for (int i = 0; i< puntos.num_jugadores; i++) {
		cout << "Nombre: " << puntos.puntuaciones[i].nombre << " " << "Puntos: " << puntos.puntuaciones[i].puntuacion << endl;
	}
}


bool actualizarPuntuacion(tPuntuaciones & puntos, const string & nombre, int nuevos) {
	bool encontrado = false, actualizado;

	int i = 0;
	while (i < puntos.num_jugadores && !encontrado) { //buscamos jugador en la lista

		encontrado = puntos.puntuaciones[i].nombre == nombre;

		i++;
	}

	i = i - 1;

	if (encontrado) {
		puntos.puntuaciones[i].puntuacion = nuevos;
		actualizado = true;
	}

	else if (puntos.num_jugadores < MAX_JUGADORES_HISTORIAL && !encontrado) { //si no lo encontramos y hay hueco, lo añadimos en la lista

		puntos.puntuaciones[i + 1].nombre = nombre;
		puntos.puntuaciones[i + 1].puntuacion = nuevos;

		puntos.num_jugadores++;

		actualizado = true;
	}

	else if (puntos.num_jugadores == MAX_JUGADORES_HISTORIAL && !encontrado) { // si la lista esta llena...

		int min = 9999, pos;
		for (int i = 0; i < puntos.num_jugadores; i++) {
			if (puntos.puntuaciones[i].puntuacion < min) {
				min = puntos.puntuaciones[i].puntuacion;
				pos = i;
			}
		}

		if (puntos.puntuaciones[pos].puntuacion < nuevos) {
			puntos.puntuaciones[pos].nombre = nombre;
			puntos.puntuaciones[pos].puntuacion = nuevos;
		}
		actualizado = true;
	}

	else
		actualizado = false;

	return actualizado;
}