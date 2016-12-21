#include "Raid.h"
#include "sys/stat.h"
#include <iostream>
#include <fstream>
// Comprobar que funciona el sistema raid antes de tocar las funciones
// lupload, etc.

int main(){

  struct stat st;
  Raid *test = new Raid();
  if(stat("Main.cpp", &st) == 0)
    test->writeFile("Main.cpp", st.st_size);
  //if(stat("Nodo.cpp", &st) == 0)
  //  test->writeFile("Nodo.cpp", st.st_size);
  return 0;
}
