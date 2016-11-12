#include "Nodo.h"

class Arbol{
  Nodo* raiz;
  Nodo* directorioActual;
  int totalNodos;
  int ultimoID;
  Nodo* buscarNodo(Nodo *nodoABuscar, char* mnombre);

public:
  Arbol();

  // Operaciones con los nodos
  Nodo* insertarNodo(char *mnombre, bool directorio);
  Nodo* buscarNodo(char* nombre);
  void modificarNodo(Nodo* aModificar, char* mnombre = NULL, off_t mtamano = -1);
  void eliminarNodo(char* mnombre);


  Nodo* getRoot();
  Nodo* getDirectorioActual();
  void setDirectorioActual(char* mnombre);

  void imprimir(Nodo* nodo, int tab);
};
