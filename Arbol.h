#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

class Nodo;

#include "Nodo.h"
#include <sys/stat.h>
#include <cstring>

class Arbol{
  Nodo* raiz;
  Nodo* directorioActual;
  int totalNodos;
  int ultimoID;
  Nodo* buscarNodo(Nodo *nodoABuscar, char* mnombre);
  Nodo* buscarNodo(Nodo *nodoABuscar, int mid);
public:
  Arbol();

  // Operaciones con los nodos
  Nodo* insertarNodo(char *mnombre, bool directorio);
  Nodo* buscarNodo(char* nombre);
  Nodo* buscarNodo(int mid);
  void modificarNodo(Nodo* aModificar, char* mnombre = NULL, off_t mtamano = -1);
  void eliminarNodo(char* mnombre);


  Nodo* getRoot();
  Nodo* getDirectorioActual();
  void setDirectorioActual(char* mnombre);

  void imprimir(Nodo* nodo, int tab);
};
#endif
