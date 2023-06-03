#include "Enemigo.h"

//Constructor A: No recibe parámetros, emplea valores por defecto en algunos casos
Enemigo::Enemigo() {

	en_movimiento = false;

	string raiz = "assets/images/";

	direccion_texturas[0] = raiz + "tortuga_roja.png";
	direccion_texturas[1] = raiz + "tortuga_azul.png";
	direccion_texturas[2] = raiz + "tortuga_amarilla.png";
	direccion_texturas[3] = raiz + "tortuga_verde.png";

	cargarGraficos("rojo");

	establecerPosicion({ 0.0f, 0.0f });

}

//Constructor B: Recibe color como parámetro
Enemigo::Enemigo(string color) {

	en_movimiento = false;

	string raiz = "assets/images/";

	direccion_texturas[0] = raiz + "tortuga_roja.png";
	direccion_texturas[1] = raiz + "tortuga_azul.png";
	direccion_texturas[2] = raiz + "tortuga_amarilla.png";
	direccion_texturas[3] = raiz + "tortuga_verde.png";

	cargarGraficos(color);

	establecerPosicion({ 0.0f, 0.0f });

}

//Carga la textura y se la aplica al sprites, además de modificar los atributos del mismo
void Enemigo::cargarGraficos(string color) {

	//La textura cargada dependerá de qué color reciba la función
	establecerColor(color);

	//Fija la textura al sprite
	sprite.setTexture(textura);

	//Variable que contiene el tamaño del sprite en ambos ejes
	Vector2f dimensiones_sprite = { sprite.getGlobalBounds().height, sprite.getGlobalBounds().width };

	//Posiciona el sprite en la ventana y cambia su origen al centro de la imagen
	sprite.setPosition(posicion);
	sprite.setOrigin(dimensiones_sprite.x / 2, dimensiones_sprite.y / 2);

}

//Envía la directiva de dibujar el sprite a la ventana pasada por parámetro
void Enemigo::renderizar(RenderWindow* ventana) {

	ventana->draw(sprite);

}

//Devuelve el sprite del enemigo
Sprite Enemigo::retornarSprite() {

	return sprite;

}

//Devuelve la caja de colisión del jugador
FloatRect Enemigo::retornarColisionador() {

	return sprite.getGlobalBounds();

}

//Método que permite "activar" un enemigo, haciendo que comience a moverse usando el bool adicional para la dirección
void Enemigo::cambiarMovimiento(bool estado, bool direccion) {

	en_movimiento = estado;
	direccion_movimiento = direccion;

}

//Devuelve el tamaño total del sprite
Vector2f Enemigo::retornarDimensionesSprite() {

	return {retornarColisionador().height, retornarColisionador().width};

}

//Fija la posicion del enemigo, dependiendo el vector suministrado
void Enemigo::establecerPosicion(Vector2f ubicacion) {

	posicion = { ubicacion.x, ubicacion.y };

	sprite.setPosition(ubicacion.x, ubicacion.y);

}

//Fija el color del enemigo, dependiendo del string pasado por parámetro
void Enemigo::establecerColor(string color) {

	//La textura cargada dependerá de qué color reciba la función
	if (color == "rojo") {

		textura.loadFromFile(direccion_texturas[0]);
	}
	else if (color == "azul") {

		textura.loadFromFile(direccion_texturas[1]);

	}
	else if (color == "amarillo") {

		textura.loadFromFile(direccion_texturas[2]);

	}
	else if (color == "verde") {

		textura.loadFromFile(direccion_texturas[3]);

	}

}

//Método que mueve al enemigo siempre y cuando este pueda moverse
void Enemigo::actualizar() {

	float movimiento = 0.0f;

	//Si el enemigo está en movimiento
	if (en_movimiento) {

		//Si debe moverse a la derecha
		if (direccion_movimiento) {

			movimiento = 5.0f;

		}
		//Si se debe mover a la izquierda
		else {

			movimiento = -5.0f;

		}

		sprite.move(movimiento, 0.0f);

	}

}