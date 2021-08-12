#ifndef ARBOLAVL_H
#define ARBOLAVL_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string.h>
#include "avl.h"
#include "registro.h"

using namespace std;

class Tree {
public:
    Tree();
    void cargarDatos();
    void addNode(char lastname[], char name[], int position);
    registro findByLastname(AVL*, char lastname[], char name[]);
	AVL* root;
    vector<string>list;
	void addNode(AVL*, AVL**, char name[], int position);
    AVL* minValueNode(AVL*);
    AVL* deleteNode(AVL*);
    bool deleteName(AVL*, char name[], char lastname[]);
    void preOrden(AVL*);
    void inOrden(AVL*);
    void postOrden(AVL*);
    int getHeight(AVL*);
    void printHojas(AVL*);
    int getSize(AVL*);

    //funciones para balancear el arbol
    void balanciar(AVL**);
    void RotaIzq(AVL**);
    void RotaDere(AVL**);
    void DobleRotaIzq(AVL**);
    void DobleRotaDere(AVL**);
};

#endif