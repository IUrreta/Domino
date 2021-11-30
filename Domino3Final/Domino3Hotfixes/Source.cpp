// PRACTICA HECHA POR MARIO GONZALEZ DE SANTOS E IGNACIO URRETAVIZCAYA TATO




//Librerias
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

//Declaracion  de ls typedef
const int NUM_FICHAS_MAX = 55;
const int FICHASJUG = 55;
const int JUGADORES_MAX = 4;
const bool JuegaHumano = false;
const bool MuestraBots = true;
const bool estrategiaInventada = true;


struct tFicha {
	int izq;
	int der;
	int suma;
};

typedef tFicha tArrayFichas[NUM_FICHAS_MAX];

struct tListaFichas {
	tArrayFichas lista;
	int cont;
};

struct tJugador {
	tListaFichas fichas;
	int puntos;
};

typedef tJugador tArrayJugadores[JUGADORES_MAX];

struct tJuego {
	int numJug;
	int maxPuntos;
	string tablero;
	tListaFichas pozo;
	tArrayJugadores jugadores;
	int turno;
	bool partidaInicida;
	bool ganado;
};



//Prototipos de las fuciones

int mostrarMenu(tJuego juego);												 //Muestra el menú
string muestraFicha(string posIzq, string posDer);		//Devuelve la ficha con los |a-b|

void mostrarTablero(tJuego juego);			//Muestra las fichas que hay puestas en el tablero

bool puedePonerIzq(tJuego juego, int ficha, int numJug);		//Funcion para compraar si una ficha en copncreto puede ser puesta a la izquierda
bool puedePonerDer(tJuego juego, int ficha, int numJug);		//Funcion para compraar si una ficha en copncreto puede ser puesta a la derecha

bool ponerFichaIzq(tJuego& juego);		//Funcion para que el jugador humano ponga una ficha a la izquierda

bool ponerFichaDer(tJuego& juego);		//Funcion para que el jugador humano ponga una ficha a la derecha

bool robarFichaMenu(tJuego& juego);			//Funcion para que el jugador humano robe una fihca desde el menu

bool ejecutarOpcion(tJuego& juego, short int opcionMenu);			//Ejecuta la opcion elegida por el humano

void guardarPartida(tJuego juego);						//Guarda la partida
void cargarPartida(tJuego& juego);						//Carga la partida								

int eligeModo();		//Menu que permite la opcion de cambiar el maximo de puntos de las fichas, entre 6, 7, 8, y 9

void generaPozo(tJuego& juego, int maxPuntos);		//Funcion que genera el pozo de todas las fichas en orden
void desordenaPozo(tJuego& juego);		//Funcion cuyo proposito es el de desordenar el pozo

void roba7(tListaFichas& pozo, tJugador& jugador);		//Funcion que roba las 7 fichas iniciales para un jugador desde el pozo

int preguntaFicha(tJuego juego);			//Funcion que le pregunta al jugador que ficha quiere colocar	
void eliminaFicha(tListaFichas& fichas, int fichaEliminar);			//Funcion que sirve para eliminar una ficha del array de las fichas del jugador

int puedePonerAmbos(tJuego juego, int numJugador);		//Funcion que compara las fichas de un jugador con ambos lados del tablero, y devuelve la primera que encuentra que se puede poner a algun lado

void calculaPuntos(tJuego& juego);		//Funcion que calcula los puntos de todos los jugadores

bool sinSalida(const tJuego juego);		//funcion quie comprueba si la partida ha acabado porque ningun jugadoir pueda poner ni tampoco robar
																												

bool inicializarJuego(tJuego& juego, int maxPuntos);		//Funcion que pregunta cuantos jugadores van a jugar, el maxiumo de puntos, genera y desordena el pozo, roba las 7 fichas para todos los jugadores, busca quien tiene el doble mas alto y lo coloca

void muestraPozo(tJuego juego);		//Funcion utilizada de prueba para mostrar el pozo en cualquiera de sus estados

//------------------------------------------------------------------V3-----------------------------------------------------------------------

int eligeJug(tJuego& juego);			//Funcion para elegir el numero de jugadores
void repartirFichas(tJuego& juego);			//Funcion que reparte las 7 fichas a los n jugadores
int quienEmpieza(tArrayJugadores jugadores, int elegido, int& posFicha);		//Funcion que comprueba cual es el doble ,mas alto y devuelve el jugador que empieza
void robarFicha(tListaFichas& pozo, tJugador& jugador);		//Funcion generica para robar una ficha
void estrategia1(tJuego& juego);		//Estrategia que selecciona la primera ficha que puede poner que encuentra
void estrategia2(tJuego& juego);		//Estrategia que pone la ficha cuya suma de ambos digitos sea mas alta
void ponerIzqBot(tJuego& juego, int fichaponer);		//Funcion para que un bot cualquiera ponga una ficha a la izquierda
void ponerDerBot(tJuego& juego, int fichaponer);		//Funcion para que un bot cualquiera ponga una ficha a la derecha
bool puedeRobar(tJuego juego);		//Funcion que comprueba que un jugador cualquiera pued robar ficha
void robarBot(tJuego& juego);		//Funcion para que un bot cualquiera robe ficha
void guardarListaFichas(ofstream& archivo, const tListaFichas listaFichas);		//Funcion para guardar una lista de fichas cualauiera
int empiezaJuego(int posFicha, tJuego& juego, int numeroDeJugadores);		//Funcion que coloca la primera ficha de todas en el tablero
void cargaListaFichas(ifstream& archivo, tListaFichas& listaFichas);		//Funcion para cargar una lista cualquiera de fichas
bool jugarMaquina(tJuego& juego);		//Funcion para que los bots realicen sus turnos
bool compruebaGanadorRonda(tJuego& juego);		//Funcion que comprueba despues de que cualquier jugador haya puesto una ficha si hay un ganador en la ronda
void endGame(tJuego juego);			//Funcion que ordena las puntuaciones de los jugadores y muestra la clasificacion final
void muestraPuntos(tJuego juego);		//Funcion que muestra los puntos de los jugadores
void inicializarRonda(tJuego& juego);		//Funcion que inicia una ronda nueva, ya sea la primera (es llamada en inicializarJuego) u otra cualquieraa
void estrategia3(tJuego& juego);		//Funcion optativa que se encarga de, primero comprobar que ficha seria mas perjudicial para otros jugadiores poner y mejor para el, y luego la pone
void compruebaFin(tJuego& juego, bool& salir, int opcionMenu);		//Funcion que comprueba por que motivo ha terminado la partida
void estrategia4(tJuego& juego);		//Funcion inventada que pone la ficha que (obviamente pueda poner) tenga el digito ams grande a la derecha, y si hay 2 empatadas, la que tenga el digito mas grande a la izquierda
bool puedeSeguir(tJuego& juego, int fichaSaltar, int numeroBusca);		//Funcion auxiliar para la estrategia 3, que comprueba si al poner X ficha, el mismo podria seguir poniendo o no



//Programa principal
int main() {
	srand(time(NULL));
	//Variables del tJuego que deben de ser inicializadas
	tJuego juego;
	juego.partidaInicida = false;
	juego.ganado = false;
	juego.turno = 0;
	//Variables
	bool salir = false;
	int opcion = 1;

	//Bucle principal
	salir = false;
	while (!salir) {
		system("cls");
		mostrarTablero(juego);
		opcion = mostrarMenu(juego);
		salir = ejecutarOpcion(juego, opcion);
		if (!salir) salir = jugarMaquina(juego);
		compruebaFin(juego, salir, opcion);
	}

	endGame(juego);
	return 0;

}

//Funcion que genera el pozo de todas las fichas en orden
void generaPozo(tJuego& juego, int maxPuntos) {			
	int izq = 0;
	int der = 0;
	juego.pozo.cont = 0;

	for (izq = 0; izq <= maxPuntos; izq++) {
		for (der = izq; der <= maxPuntos; der++) {
			juego.pozo.lista[juego.pozo.cont].izq = izq;
			juego.pozo.lista[juego.pozo.cont].der = der;
			juego.pozo.lista[juego.pozo.cont].suma = juego.pozo.lista[juego.pozo.cont].izq + juego.pozo.lista[juego.pozo.cont].der;
			juego.pozo.cont++;
		}
	}

}

//Funcion cuyo proposito es el de desordenar el pozo
void desordenaPozo(tJuego& juego) {		
	int contador = 0;
	for (contador = 0; contador < 1000; contador++) {	//Bucle para desordenar las fichas del pozo
		int pos1;
		int pos2;
		tFicha fichaCambio;

		pos1 = rand() % juego.pozo.cont;
		pos2 = rand() % juego.pozo.cont;
		fichaCambio = juego.pozo.lista[pos1];    //Utiliza fichacambio y pozo de poz1 y pos 2 para intercambiarlas b veces
		juego.pozo.lista[pos1] = juego.pozo.lista[pos2];
		juego.pozo.lista[pos2] = fichaCambio;
	}

}

//Funcion que roba las 7 fichas iniciales para un jugador desde el pozo
void roba7(tListaFichas& pozo, tJugador& jugador) {			
	int	contador = 0;
	for (contador = 0; contador < 7; contador++) {		//Bucle para ir cogiendo las 7 fichas iniciales
		robarFicha(pozo, jugador);
	}
}

//Funcion utilizada de prueba para mostrar el pozo en cualquiera de sus estados
void muestraPozo(tJuego juego) {			
	int contador;
	contador = 0;
	cout << "FICHAS DEL POZO BABY" << endl;
	for (contador = 0; contador < juego.pozo.cont; contador++) {		//Bucle para que vaya escribiendo cada una de las fichas del pozo a continuación de su número en el pozo
		cout << contador << "    " << juego.pozo.lista[contador].izq << "-" << juego.pozo.lista[contador].der << endl;

	}
	cout << endl << "----------------------------------------------" << endl << endl;

}

//Funcion que le pregunta al jugador que ficha quiere colocar	
int preguntaFicha(tJuego juego) {					
	int  numFicha;			
	cout << "Que ficha desea colocar? ";
	cin >> numFicha;
	return  numFicha;
}

//Funcion que sirve para eliminar una ficha del array de las fichas del jugador
void eliminaFicha(tListaFichas& fichas, int fichaeliminar) {			
	int contador;
	contador = 0;
	for (contador = fichaeliminar; contador < fichas.cont; contador++) {   //Bucle para ir copiando y pegando cada ficha después de la que se ha colocado en el tablero
		fichas.lista[contador] = fichas.lista[contador + 1];
	}
	fichas.cont--;

}

//Funcion que compara las fichas de un jugador con ambos lados del tablero, y devuelve la primera que encuentra que se puede poner a algun lado
int puedePonerAmbos(tJuego juego, int numJugador) {
	int numeroFicha = 0;
	int fichaponer = -1;
	bool seguir = true;

	while (seguir) {
		if ((puedePonerIzq(juego, numeroFicha, numJugador)) || (puedePonerDer(juego, numeroFicha, numJugador))) {		//Comprueba si puede poner en cualquiera de los dos lados
			seguir = false;
			fichaponer = numeroFicha;
		}
		numeroFicha++;
		if (numeroFicha == juego.jugadores[numJugador].fichas.cont) seguir = false;
	}

	return fichaponer;
}

//Funcion que calcula los puntos de todos los jugadores
void calculaPuntos(tJuego& juego) {			
	int i = 0, a = 0;
	int puntosRondaActual = 0;

	for (i = 0; i < juego.numJug; i++) {		//Bucle que va sumando todos los numeros de todas las fichas
		puntosRondaActual = 0;
		if (juego.jugadores[i].fichas.cont == 0) puntosRondaActual = 0;
		for (a = 0; a < juego.jugadores[i].fichas.cont; a++) {
			puntosRondaActual = puntosRondaActual + juego.jugadores[i].fichas.lista[a].suma;
		}
		juego.jugadores[i].puntos = juego.jugadores[i].puntos + puntosRondaActual;
	}
}

//funcion quie comprueba si la partida ha acabado porque ningun jugador pueda poner ni tampoco robar
bool sinSalida(const tJuego juego) {		
	bool salir = false;
	int i = 0;
	int bloqueo = 0;
	for (i = 0; i < juego.numJug; i++) {		//Bucle que comprueba si en todos los jugadores hay bloqueo
		if ((puedePonerAmbos(juego, i) == -1) && (juego.pozo.cont == 0)) {
			bloqueo++;		//Cuando lo hay, suma uno a esta varuiable
		}
	}
	if (bloqueo == juego.numJug) {		//Si hay tantos bloqueos como jugadores, la partida se debe volver a empezar
		system("cls");
		mostrarTablero(juego);
		cout << "La partida esta bloqueada, por lo que la ronda va a terminar." << endl;
		salir = true;
	}

	return salir;
}

//Menu que permite la opcion de cambiar el maximo de puntos de las fichas, entre 6, 7, 8, y 9
int eligeModo() {			
	int opcion = -1;
	while ((opcion < 6) || (opcion > 9)) {			//Bucle para que se introduzca un valor correcto
		cout << "Maximo de puntos en las fichas [6-9]: ";
		cin >> opcion;
	}

	return opcion;

}

//Funcion que pregunta cuantos jugadores van a jugar, el maxiumo de puntos, genera y desordena el pozo, roba las 7 fichas para todos los jugadores, busca quien tiene el doble mas alto y lo coloca
bool inicializarJuego(tJuego& juego, int maxPuntos) {		
	bool funcionEjecutada = true;
	juego.numJug = eligeJug(juego);
	if (juego.numJug != -1) {		//Si se han introudicdo bien los jugadores
		juego.maxPuntos = eligeModo();
		inicializarRonda(juego);
	}
	else {		//Si no se han introuducido bien los jugadores
		funcionEjecutada = false;
		juego.partidaInicida = false;
	}
	return funcionEjecutada;
}




//SUBPROGRAMAS DE LA VERSION 1 AQUI

 //Muestra el menú
int mostrarMenu(tJuego juego) {
	int opcion = -1;
	if ((JuegaHumano == true) || ((JuegaHumano == false) && (!juego.partidaInicida))) {			//Solo lo muestra cuando juega el humano o si no juega y la partida no esta iniciada

		int opcionMinimaDisp = 5;
		int opcionMaximaDisp = 6;
		cout << "--------------------" << endl;
		cout << "| MENU DE OPCIONES |" << endl;
		cout << "--------------------" << endl;
		cout << "1. Poner ficha por la izquierda" << endl;
		cout << "2. Poner ficha por la derecha" << endl;
		cout << "3. Robar nueva ficha" << endl;
		cout << "4. Guardar partida" << endl;
		cout << "5. Cargar partida" << endl;
		cout << "6. Empezar nueva partida" << endl;
		cout << "7. Mostrar puntos" << endl;
		cout << "0. Salir" << endl;

		cout << "Elija una opcion: ";
		cin >> opcion;
		if (juego.partidaInicida) {
			opcionMinimaDisp = 1;
			opcionMaximaDisp = 7;
		}
		while ((opcion > opcionMaximaDisp) || ((opcion < opcionMinimaDisp)) && (opcion != 0)) {		//Bucle para que siga preguntando que opcion quiere elegir
			cout << "Opcion no valida, introduzca otra: ";
			cin >> opcion;
		}


	}
	return opcion;		//Devuelve el valor que se ha introudico en  el cin
}

//Devuelve la ficha con los |a-b|
string muestraFicha(string posIzq, string posDer) {	

	return "|" + posIzq + "-" + posDer + "|";

}

//Muestra las fichas que hay puestas en el tablero y que tiene el jugador, y el numero de fichas e los bots
void mostrarTablero(tJuego juego) {			
	int numeroFicha = 0;
	int numeroJug;
	numeroJug = 1;



	cout << "--------------------" << endl;
	cout << "|      TABLERO     |";
	if (juego.partidaInicida) cout << "       Fichas en el pozo: " << juego.pozo.cont << endl;			//Contador de fichas en el pozo, para saber si cuando los jugadores no pueden robar es cierto
	else cout << endl;
	cout << "--------------------" << endl;
	cout << juego.tablero << endl << endl;			//Muestra el tablero

	if (juego.partidaInicida) {

		for (numeroJug = 1; numeroJug < juego.numJug; numeroJug++) {			//Bucle para que muestre a las maquinas
			cout << "Bot " << numeroJug << ":   ";
			if (MuestraBots) {		//Solo si MuestraBots es true te muestra las fichas
				for (numeroFicha = 0; numeroFicha < juego.jugadores[numeroJug].fichas.cont; numeroFicha++) {
					cout << muestraFicha(to_string(juego.jugadores[numeroJug].fichas.lista[numeroFicha].izq), to_string(juego.jugadores[numeroJug].fichas.lista[numeroFicha].der));
				}
			}	
			else {					//Si MuestraBots es false entonces te pone el numero de fichas, pero no cuales son
				if (juego.jugadores[numeroJug].fichas.cont != 1)cout << juego.jugadores[numeroJug].fichas.cont << " fichas";
				else cout << juego.jugadores[numeroJug].fichas.cont << " ficha";
			}
			cout << endl;
		}

		cout << endl;
		if (JuegaHumano == true) cout << "Jugador: ";		//Si JuegaHumanoe s true entonces te pone Jugador
		else cout << "Bot 0:   ";		//Si juegaHumano es false escribe que es otro Bot(porque lo es)
		numeroJug = 0;
		for (numeroFicha = 0; numeroFicha < juego.jugadores[0].fichas.cont; numeroFicha++) {			//Bucle para que te vaya escribiendo las fichas del jugador
			if (JuegaHumano == true) cout << "(" << numeroFicha << ")";
			cout << muestraFicha(to_string(juego.jugadores[numeroJug].fichas.lista[numeroFicha].izq), to_string(juego.jugadores[numeroJug].fichas.lista[numeroFicha].der));
			if (JuegaHumano == true) cout << "  ";

		}

		cout << endl << endl;

	}
}

//Funcion para compraar si una ficha en copncreto puede ser puesta a la derecha
bool puedePonerDer(tJuego juego, int ficha, int numJug) {		
	bool puede = false;
	//Comprobar
	if ((to_string(juego.jugadores[numJug].fichas.lista[ficha].izq) == juego.tablero.substr((juego.tablero.size() - 2), 1)) ||
		(to_string(juego.jugadores[numJug].fichas.lista[ficha].der) == juego.tablero.substr(juego.tablero.size() - 2, 1))) {		//Comprueba el lado derecho del tablero con ambos lados de la ficha
		puede = true;
	}

	return puede;

}

//Funcion para compraar si una ficha en copncreto puede ser puesta a la izquierda
bool puedePonerIzq(tJuego juego, int ficha, int numJug) {		
	bool puede = false;
	//Comprobar
	if ((to_string(juego.jugadores[numJug].fichas.lista[ficha].izq) == juego.tablero.substr(1, 1)) || 
		(to_string(juego.jugadores[numJug].fichas.lista[ficha].der) == juego.tablero.substr(1, 1))) {		//Comprueba el lado izquierdo del tablero con ambos lados de la ficha
		puede = true;
	}

	return puede;

}

//Funcion para que el jugador humano ponga una ficha a la izquierda
bool ponerFichaIzq(tJuego& juego) {		
	bool funcionEjecutada = true;
	int fichaElegida;

	//Comprobar
	fichaElegida = preguntaFicha(juego);
	if (!puedePonerIzq(juego, fichaElegida, juego.turno)) {			
		cout << "No se puede poner esa ficha por la izquierda" << endl;
		funcionEjecutada = false;		//Por si la ficha que ha seleccionado no se puede poner, devuelve que la funcion no se ha ejecutado
		system("pause");
	}
	else {

		if (to_string(juego.jugadores[0].fichas.lista[fichaElegida].der) == (juego.tablero.substr(1, 1))) {		//Por si se puede poner del derecho la ficha
			juego.tablero = muestraFicha(to_string(juego.jugadores[0].fichas.lista[fichaElegida].izq), to_string(juego.jugadores[0].fichas.lista[fichaElegida].der)) + juego.tablero;
			eliminaFicha(juego.jugadores[0].fichas, fichaElegida);		//Elimina la ficha colocada
		}
		else if (to_string(juego.jugadores[0].fichas.lista[fichaElegida].izq) == (juego.tablero.substr(1, 1))) {		//Por si la ficha se puede poner del reves
			juego.tablero = muestraFicha(to_string(juego.jugadores[0].fichas.lista[fichaElegida].der), to_string(juego.jugadores[0].fichas.lista[fichaElegida].izq)) + juego.tablero;
			eliminaFicha(juego.jugadores[0].fichas, fichaElegida);		//Elimina la ficha colocada

		}
	}
	return funcionEjecutada;
}

//Funcion para que el jugador humano ponga una ficha a la izquierda
bool ponerFichaDer(tJuego& juego) {		
	//Variables
	bool funcionEjecutada = true;
	int fichaElegida;

	//Comprobar	
	fichaElegida = preguntaFicha(juego);
	if (!puedePonerDer(juego, fichaElegida, juego.turno)) {
		cout << "No se puede poner esa ficha por la derecha" << endl;
		funcionEjecutada = false;		//Por si la ficha que ha seleccionado no se puede poner, devuelve que la funcion no se ha ejecutado
		system("pause");
	}
	else {
		if (to_string(juego.jugadores[0].fichas.lista[fichaElegida].izq) == (juego.tablero.substr((juego.tablero.size() - 2), 1))) {		//Por si se puede poner del derecho la ficha
			juego.tablero = juego.tablero + muestraFicha(to_string(juego.jugadores[0].fichas.lista[fichaElegida].izq), to_string(juego.jugadores[0].fichas.lista[fichaElegida].der));
			eliminaFicha(juego.jugadores[0].fichas, fichaElegida);		//Elimina la ficha colocada
		}		
		else if (to_string(juego.jugadores[0].fichas.lista[fichaElegida].der) == (juego.tablero.substr((juego.tablero.size() - 2), 1))) {		//Por si la ficha se puede poner del reves
			juego.tablero = juego.tablero + muestraFicha(to_string(juego.jugadores[0].fichas.lista[fichaElegida].der), to_string(juego.jugadores[0].fichas.lista[fichaElegida].izq));
			eliminaFicha(juego.jugadores[0].fichas, fichaElegida);		//Elimina la ficha colocada
		}

	}
	return funcionEjecutada;
}

//Funcion que comprueba que un jugador cualquiera pued robar ficha
bool puedeRobar(tJuego juego) {
	bool puede = false;
	if ((puedePonerAmbos(juego, juego.turno) == -1) && (juego.pozo.cont > 0)) {			//Puede sera true si no puede poner en ningun lado y hay fichas en el pozo
		puede = true;
	}
	return puede;
}

//Funcion para que el jugador humano robe una fihca desde el menu
bool robarFichaMenu(tJuego& juego) {		
	bool funcionEjecutada = true;
	if (puedeRobar(juego)) {		//Compara todas las fichads del jugador con el tablero 
		juego.jugadores[0].fichas.lista[juego.jugadores[0].fichas.cont] = juego.pozo.lista[juego.pozo.cont - 1];	//Copia la ultima ficha del pozo en la primera que es un hueco en blando del jugador
		juego.jugadores[0].fichas.cont++;
		juego.pozo.cont--;
		funcionEjecutada = false;		//Devuelve false, como si no se hubiera ejecutado para que al robar no pierda el turno y pueda poner
	}
	else if (puedePonerAmbos(juego, 0) != -1) {		//Comprueba que pueda poner a algun lado, para decirle que si puede poner ficha
		cout << "Puedes poner ficha" << endl;
		juego.turno = juego.numJug;
		system("pause");
		funcionEjecutada = false;		//Devuelve false para que no pierda el turno por si se ha confundido
	}
	else {
		cout << "No pouede robar ficha ni poner, por lo que su turno pasa" << endl;			//en el caso de que no pueda hacer nada
		system("pause");
	}
	return funcionEjecutada;

}

//Funcioon que guarda la partida actual
void guardarPartida(tJuego juego) {		
	//Variables
	ofstream partida;
	string nombre;
	cout << "Introduzca el nombre de guardado para el archivo (sin la extension.txt): ";
	cin >> nombre;
	nombre = nombre + ".txt";
	partida.open(nombre);		 //Apertura del archivo de guardado

	if (!partida.is_open()) cout << "Error" << endl;
	else {
		partida << juego.numJug << " " << juego.maxPuntos << endl << juego.tablero << endl;				//Guarda el pozo
		guardarListaFichas(partida, juego.pozo);
		for (int jugador = 0; jugador < juego.numJug; jugador++) {		//Bucle para que vaya guardando jugador por jugador sus listas de fichas
			guardarListaFichas(partida, juego.jugadores[jugador].fichas);
			partida << juego.jugadores[jugador].puntos << endl;			//Para que guarde los puntos de cada jugador
		}
		cout << "La partida se ha guardar correctamente." << endl;
		system("pause");
	}
	partida.close();			//Cierre del archivo
}

//Funcion para guardar una lista de fichas cualauiera
void guardarListaFichas(ofstream& archivo, const tListaFichas
	listaFichas) {

	archivo << listaFichas.cont << endl;
	for (int fichas = 0; fichas < listaFichas.cont; fichas++) {
		archivo << listaFichas.lista[fichas].izq << " " << listaFichas.lista[fichas].der << " ";		//Guarda ambos digitos de las fichas separadas por un espacio
	}
	archivo << endl;
}

//Funcion que se encarga de cargar una partida
void cargarPartida(tJuego& juego) {
	//Variables
	ifstream partidaGuardada;
	string nombre;
	cout << endl << "Nombre del archivo: ";
	cin >> nombre;
	nombre = nombre + ".txt";
	partidaGuardada.open(nombre);
	if (!partidaGuardada.is_open()) {
		cout << endl << "No existe dicho archivo" << endl << endl;		//en caso de que no haya un archivo con el nombre especificado
		system("pause");
	}
	else {
		//Carga toidos los valores que no requieren de un bucle
		partidaGuardada >> juego.numJug;
		partidaGuardada >> juego.maxPuntos;
		partidaGuardada >> juego.tablero;
		cargaListaFichas(partidaGuardada, juego.pozo);									//Carga pozo
		for (int jugadores = 0; jugadores < juego.numJug; jugadores++) {			//Carga datos de los jugadores
			cargaListaFichas(partidaGuardada, juego.jugadores[jugadores].fichas);
			partidaGuardada >> juego.jugadores[jugadores].puntos;
		}
		juego.partidaInicida = true;
		juego.turno = 0;
		cout << endl << "La partida se ha cargado correctamente." << endl;
		system("pause");
	}
	partidaGuardada.close(); // Cierre del archivo
		
}


void cargaListaFichas(ifstream& archivo, tListaFichas& listaFichas) {
	archivo >> listaFichas.cont;
	for (int fichasJugador = 0; fichasJugador < listaFichas.cont; fichasJugador++) {
		archivo >> listaFichas.lista[fichasJugador].izq;
		archivo >> listaFichas.lista[fichasJugador].der;
		listaFichas.lista[fichasJugador].suma = listaFichas.lista[fichasJugador].izq + listaFichas.lista[fichasJugador].der;
	}

}


//Ejecuta la opcion elegida por el humano
bool ejecutarOpcion(tJuego& juego, short int opcionMenu) {

	bool salir = false;
	bool siguienteTurno = true;		//Variable para saber si debe avanzar el turno o no
	if ((JuegaHumano == true) || ((JuegaHumano == false) && (!juego.partidaInicida))) {			//Para que solo lo ejecute si hay jugador humano o, si no lo hay pero la partida aun no se ha iniciado
		if (opcionMenu == 0)      salir = true;

		else if (opcionMenu == 1) siguienteTurno = ponerFichaIzq(juego);		//Por si no ha poddio poner a la izquierda, que no pierda el turno, entonces siguienteTurno sera false

		else if (opcionMenu == 2) siguienteTurno = ponerFichaDer(juego);		//Por si no ha poddio poner a la derecna, que no pierda el turno, entonces siguienteTurno sera false

		else if (opcionMenu == 3) siguienteTurno = robarFichaMenu(juego);		//robarFichaMenu siempre va a devolver false, pero asi se sigue con la misma estructura de las dos funciones anteriores

		else if (opcionMenu == 4) {
			guardarPartida(juego);
			siguienteTurno = false;		//En este caso no se iguala porque siempre que se guarda no se pierde el turno
		}
		else if (opcionMenu == 5) {
			cargarPartida(juego);
			siguienteTurno = false;		//En este caso no se iguala porque siempre que se carga no se pierde el turno
		}
		else if (opcionMenu == 6) siguienteTurno = inicializarJuego(juego, 0);		//Para que se poase de turno al inicializar

		else if (opcionMenu == 7) {
			muestraPuntos(juego);
			siguienteTurno = false;		//Seria injusto si al mostrar los puntos se perdiese el turno, asi que directamente es false
		}
		if ((juego.partidaInicida) && (opcionMenu != 0)) {		//Solo comprobara si hay ganador o bloqueo si la partida esta iniciada y no se ha seleccionado manualmente salir
			salir = compruebaGanadorRonda(juego);
			if (!juego.ganado) salir = sinSalida(juego);
		}
		if (opcionMenu != 6) {		//Solo pasara el tuirno si no se ha seleccionado inicializarJuego
			if (!siguienteTurno) juego.turno = 0;		//si siguienteTurno es false no se pasa el turno y le vuelve a tocar al jugador
			else juego.turno = ((++juego.turno) % juego.numJug);
		}


	}
	return salir;
}

//Funcion para elegir el numero de jugadores
int eligeJug(tJuego& juego) {

	int eleccionJugadores = 1;
	cout << endl << "Numero de jugadores que van a jugar la partida [2-4]: ";
	cin >> eleccionJugadores;
	if ((eleccionJugadores < 2) || (eleccionJugadores > 4)) {		//Bucle para que se introduzca un numero de jugadores correcto
		cout << endl << "Opcion no valida, Reconsidere su decision." << endl << endl;
		system("pause");
		eleccionJugadores = -1;
	}
	juego.numJug = eleccionJugadores;
	return eleccionJugadores;
}

//Funcion que reparte las 7 fichas a los n jugadores
void repartirFichas(tJuego& juego) {
	int i = 0;
	for (i = 0; i < juego.numJug; i++) {
		juego.jugadores[i].fichas.cont = 0;
		roba7(juego.pozo, juego.jugadores[i]);
		if (!juego.partidaInicida) juego.jugadores[i].puntos = 0;		//si aun no se ha iniciado la partida, se ponen los puntos a 0
	}
}

//Funcion que comprueba cual es el doble ,mas alto y devuelve el jugador que empieza
int  quienEmpieza(tArrayJugadores jugadores, int numeroDeJugadores, int& posFicha) {
	int numJug = 0;
	int numFicha = 0;
	int max = -1;
	int jugador = -1;	//Si el jugador cuando se devuelve sigue siendo -1 entonces se repartiran de nuevo todas las fichas
	int fichaPoner = 0;

	for (numJug = 0; numJug < numeroDeJugadores; numJug++) {		//Bucle que pasa por cadsa jugador
		for (numFicha = 0; numFicha < jugadores[numJug].fichas.cont; numFicha++) {		//Bucle que pasa por cada ficha de un jugador
			if (jugadores[numJug].fichas.lista[numFicha].izq == jugadores[numJug].fichas.lista[numFicha].der) {
				if (max < jugadores[numJug].fichas.lista[numFicha].izq) {
					max = jugadores[numJug].fichas.lista[numFicha].izq;
					jugador = numJug;		//Guarda el jugador que ha detectadoi que tiene de momento el doble mas alto
					fichaPoner = numFicha;		//Guarda el numero de ficha de ese juagdor que ha detectado que tiene el doble mas alto
				}
			}
		}
	}
	posFicha = fichaPoner;
	return jugador;
}

//Funcion que coloca la primera ficha de todas en el tablero
int empiezaJuego(int posFicha, tJuego& juego, int numeroDeJugadores) {
	int jugadorEmpieza = quienEmpieza(juego.jugadores, numeroDeJugadores, posFicha);
	if (jugadorEmpieza >= 0) {
		if (jugadorEmpieza == 0) {
			if (JuegaHumano == true) cout << "Empieza el jugador poniendo la ficha " << muestraFicha(to_string(juego.jugadores[0].fichas.lista[posFicha].izq), to_string(juego.jugadores[0].fichas.lista[posFicha].der));		
			//Para diferenciar si juega el humano o el bot 0
			else cout << "Empieza el Bot 0 poniendo la ficha " << muestraFicha(to_string(juego.jugadores[0].fichas.lista[posFicha].izq), to_string(juego.jugadores[0].fichas.lista[posFicha].der));
		}
		else {		//Rama en la que em pieza cualquiera de las otras maquinas
			cout << "Empieza el Bot " << jugadorEmpieza << " poniendo la ficha " << muestraFicha(to_string(juego.jugadores[jugadorEmpieza].fichas.lista[posFicha].izq), to_string(juego.jugadores[jugadorEmpieza].fichas.lista[posFicha].der));
		}
		juego.tablero = muestraFicha(to_string(juego.jugadores[jugadorEmpieza].fichas.lista[posFicha].izq), to_string(juego.jugadores[jugadorEmpieza].fichas.lista[posFicha].izq));		//Pone la pirmera ficha
		eliminaFicha(juego.jugadores[jugadorEmpieza].fichas, posFicha);			//La elimina del jugador que la tuviese
		cout << endl << endl;
		system("pause");
	}
	else {
		cout << "No hay dobles, se reparte de nuevo" << endl;
		system("pause");
		system("cls");
	}

	return jugadorEmpieza;
}

//Funcion generica para robar una ficha
void robarFicha(tListaFichas& pozo, tJugador& jugador) {

	jugador.fichas.lista[jugador.fichas.cont].izq = pozo.lista[pozo.cont - 1].izq;
	jugador.fichas.lista[jugador.fichas.cont].der = pozo.lista[pozo.cont - 1].der;
	jugador.fichas.lista[jugador.fichas.cont].suma = pozo.lista[pozo.cont - 1].suma;
	pozo.cont--;
	jugador.fichas.cont++;

}

//Funcion para que un bot cualquiera ponga una ficha a la izquierda
void ponerIzqBot(tJuego& juego, int fichaPoner) {

	if (to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].der) == (juego.tablero.substr(1, 1))) {		//Copmprueba si la ficha la puede poner del derecho
		juego.tablero = muestraFicha(to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].izq), to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].der)) + juego.tablero;
		eliminaFicha(juego.jugadores[juego.turno].fichas, fichaPoner);
	}
	else if (to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].izq) == (juego.tablero.substr(1, 1))) {		//Copmprueba si la ficha la puede poner del reves
		juego.tablero = muestraFicha(to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].der), to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].izq)) + juego.tablero;
		eliminaFicha(juego.jugadores[juego.turno].fichas, fichaPoner);

	}
}

//Funcion para que un bot cualquiera ponga una ficha a la derecha
void ponerDerBot(tJuego& juego, int fichaPoner) {
	
	if (to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].izq) == (juego.tablero.substr((juego.tablero.size() - 2), 1))) {		//Copmprueba si la ficha la puede poner del derecho
		juego.tablero = juego.tablero + muestraFicha(to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].izq), to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].der));
		eliminaFicha(juego.jugadores[juego.turno].fichas, fichaPoner);
	}
	else if (to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].der) == (juego.tablero.substr((juego.tablero.size() - 2), 1))) {		//Copmprueba si la ficha la puede poner del reves
		juego.tablero = juego.tablero + muestraFicha(to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].der), to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].izq));
		eliminaFicha(juego.jugadores[juego.turno].fichas, fichaPoner);
	}

}

//Funcion para que un bot cualquiera robe ficha
void robarBot(tJuego& juego) {

	juego.jugadores[juego.turno].fichas.lista[juego.jugadores[juego.turno].fichas.cont] = juego.pozo.lista[juego.pozo.cont - 1];
	juego.jugadores[juego.turno].fichas.cont++;
	juego.pozo.cont--;

}

//Estrategia que selecciona la primera ficha que puede poner que encuentra
void estrategia1(tJuego& juego) {

	while (puedeRobar(juego)) {
		robarBot(juego);
		cout << "El Bot " << juego.turno << " va a robar ficha" << endl << endl;
		system("pause");
		system("cls");
		mostrarTablero(juego);
	}
	 int fichaponer = puedePonerAmbos(juego, juego.turno);
	if (fichaponer >= 0) {		//Comprueba si puede poner alguna (si es -1 es que no puede poner ninguna)
		if (puedePonerIzq(juego, fichaponer, juego.turno)) {
			cout << "El Bot " << juego.turno << " pondra la ficha " << muestraFicha(to_string(juego.jugadores[juego.turno].fichas.lista[fichaponer].izq), to_string(juego.jugadores[juego.turno].fichas.lista[fichaponer].der)) << " a la izquierda" << endl;
			ponerIzqBot(juego, fichaponer);
		}
		else if (puedePonerDer(juego, fichaponer, juego.turno)) {
			cout << "El Bot " << juego.turno << " pondra la ficha " << muestraFicha(to_string(juego.jugadores[juego.turno].fichas.lista[fichaponer].izq), to_string(juego.jugadores[juego.turno].fichas.lista[fichaponer].der)) << " a la derecha" << endl;
			ponerDerBot(juego, fichaponer);
		}
	}
	else {		 //Si no puede poner ninguna
		cout << "El Bot " << juego.turno << " no puede poner y no puede robar. Pasa turno." << endl;
	}
	cout << endl;
	system("pause");

}

//Funcion para que los bots realicen sus turnos
bool jugarMaquina(tJuego& juego) {
	bool salir = false;
	int contadorJugadas = 0;
	if (juego.ganado == false) {		//Para que no lo ejecute si el jugador ha ganado antes
		//bucle para qeu ejecute las jugadas. Si hay hunmano, que lo haga solo si el turno es diferente de 0(eld el jugador). SI no hay jugador, que lo haga hasta que se hayan hecho tantas jugadas como bots haya en la partida
		while ((JuegaHumano == true) && ((juego.turno != 0) && (!salir)) || ((JuegaHumano == false) && (contadorJugadas < juego.numJug) && (!salir))) {		
			system("cls");
			mostrarTablero(juego);
			if ((JuegaHumano == false) && (juego.turno == 0)) estrategia3(juego);
			if (juego.turno == 1) estrategia2(juego);
			if (juego.turno == 2) estrategia1(juego);
			if (juego.turno == 3) {
				if (!estrategiaInventada) estrategia1(juego);		//si la constante de estrategiaInventada es false entonces hace la uno, si no, la 4
				else estrategia4(juego);
			}
			salir = compruebaGanadorRonda(juego);		//Comprueba si alguna maquina ha ganado
			if (!salir) salir = sinSalida(juego);		//Si ninguna ha ganado, comprueba si hay bloqueo
			if (!salir) {			//Si no se da ninguno de los dos casos anteriores, entonces el trurno pasa al siguiente
				juego.turno = ((++juego.turno) % juego.numJug);
				contadorJugadas++;		//Y se suma uno al contador de las jugadas que ha hecho la maquina
			}
		}
	}
	return salir;
}

//Estrategia que pone la ficha cuya suma de ambos digitos sea mas alta
void estrategia2(tJuego& juego) {
	int numFicha = 0;
	int sumaMax = -1;
	int fichaPoner = -1;

	while (puedeRobar(juego)) {			//Bucle para quye robe hasta que pueda poner
		robarBot(juego);
		cout << "El Bot " << juego.turno << " va a robar ficha" << endl << endl;
		system("pause");
		system("cls");
		mostrarTablero(juego);		//Refresca el tablero y la pantalla
	}
	for (numFicha = 0; numFicha < juego.jugadores[juego.turno].fichas.cont; numFicha++) {		//Bucle para encontrar cual de las fichas suma más
		if ((puedePonerIzq(juego, numFicha, juego.turno)) || (puedePonerDer(juego, numFicha, juego.turno))) {
			if (sumaMax < juego.jugadores[juego.turno].fichas.lista[numFicha].suma) {
				sumaMax = juego.jugadores[juego.turno].fichas.lista[numFicha].suma;
				fichaPoner = numFicha;
			}
		}
	}

	if (fichaPoner >= 0) {		//Compribación por si no puede pòner ninguna (en ese caso, fichaponer valdria -1)
		if (puedePonerIzq(juego, fichaPoner, juego.turno)) {
			cout << "El Bot " << juego.turno << " pondra la ficha " << muestraFicha(to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].izq), to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].der)) << " a la izquierda" << endl;
			ponerIzqBot(juego, fichaPoner);
		}
		else if (puedePonerDer(juego, fichaPoner, juego.turno)) {
			cout << "El Bot " << juego.turno << "  pondra la ficha " << muestraFicha(to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].izq), to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].der)) << " a la derecha" << endl;
			ponerDerBot(juego, fichaPoner);
		}
	}
	else cout << "El Bot " << juego.turno << " no puede poner y no puede robar. Pasa turno" << endl;
	cout << endl;
	system("pause");
}

//Funcion que comprueba despues de que cualquier jugador haya puesto una ficha si hay un ganador en la ronda
bool compruebaGanadorRonda(tJuego& juego) {
	if (juego.jugadores[juego.turno].fichas.cont == 0) {		//comprueba si el contador de las fichas del jugador que tiene el turno es 0, en cuyo caso habria ganado la ronda
		system("cls");
		mostrarTablero(juego);
		if (juego.turno == 0) {
			if (JuegaHumano) cout << "Has ganado esta ronda. Enhorabuena" << endl;
			else cout << "El Bot 0 ha ganado esta ronda. Enhorabuena" << endl;
		}
		else cout << "El Bot " << juego.turno << " ha ganado esta ronda. Enhorabuena" << endl;
		juego.ganado = true;
	}
	return juego.ganado;
}

//Funcion que muestra los puntos de los jugadores
void muestraPuntos(tJuego juego) {
	int i = 0;
	cout << endl;
	for (i = 0; i < juego.numJug; i++) {		//Bucle que va escribiendo los puntos de todos los jugadores
		if (i == 0) {
			if (JuegaHumano) cout << "Jugador - ";
			else cout << "Bot 0 - ";
		}
		else cout << "Bot " << i << " - ";
		cout << juego.jugadores[i].puntos << endl;
	}
	cout << endl;
	system("pause");
}

//Funcion que ordena las puntuaciones de los jugadores y muestra la clasificacion final
void endGame(tJuego juego) {
	int i = 0, a = 0, j = 0, puntAux = 0, posAux = 0, b = 0;
	typedef int tArrayPuntuaciones[4];		//Array de las puntuacines
	tArrayPuntuaciones minimos;
	typedef int tArrayPosiciones[4];		//Array de las posiciones segun el turno que le corresponde a cada jugador
	tArrayPosiciones posiciones;
	for (a = 0; a < juego.numJug; a++) {		//Bucle que le asigna a cada posicion de ambos arrays la puntuacion 
		minimos[a] = juego.jugadores[a].puntos;
		posiciones[a] = a;
	}
	//Metodo de la burbuja
	for (i = 0; i < juego.numJug; i++) {		//Bucle para que vaya pasando por todas las posicioes de un array
		for (j = i + 1; j < juego.numJug; j++) {		//Bucle para que vaya comparando el array del bucle de arriba copn todos los demas, asi los ordena
			if (minimos[j] < minimos[i]) {
				puntAux = minimos[i];		//Intercambia las posiciones de ambos arrays utilizando enteros auxiliares(posAux, puntAux)
				minimos[i] = minimos[j];
				minimos[j] = puntAux;
				posAux = posiciones[i];
				posiciones[i] = posiciones[j];
				posiciones[j] = posAux;
			}
		}
	}
	//Bucle que muestra la clasificacion final. No se invoca a muestrapuntos porque esa funcion no ordena los puntos de menor a mayor.
	cout << endl << "CLASIFICACION FINAL" << endl << endl;
	for (b = 0; b < juego.numJug; b++) {
		cout << b + 1 << ". ";
		if (posiciones[b] == 0) {
			if (JuegaHumano) cout << "Jugador - ";
			else cout << "Bot 0 - ";
		}
		else cout << "Bot " << posiciones[b] << " - ";

		cout << minimos[b] << " puntos" << endl;
	}
	cout << endl << endl;
	system("pause");
}

//Funcion que inicia una ronda nueva, ya sea la primera (es llamada en inicializarJuego) u otra cualquieraa
void  inicializarRonda(tJuego& juego) {

	juego.turno = -1;		//Se inicializa como -1 para que entre directamente en el bucle
	while (juego.turno == -1) {
		generaPozo(juego, juego.maxPuntos);
		desordenaPozo(juego);
		repartirFichas(juego);
		system("cls");
		juego.tablero = "";
		juego.partidaInicida = true;
		mostrarTablero(juego);
		juego.turno = empiezaJuego(-1, juego, juego.numJug);		//El turno se le asigna al que empiexa poniendo el doble mayor
	}
	juego.turno = ((++juego.turno) % juego.numJug);			//Al inicializarse con exito la ronda se pasa al turno siguiente
	jugarMaquina(juego);		//Juegan las maquinas para que si se ha comenzado una ronda que no es la primera no le toque siempre al juagdor humano

}

//Funcion optativa que se encarga de, primero comprobar que ficha seria mas perjudicial para otros jugadiores poner y mejor para el, y luego la pone
void estrategia3(tJuego& juego) {
	struct fichascantidad {			//struct que guarda el numero que busca, la cantiudad que hay en total y la cantidad que hay en la mano del juagdor
		int contadorNumeros = 0;
		int numeroEnCuestion;
	};
	typedef fichascantidad tArrayfichasColocar[10];		//Array con 10 structsa del tipo anterior, porque puede haber como maximo 10 numeros diferentes
	tArrayfichasColocar decidefichasponer;
	for (int i = 1; i <= ((juego.tablero.size() / 5)); i++) { //Bucle que va mirando en cada numero izquierdo de las fichas puestas en el tablero, y le suma uno a su contador
		string izqs;
		int numfichaizq;
		izqs = juego.tablero.substr((1 + 5 * (i - 1)), 1);
		numfichaizq = stoi(izqs);
		decidefichasponer[numfichaizq].contadorNumeros++;
		decidefichasponer[numfichaizq].numeroEnCuestion = numfichaizq;
	}
	for (int i = 1; i <= ((juego.tablero.size() / 5)); i++) {		//Bucle que va mirando en cada numero derecho de las fichas puestas en el tablero y le suma uno al contador de cada uno
		string ders;
		int numfichader;
		ders = juego.tablero.substr((3 + 5 * (i - 1)), -1);
		numfichader = stoi(ders);
		decidefichasponer[numfichader].contadorNumeros++;
		decidefichasponer[numfichader].numeroEnCuestion = numfichader;
	}
	for (int i = 1; i <= juego.jugadores[juego.turno].fichas.cont; i++) { //Bucle que pasa por todas las fichas del jugador y a cada numero que encuentra le suma uno al contador
		int manoizq;
		int manoder;
		manoizq = juego.jugadores[juego.turno].fichas.lista[i - 1].izq;
		manoder = juego.jugadores[juego.turno].fichas.lista[i - 1].der;
		decidefichasponer[manoizq].contadorNumeros++;
		decidefichasponer[manoder].contadorNumeros++;
		decidefichasponer[manoizq].numeroEnCuestion = manoizq;
		decidefichasponer[manoder].numeroEnCuestion = manoder;

	}
	int aux, numaux;		
	//metodo de la burbuja
	for (int i = 0; i <= juego.maxPuntos; i++) {		//Bucle que va pasando los arrays uno por uno
		for (int j = 0; j <= juego.maxPuntos; j++) {		//Bucle para ir comparando el resto con el array que proporciona el primer bucle
			if (decidefichasponer[j].contadorNumeros < decidefichasponer[j + 1].contadorNumeros) {
				aux = decidefichasponer[j].contadorNumeros;
				numaux = decidefichasponer[j].numeroEnCuestion;
				decidefichasponer[j].contadorNumeros = decidefichasponer[j + 1].contadorNumeros;
				decidefichasponer[j].numeroEnCuestion = decidefichasponer[j + 1].numeroEnCuestion;
				decidefichasponer[j + 1].contadorNumeros = aux;
				decidefichasponer[j + 1].numeroEnCuestion = numaux;
			}
		}
	}
	while (puedeRobar(juego)) {
		robarBot(juego);
		cout << "El Bot " << juego.turno << " va a robar ficha" << endl;
		system("pause");
		system("cls");
		mostrarTablero(juego);
	}
	int numOpuesto = -1;
	int haPuesto = -1;
	bool puedeseguir = false;

	for (int i = 0; i <= juego.maxPuntos; i++) {		//contador que va desde 0, equivalente en el array al elemento que mas se repite en el tablero y en su mano, hasta el ultimo numero posible de ficha
		for (int numFicha = 0; numFicha < juego.jugadores[juego.turno].fichas.cont; numFicha++) {	//contador para comparar todas las fichas de la mano
			numOpuesto = -1;
			if ((decidefichasponer[i].numeroEnCuestion == juego.jugadores[juego.turno].fichas.lista[numFicha].izq)) {	//Comprobacion de si se puede poner la ficha que toca por la izquierda del derecho
				if ((to_string(juego.jugadores[juego.turno].fichas.lista[numFicha].der) == juego.tablero.substr(1, 1))) numOpuesto = juego.jugadores[juego.turno].fichas.lista[numFicha].izq;
			}
			else if ((decidefichasponer[i].numeroEnCuestion == juego.jugadores[juego.turno].fichas.lista[numFicha].der)) {	//Comprobacion de si se puede poner la ficha que toca por la izquierda del reves
				if ((to_string(juego.jugadores[juego.turno].fichas.lista[numFicha].izq) == juego.tablero.substr(1, 1))) numOpuesto = juego.jugadores[juego.turno].fichas.lista[numFicha].der;
			}
			if (numOpuesto != -1) { //Si opuesto ya no es -1 entonces es que la ficha la puede poner de algun modo
				puedeseguir = puedeSeguir(juego, numFicha, numOpuesto);		//Comprueba que si pone esa ficha el mismo jugador podra seguir poniendo por ese lado
				if (puedeseguir) {
					cout << "El Bot " << juego.turno << " pondra la ficha " << muestraFicha(to_string(juego.jugadores[juego.turno].fichas.lista[numFicha].izq), to_string(juego.jugadores[juego.turno].fichas.lista[numFicha].der)) << " a la izquierda" << endl;
					ponerIzqBot(juego, numFicha);		//Pone la ficha por la izquierda e iguala numficha e i a diferentes valores para que se salga del bucle
					cout << endl;
					numFicha = juego.jugadores[juego.turno].fichas.cont;
					i = juego.maxPuntos + 1;
					haPuesto = 1;
				}
			}
			if (numOpuesto == -1) {			//Si opuestoi es -1 es que por la izquierda no se puede poner la ficha, por lo que lo va a comprobar por la derecha
				if ((decidefichasponer[i].numeroEnCuestion == juego.jugadores[juego.turno].fichas.lista[numFicha].izq)) {		//Comprobacion de si se puede poner la ficha que toca por la derecha del derecho
					if ((to_string(juego.jugadores[juego.turno].fichas.lista[numFicha].der) == juego.tablero.substr(juego.tablero.size() - 2, 1))) numOpuesto = juego.jugadores[juego.turno].fichas.lista[numFicha].izq;
				}
				else if ((decidefichasponer[i].numeroEnCuestion == juego.jugadores[juego.turno].fichas.lista[numFicha].der)) {		//Comprobacion de si se puede poner la ficha que toca por la derecha del reves
					if ((to_string(juego.jugadores[juego.turno].fichas.lista[numFicha].izq) == juego.tablero.substr(juego.tablero.size() - 2, 1)))	numOpuesto = juego.jugadores[juego.turno].fichas.lista[numFicha].der;
				}
				if (numOpuesto != -1) {		//Si opuesto ya no es -1 entonces es que la ficha la puede poner de algun modo
					puedeseguir = puedeSeguir(juego, numFicha, numOpuesto); // Comprueba que si pone esa ficha el mismo jugador podra seguir poniendo por ese lado
					if (puedeseguir) {
						cout << "El Bot " << juego.turno << " pondra la ficha " << muestraFicha(to_string(juego.jugadores[juego.turno].fichas.lista[numFicha].izq), to_string(juego.jugadores[juego.turno].fichas.lista[numFicha].der)) << " a la derecha" << endl;
						ponerDerBot(juego, numFicha);		//Pone la ficha por la derecha e iguala numficha e i a diferentes valores para que se salga del bucle
						cout << endl;
						numFicha = juego.jugadores[juego.turno].fichas.cont;
						i = juego.maxPuntos + 1;
						haPuesto = 1;
					}
				}
			}
		}
	}
	if (haPuesto == -1) estrategia2(juego);			//Si no ha poddio poner ninguna puede ser por que niunguna cumple los requisitos, pero no tiene por qwue significar que no pueda poner ninguna, por lo que hace la estrategia2
	else system("pause");
}

//Funcion inventada que pone la ficha que (obviamente pueda poner) tenga el digito ams grande a la derecha, y si hay 2 empatadas, la que tenga el digito mas grande a la izquierda
void estrategia4(tJuego& juego) {
	int i = 0;
	int fichaPoner = -1;
	int maxizq = -1, maxder = -1;
	while (puedeRobar(juego)) {		//Bucle que roba hasta que pueda poner
		robarBot(juego);
		cout << "El Bot " << juego.turno << " va a robar ficha" << endl << endl;
		system("pause");
		system("cls");
		mostrarTablero(juego);
	}
	for (i = 0; i < juego.jugadores[juego.turno].fichas.cont; i++) {		//Bucle que va mirando todas las fichas del jugador hasta encontrar la que tenga el numero derecho mas alto
		if ((puedePonerIzq(juego, i, juego.turno)) || (puedePonerDer(juego, i, juego.turno))) {
			if (stoi(to_string(juego.jugadores[juego.turno].fichas.lista[i].der)) > maxder) {
				fichaPoner = i;
				maxder = stoi(to_string(juego.jugadores[juego.turno].fichas.lista[i].der));
				maxizq = stoi(to_string(juego.jugadores[juego.turno].fichas.lista[i].izq));
			}
			else if (stoi(to_string(juego.jugadores[juego.turno].fichas.lista[i].der)) == maxder) {		//Si ambos derechos son iguales, entonces se procede a commparar el lado izquierdo
				if (stoi(to_string(juego.jugadores[juego.turno].fichas.lista[i].izq)) > maxizq) {
					fichaPoner = i;
					maxder = stoi(to_string(juego.jugadores[juego.turno].fichas.lista[i].der));
					maxizq = stoi(to_string(juego.jugadores[juego.turno].fichas.lista[i].izq));
				}
			}

		}
	}

	if (fichaPoner >= 0) {		//Comprobacion por si no hya ninguna ficha que pueda poner 
		if (puedePonerIzq(juego, fichaPoner, juego.turno)) {
			cout << "El Bot " << juego.turno << " pondra la ficha " << muestraFicha(to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].izq), to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].der)) << " a la izquierda" << endl;
			ponerIzqBot(juego, fichaPoner);
		}
		else if (puedePonerDer(juego, fichaPoner, juego.turno)) {
			cout << "El Bot " << juego.turno << " pondra la ficha " << muestraFicha(to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].izq), to_string(juego.jugadores[juego.turno].fichas.lista[fichaPoner].der)) << " a la derecha" << endl;
			ponerDerBot(juego, fichaPoner);
		}
	}
	else {
		cout << "El Bot " << juego.turno << " no puede poner y no puede robar. Pasa turno." << endl;
	}
	cout << endl;
	system("pause");


}

//Funcion que comprueba por que motivo ha terminado la partida
void compruebaFin(tJuego& juego, bool& salir, int opcionMenu) {
	string eleccion = "novale";
	if (salir) {
		calculaPuntos(juego);
		if (opcionMenu == 0) {		//Caso en el que la opcion seleccionada por la persona es salir
			while ((eleccion != "si") && (eleccion != "no")) {
				cout << "Seguro que quiere salir (si/no) ? ";
				cin >> eleccion;
				if (eleccion == "si") salir = true;
				else if (eleccion == "no") salir = false;
				else {
					cout << "Opcion no valida, introduzca otra." << endl;
					system("pause");
					system("cls");
					mostrarTablero(juego);
					mostrarMenu(juego);
				}

			}
		}
		else {		//Esta rama aúna tanto el caso de que haya un ganador tanto el que haya un bloqueo
			while ((eleccion != "si") && (eleccion != "no")) {
				cout << endl;
				cout << endl << "La ronda ha terminado, desearia empezar otra(si/no)?" << endl;
				cin >> eleccion;
				if (eleccion == "si") {
					salir = false;		//Salir es false porque no se va salir del bucle principal del main
					juego.ganado = false;
					muestraPuntos(juego);		//muestra la clasificacion al final de esa ronda
					cout << "La ronda esta a punto de  comenzar" << endl;
					system("pause");
					inicializarRonda(juego);		//Inicicializa otra ronda si le da a si
				}
				if ((eleccion != "si") && (eleccion != "no")) {		//Caso en el que se pone una opcion incorrecta
					cout << "Opcion no valida, introduzca otra." << endl;
					system("pause");
					system("cls");
					mostrarTablero(juego);
				}

			}
		}
	}

}

//Funcion auxiliar para la estrategia 3, que comprueba si al poner X ficha, el mismo podria seguir poniendo o no
bool puedeSeguir(tJuego& juego, int fichaSaltar, int numeroBusca) {
	int i = 0;
	bool encontrado = false;
	bool seguir = true;
	while (seguir) {
		if (i == fichaSaltar) i++;		//Ficha que se supone qwue va a poner en la estrategia 3, por lo que no puede mirar si ese numero está en esa ficha, porque es la que va a poner
		else {
			if (juego.jugadores[juego.turno].fichas.lista[i].izq == numeroBusca || juego.jugadores[juego.turno].fichas.lista[i].der == numeroBusca) {
				encontrado = true;		//Si encuentra otro numero com el que busca (el que se quedaria en el extremo del tablero en la estrategia 3), pone encontrado a true y sale del bucle
				seguir = false;
			}
			else i++;
		}
		if (i == juego.jugadores[juego.turno].fichas.cont) seguir = false;
	}

	return encontrado;
}
