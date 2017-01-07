#include "mpi.h"
#include <stdio.h>

int main(int argc, char **argv){
  int rank;
  char msg[20];
  MPI_Status status;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0){
    printf("I am master. Sending the message.\n\n");
    strcpy(msg,"Hello world!");
    MPI_Send(msg,13,MPI_CHAR,1,100, MPI_COMM_WORLD);
  }else{
    MPI_Recv(msg, 13, MPI_CHAR, 0, 100, MPI_COMM_WORLD, &status);
    printf("The message is: %s\n", msg);
  }

  MPI_Finalize();
  return 0;
}
