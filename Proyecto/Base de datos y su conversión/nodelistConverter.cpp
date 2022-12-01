#include <iostream>
#include<fstream>
#include<sstream>
#include<map>
using namespace std;

int main() {
	string temp;
	ifstream archivo("basededatosspace.csv");
	ofstream nodelist("nodelist.csv");
	getline(archivo, temp);
	while(!archivo.eof()){
	archivo >> temp;
	nodelist << temp;
	nodelist << " ";
	archivo >> temp;
	nodelist << temp;
	nodelist << " ";
	archivo >> temp;
	nodelist << temp;
	nodelist << " ";
	archivo >> temp;
	nodelist << temp;
	nodelist << " ";
	archivo >> temp;
	nodelist << temp;
	nodelist << "\n";
	getline(archivo, temp);
	}

	cout << "EXITO AL CONVERTIR LA BASE DE DATOS A nodelist.csv" << "\n" << "\n";

	return 0;
}