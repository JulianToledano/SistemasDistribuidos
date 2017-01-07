// Julián Toledano Díaz

#pragma once
#include <string>
#include "Nodo.h"

class Raid{
public:
  Raid();
  void format(int tamano);
  // Copiar 1 bloque
  void writeBlock(std::string nombre, int count, int disco, Nodo *nodo);
  // Función que libera un sector al ser llamada desde rm
  void liberarBloque(int n);
  void writeFile(std::string nombre, size_t mtamano, Nodo *nodo);
  // n secor que ocupa el bloque que debemos leer
  void readBlock(int n);
  void readFile(Nodo *nodo);
};
