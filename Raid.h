// Julián Toledano Díaz

#pragma once
#include <string>
#include "Nodo.h"

class Raid{
  int size;
public:
  Raid(bool esclavo);
  void format(int tamano);
  // Escribe 1024 bytes en disco.dat
  void writeBlock(int sector, char *bloque);
  // Copia un archivo entre los distintos disco.dat
  void writeFile(std::string nombre, int *sectores, int size);
  // Función que libera un sector al ser llamada desde rm
  void liberarBloque(int n);
  // n secor que ocupa el bloque que debemos leer
  void readBlock(int n);
  void readFile(Nodo *nodo);
  void setSize(int msize);
  int getSize();
};
