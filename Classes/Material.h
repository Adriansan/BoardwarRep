#pragma once
#include "Librerias.h"

const int cantidadtipos = 3;
enum tipo {oro = 1, plata = 2, bronce = 3};

class Material
{
private:
	tipo miTipo;
	// Sprite imagen;

public:
	Material(tipo auxTipo);
	tipo getTipo();
	~Material(void);
};
