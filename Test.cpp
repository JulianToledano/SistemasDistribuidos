#include "Arbol.h"
#include <iostream>
int main(){

  Arbol *test = new Arbol();

  test->insertarNodo("tmp", true);
  test->insertarNodo("bin", true);
  test->insertarNodo("urs", true);
  test->insertarNodo("ttt", true);

  std::cout << "SIN MODIFICACION\n";
  for(int i = 0; i < test->getRoot()->getHijos()->size(); i++)
    std::cout << test->getRoot()->getHijos()->at(i)->getNombre() << std::endl;

  std::cout << "BUSCANDO EL NODO: ";
  Nodo* buscado = test->buscarNodo("tmp");
  std::cout << buscado->getNombre() << std::endl;

  std::cout << "CAMBIAMOS EL NOMBRE DESDE EL NODO ENCONTRADO: ";
  buscado->setNombre("chg");
  for(int i = 0; i < test->getRoot()->getHijos()->size(); i++)
    std::cout << test->getRoot()->getHijos()->at(i)->getNombre() << std::endl;

  std::cout << "no error" << std::endl;

  delete test;
  return 0;
}
