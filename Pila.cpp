#include "Pila.h"
#include "Enemigo.h"

//Constructor de la clase
Pila::Pila() {

	//Se asigna NULL al primer elemento, denotando que la lista se inicializa vac�a
	primer_elemento = nullptr;

}

//Inserta un nuevo nodo a la pila, el cual contendr� el dato pasado por par�metro (en este caso, un enemigo)
void Pila::insertar(const Enemigo& nuevo_enemigo) {

	//Variable para el nuevo nodo
	Nodo* nuevo_nodo = new Nodo(nuevo_enemigo);

	//Se le asigna el enlace al nodo nuevo
	nuevo_nodo->siguiente_nodo = primer_elemento;

	//Ahora el nodo insertado es el primer elemento
	primer_elemento = nuevo_nodo;

}

//Obtiene el pr�ximo nodo de la pila y lo elimina. NOTA: Funci�n sin terminar
void Pila::retirar() {
	
	if (estaVacia()) {

		return;

	}

	Nodo* nodo_temporal = primer_elemento;

	primer_elemento = primer_elemento->siguiente_nodo;

	delete nodo_temporal;

}

//Devuelve true si la pila est� vac�a
bool Pila::estaVacia() {

	//Si el primer elemento es nulo, significa que la lista est� vac�a
	return primer_elemento == nullptr;

}
