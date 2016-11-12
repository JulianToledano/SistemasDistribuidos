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
  if(!strcmp(nodoABuscar->getNombre(), mnombre))return nodoABuscar;
  else{
    for(int i = 0; i < nodoABuscar->getHijos()->size(); i++){
      Nodo *resultado = buscarNodo(nodoABuscar->getHijos()->at(i), mnombre);
      if(resultado != NULL)return resultado;
    }
  }
  return (NULL);
}
/*
Nodo* Arbol::buscarNodo(Nodo *nodoABuscar, char* mnombre){
  if(!strcmp(nodoABuscar->getNombre(), mnombre))return nodoABuscar;
  else{
    bool encontrado = false;
    int i = 0;
    while(!encontrado && i < nodoABuscar->getHijos()->size()){
      buscarNodo(nodoABuscar->getHijos()->at(i), mnombre);
      i++;
    }
  }
  if(encontrado)return nodoABuscar;
  return NULL;
}*/

Nodo* Arbol::buscarNodo(char* mnombre){
  if(!strcmp(mnombre, "/"))return raiz;
  buscarNodo(raiz, mnombre);
}

void Arbol::eliminarNodo(char* mnombre){
  // Tal vez sea mejor cambiarlo por el directorio actual.
  // De esta manera el comando rm afecta solo al directorio en el que nos encontramos
  Nodo* padre = buscarNodo(mnombre)->getPadre();
  for(int i = 0; i < padre->getHijos()->size(); i++){
    if(!strcmp(padre->getHijos()->at(i)->getNombre(), mnombre))
      padre->getHijos()->erase(padre->getHijos()->begin()+i);
  }
}

Nodo* Arbol::getRoot(){return raiz;}
Nodo* Arbol::getDirectorioActual(){return directorioActual;}
void Arbol::setDirectorioActual(char* mnombre){
  directorioActual = buscarNodo(mnombre);
}

void Arbol::imprimir(Nodo* nodo){
    std::cout << "  ";
  for(int i = 0; i < nodo->getHijos()->size(); i++){
    std::cout << nodo->getHijos()->at(i)->getNombre() << std::endl;
    if(nodo->getHijos()->at(i)->getHijos()->size() > 0){
      std::cout << "  ";
      imprimir(nodo->getHijos()->at(i));
    }
  }
}
