#include "Cola.h"

//Constructor de la clase
Cola::Cola() {

    //Se establecen ambos elementos en NULL, para marcar que nuestra cola está vacía al crearse
    primer_elemento = nullptr;
    ultimo_elemento = nullptr;

}

//Inserta un nuevo nodo a la cola, recibe como parámetro el dato a insertar (en este caso, un enemigo pasado por referencia)
void Cola::insertar(const Enemigo& nuevo_enemigo) {

    //Crea el nuevo nodo a insertar, con el valor recibido
    Nodo* nodo_nuevo = new Nodo(nuevo_enemigo);

    //Si la cola está vacía...
    if (estaVacia()) {

        //El último y primer elemento son ahora el mismo nodo
        primer_elemento = ultimo_elemento = nodo_nuevo;

    }
    //Si ya tenía nodos...
    else {

        //El nodo se inserta al final de la cola
        ultimo_elemento->siguiente_nodo = nodo_nuevo;
        ultimo_elemento = nodo_nuevo;

    }

}

//Obtiene el próximo nodo de la cola y lo elimina
Enemigo Cola::retirar() {

    //Si la cola está vacía...
    if (estaVacia()) {

        //Se devuelve un enemigo nulo
        return Enemigo();

    }

    //Variables de enemigo y nodo temporal
    Enemigo enemigo = primer_elemento->enemigo_actual;
    Nodo* nodo_temporal = primer_elemento;

    //El primer elemento pasa al segundo lugar, siendo borrado en el proceso
    primer_elemento = primer_elemento->siguiente_nodo;
    delete nodo_temporal;

    if (estaVacia()) {

        //Si el elemento extraído fue el último en la cola, el último lugar ahora es nulo
        ultimo_elemento = nullptr;

    }

    //Se retorna el enemigo retirado
    return enemigo;

}

//Devuelve true si la cola está vacía
bool Cola::estaVacia() {

    return primer_elemento == nullptr;

}

//Método encargado de renderizar todos los elementos de la lista a la ventana pasada por referencia
void Cola::renderizarElementos(RenderWindow*& ventana) {

    //Toma el nodo actual
    Nodo* nodo_actual = primer_elemento;

    //Mientras el nodo actual no sea nulo, se ejecutan las directivas
    while (nodo_actual != nullptr) {

        //Variables para el enemigo y el sprite del mismo
        Enemigo enemigo_seleccionado = nodo_actual->enemigo_actual;
        Sprite sprite = enemigo_seleccionado.retornarSprite();

        //Se pasa la directiva para dibujar el sprite obtenido
        ventana->draw(sprite);

        //Finalmente, se pasa al siguiente nodo para repetir el ciclo hasta que el siguiente nodo apunte a NULL, rompiendo el ciclo
        nodo_actual = nodo_actual->siguiente_nodo;

    }

}

void Cola::actualizarElementos(Jugador& jugador, Vector2f dimensiones_ventana) {

    //Toma el nodo actual
    Nodo* nodo_actual = primer_elemento;

    //Mientras el nodo actual no sea nulo, se ejecutan las directivas
    while (nodo_actual != nullptr) {

        nodo_actual->enemigo_actual.actualizar(jugador, dimensiones_ventana);

        //Finalmente, se pasa al siguiente nodo para repetir el ciclo hasta que el siguiente nodo apunte a NULL, rompiendo el ciclo
        nodo_actual = nodo_actual->siguiente_nodo;

    }

}

Enemigo* Cola::buscarEnemigoInactivo() {

    Nodo* nodo_actual = primer_elemento;

    while (nodo_actual != nullptr) {

        Enemigo* enemigo = nodo_actual->obtenerEnemigo();

        if (!enemigo->estaMoviendose()) {

            return enemigo;

        }

        nodo_actual = nodo_actual->obtenerSiguienteNodo();

    }

    return nullptr;

}

void Cola::activarSiguienteEnemigo() {

    Enemigo* enemigo = buscarEnemigoInactivo();

    if (enemigo != nullptr) {

        enemigo->cambiarMovimiento(true, enemigo->retornarDireccionMovimiento());

    }

}