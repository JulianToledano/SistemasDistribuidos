// Julián Toledano Díaz
// Sistemas Distribuidos

#ifndef ARBOL_H
#define ARBOL_H

class Arbol;

#include "Arbol.h"
#include <sys/stat.h>
#include <vector>
#include <cstring>
#include <time.h>

#define MAX 25

class Nodo{
  Arbol* esteArbol;
  Nodo* padre;
  std::vector<Nodo*>* hijos;
  char nombre[MAX];
  int id;
  int nivel;
  bool directorio;
  off_t tamano;
  time_t ultimaModificacion;
  int numBloques;
  int *bloques;
public:
  // Constructores
  Nodo();
  Nodo(Arbol* arbol);
  Nodo(Arbol* arbol, Nodo *mpadre, char *mnombre, int mid, bool mdirectorio, off_t mtamano);
  // Métodos get
  Nodo* getPadre();
  std::vector<Nodo*>* getHijos();
  char* getNombre();
  int getId();
  int getNivel();
  bool esDirectorio();
  off_t getTamano();
  time_t getUltimaModificacion();
  int getNumBloques();
  int* getBloques();
  // Métodos set
  void setNombre(char *mnombre);
  void setId(int mid);
  void setNivel(int mid);
  void setDirectorio(bool mdirectorio);
  void setTamano(off_t mtamano);
  void setModificacion(time_t multimaModificacion);
  void setUltimaModificacion();
  void setHijos(Nodo *nuevoNodo);
  void setArbol(Arbol* arbol);
  void setNumBloques(int numBloques);
  void setBloques(int *bloques);
  void anadirBloques(int sector);
};
#endif
