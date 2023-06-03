#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

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
	Texture textura;
	Sprite sprite;
	Vector2f posicion;

public:

	//Constructor
	Enemigo();
	Enemigo(string color, bool direccion);

	//Métodos sin retorno
	void cargarGraficos(string color);
	void renderizar(RenderWindow* ventana);
	void cambiarMovimiento(bool estado, bool direccion);
	void actualizar();
	void establecerPosicion(Vector2f ubicacion);
	void establecerColor(string color);

	//Funciones con retorno
	Sprite retornarSprite();
	FloatRect retornarColisionador();
	Vector2f retornarDimensionesSprite();

};

