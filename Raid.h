#pragma once
#include <string>
#include "Nodo.h"

class Raid{
public:
  Raid();
  // Copiar 1 bloque
  void writeBlock(std::string nombre, int count, Nodo *nodo);
  void liberarBloque(int n);
  //void readBlock();
  void writeFile(std::string nombre, size_t mtamano, Nodo *nodo);
  //void reafFile();
  void format(int tamano);
};
