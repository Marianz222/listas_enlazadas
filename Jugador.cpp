#include "Jugador.h"

//Constructor de la clase
Jugador::Jugador(Vector2f ubicacion) {

	coordenadas = ubicacion;

	sprite.setPosition(coordenadas);

	cargarGraficos("assets/images/personaje.png");

}

//Carga la textura y se la aplica al sprites, adem�s de modificar los atributos del mismo
void Jugador::cargarGraficos(string direccion) {

	//Carga la textura y la aplica al sprite
	textura.loadFromFile(direccion);
	sprite.setTexture(textura);

	//Obtiene el tama�o total del sprite
	Vector2f dimensiones_sprite = { sprite.getGlobalBounds().height, sprite.getGlobalBounds().width };
	
	//Asigna posicion, escala y origen del sprite
	sprite.setPosition(coordenadas);
	sprite.setScale(0.4f, 0.4f);
	sprite.setOrigin(dimensiones_sprite.x / 2, dimensiones_sprite.y / 2);

}

//Env�a la directiva de dibujar el sprite a la ventana pasada por par�metro
void Jugador::renderizar(RenderWindow *ventana) {

	//Dibuja el sprite
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

	return coordenadas;

}

//Mueve el sprite por el valor pasado por par�metro
void Jugador::mover(Vector2f movimiento) {

	//Aplica las coordenadas en ambos ejes
	coordenadas += movimiento;

	sprite.move(coordenadas);

}

//Sobrecarga del m�todo anterior, pide dos float en lugar de un Vector
void Jugador::mover(float x, float y) {

	//Aplica las coordenadas en ambos ejes
	coordenadas += { x, y };

	sprite.move(coordenadas);

}

//M�todo encargado de actualizar la posici�n del sprite para que coincida con la variable de posici�n que tiene el objeto
void Jugador::actualizarPosicion() {

	sprite.setPosition(coordenadas);

}

void Jugador::moverAlSpawn() {

	float ventana_x = 800.0f;
	float ventana_y = 600.0f;

	coordenadas = { ventana_x / 2, ventana_y - 100.0f};

	sprite.setPosition(coordenadas);

}