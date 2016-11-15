#include "Arbol.h"
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
  char* comando = new char(directorio.size() + 1);
  memcpy(comando, directorio.c_str(), directorio.size() + 1);
  chdir(comando);
  delete comando;
}
void uploadRecursivo(Arbol* arbol, char* path, char* directorio);
void lupload(Arbol* arbol,std::string directorio){
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  char* barra = "/";
  char* path = (char*)malloc(1 + strlen(cwd) + strlen(barra) + strlen(directorio.c_str()));
  strcpy(path, cwd);
  strcat(path, barra);
  strcat(path, directorio.c_str());
  char* comando = new char(directorio.size() + 1);
  memcpy(comando, directorio.c_str(), directorio.size() + 1);
  uploadRecursivo(arbol, cwd, comando);
}

void uploadRecursivo(Arbol* arbol, char* path, char* directorio){
  char* barra = "/";
  char* pathCompleto = (char*)malloc(1 + strlen(path) + strlen(barra) + strlen(directorio));
  strcpy(pathCompleto, path);
  strcat(pathCompleto, barra);
  strcat(pathCompleto, directorio);
  DIR* dir;
  struct dirent* d;
  if((dir=opendir(pathCompleto)) != NULL){
    while((d = readdir(dir)) != NULL){
      if(strcmp(d->d_name, "..") != 0 && strcmp(d->d_name, ".") != 0){
        uploadRecursivo(arbol, pathCompleto, d->d_name);
      }
    }
  }else std::cout << pathCompleto << "\n";
  closedir(dir);
}
/*
void lupload(Arbol* arbol,std::string directorio){
  struct stat st;
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  char* comando = new char(directorio.size() + 1);
  memcpy(comando, directorio.c_str(), directorio.size() + 1);
  char* barra = "/";
  char* path = (char*)malloc(1 + strlen(cwd) + strlen(barra) + strlen(comando));
  strcpy(path, cwd);
  strcat(path, barra);
  strcat(path, comando);
  // Comprobamos que existe
  if(stat(path, &st) == 0){
    // Comprobamos si es un directorio
    if(S_ISDIR(st.st_mode)){
        std::cout << "|";
        // Comprobamos si tiene hijos
        DIR* d;
        struct dirent* dir;
        d = opendir(path);
        while((dir = readdir(d)) != NULL)
          if(stat(dir->d_name, &st) == 0)
            std::cout << dir->d_name;
    }
    else
        std::cout << "file " << path;
  }
}

/*if(stat(directorio, &st) == 0){
  // Existe. Comprobamos si es un fichero o un directorio

  // Es un directorio
  if(S_ISDIR(st.st_mode)){

    // Comprobamos si tiene hijos
  /*  DIR* d;
    struct dirent* dir;
    d = opendir();
    // Recorremos la lista de hijos
    while((dir = readdir(d)) != NULL)
      std::cout << "|";
  }
  else{
    // Es un fichero
  //  arbol->insertarNodo(, false, st.st_size);
}
}*/
