#include "GameScene.h"


Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene

    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{	Size visibleSize = Director::getInstance()->getVisibleSize();
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto playItem = MenuItemImage::create("Play_Button.png", "Play_Button(Click).png", CC_CALLBACK_1(GameScene::CambiarTurnoUsuario, this));
 
	botonFinTurno = Menu::create(playItem, NULL);
	botonFinTurno->setPosition(950, visibleSize.height-600);

	InicioJuego();

	enPartida = false;
	tiempopartida = 0;
	pasado = false;

	auto eventoRaton = EventListenerMouse::create();
	eventoRaton->onMouseDown = CC_CALLBACK_1(GameScene::ClickRaton, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventoRaton, this);

	this->scheduleUpdate();
	posRaton[0] = 0;
	posRaton[1] = 1;
	posAntiguaRaton[0] = posRaton[0];
	posAntiguaRaton[1] = posRaton[1];
	idProvinciaSeleccionada = 0;
	idAntiguaSeleccionada = idProvinciaSeleccionada;

	__String *text;
	auto Afirmativo = MenuItemImage::create("Play_Button.png", "Play_Button(Click).png", CC_CALLBACK_1(GameScene::EmpezarPartida, this));
	auto Negativo = MenuItemImage::create("Play_Button.png", "Play_Button(Click).png", CC_CALLBACK_1(GameScene::VolverAEscoger, this));
	Menu* botonEscogerMapa = Menu::create(Afirmativo, Negativo, NULL);
	botonEscogerMapa->setPosition(950, visibleSize.height-600);
	botonEscogerMapa->alignItemsHorizontallyWithPadding(100);
	addChild(botonEscogerMapa);

	text = __String::createWithFormat("¿Deseas coger este mapa?");
	LabelTTF* EscogerMapa = LabelTTF::create(text->getCString(), "Arial", 20);	EscogerMapa->setPosition(Vec2(950, visibleSize.height-500));
	EscogerMapa->setColor(ccc3(255,255,255));
	addChild(EscogerMapa);

    return true;
}

void GameScene::goToMainMenu(Ref *pSender) {
	 enPartida = false;
	 auto scene = MainMenuScene::createScene();
	 Director::getInstance()->replaceScene(scene);
}


void GameScene::VolverAEscoger(Ref *pSender) {
	auto scene = GameScene::createScene();

	Director::getInstance()->replaceScene(scene);
}

void GameScene::EmpezarPartida(Ref *pSender) {
	enPartida = true;
	AsignarVisibilidadInicio();
	Redibujar();
}

void GameScene::AsignarVisibilidadInicio(){
	list<int>::iterator provincia;
	list<int>::iterator provinciaColindante;
	int idProvincia = 0;
	for (provincia = Jugadores[idJugadorUsuario]->propiedadProvincias.begin(); provincia != Jugadores[idJugadorUsuario]->propiedadProvincias.end(); provincia++){
		idProvincia = *provincia;
		miTablero->listaProvincias[idProvincia]->setVisible(true);
		for (provinciaColindante = miTablero->listaProvincias[idProvincia]->provinciasColindantes.begin(); provinciaColindante != miTablero->listaProvincias[idProvincia]->provinciasColindantes.end(); ++provinciaColindante){
			miTablero->listaProvincias[*provinciaColindante]->setVisible(true);
		}
	}
}

void GameScene::update(float dt){
	if (enPartida){
		Size visibleSize = Director::getInstance()->getVisibleSize();
		if (turnojugador == idJugadorUsuario){
			if (posAntiguaRaton[0] != posRaton[0] || posAntiguaRaton[1] != posRaton[1]){
				if (idProvinciaSeleccionada != 0){
					if (idAntiguaSeleccionada != 0){
						AtacarProvincia(idAntiguaSeleccionada, idProvinciaSeleccionada);
					}
				}
			}
		}
		else {
			if (tiempopartida > 1){
				AccionesIA();
				tiempopartida = 0;
			}
		}
		tiempopartida += dt;
	}
}

void GameScene::CambiarTurnoUsuario(Ref *pSender){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (turnojugador == idJugadorUsuario){
		tiempopartida = 0;
		CambiarTurnoJuego();
	}
}

void GameScene::CambiarTurnoJuego(){
	Jugadores[turnojugador]->CambiarTurno();
	AsignacionLegiones();
	turnojugador++;
	if (turnojugador == numJugadores){
		turnojugador = 0;
	}
	Jugadores[turnojugador]->CambiarTurno();

	Redibujar();
}

void GameScene::AccionesIA(){
	list<int>::iterator provincia;
	list<int>::iterator provinciaColindante;
	int idProvincia = 0;
	int legionesProvincia = 0;
	int idProvinciaAtacable = 0;
	for (provincia = Jugadores[turnojugador]->propiedadProvincias.begin(); provincia != Jugadores[turnojugador]->propiedadProvincias.end(); provincia++){
		idProvincia = *provincia;
		legionesProvincia = miTablero->listaProvincias[*provincia]->getLegiones();
		if(legionesProvincia>1){
			idProvinciaAtacable = 0;
			for (provinciaColindante = miTablero->listaProvincias[idProvincia]->provinciasColindantes.begin(); provinciaColindante != miTablero->listaProvincias[idProvincia]->provinciasColindantes.end(); ++provinciaColindante){
				idProvinciaAtacable = *provinciaColindante;
				if (miTablero->listaProvincias[idProvinciaAtacable]->getPerteneceIdJugador() != turnojugador){ 
					if (miTablero->listaProvincias[idProvincia]->getLegiones() >= miTablero->listaProvincias[idProvinciaAtacable]->getLegiones()){
						break;
					}
				}
				idProvinciaAtacable = 0;
			}
			if (idProvinciaAtacable != 0){
				AtacarProvincia(idProvincia, idProvinciaAtacable);
				return;
			}
		}
	}
	CambiarTurnoJuego();
	return;
}
void GameScene::AsignacionLegiones(){
	int cantidad = 0;
	int cantidadmaxima = Jugadores[turnojugador]->propiedadProvincias.size();
	int idProvinciaAsignacion = 0;
	int legionesProvincia = 0;
	bool llenas = false;
	list<int>::iterator posicion;
	while (cantidad <= cantidadmaxima && !llenas){
		llenas = true;
		for (posicion = Jugadores[turnojugador]->propiedadProvincias.begin(); posicion != Jugadores[turnojugador]->propiedadProvincias.end(); ++posicion){
			idProvinciaAsignacion = *posicion;
			legionesProvincia = miTablero->listaProvincias[idProvinciaAsignacion]->getLegiones();
			if (legionesProvincia < 5){
				llenas = false;
			}
			if (cantidad > cantidadmaxima){
				break;
			}
			if ((rand()%3)==0 && legionesProvincia < 5){
				miTablero->listaProvincias[idProvinciaAsignacion]->setLegiones(legionesProvincia+1);
				cantidad++;
			}
		}
	}
}

void GameScene::ReasignarProvinciasVisibles(){
	for (int i = 1; i<numeros-1; i++){
		miTablero->listaProvincias[i]->setVisible(false);
	}
	AsignarVisibilidadInicio();
}

void GameScene::AtacarProvincia(int idProvinciaOrigen, int idProvinciaDestino){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	idAntiguaSeleccionada = 0;
	idProvinciaSeleccionada = 0;
	int dañoataque = 0;
	int dañodefensa = 0;
	int jugadoratacante = miTablero->listaProvincias[idProvinciaOrigen]->getPerteneceIdJugador();
	int jugadordefensor = miTablero->listaProvincias[idProvinciaDestino]->getPerteneceIdJugador();
	int legionesrestantes;
	__String *text;

	if (!miTablero->listaProvincias[idProvinciaOrigen]->ProvinciaEnFrontera(idProvinciaDestino)){
		text = __String::createWithFormat("Provincia atacada no en Frontera.");
	}
	else if (miTablero->listaProvincias[idProvinciaOrigen]->getLegiones() == 1){
		text = __String::createWithFormat("Solo 1 Legión en la provincia.");
	}
	else if (miTablero->listaProvincias[idProvinciaOrigen]->getPerteneceIdJugador() == miTablero->listaProvincias[idProvinciaDestino]->getPerteneceIdJugador()){
		text = __String::createWithFormat("No pueden ser del mismo jugador.");
	}
	else {
		for (int i = 0; i<miTablero->listaProvincias[idProvinciaOrigen]->getLegiones(); i++){
			dañoataque += ((rand()%6)+1);
		}
		for (int i = 0; i<miTablero->listaProvincias[idProvinciaDestino]->getLegiones(); i++){
			dañodefensa += ((rand()%6)+1);
		}
		if (dañoataque > dañodefensa) {
			legionesrestantes = miTablero->listaProvincias[idProvinciaOrigen]->getLegiones()-1;
			miTablero->listaProvincias[idProvinciaDestino]->setPerteneceIdJugador(jugadoratacante);
			Jugadores[jugadordefensor]->EliminarProvincia(idProvinciaDestino);
			Jugadores[jugadoratacante]->AñadirProvincia(idProvinciaDestino);
			miTablero->listaProvincias[idProvinciaOrigen]->setLegiones(1);
			miTablero->listaProvincias[idProvinciaDestino]->setLegiones(legionesrestantes);
			text = __String::createWithFormat("El atacante %d gana a la defensa %d con un resultado de %d a %d", jugadoratacante, jugadordefensor, dañoataque, dañodefensa);
			if (jugadoratacante == idJugadorUsuario){
				ReasignarProvinciasVisibles();
			}
			if (jugadordefensor == idJugadorUsuario){
				ReasignarProvinciasVisibles();
			}
		}
		else {
			miTablero->listaProvincias[idProvinciaOrigen]->setLegiones(1);
			text = __String::createWithFormat("El defensor %d gana al ataque %d con un resultado de %d a %d", jugadordefensor, jugadoratacante, dañodefensa, dañoataque);
		}
	}
	LabelTTF* prueba =  LabelTTF::create(text->getCString(), "Arial", 20);
	prueba->setPosition(Vec2(950, visibleSize.height-200));
	prueba->setColor(ccc3(255,255,255));	if (DeteccionFin()){		goToMainMenu(NULL);	}	Redibujar();	addChild(prueba, 1);

}

void GameScene::InicioJuego(){
	int i;
	int j;
	int z;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	miTablero = new Tablero(numJugadores);
	Jugadores[numJugadores];
	for (i = 0; i<numJugadores; i++){
		Jugadores[i] = new Jugador(i);
	}
	miTablero->GenerarMapa();

	int idProvincia;
	for (i = 0; i<numJugadores; i++){
		for (j = 0; j<(numeros/numJugadores); j++){
			idProvincia = miTablero->AsignarProvincia();
			Jugadores[i]->AñadirProvincia(idProvincia);
			miTablero->listaProvincias[idProvincia]->setPerteneceIdJugador(i);

		}
	}
	
	int sobrantes = numeros % numJugadores;
	if(numeros % numJugadores != 0){
		for (i = 0; i<sobrantes-1; i++){
			idProvincia = miTablero->AsignarProvincia();
			Jugadores[i]->AñadirProvincia(idProvincia);
			miTablero->listaProvincias[idProvincia]->setPerteneceIdJugador(i);
		}
	}

	Jugadores[i]->CambiarTurno();
	turnojugador = i;
	idJugadorUsuario = i;
	Redibujar();
}

void GameScene::MostrarProvincia(int idProvincia){
	if (idProvincia<numeros && idProvincia >= 0){
		removeChildByName("Provincia");
		Size visibleSize = Director::getInstance()->getVisibleSize();
		__String *text;
		if (idProvincia == 0){
			text = __String::createWithFormat("Mar");
		}
		else {
			int auxlegiones = miTablero->listaProvincias[idProvincia]->getLegiones();
			int auxCentro[2] = {miTablero->listaProvincias[idProvincia]->getCentroProvinciax(), miTablero->listaProvincias[idProvincia]->getCentroProvinciay()};
			int auxJugador = miTablero->listaProvincias[idProvincia]->getPerteneceIdJugador();
			Material* auxMaterial = miTablero->listaProvincias[idProvincia]->getMaterial();
			tipo auxtipo = auxMaterial->getTipo();
			switch (auxtipo){
			case oro:
				text = __String::createWithFormat("Provincia n: %d\nCentro: (%d, %d)\nLegiones: %d\nMaterial: oro\nJugador: %d", idProvincia, auxCentro[0], auxCentro[1], auxlegiones, auxJugador);
				break;

			case plata:
				text = __String::createWithFormat("Provincia n: %d\nCentro: (%d, %d)\nLegiones: %d\nMaterial: plata\nJugador: %d", idProvincia, auxCentro[0], auxCentro[1], auxlegiones, auxJugador);
				break;

			case bronce:
				text = __String::createWithFormat("Provincia n: %d\nCentro: (%d, %d)\nLegiones: %d\nMaterial: bronce\nJugador: %d", idProvincia, auxCentro[0], auxCentro[1], auxlegiones, auxJugador);
				break;
			}		}		informacionProvincia = LabelTTF::create(text->getCString(), "Arial", 20);		informacionProvincia->setPosition(Vec2(950, visibleSize.height-100));
		informacionProvincia->setColor(ccc3(255,255,255));
		informacionProvincia->setName("Provincia");
		addChild(informacionProvincia);
	}
}

void GameScene::Redibujar() {
	removeAllChildren();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	cocos2d::Color3B color;
	int i;
	int j;
	for (i = 0; i<largo; i++){
		for (j = 0; j<largo; j++){
			_backgroundArray[i][j] = Sprite::create("hexagono.png");
			int auxIdProvincia = miTablero->matrizMapa[i][j];
			if (auxIdProvincia != 0){
				switch (miTablero->listaProvincias[auxIdProvincia]->getPerteneceIdJugador()){
				case 0:
					color = Color3B(255,104,0);
					break;

				case 1:
					color = Color3B(199,255,0);
					break;

				case 2:
					color = Color3B(255,0,0);
					break;

				case 3:
					color = Color3B(255,255,255);
					break;
				}
				if (!miTablero->listaProvincias[auxIdProvincia]->getVisible()){
					_backgroundArray[i][j]->setOpacity(200);
				}
				else {
					_backgroundArray[i][j]->setOpacity(255);
				}
			}
			else {
				color = Color3B(0,0,255);
			}
			_backgroundArray[i][j]->setColor(color);
			if (i%2 == 0){
				_backgroundArray[i][j]->setPosition(Point((i*14)+14, visibleSize.height-(j*18)-18));
			}
			else {
				_backgroundArray[i][j]->setPosition(Point((i*14)+14, visibleSize.height-(j*18)-27));
			}
			addChild(_backgroundArray[i][j], 0);

		}
	}

	_etiquetasSoldados[0] = NULL;
	__String *text;
	int auxX;
	int auxY;
	for (i = 1; i<numeros; i++){
		if (miTablero->listaProvincias[i]->getVisible()){
			text = __String::createWithFormat("%d", miTablero->listaProvincias[i]->getLegiones());
			_etiquetasSoldados[i] =  LabelTTF::create(text->getCString(), "Arial", 20);
			auxX = miTablero->listaProvincias[i]->getCentroProvinciax();
			auxY = miTablero->listaProvincias[i]->getCentroProvinciay();
			if (i%2 == 0){
				_etiquetasSoldados[i]->setPosition(Vec2((auxX*14)+14, visibleSize.height-(auxY*18)-18));
			}
			else {
				_etiquetasSoldados[i]->setPosition(Vec2((auxX*14)+14, visibleSize.height-(auxY*18)-27));
			}
			_etiquetasSoldados[i]->setColor(ccc3(0,0,0));			addChild(_etiquetasSoldados[i], 1);		}	}

	auto playItem = MenuItemImage::create("Play_Button.png", "Play_Button(Click).png", CC_CALLBACK_1(GameScene::CambiarTurnoUsuario, this));
	botonFinTurno = Menu::create(playItem, NULL);
	botonFinTurno->setPosition(950, visibleSize.height-800);
	addChild(botonFinTurno);

	text = __String::createWithFormat("Turnojugador: %d \nUsuario: %d", turnojugador, idJugadorUsuario);
	turno = LabelTTF::create(text->getCString(), "Arial", 20);	turno->setPosition(Vec2(950, visibleSize.height-850));
	turno->setColor(ccc3(255,255,255));
	turno->setName("turno");
	addChild(turno);
}

void GameScene::ClickRaton(Event *event){
	if (enPartida){
		removeChildByName("click");
		__String *text;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto *e = dynamic_cast<EventMouse *>(event);
		int auxboton = e->getMouseButton();
		posAntiguaRaton[0] = posRaton[0];
		posAntiguaRaton[1] = posRaton[1];
		idAntiguaSeleccionada = idProvinciaSeleccionada;
		posRaton[0] = (e->getCursorX()-13)/14;
		if (posRaton[0] %2 == 0){
			posRaton[1] = (visibleSize.height-(e->getCursorY())-17)/18;
		}
		else {
			posRaton[1] = (visibleSize.height-(e->getCursorY())-26)/18;
		}
		if (auxboton == 0){
			if(turnojugador == idJugadorUsuario){
				if (idProvinciaSeleccionada != 0 || Jugadores[idJugadorUsuario]->ConsultarProvincia(miTablero->matrizMapa[posRaton[0]][posRaton[1]])){
					idProvinciaSeleccionada = miTablero->matrizMapa[posRaton[0]][posRaton[1]];
				}
				text = __String::createWithFormat("Provincia Seleccionada: %d\nAntigua Seleccionada: %d", idProvinciaSeleccionada, idAntiguaSeleccionada);
			}
			else {
				text = __String::createWithFormat("¡No es el turno del usuario!");
			}
			LabelTTF* click = LabelTTF::create(text->getCString(), "Arial", 20);			click->setPosition(Vec2(950, visibleSize.height-400));
			click->setColor(ccc3(255,255,255));			click->setName("click");			addChild(click, 1);
		}
		else if (auxboton == 1){
		
			MostrarProvincia(miTablero->matrizMapa[posRaton[0]][posRaton[1]]);
		}
	}
}

bool GameScene::DeteccionFin(){
	for (int i = 0; i<numJugadores; i++){
		if (Jugadores[i]->propiedadProvincias.size() == numeros-1){
			return true;
		}
	}
	return false;
}