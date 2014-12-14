#include "Provincia.h"


Provincia::Provincia(int auxId)
{
	escogida = false;
	id = auxId;
	visible = false;
	int auxrand = (rand() % cantidadtipos);
	switch (auxrand){
		case 0:
			recurso = new Material(oro);
			break;
		
		case 1:
			recurso = new Material(plata);
			break;

		case 2:
			recurso = new Material(bronce);
			break;
	}

}


Provincia::~Provincia(void)
{
}

void Provincia::AñadirProvinciaFronteriza(int idProvincia){
	provinciasColindantes.push_back(idProvincia);
	return;
}

bool Provincia::ComprobarProvinciaAislada(){
	if (provinciasColindantes.empty()){
		return true;
	}
	else {
		return false;
	}
}

bool Provincia::getEscogida(){
	return escogida;
}

void Provincia::setEscogida(bool auxBool){
	escogida = auxBool;
}

int Provincia::getCentroProvinciax(void){
	return centroProvincia[0];
}

int Provincia::getCentroProvinciay(void){
	return centroProvincia[1];
}

void Provincia::setCentroProvincia(int auxCentro[2]){
	centroProvincia[0] = auxCentro[0];
	centroProvincia[1] = auxCentro[1];
}

int Provincia::getLegiones(){
	return legiones;
}

void Provincia::setLegiones(int auxLegiones){
	legiones = auxLegiones;
}

bool Provincia::ProvinciaEnFrontera(int idProvincia){
	bool encontrado = false;
	list<int>::iterator it;
	for (it=provinciasColindantes.begin(); it!=provinciasColindantes.end(); ++it){
		if (*it == idProvincia){
			return true;
		}
	}
	return false;
}

int Provincia::getPerteneceIdJugador(void){
	return perteneceIdJugador;
}

void Provincia::setPerteneceIdJugador(int idJugador){
	perteneceIdJugador = idJugador;
}

Material* Provincia::getMaterial(){
	return recurso;
}

void Provincia::setVisible(bool auxVisible){
	visible = auxVisible;
}

bool Provincia::getVisible(){
	return visible;
}