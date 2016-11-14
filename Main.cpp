
#include "Arbol.h"
#include <iostream>
#include <unistd.h>
#include <map>
#include <string>
#include<sstream>
#include <stdexcept>  // handle out_of_range error
#include <stdlib.h>

// Todos los comandos disponibles para trabajar con el
// sistema de ficheros.
enum comandos{Exit, ls,
              pwd,  cd,
              mv,   cp,
              Mkdir,rm,
              Rmdir};

// Divide el string insertado por teclado y lo introduce
// en un vector para poder operar a través de un switch.
std::vector<std::string> dividirArgumentos(std::string linea);

// Inicializa un mapa con los comandos disponibles para operar
// con el sistema de ficheros.
void inicializarComandos(std::map<std::string, comandos>&com);

int main(){
  std::map<std::string, comandos>com;
  inicializarComandos(com);

  Arbol* directorioRemoto = new Arbol();

  char cwd[1024];
  std::string comando;

  std::cout << "Bienvenido al sistema de ficheros distribuido.\n";
  std::cout << "El directorio remoto actual es: " << directorioRemoto->getDirectorioActual()->getNombre();
  if(getcwd(cwd, sizeof(cwd)) != NULL)
    std::cout << "\nEl directorio local actual es: " << cwd << std::endl;
  else
    std::cout << "getcwd(). Error.";

  do{
    std::cout << directorioRemoto->getDirectorioActual()->getNombre() << "> ";

    getline(std::cin, comando);
    std::vector<std::string> argumentos = dividirArgumentos(comando);// = dividirArgumentos(comando);

    try{
      switch (com.at(argumentos[0])){
        case ls:
          break;
        case pwd:
          break;
        case cd:
          break;
        case mv:
          break;
        case cp:
          break;
        case Mkdir:
          break;
        case rm:
            break;
        case Rmdir:
            break;
        case Exit:
            std::cout << "Adiós\n";
      }
  }catch(std::out_of_range e){
    std::cout << "Error de sintaxis: " << argumentos[0] << "\n";
  }
  argumentos.clear();
  std::cin.clear();
  }while(comando != "exit");

  delete directorioRemoto;
  return 0;
}

std::vector<std::string> dividirArgumentos(std::string linea){
  std::vector<std::string> resultado;
  std::string temp;
  std::stringstream s(linea);
  while(s>>temp)
    resultado.push_back(temp);
  return resultado;
}

void inicializarComandos(std::map<std::string, comandos>&com){
  com.insert(std::pair<std::string, comandos>("exit", Exit));
  com.insert(std::pair<std::string, comandos>("ls", ls));
  com.insert(std::pair<std::string, comandos>("pwd", pwd));
  com.insert(std::pair<std::string, comandos>("cd", cd));
  com.insert(std::pair<std::string, comandos>("mv", mv));
  com.insert(std::pair<std::string, comandos>("cp", cp));
  com.insert(std::pair<std::string, comandos>("mkdir", Mkdir));
  com.insert(std::pair<std::string, comandos>("rm", rm));
  com.insert(std::pair<std::string, comandos>("rmdir", Rmdir));
}