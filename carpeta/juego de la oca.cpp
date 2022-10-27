#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <stdlib.h>
using namespace std;

//funciones declaradas
int primeraTirada(int casillaActual, bool MODO_DEBUG);
int turnoJugador(int turno, int casillaActual, int numeroDeTiradas);
int continuar (int casillaActual);

int quienEmpieza();
int tirarDado();
int tirarDadoManual();
int efectoPosicion(int casillaActual);
int efectoTiradas(int casillaActual, int numeroDeTiradas);

bool esMeta(int casilla);
bool esOca(int casilla);
bool esPuente(int casilla);
bool esDados(int casilla);
bool esLaberinto(int casilla);
bool esMuerte(int casilla);
bool esPosada(int casilla);
bool esPrision(int casilla);
bool esPozo(int casilla);

int siguienteOca(int casilla);
int siguientePuente(int casilla);
int siguienteDado(int casilla);
int siguienteLaberinto();
int siguienteMuerte();

string center(int width, string s);
int square(int casilla, string name);

int main() {
    //defino la seed del número aleatorio
    srand(time(0));

    //defino las variables
    int casillaActual1 = 1, casillaActual2 = 1;
    int tiradas1 = 0, tiradas2 = 0;
    int turno;

    int auxiliar;
    bool MODO_DEBUG;

    //elijo el modo de juego
    do {
        cout << "\n* Jugar con dado aleatorio [0]\n* Jugar sin dado aleatorio [1]\n"; cin >> auxiliar;
        MODO_DEBUG = auxiliar;
        if ((auxiliar != 0) && (auxiliar != 1))
            cout << "-> Introduzca 1 o 0...";
    } while ((auxiliar != 0) && (auxiliar != 1));

    //se elige quien comienza llamando a la funcion quienEmpieza ()
    int comienzo = quienEmpieza();
    cout << "\n* !Empieza el jugador " << comienzo << "!";
    turno = comienzo;

    //empieza la partida
    while (esMeta(casillaActual1) && esMeta(casillaActual2)){

        //turno del jugador 1
        if (turno == 1){
            tiradas1 += 1;
            turnoJugador (turno,casillaActual1, tiradas1);

            while (tiradas1 > 0){

                //primera tirada del turno
                casillaActual1 = primeraTirada(casillaActual1, MODO_DEBUG);

                //detección de casilla especial para mover
                casillaActual1 = efectoPosicion(casillaActual1);

                //detección de casilla especial para tiradas
                tiradas1 = efectoTiradas(casillaActual1, tiradas1);

                // cambio el valor de turno para pasar al turno del jugador 2
                tiradas1 -= 1;
            }
            turno += 1;
            continuar (casillaActual1);
        }

            //turno del jugador 2
        else if ((turno == 2) && (esMeta(casillaActual1))){
            tiradas2 += 1;
            turnoJugador (turno,casillaActual2, tiradas2);

            while (tiradas2 > 0){

                casillaActual2 = primeraTirada(casillaActual2, MODO_DEBUG);

                casillaActual2 = efectoPosicion(casillaActual2);

                tiradas2 = efectoTiradas(casillaActual2, tiradas2);

                tiradas2 -= 1;
            }
            turno -= 1;
            continuar(casillaActual2);
        }
    }

    if (casillaActual1 > casillaActual2)
        cout << "\n\n[****] -!El ganador es el jugador 1!- [****]";
    else
        cout << "\n\n[****] -!El ganador es el jugador 2!- [****]";

    return 0;
}

//
int primeraTirada (int casillaActual, bool MODO_DEBUG){
    //primera tirada del turno
    //modo debug
    int dado;
    string continuar = "B";
    if (MODO_DEBUG == 1){
        dado = tirarDadoManual ();
    }
        //modo aleatorio
    else if (MODO_DEBUG == 0){
        cout << "-> Pulse cualquier tecla para tirar el dado...\n";
        cin >> continuar;
        dado = tirarDado();
        cout << "* VALOR DEL DADO: " << dado << endl;
    }

    square(casillaActual + dado, "Pasas a la casilla: ");
    return casillaActual + dado;
}

int turnoJugador (int turno, int casillaActual, int numeroDeTiradas){
    cout << "\n\n(( TURNO PARA EL JUGADOR " << turno << " ))\n" << endl;
    square(casillaActual, "CASILLA:");
    if (numeroDeTiradas < 0)
        cout << "* Te quedan " << -numeroDeTiradas << " tiradas penalizadas\n";
    else if (numeroDeTiradas == 0)
        cout << "* !Jugaras en el siguiente turno!\n";

    return 0;
}

int continuar (int casillaActual){
    string continuar;

    if (esMeta(casillaActual)){
        cout << "-> Pulse cualquier tecla para continuar...\n"; cin >> continuar;
        return 0;
    }
    else
        return 0;
}
//
int quienEmpieza(){
    int empieza;
    empieza = rand() % 2 + 1;
    return empieza;
}

int tirarDado(){
    int dado;
    dado = rand() % 6 + 1;
    return dado;
}

int tirarDadoManual(){
    int dado;
    cout << "-> Introduce el valor del dado:\n"; cin >> dado;
    return dado;
}

//
int efectoPosicion(int casillaActual){
    if (!(esMeta(casillaActual))){
        return casillaActual;

    } else if (esOca(casillaActual)) {
        cout << "* !De Oca en Oca y tiro porque me toca!\n" << endl;
        square(siguienteOca(casillaActual), "Pasas a la casilla:");
        if (esMeta(casillaActual + 4)){
            cout << "\n* Y vuelves a tirar...\n";
        }return siguienteOca(casillaActual);
    } else if (esPuente(casillaActual)) {
        cout << "* !De puente a puente y tiro porque me lleva la corriente!\n" << endl;
        square(siguientePuente(casillaActual), "Pasas a la casilla:");
        cout << "\n* Y vuelves a tirar...\n" << endl;
        return siguientePuente(casillaActual);
    } else if (esDados(casillaActual)) {
        cout << "* !De dados a dados y tiro porque me ha tocado!\n" << endl;
        square(siguienteDado(casillaActual), "Pasas a la casilla:");
        cout << "\n* Y vuelves a tirar...\n" << endl;
        return siguienteDado(casillaActual);
    } else if (esLaberinto(casillaActual)) {
        cout << "* !Has caido en un laberinto! Retrocedes 12 casillas...\n" << endl;
        square(siguienteLaberinto(), "Vuelves a la casilla:");
        return siguienteLaberinto();
    } else if (esMuerte(casillaActual)) {
        cout << "* !Has caido en la muerte! Vuelves al principio...\n" << endl;
        square(siguienteMuerte(), "CASILLA:");
        return siguienteMuerte();
    } else if (esPosada(casillaActual)) {
        cout << "* !Has caido en la posada! Pierdes un turno.\n" << endl;
        return casillaActual;
    } else if (esPrision(casillaActual)) {
        cout << "* !Has caido en la prision! Pierdes dos turnos.\n" << endl;
        return casillaActual;
    } else if (esPozo(casillaActual)) {
        cout << "* !Has caido en el pozo! Pierdes tres turnos.\n" << endl;
        return casillaActual;
    } else
        return casillaActual;
}

int efectoTiradas(int casillaActual, int numeroDeTiradas){
    if (!(esMeta(casillaActual)))
        return numeroDeTiradas;

    else if (esOca (casillaActual)){
        return numeroDeTiradas + 1;
    }

    else if (esPuente(casillaActual)){
        return numeroDeTiradas + 1;
    }

    else if (esDados(casillaActual)){
        return numeroDeTiradas + 1;
    }

    else if (esPosada (casillaActual)){
        return numeroDeTiradas - 1;
    }

    else if (esPrision(casillaActual)){
        return numeroDeTiradas - 2;
    }

    else if (esPozo (casillaActual)){
        return numeroDeTiradas - 3;
    }

    else
        return numeroDeTiradas;
}

//
int siguienteOca(int casilla){
    if (casilla % 9 == 0)
        return casilla + 5;
    else
        return casilla + 4;
}

int siguientePuente(int casilla){
    int CASILLA_PUENTE_1 = 6;
    int CASILLA_PUENTE_2 = 12;
    if (casilla == CASILLA_PUENTE_1)
        return CASILLA_PUENTE_2;
    else if (casilla == CASILLA_PUENTE_2)
        return CASILLA_PUENTE_1;
}

int siguienteDado(int casilla){
    int CASILLA_DADOS_1 = 26;
    int CASILLA_DADOS_2 = 53;
    if (casilla == CASILLA_DADOS_1)
        return CASILLA_DADOS_2;
    else if (casilla == CASILLA_DADOS_2)
        return CASILLA_DADOS_1;
}

int siguienteLaberinto(){
    return 30;
}

int siguienteMuerte(){
    return 1;
}

//
bool esMeta(int casilla){
    int NUM_CASILLAS = 63;
    if (casilla >= NUM_CASILLAS)
        return 0;
    else
        return 1;
}

bool esOca(int casilla){
    if ((casilla % 9 == 0) || ((casilla + 4) % 9 == 0))
        return true;
    else
        return false;
}

bool esPuente(int casilla){
    int CASILLA_PUENTE_1 = 6;
    int CASILLA_PUENTE_2 = 12;
    if ((casilla == CASILLA_PUENTE_1) || (casilla == CASILLA_PUENTE_2))
        return true;
    else
        return false;

}

bool esDados(int casilla){
    int CASILLA_DADOS_1 = 26;
    int CASILLA_DADOS_2 = 53;
    if ((casilla == CASILLA_DADOS_1) || (casilla == CASILLA_DADOS_2))
        return true;
    else
        return false;
}

bool esLaberinto(int casilla){
    int CASILLA_LABERINTO = 42;
    if (casilla == CASILLA_LABERINTO)
        return true;
    else
        return false;

}

bool esMuerte(int casilla){
    int CASILLA_MUERTE = 58;
    if (casilla == CASILLA_MUERTE)
        return true;
    else
        return false;
}

bool esPosada(int casilla){
    int CASILLA_POSADA = 19;
    if (casilla == CASILLA_POSADA)
        return true;
    else
        return false;
}

bool esPrision(int casilla){
    int CASILLA_PRISION = 52;
    if (casilla == CASILLA_PRISION)
        return true;
    else
        return false;
}

bool esPozo(int casilla){
    int CASILLA_POZO = 31;
    if (casilla == CASILLA_POZO)
        return true;
    else
        return false;
}

string center(int width, string s){
    string out;

    //Obtenemos la longitud de la cadena deseada
    int length = s.length();

    /* Calculamos la longitud de los espacios que debe haber a cada lado de la cadena
     * obteniendo primero la diferencia entre la longitud deseada y la de la propia cadena,
     * y obteniendo la mitad, siendo el restante la diferencia entre el espacio izquierdo y
	 * la diferencia de longitudes.
     */
    int difference = width - length;
    int spL = difference/2;
    int spR = difference - spL;

    //Si la longitud deseada es menor que la de la propia cadena, retornamos la propia cadena
    if(width < length) out = s;
    else out = string(spL, ' ') + s + string(spR, ' ');

    return out;
}

int square(int casilla, string name){

    string casillaActual = to_string(casilla);

    cout << "//-----------------------------\\\\" << endl;

    for(int i = 0; i<5; i++) {
        if(i==0) cout << left << "|" << center(31, name) << right << "|" << endl;
        else if(i == 2) cout << left << "|" << center(31, casillaActual) << right << "|" << endl;
        else cout << left << "|" << setw(32) << right << "|" << endl;
    }

    cout << "\\\\-----------------------------//" << endl;

    return 0;
}
