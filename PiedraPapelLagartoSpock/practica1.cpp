/*
	VERSION 2.0. JUEGO DE PIEDRA-PAPEL-TIJERAS-LAGARTO-SPOCK
	Hecho por: MARYNY ZARA CASTADA COLLADO y RICHARD JUNIOR MERCADO CORREA
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

bool localizacionJugador(string apodo);
int menu();
bool mostrarReglas();
typedef enum {PIEDRA, PAPEL, TIJERAS, LAGARTO, SPOCK} tElemento;
typedef enum {empate, ganaMaquina, ganaHumano} tResultado;
tElemento eleccionHumano();
string elementoAstring (tElemento elemento);
tResultado quienGana(tElemento humano, tElemento maquina);

int main(){
	
	srand(time(NULL));
	int opcion, armamaquina, victorias=0, derrotas=0, empates=0, partidas;
	bool existeReglas, existeJugador;
	string apodo;
	ifstream archivo;
	tResultado recuento;
	tElemento maquina, humano;
	
	cout<< "Identifiquese intruso: "; cin>> apodo; //Identificacion del usuario
	existeJugador= localizacionJugador(apodo);
	
	if(!existeJugador) {
		cout<< "El fichero de usuarios registrados no existe. NO PUEDE JUGAR!" << endl;
	}
	
	else {
	
		opcion= menu(); //Apertura del menu
	
		while(opcion!=0) {
		
			if(opcion==1) {
				
				armamaquina= (rand() % 5);
				maquina= tElemento(armamaquina);
				
				cout<<endl;
				cout<< "************* ATAQUE DE LA MAQUINA ************"<<endl;
				cout<< "La maquina ha elegido "<<elementoAstring(maquina) << "!" <<endl; //Se muestra la eleccion de la maquina
				cout<< "***********************************************"<<endl;	
			
				
				humano = eleccionHumano(); //Eleccion del humano
				
				cout<< endl;
				cout<< "******************* TU ATAQUE *****************"<<endl;
				cout<< "Has elegido " << elementoAstring(humano) <<"!" <<endl; //Se muestra la eleccion del humano
				cout<< "***********************************************"<<endl;	
				cout<< endl;									
				cout<< endl;
				cout<< "********** RESULTADOS DE LA BATALLA ***********"<<endl;
				
				recuento= quienGana(maquina, humano); //Se muestran los resultados de la batalla
				
				//RECUENTOS
				if (recuento== ganaHumano){cout<< "Ha sido muy efectivo! HAS GANADO!!!" << endl; victorias++;}
				else if (recuento== empate) {cout<< "No ha sido tan efectivo... ES UN EMPATE!!!"<< endl; empates++;}
				else  {cout<< "Has fallado... HAS PERDIDO!"<< endl; derrotas++;}
				cout<< "***********************************************"<<endl;
				cout<< endl;
			
				opcion = menu();
				}		
				
				else { 
				
					existeReglas=mostrarReglas(); //Se muestran las reglas si el archivo existe
					
					if(!existeReglas) {
						cout<<endl;
						cout << "ERROR! No se ha podidio abrir el archivo." <<endl; //Si el archivo no existe se muestra inmediatamente el menu
						cout<<endl; 
						opcion=menu(); 
					}
				
					else {
						opcion=menu();
					}
				}
		}
		
		//FIN DE LA PARTIDA
		cout <<endl;
		cout<< "*********************" <<endl;
		cout<< "PARTIDAS: "<<victorias+derrotas+empates<<endl;
		cout<< endl;
		cout<< "VICTORIAS: "<<victorias<<endl;
		cout<< "DERROTAS: "<<derrotas<<endl;
		cout<< "EMPATES: "<<empates<<endl;
		cout<< "*********************"<<endl;
		cout<< endl;
		cout<< "El juego ha finalizado. Pulsa cualquier tecla para salir."<<endl;
		
	}
	
	return 0;
}
	




//----------------SUBPROGRAMAS------------------------------------------------------------


//SUBPROGRAMA DE IDENTIFICACION DE USUARIO
bool localizacionJugador(string apodo) {
	
	ifstream identificacion;
	string i;
	bool encontrado= false;
	
	identificacion.open("registro.txt");
	identificacion>>i;
	
	if(identificacion.is_open()){
		
		while (!identificacion.eof() && !encontrado){
			encontrado= i==apodo;
			identificacion>>i;
		}
		
		while(!encontrado){
			identificacion.close();
			identificacion.open("registro.txt");
			
			cout<< "Usuario no valido. Introduzca un usuario REGISTRADO: "; cin>> apodo;
	
			while (!identificacion.eof() && !encontrado){
				encontrado= i==apodo;
				identificacion>>i;
			}
		}
		
		cout<< "Usuario registrado. Puedes JUGAR!" <<endl << endl;
		identificacion.close();
	}
	
	else{
		identificacion.close();
		return false;
	}
	return true;
}

//SUBPROGRAMA MENU
int menu(){
	
	int opcion;

	cout<< "Ha comenzado el juego. Sus opciones son:"<<endl;
	cout<< "1- JUGAR"<< endl;
	cout<< "2- VER REGLAS"<<endl;
	cout<< "0- SALIR"<< endl;
	cout<< "Introduzca su opcion: "; cin>> opcion;
	
	while(opcion<0 || opcion>2){
		cout<< "Opcion no valida. Vuelva a introducir una opcion VALIDA: "; cin>> opcion;
	}
	
	return opcion;
}


//FUNCION QUE COMPRUEBA LA EXISTENCIA DEL ARCHIVO QUE MUESTRA LAS REGLAS
bool mostrarReglas() {
	ifstream archivoReglas;
	string texto;
	
	archivoReglas.open("reglas.txt");
	
	if(archivoReglas.is_open()) {
	
		getline(archivoReglas, texto);
				
		while (texto != "XXX") {
			cout << texto << endl;
			getline(archivoReglas, texto);
		}
		
		archivoReglas.close();
		return true;		
	}
	else {
		archivoReglas.close();
		return false;
	}
		
}

//SUBPROGRAMA DE LA ELECCION DEL HUMANO
tElemento eleccionHumano() {
	
	int armahumano;
	tElemento armaH;
	
	cout<< endl;
	cout<< "Has elegido JUGAR. Buena suerte!"<<endl;
	cout<< endl;
	cout<< "Es tu turno! Elige un arma:"<<endl;
	cout<< "1- PIEDRA"<<endl;
	cout<< "2- PAPEL"<<endl;
	cout<< "3- TIJERAS"<<endl;
	cout<< "4- LAGARTO"<<endl;
	cout<< "5- SPOCK"<<endl;
	cout<< endl;
	cout<< "Introduzca su arma: "; cin>> armahumano;
					
	while(armahumano<1 || armahumano >5){
		cout<< "El arma elegido no existe! Introduzca otro arma: "; cin>> armahumano;
	}
	
	armaH = tElemento(armahumano-1); 
	
	return armaH;
}

//SUBPROGRAMA QUE MUESTRA EL ATAQUE DEL HUMANO Y DE LA MAQUINA
string elementoAstring(tElemento elemento) {
	
	string ataque;
	
	if(elemento == PIEDRA) ataque = "PIEDRA";
	else if(elemento == PAPEL) ataque = "PAPEL";
	else if(elemento == TIJERAS) ataque = "TIJERAS";
	else if(elemento == LAGARTO) ataque = "LAGARTO";
	else ataque = "SPOCK";	
	
	return ataque;
}



//SUBPROGRAMA QUE DECIDE QUIEN GANA LA PARTIDA
tResultado quienGana(tElemento maquina , tElemento humano){
	
	tResultado resultado;
	
	if( (humano==TIJERAS && maquina==PAPEL) ||
		(humano==PAPEL && maquina==PIEDRA) ||
		(humano==PIEDRA && maquina==LAGARTO) ||
		(humano==LAGARTO && maquina==SPOCK) ||
		(humano==SPOCK && maquina==TIJERAS) ||
		(humano==TIJERAS && maquina==LAGARTO) ||
		(humano==LAGARTO && maquina==PAPEL) ||
		(humano==PAPEL && maquina==SPOCK) ||
		(humano==SPOCK && maquina==PIEDRA) ||
		(humano==PIEDRA && maquina==TIJERAS) ){
			
		resultado= ganaHumano;
	}
						
	else if(humano==maquina){
		resultado= empate;
	}
					
	else{
		resultado= ganaMaquina;
	}
	
	return resultado;		
}
