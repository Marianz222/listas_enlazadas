#include "Pila.h"
#include "Enemigo.h"

//Constructor de la clase
Pila::Pila() {

	//Se asigna NULL al primer elemento, denotando que la lista se inicializa vacía
	primer_elemento = nullptr;

}

//Inserta un nuevo nodo a la pila, el cual contendrá el dato pasado por parámetro (en este caso, un enemigo)
void Pila::insertar(const Enemigo& nuevo_enemigo, Vector2f nueva_posicion) {

	//Variable para el nuevo nodo
	Nodo* nuevo_nodo = new Nodo(nuevo_enemigo);
	nuevo_nodo->obtenerEnemigo()->establecerPosicion(nueva_posicion);

	//Se le asigna el enlace al nodo nuevo
	nuevo_nodo->siguiente_nodo = primer_elemento;

	//Ahora el nodo insertado es el primer elemento
	primer_elemento = nuevo_nodo;

}

//Obtiene el próximo nodo de la pila y lo elimina. NOTA: Función sin terminar
Enemigo* Pila::retirar() {
	
	//Si está vacía, no se retira nada
	if (estaVacia()) {

		return nullptr;

	}

	//El nuevo nodo se convierte en el primer elemento de la lista
	Nodo* nodo_temporal = primer_elemento;

	//El primer elemento pasa a ser el segundo en la lista
	primer_elemento = primer_elemento->siguiente_nodo;

	return nodo_temporal->obtenerEnemigo();

	//Se libera la memoria del nodo retirado anteriormente
	delete nodo_temporal;

}

//Devuelve true si la pila está vacía
bool Pila::estaVacia() {

	//Si el primer elemento es nulo, significa que la lista está vacía
	return primer_elemento == nullptr;

}

//Método que recorre toda la lista enlazada comenzando por el inicio, y utilizando el puntero a siguiente nodo para saltar de nodo en nodo y leer
//los datos del mismo. Dentro del bucle, se llama a la función actualizar de cada enemigo, para que estos respondan a colisiones y demás
void Pila::actualizarElementos(Jugador& jugador, Vector2f dimensiones_ventana) {

	Nodo* nodo_iterador = primer_elemento;

	while (nodo_iterador != nullptr)
	{

		nodo_iterador->obtenerEnemigo()->actualizar(jugador, dimensiones_ventana);
		nodo_iterador = nodo_iterador->siguiente_nodo;

	}

}

//Método encargado de renderizar todos los elementos de la lista a la ventana pasada por referencia
void Pila::renderizarElementos(RenderWindow*& ventana) {

	//Toma el nodo actual
	Nodo* nodo_actual = primer_elemento;

	//Mientras el nodo actual no sea nulo, se ejecutan las directivas
	while (nodo_actual != nullptr) {

		//Variables para el enemigo y el sprite del mismo
		Enemigo enemigo_seleccionado = nodo_actual->enemigo_actual;
		Sprite sprite = enemigo_seleccionado.retornarSprite();

		//Se pasa la directiva para dibujar el sprite obtenido
		ventana->draw(sprite);

		//Finalmente, se pasa al siguiente nodo para repetir el ciclo hasta que el siguiente nodo apunte a NULL, rompiendo el mismo
		nodo_actual = nodo_actual->siguiente_nodo;

	}

}

Enemigo* Pila::retornarPrimerEnemigo() {

	return primer_elemento->obtenerEnemigo();

}