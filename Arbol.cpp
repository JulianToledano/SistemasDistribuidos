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
Nodo* Arbol::buscarNodo(char* mnombre){
  for(int i = 0; i < raiz->getHijos()->size(); i++){
    if(strcmp(raiz->getHijos()->at(i)->getNombre(), mnombre) == 0){
      return raiz->getHijos()->at(i);
    }
    if(raiz->getHijos()->at(i)->getHijos()->size() > 0){}
    //  buscarNodo(mnombre,raiz->getHijos()->at(i).getHijos());
  }
  std::cout << "Error al buscar";
  return NULL;
}
Nodo* Arbol::getRoot(){return raiz;}
Nodo* Arbol::getDirectorioActual(){return directorioActual;}
void Arbol::setDirectorioActual(char* mnombre){


}
