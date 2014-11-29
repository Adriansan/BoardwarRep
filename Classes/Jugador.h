#pragma once
#include "Librerias.h"
#include "Provincia.h"

class Jugador
{
private:
	int id;
	bool turno;

public:
	list<int> propiedadProvincias;
	void AñadirProvincia(int auxId);
	void CambiarTurno();
	bool ConsultarProvincia(int provinciaId);
	void EliminarProvincia(int provinciaId);

	Jugador(int auxId);
	~Jugador(void);
};

