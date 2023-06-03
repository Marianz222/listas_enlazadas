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
	void retirar();
	void insertar(const Enemigo& nuevo_enemigo);

	//Métodos con devolución de valor
	bool estaVacia();

};

