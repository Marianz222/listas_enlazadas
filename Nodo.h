#pragma once
#include "Enemigo.h"

class Nodo

{

private:

	Enemigo enemigo_actual;
	Nodo* siguiente_nodo;

public:

	Nodo(const Enemigo& nuevo_enemigo);

	friend class Pila;
	friend class Cola;

};

