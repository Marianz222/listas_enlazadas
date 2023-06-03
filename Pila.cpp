#include "Pila.h"
#include "Enemigo.h"

//Constructor de la clase
Pila::Pila() {

	primer_elemento = nullptr;

}

//Inserta un nuevo nodo a la pila
void Pila::insertar(const Enemigo& nuevo_enemigo) {

	Nodo* nuevo_nodo = new Nodo(nuevo_enemigo);

	nuevo_nodo->siguiente_nodo = primer_elemento;

	primer_elemento = nuevo_nodo;

}

//Obtiene el próximo nodo de la pila y lo elimina
void Pila::retirar() {
	
	if (estaVacia()) {

		return;

	}

	Nodo* nodo_temporal = primer_elemento;

	primer_elemento = primer_elemento->siguiente_nodo;

	delete nodo_temporal;

}

//Devuelve true si la pila está vacía
bool Pila::estaVacia() {

	return primer_elemento == nullptr;

}
