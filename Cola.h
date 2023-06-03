#pragma once
#include "Nodo.h"

class Cola

{

private:

	Nodo* primer_elemento;
	Nodo* ultimo_elemento;

public:

	Cola();
	void retirar();
	void insertar(const Enemigo& nuevo_enemigo);
	bool estaVacia();
	void renderizarElementos(RenderWindow* ventana);

};

