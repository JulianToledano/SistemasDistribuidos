#include "Arbol.h"
#include <cstring>
#include <iostream>

Arbol::Arbol(){
  raiz = new Nodo();
  directorioActual = raiz;
  totalNodos = 0;
  ultimoID = 0;
}
// Se inserta en el directorio alctual. Se sobreentiende que antes existirá un
// control para no poder entrar a ficheros.
Nodo* Arbol::insertarNodo(char* mnombre, bool directorio){
  // Comprobamos que no existe un hijo con ese mismo nombre
  for(int i = 0; i < directorioActual->getHijos()->size(); i++)
    if(!strcmp(directorioActual->getHijos()->at(i)->getNombre(), mnombre)){
      std::cout << "Error. Ya existe con es nombre.\n";
      return (NULL);
    }
  Nodo *nuevoNodo = new Nodo(directorioActual, mnombre, ultimoID+1, directorio, 4096);
  directorioActual->setHijos(nuevoNodo);
  totalNodos += 1;
  ultimoID += 1;
  return nuevoNodo;
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

Nodo* Arbol::buscarNodo(Nodo *nodoABuscar, int mid){
  if(nodoABuscar->getId() == mid)return nodoABuscar;
  else{
    for(int i = 0; i < nodoABuscar->getHijos()->size(); i++){
      Nodo *resultado = buscarNodo(nodoABuscar->getHijos()->at(i), mid);
      if(resultado != NULL)return resultado;
    }
  }
  return (NULL);
}

Nodo* Arbol::buscarNodo(char* mnombre){
  if(!strcmp(mnombre, "/"))return raiz;
  buscarNodo(raiz, mnombre);
}
Nodo* Arbol::buscarNodo(int mid){
  if(mid == 0)return raiz;
  buscarNodo(raiz, mid);
}

void Arbol::modificarNodo(Nodo *aModificar, char* mnombre, off_t mtamano){
  if(mnombre == NULL && mtamano <= 0)return;
  else{
    if(mnombre != NULL)
      aModificar->setNombre(mnombre);
    if(mtamano > 0)
      aModificar->setTamano(mtamano);
    aModificar->setUltimaModificacion();
  }
}

void Arbol::eliminarNodo(char* mnombre){
  // Tal vez sea mejor cambiarlo por el directorio actual.
  // De esta manera el comando rm afecta solo al directorio en el que nos encontramos
  Nodo* buscado = buscarNodo(directorioActual, mnombre);
  if(buscado->getHijos()->size() > 0) std::cout << "Contiene subdirectorios o ficheros, no se puede eliminar.\n";
  else{
    for(int i = 0; i < buscado->getPadre()->getHijos()->size(); i++){
      if(!strcmp(buscado->getPadre()->getHijos()->at(i)->getNombre(), mnombre))
        buscado->getPadre()->getHijos()->erase(buscado->getPadre()->getHijos()->begin()+i);
        totalNodos -= 1;
    }
  }
}

Nodo* Arbol::getRoot(){return raiz;}
Nodo* Arbol::getDirectorioActual(){return directorioActual;}
void Arbol::setDirectorioActual(char* mnombre){
  // Nos aseguramos de que el directorio es realmente un directorio
  if(buscarNodo(mnombre)->esDirectorio())
    directorioActual = buscarNodo(mnombre);
  else
    std::cout << "Error. Intenta entrar en un archivo, no un directorio.\n";
}

void Arbol::imprimir(Nodo* nodo, int tab){
  for(int i = 0; i < nodo->getHijos()->size(); i++){
    for(int j = 0; j < tab; j++)std::cout << "  ";
    std::cout << nodo->getHijos()->at(i)->getNombre() << " ID: "<< nodo->getHijos()->at(i)->getId() << " Nivel: "<< nodo->getHijos()->at(i)->getNivel()<<std::endl;
    if(nodo->getHijos()->at(i)->getHijos()->size() > 0){
      std::cout << "  ";
      imprimir(nodo->getHijos()->at(i),tab+1);
    }
  }
}
