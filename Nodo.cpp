// Julián Toledano Díaz
// Sistemas Distribuidos

#include "Nodo.h"
#include <stdlib.h>
// Por defecto no hace nada
Nodo::Nodo(){}

// Constructor root
Nodo::Nodo(Arbol* arbol){
  esteArbol = arbol;
  padre = NULL;
  hijos = new std::vector<Nodo*>();
  strncpy(nombre, "/root", MAX);
  id = 0;
  nivel = 0;
  directorio = true;
  tamano = 4096;
  ultimaModificacion = time(0); // Utilizar la estructura st para convertir el número entero a formato fecha
  numBloques = 0;
  bloques = (int*)malloc(numBloques*sizeof(int));
}

// Constructor para nodos distintos de la raiz
Nodo::Nodo(Arbol *arbol, Nodo* mpadre, char* mnombre, int mid, bool mdirectorio, off_t mtamano){
  esteArbol = arbol;
  padre = mpadre;
  hijos = new std::vector<Nodo*>();
  strncpy(nombre, mnombre, MAX);
  id = mid;
  nivel = mpadre->getNivel() + 1;
  directorio = mdirectorio;
  tamano  = mtamano;
  ultimaModificacion = time(0);
  numBloques = 0;
  bloques = (int*)malloc(numBloques*sizeof(int));
}

// Métodos GET
Nodo* Nodo::getPadre(){return padre;}
std::vector<Nodo*>* Nodo::getHijos(){return hijos;}
char* Nodo::getNombre(){return nombre;}
int Nodo::getId(){return id;}
int Nodo::getNivel(){return nivel;}
bool Nodo::esDirectorio(){return directorio;}
off_t Nodo::getTamano(){return tamano;}
time_t Nodo::getUltimaModificacion(){return ultimaModificacion;}
int Nodo::getNumBloques(){return numBloques;}
int* Nodo::getBloques() {return bloques;}

// MÉTODOS SET
void Nodo::setNombre(char* mnombre){strncpy(nombre, mnombre, MAX);}
void Nodo::setId(int mid){id = mid;}
void Nodo::setNivel(int mnivel){nivel = mnivel;}
void Nodo::setDirectorio(bool mdirectorio){directorio = mdirectorio;}
void Nodo::setTamano(off_t mtamano){tamano = mtamano;}
void Nodo::setModificacion(time_t multimaModificacion){ultimaModificacion = multimaModificacion;}
void Nodo::setUltimaModificacion(){ultimaModificacion = time(0);}
void Nodo::setHijos(Nodo* nuevoNodo){hijos->push_back(nuevoNodo);}
void Nodo::setArbol(Arbol *arbol){esteArbol = arbol;}
void Nodo::setNumBloques(int mnumBloques){numBloques = mnumBloques;}
void Nodo::setBloques(int *mbloques){
  bloques = (int*)malloc(sizeof(int)*numBloques);
  for(int i = 0; i < numBloques; i++)
    bloques[i] = mbloques[i];
}

void Nodo::anadirBloques(int sector){
  numBloques += 1;
  bloques = (int*)realloc(bloques, numBloques * sizeof(int));
  bloques[numBloques-1] = sector;
}
