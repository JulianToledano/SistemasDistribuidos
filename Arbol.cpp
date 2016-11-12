#include "Arbol.h"
#include <cstring>
#include <iostream>

Arbol::Arbol(){
  raiz = new Nodo();
  directorioActual = raiz;
  totalNodos = 0;
  ultimoID = 0;
}

void Arbol::insertarNodo(char* mnombre, bool directorio){
  Nodo *nuevoNodo = new Nodo(directorioActual, mnombre, ultimoID+1, directorio, 4096);
  directorioActual->setHijos(nuevoNodo);
}

Nodo* Arbol::buscarNodo(Nodo *nodoABuscar, char* mnombre){
  for(int i = 0; i < nodoABuscar->getHijos()->size(); i++){
    if(!strcmp(nodoABuscar->getHijos()->at(i)->getNombre(), mnombre)){
      std::cout << "Encontrado\n";
      return nodoABuscar->getHijos()->at(i);
    }
    if(nodoABuscar->getHijos()->at(i)->getHijos()->size() > 0){}
       buscarNodo(nodoABuscar->getHijos()->at(i), mnombre);
  }
  return NULL;
}

Nodo* Arbol::buscarNodo(char* mnombre){
  buscarNodo(raiz, mnombre);
}

void Arbol::eliminarNodo(char* mnombre){
  Nodo* padre = buscarNodo(mnombre)->getPadre();
  for(int i = 0; i < padre->getHijos()->size(); i++){
    if(!strcmp(padre->getHijos()->at(i)->getNombre(), mnombre)){
      padre->getHijos()->erase(padre->getHijos()->begin()+i);
    }
  }
}

Nodo* Arbol::getRoot(){return raiz;}
Nodo* Arbol::getDirectorioActual(){return directorioActual;}
void Arbol::setDirectorioActual(char* mnombre){
  directorioActual = buscarNodo(mnombre);
}
