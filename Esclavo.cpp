#include <mpi.h>
#include "Raid.h"
#include "iostream"
#include <fstream>
#include <stdlib.h>

int main(){
  int rank;
  MPI_Status status;
  int code = 100;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  Raid *raid = new Raid(true);
  // Recive el código
  while(code != -1){
    MPI_Recv(&code,1,MPI_INT,0,0,MPI_COMM_WORLD, &status);
    // Código 0 enviar sector libre y refrescar sectoresLibres.dat
    if(code == 0){
      //std::cout << "Codigo0";
      // Se envía el sector libre y se sobreescribe por 0 en sectoresLibres.dat
        int sector;
        std::fstream temp("temp.dat", std::ios::out | std::ios::binary);
        std::fstream disc("sectoresLibres.dat");
        if(disc.is_open()){
          bool encontrado = false;
          for(int i = 1; i <= 32000; i++){
            disc >> sector;
            if(!encontrado && sector != 0){
              temp << "0";
              encontrado = true;
              MPI_Send(&sector,1,MPI_INT,0,0,MPI_COMM_WORLD);
            }
            else
              temp << sector;
            temp << "\n";
          }
        }
        temp.close(); disc.close();
        remove("sectoresLibres.dat");
        rename("temp.dat","sectoresLibres.dat");
    }
    // Codigo 1 write block
    if(code == 1){
      //std::cout << "Codigo1";
      int sector;
      MPI_Recv(&sector,1,MPI_INT,0,0,MPI_COMM_WORLD, &status);
      //std::cout << "Sector: " << sector << "\n";
      char buffer[1025] = {};
      MPI_Recv(buffer,1025,MPI_CHAR,0,0,MPI_COMM_WORLD, &status);
      raid->writeBlock(sector, buffer);
    }
  }
  MPI_Finalize();
  return 0;
}
