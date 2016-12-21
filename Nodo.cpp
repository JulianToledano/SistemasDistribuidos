#include "Nodo.h"

Nodo::Nodo(){}
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
}

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
}

Nodo* Nodo::getPadre(){return padre;}
std::vector<Nodo*>* Nodo::getHijos(){return hijos;}
char* Nodo::getNombre(){return nombre;}
int Nodo::getId(){return id;}
int Nodo::getNivel(){return nivel;}
bool Nodo::esDirectorio(){return directorio;}
off_t Nodo::getTamano(){return tamano;}
time_t Nodo::getUltimaModificacion(){return ultimaModificacion;}

void Nodo::setNombre(char* mnombre){strncpy(nombre, mnombre, MAX);}
void Nodo::setId(int mid){id = mid;}
void Nodo::setNivel(int mnivel){nivel = mnivel;}
void Nodo::setDirectorio(bool mdirectorio){directorio = mdirectorio;}
void Nodo::setTamano(off_t mtamano){tamano = mtamano;}
void Nodo::setModificacion(time_t multimaModificacion){ultimaModificacion = multimaModificacion;}
void Nodo::setUltimaModificacion(){ultimaModificacion = time(0);}
void Nodo::setHijos(Nodo* nuevoNodo){hijos->push_back(nuevoNodo);}
void Nodo::setArbol(Arbol *arbol){esteArbol = arbol;}
