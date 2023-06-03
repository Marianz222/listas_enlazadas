#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

//Nombres de espacios
using namespace std;
using namespace sf;

class Jugador

{

private:

	//Variables comunes
	Texture textura;
	Sprite sprite;
	Vector2f posicion;

public:

	//Constructor
	Jugador(Vector2f ubicacion);

	//Funciones sin retorno
	void cargarGraficos(string direccion);
	void renderizar(RenderWindow *ventana);
	void mover(Vector2f movimiento);
	void mover(float x, float y);
	void actualizarPosicion();

	//Funciones con retorno
	Sprite retornarSprite();
	FloatRect retornarColisionador();
	Vector2f retornarPosicion();

};

