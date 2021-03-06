#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "MainMenuScene.h"
#include "Tablero.h"
#include "Librerias.h"
#include "Jugador.h"

using namespace std;

const int numJugadoresMaximos = 8;
USING_NS_CC;

class GameScene : public cocos2d::Layer
{
private:
	int numJugadores;
	float tiempopartida;
	int turnojugador;
	bool numJugMas;
	bool modoEspía;
	bool pasado;
	bool enPartida;
	LabelTTF* _etiquetasSoldados[numeros];
	LabelTTF* turno;
	LabelTTF* informacionProvincia;
	LabelTTF* modoEspíaLabel;
	Sprite* _backgroundArray[largo][largo];
	Menu* botonFinTurno;
	Tablero* miTablero;
	Jugador* Jugadores[numJugadoresMaximos];
	int posRaton[2];
	int posAntiguaRaton[2];
	int idJugadorUsuario;
	int idProvinciaSeleccionada;
	int idAntiguaSeleccionada;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
	void goToMainMenu(Ref *pSender);	void VolverAEscoger(Ref *pSender);	void EmpezarPartida(Ref *pSender);	void MostrarOpcionesInicio();	void MoverNumeroJugadores(Ref *pSender);	void MoverNumeroJugadores2(Ref *pSender);	void InicioJuego();	void AsignarVisibilidadInicio();	void CambiarModoEspía(Ref *pSender);	void EspiarProvincia(int idProvinciaOrigen, int idProvinciaDestino);	void CambiarTurnoJuego();	void CambiarTurnoUsuario(Ref *pSender);	void AsignacionLegiones();	int  GenerarLegiones();	void AtacarProvincia(int idProvinciaOrigen, int idProvinciaDestino);	void ReasignarProvinciasVisibles();	void MostrarProvincia(int idProvincia);	void update(float dt);	void Redibujar();
	void ClickRaton(Event *event);
	void AccionesIA();
	bool DeteccionFin();
};

#endif // __HELLOWORLD_SCENE_H__
