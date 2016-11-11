#include <sys/stat.h>
#include <vector>

#define MAX 25

class Nodo{
  // Puntero al árbol al que pertecene
  Nodo* padre;
  std::vector<Nodo>* hijos;
  char nombre[MAX];
  int id;
  int nivel;
  bool directorio;
  off_t tamano;
  time_t ultimaModificacion;
public:
  // Constructores
  Nodo();
  Nodo(Nodo *mpadre, char *mnombre, int mid, bool mdirectorio, off_t mtamano);
  // Métodos get
  Nodo* getPadre();
  std::vector<Nodo>* getHijos();
  char* getNombre();
  int getId();
  int getNivel();
  bool esDirectorio();
  off_t getTamano();
  time_t getUltimaModificacion();
  // Métodos set
  void setNombre(char *mnombre);
  void setTamano(off_t mtamano);
  void setUltimaModificacion();
  void setHijos(Nodo nuevoNodo);
};
