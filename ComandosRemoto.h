#include "Arbol.h"
#include "Nodo.h"
#include <cstring>
#include <iostream>

// Comando ls
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

// Imprime el directorio actual de trabajo.
// saltoLinea es
void printWD(Arbol* arbol, bool saltoLinea){
  std::vector<std::string> pwd;
  Nodo* actual = arbol->getDirectorioActual();
  // Mientras el nombre del nodo sea distinto de root,
  // introducimos todos los nombres de directorios hasta llegar a este
  while(strcmp(actual->getNombre(), "/root")){
    pwd.push_back(actual->getNombre());
    actual = actual->getPadre();
  };
  std::cout << "/root";
  // Recorremos el vector con los nombres de todos los directorios
  for(int i = pwd.size() - 1; i >= 0; i--)
    std::cout << "/" << pwd[i];
  if(saltoLinea)std::cout << "\n";
}

// Comando cd
void changeDirectori(Arbol* arbol, std::string directorio){
  // Si se quiere acceder a la raiz
  if(directorio == "/"){
    arbol->setDirectorioActual(arbol->getRoot());
    return;
  }
  // Si se quiere acceder al directorio anterir '..' y no nos encontrmos en el directorio raiz.
  else if(directorio == ".." && strcmp(arbol->getDirectorioActual()->getNombre(), "/root")){
    arbol->setDirectorioActual(arbol->getDirectorioActual()->getPadre());
    return;
  }
  char* dir = new char(directorio.size() + 1);
  memcpy(dir, directorio.c_str(), directorio.size() + 1);
  // Si al directorio que se quiere acceder tiene el mismo nombre que el actual '/root/test --> /root/test/test'
  if(!strcmp(arbol->getDirectorioActual()->getNombre(), dir)){
    // Recorremos el vector de hijos
    for(int i = 0; i < arbol->getDirectorioActual()->getHijos()->size(); i++)
      // Si encontramos el nodo con el mismo nombre que el padre realizamos el cambio de directorio actual
      if(!strcmp(dir,arbol->getDirectorioActual()->getHijos()->at(i)->getNombre())){
        arbol->setDirectorioActual(arbol->getDirectorioActual()->getHijos()->at(i));
        delete dir;
        return;
      }
  }
  // Si el directorio no existe
  else if(arbol->buscarNodo(arbol->getDirectorioActual(), dir) == NULL){
    std::cout << "Error en cd: " << directorio << " no existe.\n";
    delete dir;
    return;
  }
  // Si se encuentra el directorio
  else
    arbol->setDirectorioActual(dir);
    delete dir;
}

// Creacion de directorio
void makeDir(Arbol *arbol, std::string directorio){
  char* dir = new char(directorio.size() + 1);
  memcpy(dir, directorio.c_str(), directorio.size() + 1);
  arbol->insertarNodo(dir, true, 4096);
  delete dir;
}

void mv(Arbol* arbol, std::string nombre1, std::string nombre2){
    char* dir1 = new char(nombre1.size() + 1);
    memcpy(dir1, nombre1.c_str(), nombre1.size() + 1);
    char* dir2 = new char(nombre2.size() + 1);
    memcpy(dir2, nombre2.c_str(), nombre2.size() + 1);
    Nodo* acambiar = arbol->buscarNodo(arbol->getDirectorioActual(), dir1);
    if(acambiar == NULL){
      std::cout << "Error\n";
      return;
    }
    arbol->modificarNodo(acambiar, dir2);
    delete dir1;
    delete dir2;
}

// Error al intentar eliminar un directorio que tiene el mismo nombre que su padre.
// Problema reside en arbol.buscarNodo(nodo, char*)
void removeDir(Arbol* arbol, std::string directorio){
  char* dir = new char(directorio.size() + 1);
  memcpy(dir, directorio.c_str(), directorio.size() + 1);
  if(arbol->buscarNodo(arbol->getDirectorioActual(), dir)->esDirectorio()){
    if(arbol->buscarNodo(arbol->getDirectorioActual(), dir)->getHijos()->size() > 0)
      std::cout << "Error en rmdir: " << directorio << " contiene subdirecotios.\n";
    else
      arbol->eliminarNodo(dir);
    }
  else
    std::cout << "Error en rmdir: " << directorio << " es un fichero.\n";
  delete dir;
}

// rm
void removeFich(Arbol* arbol, std::string fichero){
  char* fich = new char(fichero.size() + 1);
  memcpy(fich, fichero.c_str(), fichero.size() + 1);
  if(!arbol->buscarNodo(arbol->getDirectorioActual(), fich)->esDirectorio())
    arbol->eliminarNodo(fich);
  else
    std::cout << "Error en rm: " << fichero << " es un directorio, no un fichero.\n";
  delete fich;
}

// No es necesario retocar ya que son los mismos contenidos que la Copiar
// Qué pasa si se borra uno?
void copy(Arbol* arbol, std::string origen, std::string destino){
  char* ori = new char(origen.size() + 1);
  memcpy(ori, origen.c_str(), origen.size() + 1);
  char* dest = new char(destino.size() + 1);
  memcpy(dest, destino.c_str(), destino.size() + 1);
  Nodo* nodoOrigen = arbol->buscarNodo(arbol->getDirectorioActual(), ori);
  Nodo* nodoDestino = arbol->buscarNodo(arbol->getDirectorioActual(), dest);
  // El único caso no permitido es que el origen sea un directorio y el destino un archivo,
  // en cualquier otro caso se puede realizar la operación.
  if(nodoOrigen->esDirectorio() && !nodoDestino->esDirectorio()){}
  else
    nodoDestino->setHijos(nodoOrigen);
  delete ori;
  delete dest;
}
