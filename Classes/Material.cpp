#include "Material.h"


Material::Material(tipo auxTipo)
{
	miTipo = auxTipo;

}


Material::~Material(void)
{
}

tipo Material::getTipo(){
	return miTipo;
}
