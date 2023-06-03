#pragma once
#include "Nodo.h"

class Cola

{

private:

	//Punteros para referenciar el inicio y fin de la cola
	Nodo* primer_elemento;
	Nodo* ultimo_elemento;

public:

	//Constructor de la clase
	Cola();

	//Métodos sin devolución de valores
	void insertar(const Enemigo& nuevo_enemigo);
	void renderizarElementos(RenderWindow*& ventana);

	//Métodos con devolución de valor
	Enemigo retirar();
	bool estaVacia();

};

