// Julián Toledano Díaz
#include "Arbol.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

Arbol::Arbol(){
  struct stat st;
  if(stat("arbol.dat", &st) == 0){
    cargarArbol(NULL,0);
    directorioActual = raiz;
    ultimoID = 0;
    remove("arbol.dat");
  }
  else{
    raiz = new Nodo(this);
    directorioActual = raiz;
    totalNodos = 0;
    ultimoID = 0;
  }
}
// Se inserta en el directorio alctual. Se sobreentiende que antes existirá un
// control para no poder entrar a ficheros.
Nodo* Arbol::insertarNodo(char* mnombre, bool directorio, off_t mtamano){
  // Comprobamos que no existe un hijo con ese mismo nombre
  for(int i = 0; i < directorioActual->getHijos()->size(); i++)
    if(!strcmp(directorioActual->getHijos()->at(i)->getNombre(), mnombre)){
    //  std::cout << "Error. Ya existe con es nombre.\n";
      return (NULL);
    }
  Nodo *nuevoNodo = new Nodo(this, directorioActual, mnombre, ultimoID+1, directorio, mtamano);
  directorioActual->setHijos(nuevoNodo);
  totalNodos += 1;
  ultimoID += 1;
  return nuevoNodo;
}

// Causa problemas cuando se busca un nodo que tiene el mismo nombre que el padre,
// que es el directorio actual.
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
  return buscarNodo(raiz, mnombre);
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
  Nodo* buscado = buscarNodo(directorioActual, mnombre);
  //if(buscado->getHijos()->size() > 0) std::cout << "Contiene subdirectorios o ficheros, no se puede eliminar.\n";
//  else{
    for(int i = 0; i < buscado->getPadre()->getHijos()->size(); i++){
      if(!strcmp(buscado->getPadre()->getHijos()->at(i)->getNombre(), mnombre)){
        buscado->getPadre()->getHijos()->erase(buscado->getPadre()->getHijos()->begin()+i);
        totalNodos -= 1;
      }
    //}
  }
}

Nodo* Arbol::getRoot(){return raiz;}
Nodo* Arbol::getDirectorioActual(){return directorioActual;}

void Arbol::setDirectorioActual(char* mnombre){
  // Nos aseguramos de que el directorio existe
  if(buscarNodo(directorioActual, mnombre) == NULL){}
  // Nos aseguramos de que el directorio es realmente un directorio
  else if(buscarNodo(directorioActual, mnombre)->esDirectorio())
    directorioActual = buscarNodo(directorioActual, mnombre);
  else
    std::cout << "Error. Intenta entrar en un archivo, no un directorio.\n";
}

void Arbol::setDirectorioActual(Nodo* nodo){
  directorioActual = nodo;
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

void Arbol::guardarArbol(Nodo *nodo){
  std::fstream f("arbol.dat", std::ios::out | std::ios::app | std::ios::binary);
  f << nodo->getNivel() << '\n';
  f << nodo->getNombre() << '\n';
  f << nodo->getId() << '\n';
  f << nodo->esDirectorio() << '\n';
  f << nodo->getTamano() << '\n';
  f << nodo->getUltimaModificacion() << '\n';
  f << nodo->getNumBloques() << '\n';
  for(int i = 0; i < nodo->getNumBloques(); i++)
    f << nodo->getBloques()[i] << ' ';
  f << '\n';
  f.close();
  for(int i = 0; i < nodo->getHijos()->size(); i++)
    guardarArbol(nodo->getHijos()->at(i));

}

void Arbol::cargarArbol(Nodo *nodo, int n){
  std::fstream f("arbol.dat", std::ios::in);
  f.seekg(n, f.beg);
  int mnivel; f >> mnivel;
  std::string mnombre; f >> mnombre;
  char* nom = new char(mnombre.size() + 1);
  memcpy(nom, mnombre.c_str(), mnombre.size() + 1);
  int mid; f >> mid;
  bool dire; f >> dire;
  off_t tam; f >> tam;
  time_t ultmod; f >> ultmod;
  int numBloques; f >> numBloques;
  int *bloques = (int*)malloc(numBloques*sizeof(int));
  // Comprobamos que guarda bloques
  if(numBloques > 0){
    for(int i = 0; i < numBloques; i++)
      f >> bloques[i];
  }
  f.seekg(0, f.cur);
  int nn = f.tellg();
  f.seekg(0, f.end);
  int end = f.tellg();
  if(nn == end) return;
  // Si es la primera vez se carga la raiz.
  if(mnivel == 0){
    raiz = new Nodo(this);
    raiz->setTamano(tam);
    raiz->setModificacion(ultmod);
    raiz->setNombre(nom);
    f.close();
    cargarArbol(raiz, nn);
  }
  // En caso contrario recorremos el arbol
  else{
    this->setDirectorioActual(nodo);
    // Si el nivel leído no es uno superior al anterior hay que encontrar a su padre
    if(mnivel - 1 != nodo->getNivel())
      recur(nodo, mnivel);
      this->insertarNodo(nom, dire, tam);
      this->setDirectorioActual(this->getDirectorioActual()->getHijos()->at(this->getDirectorioActual()->getHijos()->size() - 1));
      this->getDirectorioActual()->setId(mid);
      this->getDirectorioActual()->setModificacion(ultmod);
      this->getDirectorioActual()->setNumBloques(numBloques);
      this->getDirectorioActual()->setBloques(bloques);
      cargarArbol(this->getDirectorioActual(), nn);
      f.close();
  }
}

void Arbol::recur(Nodo *nodo, int nivel){
  this->setDirectorioActual(nodo->getPadre());
  if(nivel - 1 == this->getDirectorioActual()->getNivel()) return;
  else recur(this->getDirectorioActual(), nivel);
}

Arbol::~Arbol(){
  delete raiz;
}
