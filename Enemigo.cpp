#include "Enemigo.h"

//Constructor A: No recibe parámetros, emplea valores por defecto en algunos casos
Enemigo::Enemigo() {

	//Los enemigos empiezan sin moverse
	en_movimiento = false;

	direccion_movimiento = true;

	coordenadas = { 0.0f, 0.0f };

	//Raiz del directorio de imagenes
	string raiz = "assets/images/";

	//Usa la raiz para determinar el directorio de cada textura
	direccion_texturas[0] = raiz + "tortuga_roja.png";
	direccion_texturas[1] = raiz + "tortuga_azul.png";
	direccion_texturas[2] = raiz + "tortuga_amarilla.png";
	direccion_texturas[3] = raiz + "tortuga_verde.png";

	//Carga los gráficos por defecto
	cargarGraficos(0);

	//Asigna la posición por defecto
	establecerPosicion(coordenadas);

}

//Constructor B: Recibe color como parámetro
Enemigo::Enemigo(int color, bool direccion, bool activo) {
	
	//Fija la dirección en la que se moverá el enemigo cuando tenga la directiva de hacerlo
	direccion = direccion_movimiento;

	//Los enemigos empiezan sin moverse
	en_movimiento = activo;

	coordenadas = { 0.0f, 0.0f };

	//Raiz del directorio de imagenes
	string raiz = "assets/images/";

	//Usa la raiz para determinar el directorio de cada textura
	direccion_texturas[0] = raiz + "tortuga_roja.png";
	direccion_texturas[1] = raiz + "tortuga_azul.png";
	direccion_texturas[2] = raiz + "tortuga_amarilla.png";
	direccion_texturas[3] = raiz + "tortuga_verde.png";

	//Carga los gráficos usando el color suministrado
	cargarGraficos(color);

	//Asigna la posición por defecto
	establecerPosicion(coordenadas);

}

//Carga la textura y se la aplica al sprites, además de modificar los atributos del mismo
void Enemigo::cargarGraficos(int color) {

	textura = new Texture;

	textura->loadFromFile(direccion_texturas[color]);

	//Fija la textura al sprite
	sprite.setTexture(*textura);

	//Variable que contiene el tamaño del sprite en ambos ejes
	Vector2f dimensiones_sprite = { retornarDimensionesSprite().x, retornarDimensionesSprite().y};

	//Posiciona el sprite en la ventana y cambia su origen al centro de la imagen
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

//Devuelve la caja de colisión del enemigo
FloatRect Enemigo::retornarColisionador() {

	return sprite.getGlobalBounds();

}

//Método que permite "activar" un enemigo, haciendo que comience a moverse usando el bool adicional para la dirección
void Enemigo::cambiarMovimiento(bool estado, bool direccion) {

	//Activa/Desactiva el movimiento
	en_movimiento = estado;

	//Asigna la dirección de movimiento:
	// True = derecha
	// False = izquierda
	direccion_movimiento = direccion;

}

//Devuelve el tamaño total del sprite. NOTA: Función de prueba. No se ha usado
Vector2f Enemigo::retornarDimensionesSprite() {

	return {retornarColisionador().height, retornarColisionador().width};

}

//Fija la posicion del enemigo, dependiendo el vector suministrado
void Enemigo::establecerPosicion(Vector2f ubicacion) {

	//Fija la posición del sprite usando la ubicacion recibida
	coordenadas = ubicacion;

	//Actualiza la posición del sprite
	sprite.setPosition(ubicacion.x, ubicacion.y);

}

//Mueve el sprite por el desplazamiento pasado por parámetro
void Enemigo::mover(Vector2f desplazamiento) {

	coordenadas += desplazamiento;

	establecerPosicion(coordenadas);

}

//Método que mueve al enemigo siempre y cuando este pueda moverse
void Enemigo::actualizar(Jugador& jugador, Vector2f dimensiones_ventana) {

	//Variable del movimiento horizontal
	float movimiento = 0.0f;

	//Si el enemigo está en movimiento
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

		coordenadas.x += movimiento;

		//Ejerce el movimiento previamente determinado
		establecerPosicion(coordenadas);

	}
	
	//Si el enemigo en cuestión colisiona con el jugador...
	if (hayColision(jugador)) {

		//El player regresa a su punto de aparición
		jugador.moverAlSpawn();

	}
	
}

//Revisa si el sprite del enemigo ha colisionado con el jugador pasado por parámetro
bool Enemigo::hayColision(Jugador jugador) {

	//Variables para almacenar la caja de colisión de ambos sprites
	FloatRect colisionador_jugador = jugador.retornarColisionador();
	FloatRect colisionador_enemigo = retornarColisionador();

	//Si hay colisión
	if (colisionador_enemigo.intersects(colisionador_jugador)) {

		//Retorna verdadero
		return true;
	}

	//Retorna falso, que significa que no hubo colisiones
	return false;

}

//Método para revisar si el enemigo está en movimiento o no
bool Enemigo::estaMoviendose() {

	return en_movimiento;

}

//Devuelve la dirección del movimiento (true = derecha, false = izquierda)
bool Enemigo::retornarDireccionMovimiento() {

	return direccion_movimiento;

}

//Devuelve la posición del enemigo
Vector2f Enemigo::retornarPosicion() {

	return coordenadas;

}