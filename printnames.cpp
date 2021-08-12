#include <iostream>
#include <fstream>
#include "registro.h"

using namespace std;

int main() {
    ifstream in("datab_jc.dat", ios::in | ios::binary);
	if(!in.is_open()) {
		std::cout << "could not open file" << std::endl;
		return -1;
	}
	registro nuevoRegistro;
	for(int i = 0; i < 100; i++) {
		in.read((char*)&nuevoRegistro, sizeof(registro));
        cout << "Registro " << i+1 << ": " << nuevoRegistro.name << " " << nuevoRegistro.lastname << endl;
	}
    return 0;
}