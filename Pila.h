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

	//Métodos sin devolución de valores
	Enemigo* retirar();
	void insertar(const Enemigo& nuevo_enemigo, Vector2f nueva_posicion);
	void actualizarElementos(Jugador& jugador, Vector2f dimensiones_ventana);
	void renderizarElementos(RenderWindow*& ventana);
	Enemigo* retornarPrimerEnemigo();

	//Métodos con devolución de valor
	bool estaVacia();

};

