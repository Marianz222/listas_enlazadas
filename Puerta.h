#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

//Nombres de espacios
using namespace sf;
using namespace std;

class Puerta

{

private:

	Texture textura;
	Sprite sprite;
	Vector2f posicion;

public:

	//Constructor
	Puerta(Vector2f ubicacion);

	//Funciones sin retorno
	void cargarGraficos(string direccion);
	void renderizar(RenderWindow* ventana);

	//Funciones con retorno
	Sprite retornarSprite();
	FloatRect retornarColisionador();

};

