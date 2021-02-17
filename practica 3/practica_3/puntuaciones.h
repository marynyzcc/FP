//PRACTICA 3: TORTUGAS ROBOTICAS
//Hecho por: Richard Junior Mercado Correa y Maryny Zara Castada Collado

#ifndef puntuaciones_h
#define puntuaciones_h
#include <string>
using namespace std;

const int MAX_JUGADORES_HISTORIAL = 4;  // poner la dimensión que se desee a la lista

typedef struct {
	string nombre;
	int puntuacion;
} tPuntuacionJugador;

typedef struct {
	tPuntuacionJugador puntuaciones[MAX_JUGADORES_HISTORIAL];
	int num_jugadores;
} tPuntuaciones;

bool cargarPuntuaciones(tPuntuaciones & puntos);
bool guardarPuntuaciones(const tPuntuaciones & puntos);
void mostrarPuntuaciones(const tPuntuaciones & puntos);
bool actualizarPuntuacion(tPuntuaciones & puntos, const string & nombre, int nuevos);
#endif