#pragma once
#include "Librerias.h"

const int cantidadtipos = 3;
enum tipo {oro, plata, bronce};

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
