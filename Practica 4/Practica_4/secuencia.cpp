//PRACTICA 3: TORTUGAS ROBOTICAS
//Hecho por: Richard Junior Mercado Correa y Maryny Zara Castada Collado

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "secuencia.h"
#include "checkML.h"
using namespace std;

//TESTEO
//int main() {
//	tMazo mazo;
//	tCarta carta;
//
//	crearVacia(mazo);
//	crearMazoAleatorio(mazo);
//
//	for (int i = 0; i < MAX_CARTAS_MAZO; i++)
//		cout << mazo.lista[i]<< " ";
//
//	for (int i = 0; i < 3; i++) {
//		sacar(mazo, carta);
//		cout << carta;	
//	}
//	cout << endl << "mazo " << mazo.numcartas << endl;
//
//	for (int i = 0; i < mazo.numcartas; i++)
//		cout << mazo.lista[i] << " ";
//
//	system("pause");
//
//	return 0;
//}

void crearVacia(tMazo & mazo) {
	mazo.numcartas = 0;
}

void insertar(tMazo & mazo, tCarta carta) {

	if (mazo.numcartas < MAX_CARTAS_MAZO) {
		mazo.lista[mazo.numcartas] = new tCarta(carta);
		mazo.numcartas++;
	}
}

bool sacar(tMazo & mazo, tCarta &carta) { //desplazar izquierda....
	bool ok;

	if (mazo.numcartas > 0) {
		carta = *mazo.lista[0];
		delete mazo.lista[0]; //borramos de la memoria del mazo la carta

		for (int i = 0; i < MAX_CARTAS_MAZO; i++)
			mazo.lista[i] = mazo.lista[i + 1];

		mazo.numcartas--;
		ok = true;
	}

	else
		ok = false;

	return ok;
}

void crearMazoAleatorio(tMazo &mazo) {
	bool fin = false;
	tCarta carta;
	int pos = 0;

	// primero rellenar ad-hoc con las cartas
	for (int i = 0; i < NUM_CARTAS_AVANZA; i++) {
		carta = avanzar;
		insertar(mazo, carta);
		pos++;
	}

	for (int j = 0; j < NUM_CARTAS_IZQUIERDA; j++) {
		carta = giroIzquierda;
		insertar(mazo, carta);
		pos++;
	}

	for (int k = 0; k < NUM_CARTAS_DERECHA; k++) {
		carta = giroDerecha;
		insertar(mazo, carta);
		pos++;
	}

	for (int l = 0; l < NUM_CARTAS_LASER; l++) {
		carta = laser;
		insertar(mazo, carta);
		pos++;
	}

	mazo.numcartas = pos;

	// y ahora hacer la mezcla aleatoria

	srand(time(NULL)); // para que random_shuffle pueda elegir aleatoriamente 
					   // el elemento con el que intercambiar cada elemento de la secuencia
	random_shuffle(&(mazo.lista[0]), &(mazo.lista[MAX_CARTAS_MAZO - 1]));
}

void liberar(tMazo &mazo) {
	for (int i = 0; i < mazo.numcartas; i++)
		delete mazo.lista[i];

	mazo.numcartas = 0;
}