#pragma once
#include "Nodo.h"

class Pila

{

private:

	Nodo* primer_elemento;

public:

	Pila();
	void retirar();
	void insertar(const Enemigo& nuevo_enemigo);
	bool estaVacia();

};

