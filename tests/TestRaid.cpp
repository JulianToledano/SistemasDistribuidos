#include "Raid.h"
#include "sys/stat.h"
#include <iostream>
#include <fstream>
// Comprobar que funciona el sistema raid antes de tocar las funciones
// lupload, etc.

int main(){

  struct stat st;
  Raid *test = new Raid();
  if(stat("rrr.txt", &st) == 0)
    test->writeFile(st.st_size);
  return 0;
}
