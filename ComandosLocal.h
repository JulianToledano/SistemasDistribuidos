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
void uploadRecursivo(Arbol* arbol, char* path, char* directorio, Raid *raid);

void lupload(Arbol* arbol,std::string directorio, Raid *raid){
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  char* dir = new char(directorio.size() + 1);
  memcpy(dir, directorio.c_str(), directorio.size() + 1);
  uploadRecursivo(arbol, cwd, dir, raid);
}

// Comprueba si es un directoio o un archivo
bool esDirectorio(char* path, char *nombre);
// Devuelve el tamaño de un archivo o directorio
off_t tamano(char* path, char *nombre);

void uploadRecursivo(Arbol *arbol, char* path, char* directorio, Raid *raid){
  char* barra = "/";
  char* pathCompleto = (char*)malloc(1 + strlen(path) + strlen(barra) + strlen(directorio));
  strcpy(pathCompleto, path);
  strcat(pathCompleto, barra);
  strcat(pathCompleto, directorio);
  DIR* dir;
  struct dirent* d;
  struct stat st;
  // Comprobamos que es un directorio
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
          arbol->insertarNodo(d->d_name, esDirectorio(pathCompleto,d->d_name), tamano(pathCompleto,d->d_name));
          // Insertamos los hijos de los hijos
          uploadRecursivo(arbol, pathCompleto, d->d_name, raid);
          // Devolvemos el nodo actual a su posición
          arbol->setDirectorioActual(temp);
        }
      }
    }
  // En caso de no ser un directorio simplemente lo introducimos
  }else{
    // 1º Creamos el nodo
    if(stat(pathCompleto, &st) == 0)
      arbol->insertarNodo(directorio, false, st.st_size);
    // 2º Guardamos en archivos .dat y retocamos bloques en el nodo
    Nodo *actual = arbol->getDirectorioActual();
    for(int i = 0; i < actual->getHijos()->size(); i++)
      if(!strcmp(actual->getHijos()->at(i)->getNombre(), directorio))
        arbol->setDirectorioActual(actual->getHijos()->at(i));
    raid->writeFile(directorio, st.st_size, arbol->getDirectorioActual());
    arbol->setDirectorioActual(actual);

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
