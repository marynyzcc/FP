//PRACTICA 3: TORTUGAS ROBOTICAS
//Hecho por: Richard Junior Mercado Correa y Maryny Zara Castada Collado

#ifndef Secuencia_h
#define Secuencia_h

// a�adir includes (si necesarios) y guardas de inclusi�n

const int MAX_CARTAS_MAZO = 38; // cu�ntas cartas en total
const int NUM_CARTAS_AVANZA = 18; // cu�ntas cartas avanza
const int NUM_CARTAS_IZQUIERDA = 8; // cu�ntas cartas girar izda
const int NUM_CARTAS_DERECHA = 8; // cu�ntas cartas girar dcha
const int NUM_CARTAS_LASER = 4; // cu�ntas cartas l�ser
const int NUM_TIPOS_CARTAS = 4;  // cu�ntos tipos de cartas 4 = avanza, izda, dcha, laser


typedef enum { avanzar, giroIzquierda, giroDerecha, laser } tCarta;
typedef struct {
	tCarta lista[MAX_CARTAS_MAZO];
	int numcartas;
} tMazo;

void crearVacia(tMazo & mazo);
bool sacar(tMazo & mazo, tCarta & carta);
void insertar(tMazo & mazo, tCarta carta);
void crearMazoAleatorio(tMazo & mazo);
#endif 
