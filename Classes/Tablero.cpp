#include "Tablero.h"


Tablero::Tablero(int Jugadores)
{
	numJugadores = Jugadores;
	srand(time(NULL));
	for (int i = 0; i<numeros; i++){
		listaProvincias[i] = new Provincia(i);
	}
}


Tablero::~Tablero(void)
{
}

int Tablero::AsignarProvincia(){
	bool encontrada = false;
	while(!encontrada){
		int auxrand = rand() % numeros;
		if (auxrand == 0){
			continue;
		}
		if (listaProvincias[auxrand]->getEscogida() == false){
			listaProvincias[auxrand]->setEscogida(true);
			return auxrand;
		}
	}
}

void Tablero::GenerarMapa()
{
	int w;
	int e;
	int auxrand;
	int aux;
	int i;
	int j;
	int puestos;
	int auxCentro[2];
	const double relacionprovincias = 1.5;
	bool repetir = true;
	int cantidades[numeros];
	bool direcciones[numeros][numeros];

	
	while (repetir){
		// Reservar espacio en la matriz.
		for (i = 0; i<largo; i++){
			for (j = 0; j<largo; j++){
				matrizMapa[i][j] = 0;
			}
		}

		// Asignar el primer hexágono aleatorio.
		for (int x = 1; x<numeros; x++){
			w = (rand() % largo);
			e = (rand() % largo);
			if (matrizMapa[w][e] == 0){
				matrizMapa[w][e] = x;
				auxCentro[0] = w;
				auxCentro[1] = e;
				listaProvincias[x]->setCentroProvincia(auxCentro);
			}
		}

		// Generar todos los hexágonos a partir de los ya puestos.
		bool nohayceros = false;
		puestos = 0;
		while (puestos <= (largo*largo)/relacionprovincias){
			nohayceros = true;
			w = (rand() % largo);
			e = (rand() % largo);
			if (matrizMapa[w][e] != 0){
				auxrand = rand() % 4;
				aux = matrizMapa[w][e];
				switch (auxrand){
					case 1:
						if (w-1 >= 0){
							if (matrizMapa[w-1][e] == 0){
								matrizMapa[w-1][e] = aux;
								puestos += 1;
							}
						}
						break;

					case 2:
						if (w+1 < largo){
							if (matrizMapa[w+1][e] == 0){
								matrizMapa[w+1][e] = aux;
								puestos += 1;
							}
						}
						break;

					case 3:
						if (e-1 >= 0){
							if (matrizMapa[w][e-1] == 0){
								matrizMapa[w][e-1] = aux;
								puestos += 1;
							}
						}
						break;

					case 4:
						if (e+1 < largo){
							if (matrizMapa[w][e+1] == 0){
								matrizMapa[w][e+1] = aux;
								puestos += 1;
							}
						}
						break;
				}	
			}
		}

		// Busca las fronteras de cada provincia y las guarda en una matriz auxiliar.
		for (i = 0; i<numeros; i++){
			cantidades[i] = 0;
			for (j = 0; j<numeros; j++){
				direcciones[i][j] = false;
			}
		}

		for (i = 0; i<largo; i++){
				for (j = 0; j<largo; j++){
					if (i-1 >= 0){
						if (direcciones[matrizMapa[i][j]][matrizMapa[i-1][j]] == false){
							direcciones[matrizMapa[i][j]][matrizMapa[i-1][j]] = true;
						}
					}
					if (i+1 < largo){
						if (direcciones[matrizMapa[i][j]][matrizMapa[i+1][j]] == false){
							direcciones[matrizMapa[i][j]][matrizMapa[i+1][j]] = true;
						}
					}
					if (j-1 >= 0){
						if (direcciones[matrizMapa[i][j]][matrizMapa[i][j-1]] == false){
							direcciones[matrizMapa[i][j]][matrizMapa[i][j-1]] = true;
						}
					}
					if (j+1 < largo){
						if (direcciones[matrizMapa[i][j]][matrizMapa[i][j+1]] == false){
							direcciones[matrizMapa[i][j]][matrizMapa[i][j+1]] = true;
						}
					}
					if (j%2 == 0){
						if (i-1 >= 0 && j-1 >= 0){
							if (direcciones[matrizMapa[i][j]][matrizMapa[i-1][j-1]] == false){
								direcciones[matrizMapa[i][j]][matrizMapa[i-1][j-1]] = true;
							}
						}
						if (i-1 >= 0 && j+1 < largo){
							if (direcciones[matrizMapa[i][j]][matrizMapa[i-1][j+1]] == false){
								direcciones[matrizMapa[i][j]][matrizMapa[i-1][j+1]] = true;
							}
						}
					}
					else {
						if (i+1 < largo && j-1 >= 0){
							if (direcciones[matrizMapa[i][j]][matrizMapa[i+1][j-1]] == false){
								direcciones[matrizMapa[i][j]][matrizMapa[i+1][j-1]] = true;
							}
						}
						if (i+1 < largo && j+1 < largo){
							if (direcciones[matrizMapa[i][j]][matrizMapa[i+1][j+1]] == false){
								direcciones[matrizMapa[i][j]][matrizMapa[i+1][j+1]] = true;
							}
						}
					}
					cantidades[matrizMapa[i][j]] += 1;
				}
		}

		// Asocia cada frontera para cada una de las provincias.
		for (i = 0; i<numeros; i++){
			for (j = 0; j<numeros; j++){
				if (j != 0 && j != i){
					if (direcciones[i][j]){
						listaProvincias[i]->AñadirProvinciaFronteriza(j);
					}
				}
			}
		}

		// Comprobación de que ninguna provincia está aislada, es decir, tiene frontera
		// con al menos alguna provincia.
		repetir = false;
		for (i = 0; i<numeros; i++){
			if (listaProvincias[i]->ComprobarProvinciaAislada()){
				repetir = true;
				break;
			}
		}
	}

	for (i = 1; i<numeros; i++){
		AsignarCentroProvincias(i);
	}

	AsignarLegionesInicio();

	/*string prueba;
	prueba = "";
	
	i = 0;
	j = 0;

	for (i = 0; i<largo; i++){
			for (j = 0; j<largo; j++){
				prueba += myarray[i][j] + '0';
			}
			prueba += '\n';
	}
	char * devuelto;
	devuelto = new char[prueba.size() + 1];
    memcpy(devuelto, prueba.c_str(), prueba.size() + 1);*/
	return;
}

void Tablero::AsignarCentroProvincias(int idProvincia){
	int sumax = 0;
	int sumay = 0;
	int cantidad = 0;
	int auxCentro[2];

	for (int i = 0; i<largo; i++){
		for (int j = 0; j<largo; j++){
			if (matrizMapa[i][j] == idProvincia){
				sumax += i;
				sumay += j;
				cantidad++;
			}
		}
	}
	if (cantidad == 0){
		cantidad = 1;
	}
	auxCentro[0] = sumax / cantidad;
	auxCentro[1] = sumay / cantidad;
	listaProvincias[idProvincia]->setCentroProvincia(auxCentro);
}

void Tablero::AsignarLegionesInicio(){
	int auxrand;
	for (int i = 1; i<numeros; i++){
		auxrand = (rand() % 3)+1;
		listaProvincias[i]->setLegiones(auxrand);
	}
}
