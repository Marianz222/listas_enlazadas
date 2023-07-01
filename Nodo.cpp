#include "Nodo.h"

using namespace std;

//Constructor de la clase, recibe un enemigo como nuevo dato
Nodo::Nodo(const Enemigo& nuevo_enemigo) {

	//El dato se aloja en la variable de enemigo_actual
	enemigo_actual = nuevo_enemigo;

	//Como no hay siguiente nodo, se asigna NULL
	siguiente_nodo = nullptr;

}

//Método usado para obtener el enemigo dentro del nodo seleccionado
Enemigo* Nodo::obtenerEnemigo() {

	return &enemigo_actual;

}

//Método similar al anterior, pero en su lugar obtiene la dirección al siguiente nodo
Nodo* Nodo::obtenerSiguienteNodo() {

	return siguiente_nodo;

}
