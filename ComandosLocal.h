#include "Arbol.h"
#include <stdlib.h>
#include <string>
#include <unistd.h> // Llamada a chdir

void localls(){
  system("ls -l");
}

void localpwd(){
  system("pwd");
}

void localcd(std::string directorio){
  char* comando = new char(directorio.size() + 1);
  memcpy(comando, directorio.c_str(), directorio.size() + 1);
  chdir(comando);
  delete comando;
}
