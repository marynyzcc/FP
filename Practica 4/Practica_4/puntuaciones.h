//PRACTICA 4: TORTUGAS ROBOTICAS
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
	tPuntuacionJugador *puntuaciones;
	int num_jugadores;
	int capacidad;
} tPuntuaciones;

bool cargarPuntuaciones(tPuntuaciones & puntos);
bool guardarPuntuaciones(const tPuntuaciones & puntos);
void mostrarPuntuaciones(const tPuntuaciones & puntos, int visualizacion);
void actualizarPuntuacion(tPuntuaciones & puntos, const string & nombre, int nuevos);

void inicializar(tPuntuaciones & clasificacion);
void redimensionar(tPuntuaciones & clasificacion);
void liberar(tPuntuaciones & clasificacion);

void insertarOrdenado(tPuntuaciones & clasificacion, const tPuntuacionJugador &jugador);
void posicionInsercion(const tPuntuaciones & clasificacion, const tPuntuacionJugador &jugador, int & pos);
void desplazarDcha(tPuntuaciones & clasificacion, int pos);
void eliminarJugador(tPuntuaciones & puntos, int posicion);

#endif