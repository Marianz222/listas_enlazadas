#include "Juego.h"

//Constructor de la clase
Juego::Juego() {

	//Inicializa las variables básicas: juego terminado, fps y altura requerida
	juego_terminado = false;
	fps = 60;
	requerimiento_altura = 50;

	//Crea la ventana y establece los frames por segundo de la misma
	ventana = new RenderWindow(VideoMode(int(VENTANA_X), int(VENTANA_Y)), NOMBRE_VENTANA);
	ventana->setFramerateLimit(fps);

	//Fija el tiempo inicial del juego
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

	//Crea la puerta y envia un registro a consola
	salida = new Puerta({ VENTANA_X / 2, 35.0f });
	registrarEnConsola("[INFO/DEBUG]: Puerta creada y posicionada", true);

	//Crea una nueva instancia del gestor de eventos
	gestor_eventos = new Event;

	//Llama a la configuracion de las listas
	configurarListas();

	//Variable para determinar si los sonidos se reproducen o no
	silenciar_juego = false;

}

//Método de bucle. Aca se ejecuta toda la lógica del programa
void Juego::bucleJuego() {

	//Variables de control de tiempo
	Clock reloj;
	float tiempo_delta;

	static int extracciones_pilas = 0;

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

		//Actualiza las listas
		actualizarColas();

		//Actualiza las pilas
		actualizarPilas();

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

					//Si el juego no está silenciado...
					if (!silenciar_juego) {

						//Reproduce el sonido: Salto
						sonidos[0].play();

					}

				}

				//Informa por consola que se presionó la tecla
				registrarEnConsola("[INFO/DEBUG]: Tecla Presionada: Espacio", true);

				break;

			case Keyboard::F2: //Tecla Presionada: F2

				//Intercambia entre con sonido y sin sonido
				silenciar_juego = !silenciar_juego;

				if (silenciar_juego) {

					//Informa por consola que se presionó la tecla
					registrarEnConsola("[INFO/NORMAL]: Sonido desactivado", true);

				}
				else {

					//Informa por consola que se presionó la tecla
					registrarEnConsola("[INFO/NORMAL]: Sonido activado", true);

				}

				//Informa por consola que se presionó la tecla
				registrarEnConsola("[INFO/DEBUG]: Tecla Presionada: F2", true);

			}

			break;

		}

	}

	//Mueve el personaje en el eje y
	jugador->mover(0.0f, movimiento_y);

	//Actualiza la posicion del sprite en jugador
	jugador->actualizarPosicion();

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
	if (Keyboard::isKeyPressed(Keyboard::D) && jugador->retornarPosicion().x <= VENTANA_X - 30) {

		movimiento_x = 5.0f;

	}

	//Revisa que no se esté intentando mover por fuera de la ventana
	if (Keyboard::isKeyPressed(Keyboard::A) && jugador->retornarPosicion().x >= 30) {

		movimiento_x = -5.0f;

	}

	//Mueve el personaje en el eje x
	jugador->mover(movimiento_x, 0.0f);

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

			//Si el juego tiene sonido activado...
			if (!silenciar_juego) {

				//Reproduce el sonido: Perder
				sonidos[2].play();

			}

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

			//Si el sonido está activado...
			if (!silenciar_juego) {

				//Reproduce el sonido: Ganar
				sonidos[1].play();

			}

		}

	}

}

//Método encargado de revisar si el tiempo ha terminado, en cuyo caso detendrá otros procesos del juego
void Juego::chequearDerrota() {

	//Revisa si el tiempo es 0
	if (tiempo_inicial == 0) {

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

	if (silenciar_juego) {

		return;

	}

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
	// -> Piso 6: Pila
	//Las pilas y colas se cuentan desde el piso más bajo hasta el más alto, lo cual significa que "colas_enemigos[2]" corresponde al piso 5,
	//y "pilas_enemigos[3]" corresponde al piso 4 - pila derecha
	//Cada piso que contenga pilas tendrá pila izquierda y pila derecha, en ese orden

	//Se recorre el arreglo de enemigos retirados...
	for (int i = 0; i < 3; i++) {

		//Se le asigna NULL a cada enemigo retirado, por defecto todos comienzan siendo nulos
		enemigos_retirados_cola[i] = nullptr;
		enemigos_retirados_pila[i] = nullptr;

	}

	//Variables para usar de iterador a la hora de recorrer los ciclos for
	const int CANTIDAD_LISTAS = 3;

	//Fija el origen derecho e izquierdo para el posicionamiento de los enemigos
	float origen_izquierda = 15.0f;
	float origen_derecha = VENTANA_X - 20.0f;

	//El offset es la anchura del sprite enemigo
	float offset_x = 30.0f;

	//Bucle de configuracion de COLAS
	for (int i = 0; i < CANTIDAD_LISTAS; i++) {

		//Se crean los enemigos, uno con cada color disponible
		Enemigo tortuga_roja(0, true, false);
		Enemigo tortuga_azul(1, true, false);
		Enemigo tortuga_amarilla(2, true, false);
		Enemigo tortuga_verde(3, true, false);

		//Se añaden los 4 enemigos como nodos a las 3 colas
		colas_enemigos[i].insertar(tortuga_roja, { origen_izquierda + (offset_x * 3), altura_colas[i] });
		colas_enemigos[i].insertar(tortuga_azul, { origen_izquierda + (offset_x * 2), altura_colas[i] });
		colas_enemigos[i].insertar(tortuga_amarilla, { origen_izquierda + (offset_x), altura_colas[i] });
		colas_enemigos[i].insertar(tortuga_verde, { origen_izquierda, altura_colas[i] });

	}

	////////////////////////////////////////////////////////////////////////////////////////////////

	//Bucle de configuracion de PILAS llenas, las vacías no se configuran ya que solo recibirán elementos nuevos
	for (int i = 0; i < CANTIDAD_LISTAS; i++) {

		//Se crean los enemigos
		Enemigo tortuga_verde(0, true, false);
		Enemigo tortuga_amarilla(1, true, false);
		Enemigo tortuga_azul(2, true, false);
		Enemigo tortuga_roja(3, true, false);

		//Se añaden los 4 enemigos como nodos a las 3 pilas derechas (las izquierdas se instancian vacías para recibir elementos luego)
		pilas_enemigos_derecha[i].insertar(tortuga_verde, {origen_derecha, altura_pilas[i]});
		pilas_enemigos_derecha[i].insertar(tortuga_amarilla, { origen_derecha - (offset_x), altura_pilas[i] });
		pilas_enemigos_derecha[i].insertar(tortuga_azul, { origen_derecha - (offset_x * 2), altura_pilas[i] });
		pilas_enemigos_derecha[i].insertar(tortuga_roja, { origen_derecha - (offset_x * 3), altura_pilas[i] });

	}

}

//Método que actualiza las colas para retirar un elemento y reinsertarlo en la misma pila tras completar su viaje
void Juego::actualizarColas() {

	//Si el juego ya terminó, no se actualizarán las listas
	if (juego_terminado) {

		return;

	}

	//Almacena el tamaño de la ventana
	Vector2f dimensiones_ventana = { VENTANA_X, VENTANA_Y };

	//Recorre el arreglo de las 3 colas, iterando a su vez en el arreglo de elementos retirados que corresponde a las colas
	for (int i = 0; i < 3; i++) {

		//Si no hay ningún enemigo retirado...
		if (enemigos_retirados_cola[i] == nullptr) {

			//Se retira el primer enemigo de la cola
			enemigos_retirados_cola[i] = colas_enemigos[i].retirar();

			//Registra en consola cuando una de las colas ejecuta una extracción
			//registrarEnConsola("[INFO/DEBUG]: Evento - Extraccion en cola", true);

		}
		//Si en cambio hay un enemigo ya retirado...
		else {

			//Se activa el movimiento del enemigo retirado
			enemigos_retirados_cola[i]->cambiarMovimiento(true, true);
			enemigos_retirados_cola[i]->actualizar(*jugador, dimensiones_ventana);

			//Revisa si el enemigo en desplazamiento ha alcanzado su objetivo (salir de la ventana)...
			if (enemigos_retirados_cola[i]->retornarPosicion().x > dimensiones_ventana.x + 30) {

				//Mueve los enemigos restantes todos un espacio a la derecha, para dar lugar a la re-inserción del primer enemigo
				colas_enemigos[i].desplazarEnemigos();

				//Re-inserta el enemigo retirado, quedando así al final de la cola. Para esto se usan las coordenadas de origen + la altura de
				//la plataforma donde se reinsertará. Tras esto el enemigo retirado se convierte en nulo
				enemigos_retirados_cola[i]->cambiarMovimiento(false, true);
				colas_enemigos[i].insertar(*enemigos_retirados_cola[i], { 15.0f, altura_colas[i] });
				enemigos_retirados_cola[i] = nullptr;

				//Registra en consola cuando una de las colas ejecuta una re-inserción
				//registrarEnConsola("[INFO/DEBUG]: Evento - Insercion en cola", true);

			}

		}

		//Recorre todas las colas de enemigos, llamando al método actualizar el cual recorrerá las listas usando un while para llamar a "actualizar"
		//dentro del enemigo en cada uno de los nodos
		colas_enemigos[i].actualizarElementos(*jugador, dimensiones_ventana);

	}

}

//Método que actualiza las colas, haciendo que todos los elementos abandonen uno a uno la pila A
//para luego desde la B repetir el proceso a la inversa
void Juego::actualizarPilas() {

	//Si el juego ya terminó, no se actualizarán las listas
	if (juego_terminado) {

		return;

	}

	//Constante de la cantidad de pilas llenas
	const int CANTIDAD_PILAS = 3;

	//Variables estáticas para controlar el offset de posición, el contador de enemigos extraídos y la dirección de extracción
	static float offset[3] = { 0.0f, 0.0f, 0.0f };
	static int contador = 0;
	static bool direccion_actual = false;

	//Almacena el tamaño de la ventana
	Vector2f dimensiones_ventana = { VENTANA_X, VENTANA_Y };

	//Si la dirección es izquierda...
	if (!direccion_actual) {

		//Recorre el arreglo de las 3 pilas derechas, iterando a su vez en el arreglo de elementos retirados
		for (int i = 0; i < 3; i++) {

			//Si no hay ningún enemigo retirado...
			if (enemigos_retirados_pila[i] == nullptr) {

				//Se retira el primer enemigo de la pila
				enemigos_retirados_pila[i] = pilas_enemigos_derecha[i].retirar();

				//Registra en consola cuando una de las colas ejecuta una extracción
				//registrarEnConsola("[INFO/DEBUG]: Evento - Extraccion en pila derecha", true);

			}
			//Si en cambio hay un enemigo ya retirado...
			else {

				//Se activa el movimiento del enemigo retirado
				enemigos_retirados_pila[i]->cambiarMovimiento(true, false);
				enemigos_retirados_pila[i]->actualizar(*jugador, dimensiones_ventana);

				//Revisa si el enemigo en desplazamiento ha alcanzado su objetivo (tocar el borde o colisionar con otro enemigo)
				if (enemigos_retirados_pila[i]->retornarPosicion().x == 0 + offset[i]) {

					//Inserta el enemigo retirado de la pila A a la pila B
					enemigos_retirados_pila[i]->cambiarMovimiento(false, false);

					//El enemigo extraído se inserta en la pila izquierda correspondiente, tomando como referencia el inicio de ventana + el offset
					pilas_enemigos_izquierda[i].insertar(*enemigos_retirados_pila[i], { 15.0f + offset[i], altura_pilas[i]});

					//Añade el tamaño de las tortugas (30) al offset
					offset[i] += 30.0f;

					//Incrementa el contador de extracciones en 1
					contador++;

					//El enemigo reitrado pasa a ser nulo
					enemigos_retirados_pila[i] = nullptr;

					//Registra en consola cuando una de las colas ejecuta una re-inserción
					//registrarEnConsola("[INFO/DEBUG]: Evento - Insercion en pila izquierda", true);

				}

			}

			//Recorre todas las colas de enemigos, llamando al método actualizar el cual recorrerá las listas usando un while para llamar a "actualizar"
			//dentro del enemigo en cada uno de los nodos
			pilas_enemigos_derecha[i].actualizarElementos(*jugador, dimensiones_ventana);

		}

	} //Sino si la dirección es derecha...
	else if (direccion_actual) {

		//Recorre el arreglo de las 3 pilas derechas, iterando a su vez en el arreglo de elementos retirados
		for (int i = 0; i < 3; i++) {

			//Si no hay ningún enemigo retirado...
			if (enemigos_retirados_pila[i] == nullptr) {

				//Se retira el primer enemigo de la pila
				enemigos_retirados_pila[i] = pilas_enemigos_izquierda[i].retirar();

				//Registra en consola cuando una de las colas ejecuta una extracción
				//registrarEnConsola("[INFO/DEBUG]: Evento - Extraccion en pila izquierda", true);

			}
			//Si en cambio hay un enemigo ya retirado...
			else {

				//Se activa el movimiento del enemigo retirado
				enemigos_retirados_pila[i]->cambiarMovimiento(true, true);
				enemigos_retirados_pila[i]->actualizar(*jugador, dimensiones_ventana);

				//Revisa si el enemigo en desplazamiento ha alcanzado su objetivo (tocar el borde o colisionar con otro enemigo)
				if (enemigos_retirados_pila[i]->retornarPosicion().x == dimensiones_ventana.x - 15.0f - offset[i]) {

					//Detiene el movimiento del enemigo
					enemigos_retirados_pila[i]->cambiarMovimiento(false, true);

					//El enemigo extraído se inserta en la correspondiente pila derecha, usando como referencia el tamaño de la ventana menos el offset
				    pilas_enemigos_derecha[i].insertar(*enemigos_retirados_pila[i], { dimensiones_ventana.x - 15.0f - offset[i], altura_pilas[i]});

					//Añade el tamaño de los enemigos (30) al offset
					offset[i] += 30.0f;

					//Incrementa el contador de extracciones en 1
					contador++;

					//El enemigo reitrado pasa a ser nulo
					enemigos_retirados_pila[i] = nullptr;

					//Registra en consola cuando una de las colas ejecuta una re-inserción
					//registrarEnConsola("[INFO/DEBUG]: Evento - Insercion en pila derecha", true);

				}

			}

			//Recorre todas las colas de enemigos, llamando al método actualizar el cual recorrerá las listas usando un while para llamar a "actualizar"
			//dentro del enemigo en cada uno de los nodos
			pilas_enemigos_izquierda[i].actualizarElementos(*jugador, dimensiones_ventana);

		}

	}

	//Si el contador es igual a X. Esto se calcula usando la cantidad de enemigos a extraer por pila (4 en este caso)
	//y multiplicandolo por la cantidad de pilas totales, ya que el contador es uno solo al hacer un ingreso entran 3 enemigos y no uno solo
	//Esto da como resultado 12, número el cual se obtiene si todas las pilas enviaron sus 4 elementos
	if (contador == 4 * CANTIDAD_PILAS) {

		//Intercambia la dirección
		direccion_actual = !direccion_actual;

		//Reinicia el contador
		contador = 0;

		//Itera sobre el arreglo de offsets de posicion para reiniciarlos
		for (int i = 0; i < 3; i++) {

			offset[i] = 0.0f;

		}

	}


}

//Método que se encarga de dibujar todos los elementos gráficos en la pantalla, llamando a clear -> draw -> display
void Juego::renderizar() {

	//Limpia la pantalla eliminando todo lo dibujado previamente
	ventana->clear();

	//Dibuja el fondo
	ventana->draw(sprite_fondo);

	//Dibuja la puerta
	salida->renderizar(ventana);
	
	//Bucle para dibujar todas las listas enlazadas
	for (int i = 0; i < 3; i++) {

		//Obtiene y carga todos los elementos de cada cola, para ser dibujados
		colas_enemigos[i].renderizarElementos(ventana);

	}

	for (int i = 0; i < 3; i++) {

		pilas_enemigos_izquierda[i].renderizarElementos(ventana);

		pilas_enemigos_derecha[i].renderizarElementos(ventana);

	}

	//Bucle para dibujar todos los enemigos temporales
	for (int i = 0; i < 3; i++) {

		//Si hay algun enemigo retirado de las colas
		if (enemigos_retirados_cola[i] != NULL) {

			//Da la directiva para que sea dibujado
			enemigos_retirados_cola[i]->renderizar(ventana);

		}

		//Si hay algun enemigo retirado de las pilas
		if (enemigos_retirados_pila[i] != NULL) {

			//Da la directiva para que sea dibujado
			enemigos_retirados_pila[i]->renderizar(ventana);

		}

	}

	//Dibuja el jugador
	jugador->renderizar(ventana);

	//Dibuja el texto del reloj
	ventana->draw(cronometro_texto);

	//Muestra todo el contenido cargado a la pantalla
	ventana->display();

}