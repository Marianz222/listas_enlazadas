#include "Cola.h"

//Constructor de la clase
Cola::Cola() {

    primer_elemento = nullptr;
    ultimo_elemento = nullptr;

}

//Inserta un nuevo nodo a la cola
void Cola::insertar(const Enemigo& nuevo_enemigo) {

    Nodo* nodo_nuevo = new Nodo(nuevo_enemigo);

    if (estaVacia()) {

        primer_elemento = ultimo_elemento = nodo_nuevo;

    }
    else {

        ultimo_elemento->siguiente_nodo = nodo_nuevo;
        ultimo_elemento = nodo_nuevo;

    }

}

//Obtiene el próximo nodo de la cola y lo elimina
void Cola::retirar() {

    

}

//Devuelve true si la cola está vacía
bool Cola::estaVacia() {

    return primer_elemento == nullptr;

}

void Cola::renderizarElementos(RenderWindow* ventana) {

    Nodo* nodo_actual = primer_elemento;

    while (nodo_actual != nullptr) {

        Enemigo enemigo_seleccionado = nodo_actual->enemigo_actual;
        Sprite sprite = enemigo_seleccionado.retornarSprite();

        ventana->draw(sprite);

        nodo_actual = nodo_actual->siguiente_nodo;

    }

}