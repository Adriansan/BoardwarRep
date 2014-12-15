#include "Jugador.h"

Jugador::Jugador(int auxId)
{
	id = auxId;
	turno = false;
}


Jugador::~Jugador(void)
{
}

void Jugador::AñadirProvincia(int auxId){
	propiedadProvincias.push_back(auxId);
}

void Jugador::CambiarTurno(){
	if (turno){
		turno = false;
	}
	else{
		turno = true;
	}
}

bool Jugador::ConsultarProvincia(int provinciaId){
	for (list<int>::iterator it=propiedadProvincias.begin(); it != propiedadProvincias.end(); ++it){
		if (provinciaId == *it){
			return true;
		}
	}
	return false;
}

void Jugador::EliminarProvincia(int idProvincia){
	propiedadProvincias.remove(idProvincia);
}
