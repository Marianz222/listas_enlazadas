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

	//M�todos sin devoluci�n de valores
	void insertar(const Enemigo& nuevo_enemigo);
	void renderizarElementos(RenderWindow*& ventana);
	void actualizarElementos(Jugador& jugador, Vector2f dimensiones_ventana);
	void activarSiguienteEnemigo();

	//M�todos con devoluci�n de valor
	Enemigo retirar();
	Enemigo* buscarEnemigoInactivo();
	bool estaVacia();

};

