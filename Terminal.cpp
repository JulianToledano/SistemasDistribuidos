// Julián Toledano Díaz

#include "mpi.h"
#include "Arbol.h"
//#include "Raid.h"
#include "ComandosRemoto.h"
#include "ComandosLocal.h"
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <stdexcept>  // handle out_of_range error
#include <stdlib.h>

// Todos los comandos disponibles para trabajar con el
// sistema de ficheros.
enum comandos{Exit, ls,
              pwd,  cd,
              Mv,   cp,
              Mkdir,Touch,
              rm,   Rmdir,
              lls,  lpwd,
              lcd,  down,
              Lupload};

// Divide el string insertado por teclado y lo introduce
// en un vector para poder operar a través de un switch.
std::vector<std::string> dividirArgumentos(std::string linea);

// Inicializa un mapa con los comandos disponibles para operar
// con el sistema de ficheros.
void inicializarComandos(std::map<std::string, comandos>&com);

int main(){
  std::map<std::string, comandos>com;
  inicializarComandos(com);
  int rank;
  MPI_Status status;
  Arbol* directorioRemoto = new Arbol();
  //Raid *raid;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // Este bucle impide que los procesos esclavo se detengan
    if(rank == 0){
      char cwd[1024];
      std::string comando;
      std::cout << "Bienvenido al sistema de ficheros distribuido.\n";
      std::cout << "El directorio remoto actual es: " << directorioRemoto->getDirectorioActual()->getNombre();
      if(getcwd(cwd, sizeof(cwd)) != NULL)
        std::cout << "\nEl directorio local actual es: " << cwd << std::endl;
      else
        std::cout << "getcwd(). Error.";

      do{
        printWD(directorioRemoto, false); std::cout << "> ";
        std::cin.clear();
        getline(std::cin, comando);
        std::vector<std::string> argumentos = dividirArgumentos(comando);

        try{
          switch (com.at(argumentos[0])){
            case ls://if(argumentos.size() > 1)break;
                list(directorioRemoto);
                break;
            case pwd:
                printWD(directorioRemoto, true);
                break;
            case cd:
                changeDirectori(directorioRemoto, argumentos[1]);
                break;
            case Mv:
                mv(directorioRemoto,argumentos[1], argumentos[2]);
                break;
            case cp:
                copy(directorioRemoto, argumentos[1], argumentos[2]);
                break;
            case Mkdir:
                makeDir(directorioRemoto, argumentos[1]);
                break;
            case Touch:
                touch(directorioRemoto, argumentos[1]);
                break;
            case rm:
                //removeFich(directorioRemoto, argumentos[1], raid);
                break;
            case Rmdir:
                removeDir(directorioRemoto, argumentos[1]);
                break;
            case lls:
                localls();
                break;
            case lpwd:
                localpwd();
                break;
            case lcd:
                localcd(argumentos[1]);
                break;
            case Lupload:
                lupload(directorioRemoto, argumentos[1]);
                break;
            case down:
                download(directorioRemoto, argumentos[1]);
                break;
            case Exit:
                // Enviamos codigo -1 a los esclavos.
                int codigo = -1;
              //  for(int i = 1; i < 5; i++)
                  MPI_Send(&codigo,1,MPI_INT,1,0,MPI_COMM_WORLD);
                std::cout << "Adiós\n";
                directorioRemoto->guardarArbol(directorioRemoto->getRoot());
          }
      }catch(std::out_of_range e){
        std::cout << "Error de sintaxis: " << argumentos[0] << "\n";
      }
      argumentos.clear();
      }while(comando != "exit");
    }

  MPI_Finalize();
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
  com.insert(std::pair<std::string, comandos>("mv", Mv));
  com.insert(std::pair<std::string, comandos>("cp", cp));
  com.insert(std::pair<std::string, comandos>("mkdir", Mkdir));
  com.insert(std::pair<std::string, comandos>("touch", Touch));
  com.insert(std::pair<std::string, comandos>("rm", rm));
  com.insert(std::pair<std::string, comandos>("rmdir", Rmdir));
  com.insert(std::pair<std::string, comandos>("lls", lls));
  com.insert(std::pair<std::string, comandos>("lpwd", lpwd));
  com.insert(std::pair<std::string, comandos>("lcd", lcd));
  com.insert(std::pair<std::string, comandos>("lupload", Lupload));
  com.insert(std::pair<std::string, comandos>("download", down));
}
