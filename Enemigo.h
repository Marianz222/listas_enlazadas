#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Jugador.h"

//Nombres de espacios
using namespace std;
using namespace sf;

class Enemigo

{

private:

	//Variables básicas
	string direccion_texturas[4];
	bool en_movimiento;

	//variable para direccionar el movimiento
	//true = derecha
	//false = izquierda
	bool direccion_movimiento;

	//Variables de SFML
	Texture* textura;
	Sprite sprite;
	Vector2f coordenadas;

public:

	//Constructor
	Enemigo();
	Enemigo(int color, bool direccion, bool activo);

	//Métodos sin retorno
	void cargarGraficos(int color);
	void renderizar(RenderWindow* ventana);
	void cambiarMovimiento(bool estado, bool direccion);
	void actualizar(Jugador& jugador, Vector2f dimensiones_ventana);
	void establecerPosicion(Vector2f ubicacion);
	void mover(Vector2f desplazamiento);

	//Funciones con retorno
	Sprite retornarSprite();
	FloatRect retornarColisionador();
	Vector2f retornarDimensionesSprite();
	Vector2f retornarPosicion();
	bool hayColision(Jugador jugador);
	bool estaMoviendose();
	bool retornarDireccionMovimiento();

};