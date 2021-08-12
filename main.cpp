#include <cstdio>
#include <ctime>
#include "ArbolAvl.h"

registro buscarRegistroEnArchivo(char lastname[]) {
	ifstream in("datab_jc.dat", ios::in | ios::binary);
	registro reg;
	in.seekg(0, ios::end);
	int end = in.tellg();
	in.seekg(0, ios::beg);
	while(in.tellg() < end) {
		int currentPos = in.tellg();
		in.read((char*)&reg, sizeof(registro));
		if(strcmp(reg.lastname, lastname) == 0) {
			return reg;
		}
	}
	reg.id = -1;
	return reg;
}

void printRegister(registro reg) {
	cout << "id: " << reg.id << endl;
    cout << "name: " << reg.name << endl;
    cout << "lastname: " << reg.lastname << endl;
    cout << "credit card: " << reg.credit_card << endl;
    cout << "date: " << reg.date << endl;
    cout << "day: " << reg.day << endl;
    cout << "month: " << reg.month << endl;
    cout << "year: " << reg.year << endl;
    cout << "payment type: " << reg.payment_type << endl;
    cout << "total: " << reg.total << endl;
    cout << "business type: " << reg.business_type << endl;
    cout << "business name: " << reg.business_name << endl;
}

int main() {
	Tree t;
	/*
	
	cout << "imprimir datos" << endl;
	t.preOrden(t.root);
	*/
	int opcion;

	do {
		cout << "1. Cargar datos al arbol AVL" << endl;
		cout << "2. Buscar dato y comparar tiempos" << endl;
		cout << "3. Eliminar registro del arbol" << endl;
		cout << "4. Salir" << endl;
		cin >> opcion;

		switch(opcion) {
			case 1: {
				cout << "cargando datos" << endl;
				t.cargarDatos();
				cout << "datos cargados exitosamente" << endl;
				break;
			}
			case 2: {
				char name[30];
				char lastname[30];
				registro reg;

				cout << "Ingrese nombre: ";
				cin >> name;
				cout << "Ingrese apellido: ";
				cin >> lastname;

				std::clock_t start;
    			double duration;

				cout << "Busqueda en arbol avl" << endl;
    			start = std::clock();
				reg = t.findByLastname(t.root, lastname, name);

				printRegister(reg);

				duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
				cout << "duracion de la busqueda: " << duration << endl; 

				cout << " " << endl;

				cout << "Busqueda en archivo binario" << endl;

				start = std::clock();
				reg = buscarRegistroEnArchivo(lastname);

				printRegister(reg);

				duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
				cout << "duracion de la busqueda: " << duration << endl; 


				break;
			}
			case 3: {
				char name[30];
				char lastname[30];
				registro reg;

				cout << "Ingrese nombre: ";
				cin >> name;
				cout << "Ingrese apellido: ";
				cin >> lastname;
				t.deleteName(t.root, name, lastname);
				break;
			}
			case 4: {
				cout << "Saliendo del programa" << endl;
				break;
			}
			default: cout << "opcion incorrecta";
		}
		cout << " " << endl;
	} while(opcion != 4);
	

    return 0;
}