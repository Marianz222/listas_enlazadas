#include "Nodo.h"
#include <iostream>

using namespace std;

//Constructor de la clase, recibe un enemigo como nuevo dato
Nodo::Nodo(const Enemigo& nuevo_enemigo) {

	//El dato se aloja en la variable de enemigo_actual
	enemigo_actual = nuevo_enemigo;

	//Como no hay siguiente nodo, se asigna NULL
	siguiente_nodo = nullptr;

}

Enemigo* Nodo::obtenerEnemigo() {

	return &enemigo_actual;

}

Nodo* Nodo::obtenerSiguienteNodo() {

	return siguiente_nodo;

}
