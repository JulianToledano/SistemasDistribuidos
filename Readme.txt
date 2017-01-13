mpiCC Terminal.cpp Nodo.cpp Raid.cpp Arbol.cpp ComandosLocal.h ComandosRemoto.h -o master
mpiCC Esclavo.cpp Raid.cpp -o slave

mpirun -np 1 master : -np 4 --hostfile hostfile slave
