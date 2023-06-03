#include "Juego.h"

//Constructor de la clase
Juego::Juego() {

	juego_terminado = false;
	fps = 60;
	requerimiento_altura = 50;

	ventana = new RenderWindow(VideoMode(int(VENTANA_X), int(VENTANA_Y)), NOMBRE_VENTANA);
	ventana->setFramerateLimit(fps);

	tiempo_inicial = 30;

	//Crea un origen base para encontrar todos los sonidos en la carga
	string raiz_sonidos = "assets/sounds/";

	//Se asigna la dirección completa (raiz + nombre.formato) de cada sonido al arreglo
	direccion_sonidos[0] = raiz_sonidos + "saltar.wav";
	direccion_sonidos[1] = raiz_sonidos + "ganar.wav";
	direccion_sonidos[2] = raiz_sonidos + "perder.wav";
	direccion_sonidos[3] = raiz_sonidos + "golpe.wav";
	direccion_sonidos[4] = raiz_sonidos + "tick.wav";

	//Carga las imagenes y sonidos para usarse
	cargarGraficos("assets/images/fondo.png");
	cargarSonidos();
	crearTexto();

	//Registra por consola que los procesos anteriores terminaron
	registrarEnConsola("[INFO/DEBUG]: Procesos de carga de activos completados", true);

	//Crea el jugador y envia un registro a consola
	jugador = new Jugador({ VENTANA_X / 2, VENTANA_Y - 100 });
	registrarEnConsola("[INFO/DEBUG]: Jugador creado y posicionado", true);

	cout << jugador->retornarPosicion().y << endl;

	//Crea la puerta y envia un registro a consola
	salida = new Puerta({ VENTANA_X / 2, 35.0f });
	registrarEnConsola("[INFO/DEBUG]: Puerta creada y posicionada", true);

	gestor_eventos = new Event;

	configurarListas();

}

//Método de bucle. Aca se ejecuta toda la lógica del programa
void Juego::bucleJuego() {

	//Variables de control de tiempo
	Clock reloj;
	float tiempo_delta;

	while (ventana->isOpen()) {

		//Tiempo transcurrido
		tiempo_delta = reloj.restart().asSeconds();

		//Refresca el valor del cronometro
		actualizarCronometro();

		//Llama a revisión de teclado
		controlarTeclado(tiempo_delta);

		//Recibe los eventos
		gestionarEventos();

		//Revisa por las colisiones
		chequearColisionesExtras();

		//Actualiza el texto
		actualizarTexto(actualizarCronometro());

		//Hace sonar el tic tac del reloj
		reproducirSonidoReloj();

		//Muestra el contenido en pantalla
		renderizar();

	}

}

//Método encargado de cargar los gráficos para el fondo del nivel
void Juego::cargarGraficos(string direccion) {

	//Carga la textura y sprite para el fondo del juego
	textura_fondo.loadFromFile(direccion);
	sprite_fondo.setTexture(textura_fondo);

	registrarEnConsola("[INFO/DEBUG]: Graficos del fondo cargados", true);

}

//Método encargado de cargar los sonidos que usará el juego
void Juego::cargarSonidos() {

	//Se itera sobre los buffers y sonidos para fijar sus propiedades
	for (int i = 0; i < SONIDOS_TOTALES; i++) {

		buffers[i].loadFromFile(direccion_sonidos[i]);
		sonidos[i].setBuffer(buffers[i]);

	}

	//Informa por consola que el juego terminó en victoria
	registrarEnConsola("[INFO/DEBUG]: Sonidos cargados", true);

}

//Recibe los eventos de la ventana y los procesa dependiendo el tipo
void Juego::gestionarEventos() {

	//Variables locales
	Sprite sprite = jugador->retornarSprite();
	float movimiento_y = 0.0f;

	while (ventana->pollEvent(*gestor_eventos)) {

		switch (gestor_eventos->type) {

		case Event::Closed:

			ventana->close();

			break;

		case Event::KeyPressed:

			switch (gestor_eventos->key.code) {

			case Keyboard::Escape: //Tecla Presionada: ESC

				ventana->close();

				//Informa por consola que se presionó la tecla
				registrarEnConsola("[INFO/DEBUG]: Tecla Presionada: Escape", true);

				//Informa que se cerró la ventana
				registrarEnConsola("[INFO/NORMAL]: Ventana cerrada", true);

				break;

			case Keyboard::Space: //Tecla Presionada: ESPACIO

				//Si el jugador ya superó el limite de altura, significa que no podrá saltar más
				if (jugador->retornarPosicion().y > requerimiento_altura) {

					//El jugador sube
					movimiento_y = -75.0f;

					//Reproduce el sonido: Salto
					sonidos[0].play();

					cout << jugador->retornarPosicion().y << endl;

				}

				//Informa por consola que se presionó la tecla
				registrarEnConsola("[INFO/DEBUG]: Tecla Presionada: Espacio", true);

				break;

			}

			break;

		}

	}

	//Mueve el personaje en el eje y
	jugador->mover(0.0f, movimiento_y);

}

//Gestiona el evento de teclas de forma separada para permitir teclas simultáneas
void Juego::controlarTeclado(float tiempo_delta) {

	//Instantáneamente regresa la llamada a la función si el juego ya terminó, para prevenir el movimiento
	if (juego_terminado) {

		return;

	}

	//Variables locales
	Sprite sprite = jugador->retornarSprite();
	float movimiento_x = 0.0f;

	//Revisa que no se esté intentando mover por fuera de la ventana
	if (Keyboard::isKeyPressed(Keyboard::D) && jugador->retornarPosicion().x <= VENTANA_X + 105) {

		movimiento_x = 5.0f;

	}

	//Revisa que no se esté intentando mover por fuera de la ventana
	if (Keyboard::isKeyPressed(Keyboard::A) && jugador->retornarPosicion().x >= 0) {

		movimiento_x = -5.0f;

	}

	//Mueve el personaje en el eje x
	jugador->mover(movimiento_x, 0.0f);

	//Tras modificarse, actualiza la posición del sprite usando la propia posición del jugador
	jugador->actualizarPosicion();

}

//Actualiza el valor del cronometro del juego
int Juego::actualizarCronometro() {

	//Reinicia el reloj, obteniendo el tiempo como segundos en el proceso
	float tiempo_transcurrido = reloj_principal.restart().asSeconds();

	//Decrementa el tiempo transcurrido (1) al tiempo inicial
	tiempo_inicial -= tiempo_transcurrido;

	//Guarda el tiempo transcurrido
	int segundos = ((int)(tiempo_inicial));

	//Devuelve los segundos
	return segundos;

}

//Encargado de cambiar el color y otros atributos del texto
//Cambia el texto del cronometro, usando el valor pasado por parámetro. En este caso, los segundos
void Juego::actualizarTexto(int segundos) {

	//Si aún no termina el juego
	if (!juego_terminado) {

		if (segundos >= 0) {

			//Convierte int a string para el texto
			string tiempo_texto = to_string(segundos);

			//Asigna el string con el valor del tiempo
			cronometro_texto.setString("Tiempo: " + tiempo_texto);

		}
		else {

			//Cambia el string por un mensaje diferente si el tiempo es 0
			cronometro_texto.setString("¡Terminó el tiempo!");

			//Finaliza el juego cambiando el bool
			juego_terminado = true;

			//Informa por consola que se acabo el tiempo
			registrarEnConsola("[INFO/NORMAL]: Termino el tiempo. Perdiste!", true);

			//Reproduce el sonido: Perder
			sonidos[2].play();

		}

		//Esta sección maneja los cambios de color del cronometro dependiendo el tiempo transcurrido
		if (segundos >= 20) {

			cronometro_texto.setFillColor(Color::Green);

		}
		else if (segundos < 20 && segundos >= 10) {

			cronometro_texto.setFillColor(Color::Yellow);

		}
		else if (segundos < 10 && segundos >= 5) {

			cronometro_texto.setFillColor(Color::Red);

		}
		else {

			cronometro_texto.setFillColor(Color::Black);

		}

	}
	else if (juego_terminado && segundos > 0) {

		cronometro_texto.setString("Ganaste!");
		cronometro_texto.setFillColor(Color::Green);

	}

}

//Pequeño método encargado de darle las propiedades al texto del cronometro
void Juego::crearTexto() {

	//Se carga la fuente strasua
	arial.loadFromFile("assets/fonts/arial.ttf");

	//Se configura el texto del cronometro con fuente, tamaño, origen, posición, etc...
	cronometro_texto.setFont(arial);
	cronometro_texto.setPosition(8.0f, 0.0f);
	cronometro_texto.setOrigin(cronometro_texto.getGlobalBounds().width / 2, cronometro_texto.getGlobalBounds().height / 2);

	//Aplica un string por defecto (no / disponible)
	cronometro_texto.setString("N/A");

	//Cambia el grosor y color de la línea externa del texto
	cronometro_texto.setOutlineThickness(1.0f);
	cronometro_texto.setOutlineColor(Color::White);

}

//Método que revisa si el jugador colisionó con la puerta o los enemigos
void Juego::chequearColisionesExtras() {

	//Bandera estática que controla la salida en consola
	static bool mensaje_registrado = false;

	//Almacena ambas cajas de colisión en variables para el fácil manejo de las mismas
	FloatRect colisionador_jugador = jugador->retornarColisionador();
	FloatRect colisionador_puerta = salida->retornarColisionador();

	//Revisa si el jugador ha colisionado con la puerta, de ser así termina el juego
	if (colisionador_jugador.intersects(colisionador_puerta)) {

		//El jugador ganó
		juego_terminado = true;

		//Revisa que el mensaje no se haya enviado todavía
		if (!mensaje_registrado) {

			//Informa por consola que el juego terminó en victoria
			registrarEnConsola("[INFO/NORMAL]: Termino la partida. Ganaste!", true);

			//Cambia el bool para evitar llenar la consola con el mensaje
			mensaje_registrado = true;

			//Reproduce el sonido: Ganar
			sonidos[1].play();

		}

	}

}

//Método encargado de revisar si el tiempo ha terminado, en cuyo caso detendrá otros procesos del juego
void Juego::chequearDerrota() {

	//Revisa si el tiempo es 0
	if (tiempo_inicial = 0) {

		//Cambia la bandera a false
		juego_terminado = true;

		//Informa por consola que el juego terminó en derrota
		registrarEnConsola("[INFO/NORMAL]: Se termino el tiempo. ¡Perdiste!", true);

	}

}

//Método encargado de crear y mandar un mensaje a consola con el string pasado por parámetro. El bool recibido controla si termina o no la linea
void Juego::registrarEnConsola(string mensaje, bool terminar_linea) {

	//Si termina la línea, se utiliza "endl"
	if (terminar_linea) {

		cout << mensaje << endl;

	}
	else { //Sino se envía el mensaje sin corte de línea

		cout << mensaje;

	}

}

//Método que toma el tiempo transcurrido para así reproducir el sonido de tic tac de reloj. El intervalo se mide en segundos
void Juego::reproducirSonidoReloj() {

	//Creamos variables estáticas para conservar sus valores en cada llamada a la función
	static Clock reloj;
	static float intervalo = 1.0f;

	//Si el tiempo es mayor a el intervalo (1 seg.) y el juego aún no termina...
	if (reloj.getElapsedTime().asSeconds() >= intervalo && !juego_terminado) {

		//Reproduce el sonido: Tick
		sonidos[4].play();

		//Reinicia el reloj
		reloj.restart();

	}

}

//Método que añade los nodos correspondientes a cada lista
void Juego::configurarListas() {

	//La estructura seleccionada para distribuir las listas fue la siguiente:
	// -> Suelo: Vacío
	// -> Piso 1: Cola
	// -> Piso 2: Pila
	// -> Piso 3: Cola
	// -> Piso 4: Pila
	// -> Piso 5: Cola
	// -> Piso 6: Vacío
	//Las pilas y colas se cuentan desde el piso más bajo hasta el más alto, lo cual significa que "colas_enemigos[2]" corresponde al piso 5,
	//y "pilas_enemigos[3]" corresponde al piso 4 - pila derecha
	//Cada piso que contenga pilas tendrá pila izquierda y pila derecha, en ese orden

	//Fija el origen derecho al inicio de la pantalla
	float origen_derecha = 0.0f;

	//Fija el origen izquierdo a la anchura de la pantalla, restando el tamaño del sprite multiplicado por la cantidad de enemigos que tiene la lista
	float origen_izquierda = VENTANA_X - (25.0f * 4);

	//El offset es la anchura del sprite enemigo
	float offset_x = 30.0f;

	//Se crean los enemigos, uno con cada color disponible
	Enemigo tortuga_roja("rojo");
	Enemigo tortuga_azul("azul");
	Enemigo tortuga_amarilla("amarillo");
	Enemigo tortuga_verde("verde");

	tortuga_roja.establecerPosicion({ origen_derecha, 425.0f });
	tortuga_azul.establecerPosicion({ origen_derecha + (offset_x), 425.0f});
	tortuga_amarilla.establecerPosicion({ origen_derecha + (offset_x * 2), 425.0f });
	tortuga_verde.establecerPosicion({ origen_derecha + (offset_x * 3), 425.0f });

	//Se añaden los 4 enemigos como nodos a la cola #1
	colas_enemigos[0].insertar(tortuga_roja);
	colas_enemigos[0].insertar(tortuga_azul);
	colas_enemigos[0].insertar(tortuga_amarilla);
	colas_enemigos[0].insertar(tortuga_verde);
	
}

void Juego::renderizarListasEnemigos() {

	colas_enemigos[0].renderizarElementos(ventana);

}

void Juego::renderizar() {

	//Limpia la pantalla eliminando todo lo dibujado previamente
	ventana->clear();
	
	//Dibuja el fondo
	ventana->draw(sprite_fondo);
	
	//Dibuja la puerta
	salida->renderizar(ventana);

	renderizarListasEnemigos();

	//Dibuja el jugador
	jugador->renderizar(ventana);

	//Dibuja el texto del reloj
	ventana->draw(cronometro_texto);

	//Muestra todo el contenido cargado a la pantalla
	ventana->display();

}