// Julián Toledano Díaz
// Sistemas Distribuidos

#pragma once
#include <string>

class Raid{
  int size;
public:
  Raid(bool esclavo);
  void format(int tamano);
  void writeBlock(int sector, char *bloque);
  void writeFile(std::string nombre, int *sectores, int size);
  void readBlock(int sector);
  void readFile(std::string nombre, int *bloques, int size);
  void setSize(int msize);
  int getSize();
};
