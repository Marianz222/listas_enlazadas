#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

//Inclusión de clases personalizadas
#include "Jugador.h"
#include "Pila.h"
#include "Cola.h"
#include "Puerta.h"

//Nombres de espacios
using namespace std;
using namespace sf;

class Juego

{

private:

	//Constantes misceláneas
	float const VENTANA_X = 800.0f;
	float const VENTANA_Y = 600.0f;
	int const SONIDOS_TOTALES = 5;
	string const NOMBRE_VENTANA = "Listas Enlazadas";

	//Variables de juego esenciales
	bool juego_terminado;
	int suelo;
	int requerimiento_altura;

	//Variables de ventana
	RenderWindow* ventana;
	int fps;
	Event* gestor_eventos;

	//Variables de textura y sprite
	Texture textura_fondo;
	Sprite sprite_fondo;

	//Objetos de juego
	Jugador* jugador;
	Puerta* salida;

	//Variables de sonido y buffers
	string direccion_sonidos[5];
	SoundBuffer buffers[5];
	Sound sonidos[5];
	bool silenciar_juego;

	//Variables de fuente y texto
	Font arial;
	Text cronometro_texto;

	//Variables de control de tiempo
	float tiempo_inicial;
	Clock reloj_principal;

	//Listas Enlazadas
	//Arreglo de colas
	Cola colas_enemigos[3];

	//Arreglo de pilas para cada lado. El lado izquierdo inicializa vacío
	Pila pilas_enemigos_izquierda[3];
	Pila pilas_enemigos_derecha[3];
	
	//Arreglos de enemigos temporales, usados para transferir enemigos de una estructura a otra y visualizarlos
	Enemigo* enemigos_retirados_cola[3];
	Enemigo* enemigos_retirados_pila[3];

	//Establece la altura de cada set de listas
	float altura_colas[3] = { 440.0f, 290.0f, 140.0f };
	float altura_pilas[3] = { 365.0f, 215.0f, 65.0f };

public:

	//Constructor
	Juego();

	//Métodos sin devolución de valores
	void bucleJuego();
	void cargarGraficos(string direccion);
	void cargarSonidos();
	void gestionarEventos();
	void controlarTeclado(float tiempo_delta);
	void renderizar();
	void actualizarTexto(int segundos);
	void chequearColisionesExtras();
	void reproducirSonidoReloj();
	void registrarEnConsola(string mensaje, bool terminar_linea);
	void chequearDerrota();
	void crearTexto();
	void configurarListas();
	void actualizarColas();
	void actualizarPilas();

	//Métodos con devolución de valor
	int actualizarCronometro();

};

/*
void Juego::actualizarPilas() {

	//Si el juego ya terminó, no se actualizarán las listas
	if (juego_terminado) {

		return;

	}

	static float offset = 0.0f;

	static bool direccion_actual = false;

	//Almacena el tamaño de la ventana
	Vector2f dimensiones_ventana = { VENTANA_X, VENTANA_Y };

	//Recorre el arreglo de las 3 pilas derechas, iterando a su vez en el arreglo de elementos retirados
	for (int i = 0; i < 3; i++) {

		//Si no hay ningún enemigo retirado...
		if (enemigos_retirados_pila[i] == nullptr) {

			//Se retira el primer enemigo de la pila
			enemigos_retirados_pila[i] = pilas_enemigos[i].retirar();

			//Registra en consola cuando una de las colas ejecuta una extracción
			registrarEnConsola("[INFO/DEBUG]: Evento - Extraccion en pila", true);

		}
		//Si en cambio hay un enemigo ya retirado...
		else {

			//Se activa el movimiento del enemigo retirado
			enemigos_retirados_pila[i]->cambiarMovimiento(true, false);
			enemigos_retirados_pila[i]->actualizar(*jugador, dimensiones_ventana);

			//Revisa si el enemigo en desplazamiento ha alcanzado su objetivo (tocar el borde o colisionar con otro enemigo)
			if (enemigos_retirados_pila[i]->retornarPosicion().x == offset ) {

				//Inserta el enemigo retirado de la pila A a la pila B
				enemigos_retirados_pila[i]->cambiarMovimiento(false, false);
				offset += 30.0f;

				//El enemigo extraído se inserta en el índice x + 3, ya que corresponde a las 3 pilas vacías (indices 3, 4 y 5)
				pilas_enemigos[i + 3].insertar(*enemigos_retirados_pila[i], { 15.0f, altura_pilas[i] });

				//El enemigo reitrado pasa a ser nulo
				enemigos_retirados_pila[i] = nullptr;

				//Registra en consola cuando una de las colas ejecuta una re-inserción
				registrarEnConsola("[INFO/DEBUG]: Evento - Insercion en pila", true);

			}

		}

		//Recorre todas las colas de enemigos, llamando al método actualizar el cual recorrerá las listas usando un while para llamar a "actualizar"
		//dentro del enemigo en cada uno de los nodos
		pilas_enemigos[i].actualizarElementos(*jugador, dimensiones_ventana);

	}

}*/