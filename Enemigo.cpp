#include "Enemigo.h"

//Constructor A: No recibe par�metros, emplea valores por defecto en algunos casos
Enemigo::Enemigo() {

	//Los enemigos empiezan sin moverse
	en_movimiento = false;

	//Raiz del directorio de imagenes
	string raiz = "assets/images/";

	//Usa la raiz para determinar el directorio de cada textura
	direccion_texturas[0] = raiz + "tortuga_roja.png";
	direccion_texturas[1] = raiz + "tortuga_azul.png";
	direccion_texturas[2] = raiz + "tortuga_amarilla.png";
	direccion_texturas[3] = raiz + "tortuga_verde.png";

	//Carga los gr�ficos por defecto
	cargarGraficos(0);

	//Asigna la posici�n por defecto
	establecerPosicion({ 0.0f, 0.0f });

}

//Constructor B: Recibe color como par�metro
Enemigo::Enemigo(int color, bool direccion) {
	
	//Fija la direcci�n en la que se mover� el enemigo cuando tenga la directiva de hacerlo
	direccion = direccion_movimiento;

	//Los enemigos empiezan sin moverse
	en_movimiento = false;

	//Raiz del directorio de imagenes
	string raiz = "assets/images/";

	//Usa la raiz para determinar el directorio de cada textura
	direccion_texturas[0] = raiz + "tortuga_roja.png";
	direccion_texturas[1] = raiz + "tortuga_azul.png";
	direccion_texturas[2] = raiz + "tortuga_amarilla.png";
	direccion_texturas[3] = raiz + "tortuga_verde.png";

	//Carga los gr�ficos usando el color suministrado
	cargarGraficos(color);

	//Asigna la posici�n por defecto
	establecerPosicion({ 0.0f, 0.0f });

}

//Carga la textura y se la aplica al sprites, adem�s de modificar los atributos del mismo
void Enemigo::cargarGraficos(int color) {

	textura = new Texture;

	textura->loadFromFile(direccion_texturas[color]);

	//Fija la textura al sprite
	sprite.setTexture(*textura);

	//Variable que contiene el tama�o del sprite en ambos ejes
	Vector2f dimensiones_sprite = { retornarDimensionesSprite().x, retornarDimensionesSprite().y};

	//Posiciona el sprite en la ventana y cambia su origen al centro de la imagen
	sprite.setPosition(posicion);
	sprite.setOrigin(dimensiones_sprite.x / 2, dimensiones_sprite.y / 2);

}

//Env�a la directiva de dibujar el sprite a la ventana pasada por par�metro
void Enemigo::renderizar(RenderWindow* ventana) {

	ventana->draw(sprite);

}

//Devuelve el sprite del enemigo
Sprite Enemigo::retornarSprite() {

	return sprite;

}

//Devuelve la caja de colisi�n del enemigo
FloatRect Enemigo::retornarColisionador() {

	return sprite.getGlobalBounds();

}

//M�todo que permite "activar" un enemigo, haciendo que comience a moverse usando el bool adicional para la direcci�n
void Enemigo::cambiarMovimiento(bool estado, bool direccion) {

	//Activa/Desactiva el movimiento
	en_movimiento = estado;

	//Asigna la direcci�n de movimiento:
	// True = derecha
	// False = izquierda
	direccion_movimiento = direccion;

}

//Devuelve el tama�o total del sprite. NOTA: Funci�n de prueba. No se ha usado
Vector2f Enemigo::retornarDimensionesSprite() {

	return {retornarColisionador().height, retornarColisionador().width};

}

//Fija la posicion del enemigo, dependiendo el vector suministrado
void Enemigo::establecerPosicion(Vector2f ubicacion) {

	//Fija la posici�n del sprite usando la ubicacion recibida
	posicion = { ubicacion.x, ubicacion.y };

	//Actualiza la posici�n del sprite
	sprite.setPosition(ubicacion.x, ubicacion.y);

}

//M�todo que mueve al enemigo siempre y cuando este pueda moverse
void Enemigo::actualizar(Jugador& jugador, Vector2f dimensiones_ventana) {

	//Variable del movimiento horizontal
	float movimiento = 0.0f;

	//Si el enemigo est� en movimiento
	if (en_movimiento) {

		//Si debe moverse a la derecha
		if (direccion_movimiento) {

			//Valor asignado
			movimiento = 5.0f;

		}
		//Si se debe mover a la izquierda
		else {

			//Valor asignado
			movimiento = -5.0f;

		}

		//Ejerce el movimiento previamente determinado
		sprite.move(movimiento, 0.0f);

	}
	
	//Si el enemigo en cuesti�n colisiona con el jugador...
	if (hayColision(jugador)) {

		//El player regresa a su punto de aparici�n
		jugador.moverAlSpawn();

	}
	
}

bool Enemigo::hayColision(Jugador jugador) {

	//Variables para almacenar la caja de colisi�n de ambos sprites
	FloatRect colisionador_jugador = jugador.retornarColisionador();
	FloatRect colisionador_enemigo = retornarColisionador();

	if (colisionador_enemigo.intersects(colisionador_jugador)) {

		return true;
	}

	return false;

}

bool Enemigo::estaMoviendose() {

	return en_movimiento;

}

bool Enemigo::retornarDireccionMovimiento() {

	return direccion_movimiento;

}