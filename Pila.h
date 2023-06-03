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
	void retirar();
	void insertar(const Enemigo& nuevo_enemigo);

	//M�todos con devoluci�n de valor
	bool estaVacia();

};

