#pragma once
#include "Nodo.h"

class Pila

{

private:

	//Puntero para referenciar el inicio de la pila
	Nodo* primer_elemento;

public:

	//Constructor
	Pila();

	//M�todos sin devoluci�n de valores
	Enemigo* retirar();
	void insertar(const Enemigo& nuevo_enemigo, Vector2f nueva_posicion);
	void actualizarElementos(Jugador& jugador, Vector2f dimensiones_ventana);
	void renderizarElementos(RenderWindow*& ventana);
	Enemigo* retornarPrimerEnemigo();

	//M�todos con devoluci�n de valor
	bool estaVacia();

};

