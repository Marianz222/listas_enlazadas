#include "Cola.h"

//Constructor de la clase
Cola::Cola() {

    //Se establecen ambos elementos en NULL, para marcar que nuestra cola está vacía al crearse
    primer_elemento = nullptr;
    ultimo_elemento = nullptr;

}

//Inserta un nuevo nodo a la cola, recibe como parámetro el dato a insertar (en este caso, un enemigo pasado por referencia)
void Cola::insertar(const Enemigo& nuevo_enemigo, Vector2f nueva_posicion) {

    //Crea el nuevo nodo a insertar, con el valor recibido
    Nodo* nodo_nuevo = new Nodo(nuevo_enemigo);
    nodo_nuevo->obtenerEnemigo()->establecerPosicion(nueva_posicion);

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
Enemigo* Cola::retirar() {

    //Si la cola está vacía...
    if (estaVacia()) {

        //Se devuelve un puntero nulo
        return nullptr;

    }

    Nodo* nodoRetirar = primer_elemento;
    primer_elemento = primer_elemento->siguiente_nodo;
    Enemigo* e = nodoRetirar->obtenerEnemigo();
    return e;

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

        //Finalmente, se pasa al siguiente nodo para repetir el ciclo hasta que el siguiente nodo apunte a NULL, rompiendo el mismo
        nodo_actual = nodo_actual->siguiente_nodo;

    }

}

//Método que recorre toda la lista enlazada comenzando por el inicio, y utilizando el puntero a siguiente nodo para saltar de nodo en nodo y leer
//los datos del mismo. Dentro del bucle, se llama a la función actualizar de cada enemigo, para que estos respondan a colisiones y demás
void Cola::actualizarElementos(Jugador& jugador, Vector2f dimensiones_ventana) {
    
    Nodo* nodo_iterador = primer_elemento;

    while (nodo_iterador != nullptr)
    {

        nodo_iterador->obtenerEnemigo()->actualizar(jugador, dimensiones_ventana);
        nodo_iterador = nodo_iterador->siguiente_nodo;

    }

}

//Método el cual desplaza todos los elementos restantes en la cola hacia la derecha
//Este metodo es con el que tengo dificultades, ya que no estoy seguro si se está ejecutando correctamente o si está bien implementado
void Cola::desplazarEnemigos() {

    Nodo* nodo_iterador = primer_elemento;

    while (nodo_iterador != nullptr)
    {

        nodo_iterador->obtenerEnemigo()->mover({ 30.0f, 0.0f });
        nodo_iterador = nodo_iterador->siguiente_nodo;

    }

}