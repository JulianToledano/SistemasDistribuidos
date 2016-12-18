#include "Raid.h"
#include <fstream>
#include <iostream>

Raid::Raid(){
  format(32000);
}
// Tal vez sea innecesario rellenar sectoreslibres con numeros de 6 bytes
// Ya que siempre hay que iterar a través de todo el archivo

void Raid::format(int tamano){
  std::fstream libres("sectoresLibres1.dat", std::ios::out);
  if(libres.is_open()){
    // Todos los numeros con una longitud de 6 bytes. De esta manera es fácil
    // acceder (n * m - 6)
    for(int i = 1; i <= tamano; i++){
      if(i < 10)
      libres << "0000" << i;
    else if(i < 100)
      libres << "000" << i;
    else if(i < 1000)
      libres << "00" << i;
    else if(i < 10000)
      libres << "0" << i;
    else
      libres << i;
    libres << "\n";
    }
    libres.close();
  }
  std::fstream disco1("disco1.dat", std::ios::out | std::ios::binary);
  disco1.close();
}

void Raid::writeBlock(std::string nombre, int x){
  std::fstream f("rrr.txt", std::ios::in | std::ios::binary);
  std::fstream r("disco1.dat", std::ios::out | std::ios::app);

  char buffer[1024];
  f.seekg(1024*x);
    f.read(buffer, sizeof(buffer));
    r << buffer;
  f.close();
  r.close();



  // 2ª parte
  std::fstream temp("temp.dat", std::ios::out);
  std::fstream disc("sectoresLibres1.dat", std::ios::in);
  if(disc.is_open()){
    int sector;
    bool sectorEncontrado = false;

    for(int i = 1; i <= 32000; i++){
      disc >> sector;
      // Comprobamos hasta encontrar el primero de la lista distinto de cero.
      if(!sectorEncontrado && sector != 0) {
        temp << "00000";
        sectorEncontrado = true;
      }
      else if(sector == 0)
        temp << "00000";
      else{
        if(sector < 10)
        temp << "0000" << sector;
      else if(sector < 100)
        temp << "000" << sector;
      else if(sector < 1000)
        temp << "00" << sector;
      else if(sector < 10000)
        temp << "0" << sector;
      else
        temp << sector;
      }
      temp << "\n";
    }
  }else
    std::cout << "Error.";

  remove("sectoresLibres1.dat");
  rename("temp.dat", "sectoresLibres1.dat");
  temp.close();
  disc.close();
}
