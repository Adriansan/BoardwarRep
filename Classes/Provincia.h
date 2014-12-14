#pragma once
#include "Librerias.h"
#include "Material.h"
#include "cocos2d.h"
#include "math\CCGeometry.h"
using namespace std;


class Provincia
{
private:
	int id;
	int legiones;
	// Jugador propiedadJugador;
	Material* recurso;
	bool escogida;
	bool visible;
	int centroProvincia[2];
	int perteneceIdJugador;
public:
	list<int> provinciasColindantes;
	void AñadirProvinciaFronteriza(int idProvincia);
	bool ComprobarProvinciaAislada();
	void ObtenerInformacion(void);
	bool ProvinciaEnFrontera(int idProvincia);
	int getPerteneceIdJugador(void);
	void setPerteneceIdJugador(int idJugador);
	bool getEscogida(void);
	void setEscogida(bool auxBool);
	int getCentroProvinciax(void);
	int getCentroProvinciay(void);
	void setCentroProvincia(int auxCentro[2]);
	int getLegiones(void);
	void setLegiones(int auxLegiones);
	bool getVisible(void);
	void setVisible(bool auxVisible);
	Material* getMaterial();
	Provincia(int auxId);
	~Provincia(void);
};

