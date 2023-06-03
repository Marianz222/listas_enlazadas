#include "Jugador.h"

//Constructor de la clase
Jugador::Jugador(Vector2f ubicacion) {

	posicion = { ubicacion.x, ubicacion.y };

	cargarGraficos("assets/images/personaje.png");

}

//Carga la textura y se la aplica al sprites, adem�s de modificar los atributos del mismo
void Jugador::cargarGraficos(string direccion) {

	textura.loadFromFile(direccion);
	sprite.setTexture(textura);

	Vector2f dimensiones_sprite = { sprite.getGlobalBounds().height, sprite.getGlobalBounds().width };
	
	sprite.setPosition(posicion);
	sprite.setScale(0.4f, 0.4f);
	sprite.setOrigin(dimensiones_sprite.x / 2, dimensiones_sprite.y / 2);

}

//Env�a la directiva de dibujar el sprite a la ventana pasada por par�metro
void Jugador::renderizar(RenderWindow *ventana) {

	ventana->draw(sprite);

}

//Devuelve el sprite
Sprite Jugador::retornarSprite() {

	return sprite;

}

//Devuelve la caja de colisi�n del sprite
FloatRect Jugador::retornarColisionador() {

	return sprite.getGlobalBounds();

}

//Devuelve la posici�n actual del sprite
Vector2f Jugador::retornarPosicion() {

	return posicion;

}

//Mueve el sprite por el valor pasado por par�metro
void Jugador::mover(Vector2f movimiento) {

	posicion.x += movimiento.x;
	posicion.y += movimiento.y;

}

//Sobrecarga del m�todo anterior, pide dos float en lugar de un Vector
void Jugador::mover(float x, float y) {

	posicion.x += x;
	posicion.y += y;

}

void Jugador::actualizarPosicion() {

	sprite.setPosition(posicion);

}