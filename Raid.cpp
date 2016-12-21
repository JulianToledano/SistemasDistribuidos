#include "Raid.h"
#include <fstream>
#include <iostream>

Raid::Raid(){
  format(32000);
}

void Raid::format(int tamano){
  std::fstream libres("sectoresLibres1.dat", std::ios::out | std::ios::app);
  if(libres.is_open()){
    for(int i = 1; i <= tamano; i++){
      libres << i;
      libres << "\n";
    }
    libres.close();
  }
  std::fstream disco1("disco1.dat", std::ios::out | std::ios::app | std::ios::binary);
  disco1.close();
}

void Raid::writeBlock(std::string nombre, int count){
  FILE *read = fopen(nombre.c_str(), "rb");
  FILE *write = fopen("disco1.dat", "ab+");
  char buffer[1024] ={};
  fseek(read, 1024*count, SEEK_SET);
  fread(buffer, 1, 1024, read);
  // Si al leer el archivo llega al final de éste y no rellena buffer
  // lo rellenamos de basura
  for(int i = 0; i < 1024; i++) /* MEJORAR*/
    if(buffer[i] == '\0') buffer[i] ='0';
  fwrite(buffer, 1, 1024, write);
  fclose(read);
  fclose(write);

  // 2ª parte
  std::fstream temp("temp.dat", std::ios::out | std::ios::binary);
  std::fstream disc("sectoresLibres1.dat", std::ios::in);

  if(disc.is_open()){
    int sector;
    bool sectorEncontrado = false;
    for(int i = 1; i <= 32000; i++){
      disc >> sector;
      // Comprobamos hasta encontrar el primero de la lista distinto de cero.
      if(!sectorEncontrado && sector != 0) {
        temp << "0";
        sectorEncontrado = true;
      }
      else
        temp << sector;
      temp << "\n";
      }
  }else
    std::cout << "Error.";

  remove("sectoresLibres1.dat");
  rename("temp.dat", "sectoresLibres1.dat");
  temp.close();
  disc.close();
}

void Raid::writeFile(std::string nombre, size_t mtamano){
  float size = (float)mtamano/(float)1024;
  // Comprueba que size es un numero entero .00 si es así solo es necesario
  // iterar size veces, de lo contrario es necesario size+1 veces
  if(size-(int)size == 0)
    for(float i = 0.0; i < size; i++)
      writeBlock(nombre,i);
  else
    for(float i = 0.0; i <= size; i++)
      writeBlock(nombre,i);
}
