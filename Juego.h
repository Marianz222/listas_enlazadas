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

	//Variables de fuente y texto
	Font arial;
	Text cronometro_texto;

	//Variables de control de tiempo
	float tiempo_inicial;
	Clock reloj_principal;

	//Listas Enlazadas
	Pila pilas_enemigos[6];
	Cola colas_enemigos[3];

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
	void renderizarListasEnemigos();

	//Métodos con devolución de valor
	int actualizarCronometro();

};

