#pragma once
#include "Enemigo.h"

class Nodo

{

private:

	//Como dato contiene un enemigo y un enlace al siguiente nodo
	Enemigo enemigo_actual;
	Nodo* siguiente_nodo;

public:

	//Constructor
	Nodo(const Enemigo& nuevo_enemigo);

	//Declaración de clases amigas
	friend class Pila;
	friend class Cola;

};

