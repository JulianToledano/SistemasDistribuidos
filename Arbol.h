// Julián Toledano Díaz
// Sistemas Distribuidos

#ifndef NODO_H
#define NODO_H

class Nodo;

#include "Nodo.h"
#include <sys/stat.h>
#include <cstring>

class Arbol{
  Nodo* raiz;
  Nodo* directorioActual;
  int totalNodos;
  int ultimoID;
public:
  Arbol();
  // Operaciones con los nodos
  Nodo* insertarNodo(char *mnombre, bool directorio, off_t mtamano);
  Nodo* buscarNodo(char* nombre);
  Nodo* buscarNodo(int mid);
  Nodo* buscarNodo(Nodo *nodoABuscar, char* mnombre);
  Nodo* buscarNodo(Nodo *nodoABuscar, int mid);
  void modificarNodo(Nodo* aModificar, char* mnombre = NULL, off_t mtamano = -1);
  void eliminarNodo(char* mnombre);


  Nodo* getRoot();
  Nodo* getDirectorioActual();
  void setDirectorioActual(char* mnombre);
  void setDirectorioActual(Nodo* nodo);
  void imprimir(Nodo* nodo, int tab); // Usado únicamente en los tests
  void guardarArbol(Nodo* nodo);
  void cargarArbol(Nodo* nodo, int n);
  void recur(Nodo *nodo, int nivel);
  ~Arbol();
};
#endif
