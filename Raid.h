#include <string>

class Raid{
public:
  Raid();
  // Copiar 1 bloque
  void writeBlock(std::string nombre, int count);
  //void readBlock();
  void writeFile(size_t mtamano);
  //void reafFile();
  void format(int tamano);
};
