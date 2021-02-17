//PRACTICA 3: TORTUGAS ROBOTICAS
//Hecho por: Richard Junior Mercado Correa y Maryny Zara Castada Collado

#ifndef Juego_h
#define Juego_h

#include <string>
#include "Puntuaciones.h"
#include "Secuencia.h"
using namespace std;

//***************TABLERO************************//
const int NUM_FILAS = 8; // alto tablero
const int NUM_COLUMNAS = 8; // ancho tablero
typedef enum { norte, este, sur, oeste } tDir;
typedef enum { vacia, hielo, muro, caja, joya, tortuga } tEstadoCasilla;
typedef struct {
	int numero; // asocia tortuga con jugador
	tDir direccion;
} tTortuga;

typedef struct {
	tEstadoCasilla estado;
	tTortuga tortuga;
} tCasilla;
typedef tCasilla tTablero[NUM_FILAS][NUM_COLUMNAS];




//******************JUGADORES**************
typedef int tMano[NUM_TIPOS_CARTAS]; // representa cuantas cartas de cada tipo hay en la mano
typedef struct {
	int fila;
	int columna;
} tCoordenada;

typedef struct {
	int avanza;
	int derecha;
	int izquierda;
	int laser;
}tContador;

typedef struct {
	string nombre;
	tMazo mazo;
	tCoordenada posActual;
	tCoordenada posJoya;
	tMano mano;
	tMazo secuencia;
	tContador contadores;
	int numMano;
} tJugador;

typedef enum { robarCarta, ejecutarSecuencia } tAccion;



//**********************ASPECTOS JUEGO*************************
const int MAX_JUGADORES = 4; // nº jugadores
typedef struct {
	tTablero tableroJuego;
	int nJugadores;
	tJugador jugadores[MAX_JUGADORES];
	int turno;
} tJuego;

typedef enum { AVANZA, DERECHA, IZQUIERDA, LASER, SALIR, NADA } tTecla;

void jugadores(tJuego &juego);
bool crearJuego(tJuego & juego);
bool ejecutarTurno(tJuego &juego);
bool accionRobar(tJuego & juego);
void obtenerSecuencia(tJuego &juego);
bool accionSecuencia(tJuego & juego, tMazo & cartas);
void cambiarTurno(tJuego &juego);
void mostrarJuego(const tJuego & juego);
void quitarCartaMano(tJuego &juego, tCarta carta);

//********************DIBUJO********************************
const int NUM_TIPOS_CASILLAS = 6; // nº de tipos de estado de casilla
const int NUM_COLORES = NUM_TIPOS_CASILLAS + MAX_JUGADORES;
const int PALETA[NUM_COLORES] = { 1, 11, 7, 4, 12, 5, 13, 9, 10, 3 };

#endif