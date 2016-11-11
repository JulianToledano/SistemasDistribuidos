#include "Nodo.h"

class Arbol{
  Nodo* raiz;
  Nodo* directorioActual;
  int totalNodos;
  int ultimoID;
  //Nodo* buscarnodo(char* mnombre, std::vector<Nodo>* mhijos);
public:
  Arbol();

  // Operaciones con los nodos
  void insertarNodo(char *mnombre, bool directorio);
  Nodo* buscarNodo(char* nombre);
  //void modificarNodo(char* mnombre);
  //void eliminarNodo(char* mnombre);


  Nodo* getRoot();
  Nodo* getDirectorioActual();
  void setDirectorioActual(char* mnombre);
};
