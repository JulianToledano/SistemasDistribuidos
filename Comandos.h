#include "Arbol.h"
#include "Nodo.h"
#include <cstring>
#include <iostream>

void list(Arbol* arbol){
  for(int i = 0; i < arbol->getDirectorioActual()->getHijos()->size(); i++){
    if( arbol->getDirectorioActual()->getHijos()->at(i)->esDirectorio())
      std::cout << "DIR";
    else
      std::cout << "  ";
    std::cout << arbol->getDirectorioActual()->getHijos()->at(i)->getNombre() << "   " << arbol->getDirectorioActual()->getHijos()->at(i)->getTamano();
    std::cout << "   " << arbol->getDirectorioActual()->getHijos()->at(i)->getUltimaModificacion() << "\n";
  }
  std::cout << arbol->getDirectorioActual()->getHijos()->size() << " elementos en directorio remoto '" << arbol->getDirectorioActual()->getNombre() << "' ocupando un total de " << " bytes\n";
}

void printWD(Arbol* arbol){
  std::vector<std::string> pwd;
  Nodo* actual = arbol->getDirectorioActual();
  while(strcmp(actual->getNombre(), "/root")){
    std::cout << actual->getNombre() << "/";
    actual = actual->getPadre();
  };
  std::cout << actual->getNombre();
}

void changeDirectori(Arbol* arbol, std::string directorio){
  if(directorio == "/")arbol->setDirectorioActual("/root");
  else if(directorio == ".." && strcmp(arbol->getDirectorioActual()->getNombre(), "/root"))
    arbol->setDirectorioActual(arbol->getDirectorioActual()->getPadre());
  else{
    char* dir = new char(directorio.size() + 1);
    memcpy(dir, directorio.c_str(), directorio.size() + 1);
    arbol->setDirectorioActual(dir);
    delete dir;
  }
}

void makeDir(Arbol *arbol, std::string directorio){
  char* dir = new char(directorio.size() + 1);
  memcpy(dir, directorio.c_str(), directorio.size() + 1);
  arbol->insertarNodo(dir, true);
  delete dir;
}
