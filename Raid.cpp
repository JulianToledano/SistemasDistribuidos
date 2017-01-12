// Julián Toledano Díaz
// Sistemas Distribuidos

#include <mpi.h>
#include "Raid.h"
#include <fstream>
#include <stdlib.h>

void Raid::format(int tamano){
  this->setSize(tamano);

  std::fstream libres1("sectoresLibres.dat", std::ios::out | std::ios::app);
  for(int i = 1; i <= size/4; i++)libres1 << i << "\n";
  libres1.close();

  std::fstream disco1("disco.dat", std::ios::out | std::ios::app | std::ios::binary);disco1.close();
}


Raid::Raid(bool esclavo){
  if(esclavo)
    format(128000);
}

void Raid::writeBlock(int sector, char *bloque){
  std::ofstream file;
  file.open("disco.dat", std::ios::app);
  file.seekp(1024*sector);
  file << bloque;
  file.close();
}

void Raid::writeFile(std::string nombre, int *sectores, int size){
  FILE *read = fopen(nombre.c_str(),"rb");
  int codigo = 1;
  for(int i = 0; i < size; i++){
    char buffer[1025] = {};
    int esclavo = i%4+1;
    MPI_Send(&codigo,1,MPI_INT,esclavo,0,MPI_COMM_WORLD); //*****
    fseek(read, 1024*i, SEEK_SET);
    fread(buffer, 1, 1024, read);
    // Rellenamos de 0s si ocupa menos de 1024
    for(int j = 0; j < 1024; j++) if(buffer[j] == '\0')buffer[j] = '0';
    MPI_Send(&sectores[i],1,MPI_INT,esclavo,0,MPI_COMM_WORLD); //***
    MPI_Send(buffer,1025,MPI_CHAR,esclavo,0,MPI_COMM_WORLD); //*****
  }
  fclose(read);
}

void Raid::readBlock(int sector){
  std::ifstream file;
  file.open("disco.dat", std::ios::binary);
  file.seekg(1024*(sector-1));
  char buffer[1024] = {};
  file.read(buffer, sizeof(buffer));
  MPI_Send(buffer,1024,MPI_CHAR,0,0,MPI_COMM_WORLD);
  file.close();
}

void Raid::readFile(std::string nombre, int *bloques, int size){
  std::ofstream file;
  file.open(nombre.c_str(), std::ios::app);
  int codigo = 2;
  MPI_Status status;
  for(int i = 0; i < size; i++){
    // Mandamos el codigo
    int esclavo = i%4+1;
    MPI_Send(&codigo,1,MPI_INT,esclavo,0,MPI_COMM_WORLD);//****
    MPI_Send(&bloques[i],1,MPI_INT,esclavo,0,MPI_COMM_WORLD);//*****
    char buffer[1024] = {};
    MPI_Recv(buffer,1024,MPI_CHAR,esclavo,0,MPI_COMM_WORLD,&status);//******
    file << buffer;
  }
  file.close();
}

void Raid::setSize(int msize){size = msize;}
int Raid::getSize(){return size;}
