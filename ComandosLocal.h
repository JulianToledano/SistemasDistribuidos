// Julián Toledano Díaz
#include <mpi.h>
#include "Arbol.h"
#include "Raid.h"
#include <stdlib.h>
#include <string>
#include <unistd.h> // Llamada a chdir
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>

void localls(){
  // Obtenemos el directoio actual de trabajo.
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  // Inicializamos una estructura DIR con todos los archivos de cwd.
  DIR *d;
  struct dirent *dir;
  struct stat st;
  d = opendir(cwd);
  // Mientras haya archivos obtenemos información sobre ellos con stat(char* path, stat* buf)
  while((dir = readdir(d)) != NULL)
    if(stat(dir->d_name, &st) == 0)
      std::cout << dir->d_name << "   " << st.st_size << "    " << st.st_mtime << "\n";
}

void localpwd(){
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  std::cout << cwd << "\n";
}

void localcd(std::string directorio){
  chdir(directorio.c_str());
}

// Función recursiva para subir los subdirectorios y archivos
void uploadRecursivo(Arbol* arbol, char* path, char* directorio);

void lupload(Arbol* arbol,std::string directorio){
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  char* dir = new char(directorio.size() + 1);
  memcpy(dir, directorio.c_str(), directorio.size() + 1);
  uploadRecursivo(arbol, cwd, dir);
}

// Comprueba si es un directoio o un archivo
bool esDirectorio(char* path, char *nombre);
// Devuelve el tamaño de un archivo o directorio
off_t tamano(char* path, char *nombre);

void uploadRecursivo(Arbol *arbol, char* path, char* directorio){
  Raid *raid = new Raid(false);
  char* barra = "/";
  char* pathCompleto = (char*)malloc(1 + strlen(path) + strlen(barra) + strlen(directorio));
  strcpy(pathCompleto, path);
  strcat(pathCompleto, barra);
  strcat(pathCompleto, directorio);
  DIR* dir;
  struct dirent* d;
  struct stat st;
  // Comprobamos si es un directorio
  if((dir = opendir(pathCompleto)) != NULL){
    if(stat(pathCompleto, &st) == 0){
      // Insertamos el nodo
      arbol->insertarNodo(directorio, true, st.st_size);
      // Cambiamos el nodo actual por el recientemente introducido para poder introducir sus hijos si los tuviera
      arbol->setDirectorioActual(directorio);
      // Mientras tenga hijos...
      while((d = readdir(dir)) != NULL){
        // Y no correspondan a los directorios . ..
        if(strcmp(d->d_name, "..") != 0 && strcmp(d->d_name, ".") != 0){
          // Guardamos el directorio actual
          Nodo* temp = arbol->getDirectorioActual();
          // Insertamos los hijos
          //En caso de ser un directorio
          if(esDirectorio(pathCompleto,d->d_name)){
            arbol->insertarNodo(d->d_name, true, tamano(pathCompleto,d->d_name));
            // Insertamos los hijos de los hijos
            uploadRecursivo(arbol, pathCompleto, d->d_name);
          }
          // En caso de ser un archivo
          else{
            char *file = (char*)malloc(1 +strlen(pathCompleto) + strlen(barra) + strlen(d->d_name));
            strcat(file, pathCompleto);
            strcat(file, barra);
            strcat(file, d->d_name);
            arbol->insertarNodo(d->d_name, false, tamano(pathCompleto, d->d_name));
            for(int i = 0; i < arbol->getDirectorioActual()->getHijos()->size(); i++){
              if(!strcmp(arbol->getDirectorioActual()->getHijos()->at(i)->getNombre(), d->d_name)){
                float numBloques = st.st_size/1024;
                if(numBloques-(int)numBloques == 0) numBloques += 1;
                  for(int j = 0; j < numBloques; j++){
                    // Se envia una peticion de bloques codigo 0
                    int codigo = 0;
                    MPI_Status status;
                    int bloque;
                    int esclavo = j%4+1;
                    MPI_Send(&codigo,1,MPI_INT,1,0,MPI_COMM_WORLD); //i%4+1 //******
                    MPI_Recv(&bloque,1,MPI_INT,1,0,MPI_COMM_WORLD,&status);//*********
                    arbol->getDirectorioActual()->getHijos()->at(i)->anadirBloques(bloque);
                  }// for j
                  raid->writeFile(file, arbol->getDirectorioActual()->getHijos()->at(i)->getBloques(),arbol->getDirectorioActual()->getHijos()->at(i)->getNumBloques());
              }// if strcmp
            }// for
          }
          // Devolvemos el nodo actual a su posición
          arbol->setDirectorioActual(temp);
        }
      }
    }
  // En caso de no ser un directorio simplemente lo introducimos
  }else{
    // 1º -> Creamos el nodo
    if(stat(pathCompleto, &st) == 0)
      arbol->insertarNodo(directorio, false, st.st_size);
    for(int i = 0; i < arbol->getDirectorioActual()->getHijos()->size(); i++)
      if(!strcmp(arbol->getDirectorioActual()->getHijos()->at(i)->getNombre(), directorio)){
        // 2º -> Averiguamos el numero de nodos
        float numBloques = st.st_size/1024;
        if(numBloques-(int)numBloques == 0) numBloques += 1;
        // 2.1 -> Guardamos los sectores libres en el array de nodos
        for(int j = 0; j < numBloques; j++){
          // Se envia una peticion de bloques codigo 0
          int codigo = 0;
          MPI_Status status;
          int bloque;
          int esclavo = j%4+1;
          MPI_Send(&codigo,1,MPI_INT,1,0,MPI_COMM_WORLD); //i%4+1 //******
          MPI_Recv(&bloque,1,MPI_INT,1,0,MPI_COMM_WORLD,&status);//*********
          arbol->getDirectorioActual()->getHijos()->at(i)->anadirBloques(bloque);
        }
        //std::cout << "antes de write\n";
        raid->writeFile(pathCompleto, arbol->getDirectorioActual()->getHijos()->at(i)->getBloques(),arbol->getDirectorioActual()->getHijos()->at(i)->getNumBloques());
        //std::cout << "despues de write\n";
      }

  }
}
off_t tamano(char* path, char *nombre){
  char* barra = "/";
  char* pathCompleto = (char*)malloc(1 + strlen(path) + strlen(barra) + strlen(nombre));
  strcpy(pathCompleto, path);
  strcat(pathCompleto, barra);
  strcat(pathCompleto, nombre);
  struct stat st;
  if(stat(pathCompleto, &st) == 0)
    return st.st_size;
  return -1;
}

bool esDirectorio(char* path, char *nombre){
  char* barra = "/";
  char* pathCompleto = (char*)malloc(1 + strlen(path) + strlen(barra) + strlen(nombre));
  strcpy(pathCompleto, path);
  strcat(pathCompleto, barra);
  strcat(pathCompleto, nombre);
  struct stat st;
  if(stat(pathCompleto, &st) == 0)
    if(S_ISDIR(st.st_mode))
      return true;
  return -false;
}

void download(Arbol *arbol, std::string nombre){
  char *nom = new char(nombre.size() + 1);
  memcpy(nom, nombre.c_str(), nombre.size() + 1);
  arbol->buscarNodo(nom);
  Raid *raid = new Raid(false);
  raid->readFile(nombre, arbol->buscarNodo(nom)->getBloques(), arbol->buscarNodo(nom)->getNumBloques());
}
