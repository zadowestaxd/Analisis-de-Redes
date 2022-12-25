#include <iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
using namespace std;

const int POKEMONS = 214; //segunda temporada 168 pokemons, quinta temporada 214
const int POPULARES = 2; //segunda temporada 3 popoulares, quinta temporada 2
const int num_episodios = 64; //segunda temporada 63 episodios, quinta temporada 65
int main() {
	string temp;
	int matriz[POKEMONS][POKEMONS] = {0};
	int cuantoseps[POKEMONS] = {0};
	int numpopulares = 0;
	int populares[POPULARES];
	int actual = 0;
	map<string, map<int, string>> diccionario;
	ifstream archivo("basededatosspace.csv");
	if (!archivo.is_open())
		cout << "error";

	ofstream edgelist("edgelist.csv");
	getline(archivo, temp);
	while (!archivo.eof() && actual != 2000) {
		archivo >> actual;
		archivo >> temp;
		archivo >> temp;
		archivo >> temp;
		archivo >> temp;
		
		getline(archivo, temp);
		if (temp == "\tToda la temporada") {
			populares[numpopulares] = actual;
			cuantoseps[actual] = num_episodios;
			numpopulares++;
		}else{
			//va llenando el mapa y la matriz
			for (int i = 3; i < temp.size(); i += 7) {
				cuantoseps[actual]++;
				string constructor = "";
				constructor = constructor + temp[i] + temp[i + 1] + temp[i + 2];
				//si no existe la entrada en el diccionario la crea
				if(diccionario.count(constructor) == 0)
				diccionario[constructor].insert({ actual, "" });
				else {
					//si existe hace una búsqueda para ir llenando la matriz haciendo uso de un iterador
					auto it = diccionario[constructor].begin();
					while (it != diccionario[constructor].end()) {
						matriz[actual][it->first]++;
						it++;
					}
					diccionario[constructor].insert({ actual, "" });
				}
			}
		}
		//matriz N*N nodos valor
		//mapa cuya key sea episodio y dentro contenga los pokemons. uniones de nodos
	}
	//Controla los pokemons con todos los episodios
	for (int i = 0; i < POPULARES; i++) {		
		for (int j = 0; j < POKEMONS; j++) {
			if(j != populares[i] && matriz[j][populares[i]] != num_episodios)
			matriz[populares[i]][j] = cuantoseps[j];
		}
	}
	//ESCRIBE EL ARCHIVO edgelist.csv
	for (int i = 0; i < POKEMONS; i++) {
		for (int j = 0; j < POKEMONS; j++) {
			if (matriz[i][j] != 0) {
				edgelist << i << " " << j << " " << matriz[i][j] << "\n";
			}
		}
	}

	cout << "EXITO AL CONVERTIR LA BASE DE DATOS A edgelist.csv"<<"\n"<<"\n";
	
	//Contador de episodios y pokemons que aparecen en estos	
	auto it = diccionario.begin();
	int cont = 0;
	while (it != diccionario.end()){
		cont++;
		cout << "KEY/EPISODIO: " << it->first << " Pokemons que aparecen en este episodio: ";
		auto it2 = diccionario[it->first].begin();
		while (it2 != diccionario[it->first].end()) {
			cout << it2->first<<" ";
			it2++;
		}
		it++;
		cout << endl;
	}
	//contador episodios
	cout << cont;
	
	return 0;
}