#include "Raid.h"
#include <fstream>
#include <iostream>

Raid::Raid(){
  format(32000);
}

void Raid::format(int tamano){
  std::fstream libres("sectoresLibres1.dat", std::ios::out);
  if(libres.is_open()){
    for(int i = 1; i <= tamano; i++){
            libres << i;
            libres << "\n";
    }
    libres.close();
  }
  std::fstream disco1("disco1.dat", std::ios::out | std::ios::binary);
  disco1.close();
}

void Raid::writeBlock(){


}
