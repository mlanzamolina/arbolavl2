#include "ArbolAvl.h"

AVL::AVL(char lastname[]) {
	//std::copy(std::begin(this->lastname), std::end(this->lastname), std::begin(lastname));
	strcpy(this->lastname, lastname);
	izq = NULL;
	dere = NULL;
}

//int AVL::peso() {
//	if (izq == NULL && dere == NULL)
//		return 0;
//}

Tree::Tree() {
	root = NULL;
}

void Tree::cargarDatos() {
	ifstream in("datab_jc.dat", ios::in | ios::binary);
	if(!in.is_open()) {
		std::cout << "could not open file" << std::endl;
		return;
	}
	registro nuevoRegistro;
	in.seekg(0, ios::end);
	int end = in.tellg();
	in.seekg(0, ios::beg);
	while(in.tellg() < end) {
		int currentPos = in.tellg();
		in.read((char*)&nuevoRegistro, sizeof(registro));
		addNode(nuevoRegistro.lastname, nuevoRegistro.name, currentPos);
	}
}

void Tree::addNode(char lastname[], char name[], int position) {
	AVL* newNode = new AVL(lastname);
	addNode(newNode, &root, name, position);
}

void Tree::addNode(AVL* nuevo, AVL** raiz, char name[], int position) {
	if (*raiz == NULL) {
		*raiz = nuevo;
		registro_nodo nuevoElemento;
		strcpy(nuevoElemento.name, name); 
		nuevoElemento.position = position;
		(*raiz)->listaNombres.push_back(nuevoElemento);
	}
	else {
		if (strcmp(nuevo->lastname, (*raiz)->lastname) < 0) {
			addNode(nuevo, &(*raiz)->izq, name, position);
			
		}
		else if (strcmp(nuevo->lastname, (*raiz)->lastname) > 0) {
			addNode(nuevo, &(*raiz)->dere, name, position);
		}
		else  {
			//agregar nombre a la lista de este apellido
			registro_nodo nuevoElemento;
			strcpy(nuevoElemento.name, name); 
			nuevoElemento.position = position;
			//agregar nuevo registro a la lista de nombres
			(*raiz)->listaNombres.push_back(nuevoElemento);
		}
		balanciar(raiz);
	}
}

AVL* Tree::minValueNode(AVL* raiz) {
	AVL* actual = raiz;

	while (actual->izq != NULL) {
		actual = actual->izq;
	}

	return actual;
}


int Tree::getHeight(AVL* raiz) {
	if (raiz == NULL)
		return 0;
	else {
		int izquierda = getHeight(raiz->izq);
		int derecha = getHeight(raiz->dere);
		if (izquierda > derecha)
			return izquierda + 1;
		else
			return derecha + 1;
	}
}

int Tree::getSize(AVL* raiz) {
	if (raiz == NULL)
		return 0;
	return (getSize(raiz->izq) + 1 + getSize(raiz->dere));
}

void Tree::RotaIzq(AVL** raiz) {
	AVL* derecha = (*raiz)->dere;
	(*raiz)->dere = derecha->izq;
	derecha->izq = *raiz;
	*raiz = derecha;
}

void Tree::RotaDere(AVL** raiz) {
	AVL* izquierda = (*raiz)->izq;
	(*raiz)->izq = izquierda->dere;
	izquierda->dere = *raiz;
	*raiz = izquierda;
}

void Tree::DobleRotaIzq(AVL** raiz) {
	AVL* derecha = (*raiz)->dere;
	RotaDere(&derecha);
	RotaIzq(raiz);
}

void Tree::DobleRotaDere(AVL** raiz) {
	AVL* izquierda = (*raiz)->izq;
	RotaIzq(&izquierda);
	RotaDere(raiz);
}

void Tree::balanciar(AVL** raiz) {
	if ((getHeight((*raiz)->izq) - getHeight((*raiz)->dere)) < 2)
		return;

	if (getHeight((*raiz)->dere) > getHeight((*raiz)->izq)) {
		if (getHeight((*raiz)->dere->dere) >= getHeight((*raiz)->dere->izq))
			RotaIzq(raiz);
		else
			DobleRotaIzq(raiz);
	}
	else {
		if (getHeight((*raiz)->izq->izq) >= getHeight((*raiz)->dere))
			RotaDere(raiz);
		else
			DobleRotaDere(raiz);
	}
}

registro Tree::findByLastname(AVL* raiz, char lastname[], char name[]) {
	//si no se encontro nada
    if (raiz == NULL) {
		registro reg;
		reg.id = -1;
		return reg;
	}
	//si el apellido coincide
	else if(strcmp(raiz->lastname, lastname) == 0) {
		registro reg;
		
		for(int i = 0; i < raiz->listaNombres.size(); i++) {
			//si el nombre coincide, ir a buscar el registro al archivo binario y devolverlo
			if(strcmp(raiz->listaNombres[i].name, name) == 0) {
				ifstream in("datab_jc.dat", ios::in | ios::binary);
				in.seekg(raiz->listaNombres[i].position);
				in.read((char*)&reg, sizeof(registro));
				return reg;
			}
		}
		//si no se encuentra el nombre, devolver un registro con id -1
		reg.id = -1;
		return reg;
	}
    
    // en caso de que el cmp sea menor
    if (strcmp(raiz->lastname, lastname) < 0)
       return findByLastname(raiz->dere, lastname, name);
 
    // en caso que el cmp sea mayor
    return findByLastname(raiz->izq, lastname, name);

}

bool Tree::deleteName(AVL* raiz, char name[], char lastname[]) {
	//si no se encuentra el apellido
	if(raiz == NULL)
		return false;
	//si el apellido coincide
    else if (strcmp(raiz->lastname, lastname) == 0) {
		
		for(int i = 0; i < raiz->listaNombres.size(); i++) {
			//si el nombre coincide, ir a buscar el registro al archivo binario y devolverlo
			if(strcmp(raiz->listaNombres[i].name, name) == 0) {
				raiz->listaNombres.erase(raiz->listaNombres.begin() + i);
				//si el nodo ya no tiene mas nombres, borrar por completo este nodo del arbol
				if(raiz->listaNombres.size() == 0) {
					deleteNode(raiz);
				}
				return true;
			}
		}
		//si no se encuentra el nombre, devolver false
		return false;
	}
    
    // en caso de que el cmp sea menor
    if (strcmp(raiz->lastname, lastname) < 0)
       return deleteName(raiz->dere, lastname, name);
 
    // en caso que el cmp sea mayor
    return deleteName(raiz->izq, lastname, name);
}

AVL* Tree::deleteNode(AVL* raiz) {
	//caso base
	if (raiz == NULL) {
		return raiz;
	}

	if (raiz->izq == NULL) {
		AVL* temp = raiz->dere;
		delete raiz;
		return temp;
	}
	else if (raiz->dere == NULL) {
		AVL* temp = raiz->izq;
		delete raiz;
		return temp;
	}

	AVL* temp = minValueNode(raiz->dere);
	strcpy(raiz->lastname, temp->lastname);
	raiz->listaNombres = temp->listaNombres;

	raiz->dere = deleteNode(raiz->dere);

	return raiz;
}

void Tree::preOrden(AVL* raiz) {
	if (raiz == NULL)
		return;

	cout << raiz->lastname << endl;

	if (raiz->izq != NULL)
		preOrden(raiz->izq);
	if (raiz->dere != NULL)
		preOrden(raiz->dere);
}

void Tree::inOrden(AVL* raiz) {
	if (raiz == NULL)
		return;
	if (raiz->izq != NULL)
		inOrden(raiz->izq);
	cout << raiz->lastname << endl;
	if (raiz->dere != NULL)
		inOrden(raiz->dere);
}

void Tree::postOrden(AVL* raiz) {
	if (raiz == NULL)
		return;
	if (raiz->izq != NULL)
		postOrden(raiz->izq);
	if (raiz->dere != NULL)
		postOrden(raiz->dere);
	cout << raiz->lastname << endl;
}

void Tree::printHojas(AVL* raiz) {
	if (raiz->izq != NULL)
		printHojas(raiz->izq);
	if (raiz->dere != NULL)
		printHojas(raiz->dere);
	if (raiz->izq == NULL && raiz->dere == NULL)
		cout << raiz->lastname << endl;
}