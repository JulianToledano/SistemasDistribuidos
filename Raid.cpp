// Julián Toledano Díaz
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
  std::cout << "Dentro write file. size: " << size;
  FILE *read = fopen(nombre.c_str(),"rb");
  int codigo = 1;
  for(int i = 0; i < size; i++){
    char buffer[1025] = {};
    //std::cout << "Dentro bucle write file. iteracion: " << i << " sector " << sectores[i] << "\n";
    MPI_Send(&codigo,1,MPI_INT,i%4+1,0,MPI_COMM_WORLD);
    fseek(read, 1024*i, SEEK_SET);
    fread(buffer, 1, 1024, read);
    int esclavo = i%4+1;
    // Rellenamos de 0s
    for(int j = 0; j < 1024; j++) if(buffer[j] == '\0')buffer[j] = '0';
    MPI_Send(&sectores[i],1,MPI_INT,esclavo,0,MPI_COMM_WORLD);
    MPI_Send(buffer,1025,MPI_CHAR,esclavo,0,MPI_COMM_WORLD);
    //std::cout << "Se envio\n";
  }
  fclose(read);
}

void Raid::liberarBloque(int n){
  std::fstream temp("temp.dat", std::ios::out | std::ios::binary);
  std::fstream disc;
  if(n <= 32000)
    disc.open("/home/julian/Documents/SistemasDistribuidos/sectoresLibres1.dat", std::ios::in);
  else if(n <= 64000)
    disc.open("/home/julian/Documents/SistemasDistribuidos/sectoresLibres2.dat", std::ios::in);
  else if(n <= 96000)
    disc.open("/home/julian/Documents/SistemasDistribuidos/sectoresLibres3.dat", std::ios::in);
  else
    disc.open("/home/julian/Documents/SistemasDistribuidos/sectoresLibres4.dat", std::ios::in);

  if(disc.is_open()){
    int sector;
    for(int i = 1; i <= 32000; i++){
      disc >> sector;
      // Comprobamos hasta encontrar el primero de la lista distinto de cero.
      if(i == n % 32000 || (i == 32000 && n % 32000 == 0)) temp << n << "\n";
      else temp << sector << "\n";

    }
  }
  if(n <= 32000){
    remove("/home/julian/Documents/SistemasDistribuidos/sectoresLibres1.dat");
    rename("temp.dat", "/home/julian/Documents/SistemasDistribuidos/sectoresLibres1.dat");
  }
  else if(n <= 64000){
    remove("/home/julian/Documents/SistemasDistribuidos/sectoresLibres2.dat");
    rename("temp.dat", "/home/julian/Documents/SistemasDistribuidos/sectoresLibres2.dat");
  }
  else if(n <= 96000){
    remove("/home/julian/Documents/SistemasDistribuidos/sectoresLibres3.dat");
    rename("temp.dat", "/home/julian/Documents/SistemasDistribuidos/sectoresLibres3.dat");
  }
  else{
    remove("/home/julian/Documents/SistemasDistribuidos/sectoresLibres4.dat");
    rename("temp.dat", "/home/julian/Documents/SistemasDistribuidos/sectoresLibres4.dat");
  }
  temp.close();
  disc.close();
}

void Raid::readBlock(int n){
  FILE *read;
  if(n <= 32000)
    read = fopen("/home/julian/Documents/SistemasDistribuidos/disco1.dat", "r");
  else if(n <= 64000)
    read = fopen("/home/julian/Documents/SistemasDistribuidos/disco2.dat", "r");
  else if(n <= 96000)
    read = fopen("/home/julian/Documents/SistemasDistribuidos/disco3.dat", "r");
  else
    read = fopen("/home/julian/Documents/SistemasDistribuidos/disco4.dat", "r");

  FILE *write = fopen("/home/julian/Documents/SistemasDistribuidos/test.dat", "a");
  int posicion = n%32000;
  if(posicion == 0)posicion = 32000;
  char *buffer[1024] = {};
  // Posicionamos el puntero para leer desde el lugar adecuado
  fseek(read, 1024*posicion, SEEK_SET);
  fread(buffer, 1, 1024, read);
  fwrite(buffer, sizeof(buffer), 1, write);
  fclose(read);
  fclose(write);
}

void Raid::readFile(Nodo *nodo){
  for(int i = 0; i < nodo->getNumBloques(); i++)
    readBlock(nodo->getBloques()[i]);

}

void Raid::setSize(int msize){size = msize;}
int Raid::getSize(){return size;}
