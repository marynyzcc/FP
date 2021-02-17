//Hecho por: Maryny Zara Castada Collado y Richard Junior Mercado Correa

//-----------------------------------------PRACTICA 2--------------------------------------------------

#include <iostream>
#include<fstream>
#include <cstdlib>
#include<ctime>
using namespace std;

//DECLARACION DE CONSTANTES
const int NUM_COLORES = 6;
enum tColor {ROJO, AZUL, VERDE, AMARILLO, MARRON, BLANCO, INCORRECTO};
  
const int TAM_CODIGO = 4;
typedef tColor tCodigo [TAM_CODIGO];
typedef tColor tHumano[TAM_CODIGO];
typedef bool esDescolocado[TAM_CODIGO];

const int MAX_INTENTOS = 15;
int intentos=0;

tColor char2color(char c);

//-----------------------------------------------------------------------------------------------------

//DECLARACION DE SUBPROGRAMAS
int menu();
void reglas();
void codigoAleatorio(tCodigo codigo, bool admiteRepetidos);
char color2char(tColor color);
void leeCodigo(tCodigo &codigo);
void juego(bool admiteRepetidos);
void compararCodigos(const tCodigo codigo, const tCodigo humano, int& colocados, int& descolocados);

//-----------------------------------------------------------------------------------------------------

int main(){
	int opcion;
	
	reglas();
	opcion=menu();
	
	return 0;
}

//==========================================SUBPROGRAMAS===============================================

void juego(bool admiteRepetidos){ //SUBPROGRAMA ENCARGADO DE REALIZAR EL JUEGO
	tCodigo codigo;
	tCodigo humano;
	int opcion, colocados, descolocados,necesitados;
	bool correcto;
	
	codigoAleatorio(codigo, admiteRepetidos);
	cout<<endl;
	leeCodigo(humano);
	compararCodigos(codigo, humano, colocados, descolocados);
	intentos++;
	while(intentos<MAX_INTENTOS || !correcto){
		cout<<endl;
		if(colocados==TAM_CODIGO){
			correcto=true;
			necesitados= intentos; //utilizamos la variable necesitados para guardar el numero de intentos necesitados antes de salir del bucle
			intentos=MAX_INTENTOS+1;
		}
			
		else if(intentos==MAX_INTENTOS){
			cout<<"	Te has quedado sin intentos..."<<endl;
			correcto=true; //ponemos "correcto=true" para poder salir del bucle y finalizar el juego en el caso de que se alcancen los maximos intentos
		}
		
		else{
			cout<<"	Vaya...Has fallado... Colocados: "<<colocados<<" Descolocados: "<<descolocados<<endl;
			cout<<endl;
			cout<<"	Prueba otra vez!"<<endl;
			cout<<endl;
			leeCodigo(humano);
			compararCodigos(codigo, humano, colocados, descolocados);
		}
		intentos++;
	}
	
	if(colocados==TAM_CODIGO && correcto)
		cout<<"	HAS ACERTADO! Has necesitado: "<<necesitados<< " intento(s)"<<endl;
	
	cout<<endl<<endl;
	cout<<"	El juego ha acabado!";
	
	intentos=0; //REINICIAMOS EL JUEGO
	menu();
}


void reglas(){ //SUBPROGRAMA QUE MUESTRA LAS REGLAS
	ifstream archivoReglas;
	string texto;
	
	archivoReglas.open("reglas.txt");
	
	if(archivoReglas.is_open()) {
	
		getline(archivoReglas, texto);
				
		while (!archivoReglas.eof()) {
			cout << texto << endl;
			getline(archivoReglas, texto);
		}
		archivoReglas.close();
	}	
	else cout<< "	El archivo de reglas no existe!"<<endl;	
}

int menu(){ //MUESTRA EL MENU
	int opcion;
	bool admiteRepetidos;
			
		cout<<endl;
		cout<<endl;
		cout<<"	Elige una opcion: ";
		cin>> opcion;
	
		while(opcion<0 || opcion>2){
			cout<< "	Opcion no valida. Escoja otra opcion: ";
			cin>>opcion;
		}
	
		
		if(opcion==1) {
			admiteRepetidos=false;
			juego(admiteRepetidos);
		}
		
		else if (opcion==2){
			admiteRepetidos=true;
			juego(admiteRepetidos);
		}
	
		else
			cout<<"	Has elegido SALIR!"<<endl;
		
	
	return opcion;
}


void codigoAleatorio(tCodigo codigo ,bool admiteRepetidos){ //generacion del codigo aleatorio
	int aleatorio;
	tColor color;
	
	if(admiteRepetidos){
		cout<<"	Admite repetidos!"<<endl;
		cout<<"	Codigo para depuracion: [";
		srand(time(NULL));
		for(int i=0; i<TAM_CODIGO; i++){
			aleatorio= (rand()%(NUM_COLORES));
			color= tColor(aleatorio);
			codigo[i]= tColor(aleatorio);

			color2char(color);
		}
		cout<<"]";
	}
	
	else {
		int posicion1,posicion2;
		bool iguales=true,valido=false;
		
		cout<<"	No admite repetidos!"<<endl;
		cout<<endl;
		
		srand(time(NULL));                  
			
		cout<<"	Codigo para depuracion: [";
		
		while(!valido){
			for(posicion1=0;posicion1<TAM_CODIGO;posicion1++){ //se genera el codigo
				aleatorio= (rand()%(NUM_COLORES));
				codigo[posicion1]= tColor(aleatorio);
			}
			
			posicion1=0;
			while(posicion1<TAM_CODIGO || !valido){ //se comprueba que no se generan repetidos
				
				posicion2=0;
				while(posicion2<TAM_CODIGO){
					iguales= codigo[posicion1]==codigo[posicion2];
					
					if(iguales && posicion1 != posicion2){ //si existen repetidos se vuelve generar otro valor
						for(posicion1=0;posicion1<TAM_CODIGO;posicion1++){
							aleatorio= (rand()%(NUM_COLORES));
							codigo[posicion1]= tColor(aleatorio);
						}
						posicion2=TAM_CODIGO+1;
						posicion1=0;	
					}
					else posicion2++;
				}
				
				if(posicion1==posicion2){ //se muestra por pantalla si el codigo no posee repetidos
					valido=true;
					for(int i=0; i<TAM_CODIGO; i++){
						color= codigo[i];
						color2char(color);
					}	
				}
				posicion1++;
			}
		}		
		cout<<"]"<<endl;	
	}
}	
	
char color2char(tColor color) { //transforma la cadena de numeros en caracteres y los muestra por pantalla [depuracion]
	char caracter;
	
	switch(color){
		case 0: caracter= 'R'; cout<<caracter; break;
		case 1: caracter='A' ; cout<<caracter; break;
		case 2: caracter='V' ; cout<<caracter; break;
		case 3: caracter='X'; cout<<caracter; break;
		case 4: caracter='M'; cout<<caracter; break;
		case 5: caracter='B' ; cout<<caracter; break;
		default: caracter='I'; cout<<caracter; break;
	
	}
	
	return caracter;
}

tColor char2color(char c){ //transforma el codigo leido por teclado en numeros para ser comparado con el codigo generado
	int caracter;
	tColor color;
	
	switch(toupper(c)){
		case 'R': caracter= 0; break;
		case 'A': caracter= 1; break;
		case 'V': caracter= 2; break;
		case 'X': caracter= 3; break;
		case 'M': caracter= 4; break;
		case 'B': caracter= 5; break;
		default: caracter=-1; break;	
	}
	color=tColor(caracter);
	
	return color;
}

void leeCodigo(tCodigo &codigo) { //lee el codigo introducido por el usuario
	tColor eleccionHumano;
	char c;
	bool valido= false;
	int num=1;
	
	cout<<"	Introduce tu apuesta: ";
	
	while(!valido){
		for(int i=0;i<TAM_CODIGO;i++){
			cin>> c;
			num++;
			eleccionHumano= char2color(c);
			codigo[i]=tColor(eleccionHumano);
		}
	
		for(int posicion=0; posicion<TAM_CODIGO; posicion++){
			
			if(codigo[posicion]== ROJO ||codigo[posicion]== AZUL ||codigo[posicion]== VERDE ||
			   codigo[posicion]== AMARILLO ||codigo[posicion]== MARRON ||codigo[posicion]== BLANCO)
			{
			valido=true;
			}
			
			else{
				cout<< "	Codigo no valido! Introduce otro codigo: ";
				for(int i=0;i<TAM_CODIGO;i++){
					cin>> c;	
					eleccionHumano= char2color(c);
					codigo[i]=tColor(eleccionHumano);
				}
			}
		}
	}
}		

void compararCodigos(const tCodigo codigo, const tCodigo humano, int& colocados, int& descolocados){ //compara los codigos para mostrar el numero de colocados y descolocados
	bool iguales=false,similares=false;
	esDescolocado colocado;
	colocados=0;
	descolocados=0;
	int posicion2;
	
	for(int i=0;i<TAM_CODIGO;i++){
		colocado[i]=false;
	}
	
	for(int posicion1=0;posicion1<TAM_CODIGO;posicion1++){
		iguales= codigo[posicion1]==humano[posicion1];
		if(iguales)
			colocados++;
		
		else{
			posicion2=0;
			while(posicion2<TAM_CODIGO ){
				colocado[posicion1]= codigo[posicion1]==humano[posicion2];
				if(colocado[posicion1]){
					descolocados++;	
				}
			
				posicion2++;
			}	
		}
	}	
}
