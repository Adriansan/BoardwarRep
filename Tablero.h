#include "Provincia.h"
#include "Librerias.h"
#include "Jugador.h"

using namespace std;

const int largo = 50;
const int numeros = 30;

class Tablero
{
private:
	int numJugadores;
	//Jugador turnoJugador;

public:
	Provincia* listaProvincias[numeros];
	int matrizMapa[largo][largo];
	Tablero(int Jugadores);
	~Tablero(void);
	void SalirPartida(void);
	void GenerarMapa(void);
	int AsignarProvincia();
	void AsignarCentroProvincias(int idProvincia);
	void AsignarLegionesInicio();
};