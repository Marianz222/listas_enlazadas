#include "Pila.h"
#include "Enemigo.h"

//Constructor de la clase
Pila::Pila() {

	//Se asigna NULL al primer elemento, denotando que la lista se inicializa vacía
	primer_elemento = nullptr;

}

//Inserta un nuevo nodo a la pila, el cual contendrá el dato pasado por parámetro (en este caso, un enemigo)
void Pila::insertar(const Enemigo& nuevo_enemigo) {

	//Variable para el nuevo nodo
	Nodo* nuevo_nodo = new Nodo(nuevo_enemigo);

	//Se le asigna el enlace al nodo nuevo
	nuevo_nodo->siguiente_nodo = primer_elemento;

	//Ahora el nodo insertado es el primer elemento
	primer_elemento = nuevo_nodo;

}

//Obtiene el próximo nodo de la pila y lo elimina. NOTA: Función sin terminar
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

	//Si el primer elemento es nulo, significa que la lista está vacía
	return primer_elemento == nullptr;

}
