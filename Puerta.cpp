#include "Puerta.h"

//Constructor de la clase
Puerta::Puerta(Vector2f ubicacion) {

	posicion = { ubicacion.x, ubicacion.y };

	cargarGraficos("assets/images/puerta.png");

}

//Carga la textura y se la aplica al sprites, además de modificar sus atributos
void Puerta::cargarGraficos(string direccion) {

	textura.loadFromFile(direccion);
	sprite.setTexture(textura);

	Vector2f dimensiones_sprite = { sprite.getGlobalBounds().height, sprite.getGlobalBounds().width };

	sprite.setPosition(posicion);
	sprite.setScale(1.2f, 1.2f);
	sprite.setOrigin(dimensiones_sprite.x / 2, dimensiones_sprite.y / 2);

}

//Envía la directiva de dibujar el sprite a la ventana pasada por parámetro
void Puerta::renderizar(RenderWindow* ventana) {

	ventana->draw(sprite);

}

//Devuelve el sprite de la puerta
Sprite Puerta::retornarSprite() {

	return sprite;

}

//Devuelve la caja de colisión de la puerta
FloatRect Puerta::retornarColisionador() {

	return sprite.getGlobalBounds();

}