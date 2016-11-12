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
  std::cout << "Tamano del vecto: " << test->getRoot()->getHijos()->size() << std::endl;

  std::cout << "BUSCANDO EL NODO: ";
  Nodo* buscado = test->buscarNodo("tmp");
  std::cout << buscado->getNombre() << std::endl;
  std::cout << "Tamano del vecto: " << test->getRoot()->getHijos()->size() << std::endl;

  std::cout << "CAMBIAMOS EL NOMBRE DESDE EL NODO ENCONTRADO:\n";
  buscado->setNombre("chg");
  for(int i = 0; i < test->getRoot()->getHijos()->size(); i++)
    std::cout << test->getRoot()->getHijos()->at(i)->getNombre() << std::endl;
  std::cout << "Tamano del vecto: " << test->getRoot()->getHijos()->size() << std::endl;

  std::cout << "ELIMINAR EL NODO: bin\n";
  test->eliminarNodo("bin");
  for(int i = 0; i < test->getRoot()->getHijos()->size(); i++)
    std::cout << test->getRoot()->getHijos()->at(i)->getNombre() << std::endl;
  std::cout << "Tamano del vecto: " << test->getRoot()->getHijos()->size() << std::endl;
  delete test;
  return 0;
}
