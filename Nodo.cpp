#include "Nodo.h"
#include <iostream>

using namespace std;

Nodo::Nodo(const Enemigo& nuevo_enemigo) {

	enemigo_actual = nuevo_enemigo;
	siguiente_nodo = nullptr;

}
