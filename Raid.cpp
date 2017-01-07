// Julián Toledano Díaz
#include "Raid.h"
#include <fstream>
#include <stdlib.h>

void Raid::format(int tamano){
  std::fstream libres1("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres1.dat", std::ios::out | std::ios::app);
  for(int i = 1; i <= tamano; i++)libres1 << i << "\n";
  libres1.close();
  std::fstream libres2("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres2.dat", std::ios::out | std::ios::app);
  for(int i = tamano + 1; i <= tamano*2; i++)libres2 << i << "\n";
  libres2.close();
  std::fstream libres3("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres3.dat", std::ios::out | std::ios::app);
  for(int i = tamano*2 + 1; i <= tamano*3; i++)libres3 << i << "\n";
  libres3.close();
  std::fstream libres4("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres4.dat", std::ios::out | std::ios::app);
  for(int i = tamano*3 + 1; i <= tamano*4; i++)libres4 << i << "\n";
  libres4.close();

  std::fstream disco1("/home/julian/Documentos/SistemasDistribuidos/disco1.dat", std::ios::out | std::ios::app | std::ios::binary);disco1.close();
  std::fstream disco2("/home/julian/Documentos/SistemasDistribuidos/disco2.dat", std::ios::out | std::ios::app | std::ios::binary);disco2.close();
  std::fstream disco3("/home/julian/Documentos/SistemasDistribuidos/disco3.dat", std::ios::out | std::ios::app | std::ios::binary);disco3.close();
  std::fstream disco4("/home/julian/Documentos/SistemasDistribuidos/disco4.dat", std::ios::out | std::ios::app | std::ios::binary);disco4.close();
}

Raid::Raid(){
  format(32000);
}

void Raid::writeBlock(std::string nombre, int count, int disco, Nodo *nodo){
  // 1ª parte. Encontramos el sect or libre.
  std::fstream temp("temp.dat", std::ios::out | std::ios::binary);
  std::fstream disc;
  if(disco == 1)
     disc.open("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres1.dat", std::ios::in);
  else if(disco == 2)
    disc.open("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres2.dat", std::ios::in);
  else if(disco == 3)
    disc.open("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres3.dat", std::ios::in);
  else
    disc.open("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres4.dat", std::ios::in);

  if(disc.is_open()){
    int sector;
    bool sectorEncontrado = false;
    for(int i = 1; i <= 32000; i++){
      disc >> sector;
      // Comprobamos hasta encontrar el primero de la lista distinto de cero.
      if(!sectorEncontrado && sector != 0) {
        nodo->anadirBloques(sector);
        temp << "0";
        sectorEncontrado = true;
      }
      else
        temp << sector;
      temp << "\n";
      }
  }else perror("abrir discos");
  if(disco == 1){
    remove("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres1.dat");
    rename("temp.dat", "/home/julian/Documentos/SistemasDistribuidos/sectoresLibres1.dat");
  }
  else if(disco == 2){
    remove("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres2.dat");
    rename("temp.dat", "/home/julian/Documentos/SistemasDistribuidos/sectoresLibres2.dat");
  }
  else if(disco == 3){
    remove("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres3.dat");
    rename("temp.dat", "/home/julian/Documentos/SistemasDistribuidos/sectoresLibres3.dat");
  }
  else{
    remove("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres4.dat");
    rename("temp.dat", "/home/julian/Documentos/SistemasDistribuidos/sectoresLibres4.dat");
  }
  temp.close();
  disc.close();

  // 2ª parte escribimos o sobreescribimos el bloque
  FILE *read = fopen(nombre.c_str(), "rb");
  if(read == NULL) perror("Error");
  FILE *write;
  if(disco == 1)
    write = fopen("/home/julian/Documentos/SistemasDistribuidos/disco1.dat", "r+b");
  else if(disco == 2)
      write = fopen("/home/julian/Documentos/SistemasDistribuidos/disco2.dat", "r+b");
  else if(disco == 3)
      write = fopen("/home/julian/Documentos/SistemasDistribuidos/disco3.dat", "r+b");
  else
      write = fopen("/home/julian/Documentos/SistemasDistribuidos/disco4.dat", "r+b");

  char buffer[1024] ={};
  // Posicionamos el puntero donde sea necesario
  fseek(read, 1024*count, SEEK_SET);
  fread(buffer, 1, 1024, read);
  // Si al leer el archivo llega al final de éste y no rellena buffer
  // lo rellenamos de basura
  for(int i = 0; i < 1024; i++) /* MEJORAR*/
    if(buffer[i] == '\0') buffer[i] ='0';

  // ATENCION  sin este paso los ficheros: disco2, disco3, disco4 serían enormes ya que se multiplicaria
  // por 32000, 64000 y 96000 como mínimo respectivamente. Por eso se coge el resto de dividirlo entre 32000.
  // Ejemplo disco3 sector 64010 -> es el sector numero 10 del disco por lo que es necesario realizar 1024*10 unicamente.
  int posicion = nodo->getBloques()[(nodo->getNumBloques()-1)]%32000;
  if(posicion == 0)posicion = 32000;
  fseek(write,1024*posicion, SEEK_SET);
  fwrite(buffer, sizeof(buffer), 1, write);
  fclose(read);
  fclose(write);
}

void Raid::writeFile(std::string nombre, size_t mtamano, Nodo *nodo){
  float size = (float)mtamano/(float)1024;
  // Comprueba que size es un numero entero .00 si es así solo es necesario
  // iterar size veces, de lo contrario es necesario size+1 veces
  int disco = 1;
  for(float i = 0.0; i < size; i++){
    writeBlock(nombre,i, disco, nodo);
    disco += 1;
    if(disco == 5) disco = 1;
  }
  if(size-(int)size == 0)
    writeBlock(nombre, (int)size, disco, nodo);
}

void Raid::liberarBloque(int n){
  std::fstream temp("temp.dat", std::ios::out | std::ios::binary);
  std::fstream disc;
  if(n <= 32000)
    disc.open("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres1.dat", std::ios::in);
  else if(n <= 64000)
    disc.open("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres2.dat", std::ios::in);
  else if(n <= 96000)
    disc.open("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres3.dat", std::ios::in);
  else
    disc.open("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres4.dat", std::ios::in);

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
    remove("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres1.dat");
    rename("temp.dat", "/home/julian/Documentos/SistemasDistribuidos/sectoresLibres1.dat");
  }
  else if(n <= 64000){
    remove("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres2.dat");
    rename("temp.dat", "/home/julian/Documentos/SistemasDistribuidos/sectoresLibres2.dat");
  }
  else if(n <= 96000){
    remove("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres3.dat");
    rename("temp.dat", "/home/julian/Documentos/SistemasDistribuidos/sectoresLibres3.dat");
  }
  else{
    remove("/home/julian/Documentos/SistemasDistribuidos/sectoresLibres4.dat");
    rename("temp.dat", "/home/julian/Documentos/SistemasDistribuidos/sectoresLibres4.dat");
  }
  temp.close();
  disc.close();
}

void Raid::readBlock(int n){
  FILE *read;
  if(n <= 32000)
    read = fopen("/home/julian/Documentos/SistemasDistribuidos/disco1.dat", "r");
  else if(n <= 64000)
    read = fopen("/home/julian/Documentos/SistemasDistribuidos/disco2.dat", "r");
  else if(n <= 96000)
    read = fopen("/home/julian/Documentos/SistemasDistribuidos/disco3.dat", "r");
  else
    read = fopen("/home/julian/Documentos/SistemasDistribuidos/disco4.dat", "r");

  FILE *write = fopen("/home/julian/Documentos/SistemasDistribuidos/test.dat", "a");
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
