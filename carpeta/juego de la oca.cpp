#include <iostream>
#include <ctime>
using namespace std;

//funciones declaradas
int quienEmpieza();
int tirarDado();
int tirarDadoManual();
int efectoPosicion(int casillaActual);
int efectoTiradas(int casillaActual, int numeroDeTiradas);

//estas funciones todavía no las he usado (menos esMeta)
bool esMeta(int casilla);
bool esOca(int casilla);
//bool esPuente(int casilla);
//bool esDados(int casilla);
//bool esLaberinto(int casilla);
//bool esMuerte(int casilla);
//bool esPosada(int casilla);
//bool esPrision(int casilla);
//bool esPozo(int casilla);

int siguienteOca(int casilla);
//int siguientePuente(int casilla);
//int siguienteDado(int casilla);
//int siguienteLaberinto();
//int siguienteMuerte();



int main() {
    //defino la seed del número aleatorio
    srand(time(0));

    //defino las variables
    int casillaActual1 = 1, casillaActual2 = 1, dado, auxiliar, turno, tiradas1 = 0, tiradas2 = 01;
    string continuar;
    bool MODO_DEBUG;

    //elijo el modo de juego
    do {
        cout << "\nJugar con dado aleatorio [0]\nJugar sin dado aleatorio [1]\n"; cin >> auxiliar;
        MODO_DEBUG = auxiliar;
        if ((auxiliar != 0) && (auxiliar != 1))
            cout << "introduzca 1 o 0";
    } while ((auxiliar != 0) && (auxiliar != 1));

    //se elige quien comienza llamando a la funcion quienEmpieza ()
    int comienzo = quienEmpieza();
    if (comienzo == 1){
        cout << "\n**** Empieza el jugador: 1 ****";
        turno = 1;
    }
    else if (comienzo == 2){
        cout << "\n**** Empieza el jugador: 2 ****";
        turno = 0;
    }


    //empieza la partida
    while (esMeta(casillaActual1) && esMeta(casillaActual2)){

        //turno del jugador 1
        if (turno == 1){
            tiradas1 += 1;
            cout << "\n\n**TURNO PARA EL JUGADOR 1**\n";
            cout << "CASILLA ACTUAL: " << casillaActual1 << endl;

            if (tiradas1 < 0)
                cout << "Te quedan " << -tiradas1 << " tiradas penalizadas";

            while (tiradas1 > 0){

                //primera tirada del turno
                //modo debug
                if (MODO_DEBUG == 1){
                    dado = tirarDadoManual ();
                }
                    //modo aleatorio
                else if (MODO_DEBUG == 0){
                    while(continuar != "A"){
                        cout << "Pulse A para tirar el dado\n";
                        cin >> continuar;
                    }
                    continuar = "B";
                    dado = tirarDado();
                    cout << "VALOR DEL DADO: " << dado << endl;
                }
                casillaActual1 += dado;
                cout << "Pasas a la casilla: " << casillaActual1 << endl;

                //detección de casilla especial para mover
                casillaActual1 = efectoPosicion(casillaActual1);

                //detección de casilla especial para tiradas
                tiradas1 = efectoTiradas(casillaActual1, tiradas1);

                // cambio el valor de turno para pasar al turno del jugador 2
                tiradas1 -= 1;
            }
        turno = turno - 1;
        }

            //turno del jugador 2
        else if (turno == 0){
            cout << "\n\n**TURNO PARA EL JUGADOR 2**\n";
            cout << "CASILLA ACTUAL: " << casillaActual2 << endl;

            if (MODO_DEBUG == 1){
                dado = tirarDadoManual ();
            }
            else{
                while(continuar != "A"){
                    cout << "Pulse A para tirar el dado\n";
                    cin >> continuar;
                }
                continuar = "B";
                dado = tirarDado();
                cout << "VALOR DEL DADO: " << dado << endl;
            }

            casillaActual2 += dado;
            cout << "Pasas a la casilla: " << casillaActual2 << endl;

            turno = turno + 1;
        }

    }

    if (casillaActual1 > casillaActual2)
        cout << "\n\nEl ganador es el jugador 1";
    else
        cout << "\n\nEl ganador es el jugador 2";

    return 0;
}

int quienEmpieza(){
    int empieza;
    empieza = rand() % 2 + 1;
    return empieza;
}

int tirarDado(){
    int dado;
    dado = rand() % 20 + 1;
    return dado;
}

int tirarDadoManual(){
    int dado;
    cout << "Introduce el valor del dado\n"; cin >> dado;
    return dado;
}

int efectoPosicion(int casillaActual){
    if (esOca (casillaActual)){
        cout << "De Oca en Oca y tiro porque me toca\n";
        cout << "Pasas a la casilla: " << siguienteOca(casillaActual) << "\n Y vuelves a tirar";
        return siguienteOca(casillaActual);

    }
    else
        return casillaActual;
}

int efectoTiradas(int casillaActual, int numeroDeTiradas){
    if (esOca (casillaActual)){

    }


}




int siguienteOca(int casilla){
    if (casilla % 9 == 0)
        return casilla + 5;
    else
        return casilla + 4;
}

bool esMeta(int casilla){
    int NUM_CASILLAS = 63;
    if (casilla >= NUM_CASILLAS)
        return 0;
    else
        return 1;
}

bool esOca(int casilla){
    if ((casilla % 9 == 0)||((casilla + 4) % 9 == 0)) {
        return true;
    } else
        return false;

}