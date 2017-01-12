// Julián Toledano Díaz

#pragma once
#include <string>
#include "Nodo.h"

class Raid{
  int size;
public:
  Raid(bool esclavo);
  void format(int tamano);
  void writeBlock(int sector, char *bloque);
  void writeFile(std::string nombre, int *sectores, int size);
  void readBlock(int bloque);
  void readFile(std::string nombre, int *bloques, int size);
  void setSize(int msize);
  int getSize();
};
