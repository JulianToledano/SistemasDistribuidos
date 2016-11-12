#include "Arbol.h"
#include <iostream>
int main(){

  Arbol *test = new Arbol();

  test->insertarNodo("tmpp", true);
  test->insertarNodo("bin", true);
  test->insertarNodo("urs", true);
  test->insertarNodo("home", true);
  test->insertarNodo("asdf", true);


  std::cout << "SIN MODIFICACION\n";
  for(int i = 0; i < test->getRoot()->getHijos()->size(); i++)
    std::cout << test->getRoot()->getHijos()->at(i)->getNombre() << std::endl;
  std::cout << "Tamano del vecto: " << test->getRoot()->getHijos()->size() << std::endl;
/*
  std::cout << "BUSCANDO EL NODO: ";
  Nodo* buscado = test->buscarNodo("tmp");
  std::cout << buscado->getNombre() << std::endl;
  std::cout << "Tamano del vecto: " << test->getRoot()->getHijos()->size() << std::endl;
  std::cout << "CAMBIAMOS EL NOMBRE DESDE EL NODO ENCONTRADO:\n";
  buscado->setNombre("chg");
  for(int i = 0; i < test->getRoot()->getHijos()->size(); i++)
    std::cout << test->getRoot()->getHijos()->at(i)->getNombre() << std::endl;
  std::cout << "Tamano del vecto: " << test->getRoot()->getHijos()->size() << std::endl;
/*
  std::cout << "ELIMINAR EL NODO: bin\n";
  test->eliminarNodo("bin");
  for(int i = 0; i < test->getRoot()->getHijos()->size(); i++)
    std::cout << test->getRoot()->getHijos()->at(i)->getNombre() << std::endl;
  std::cout << "Tamano del vecto: " << test->getRoot()->getHijos()->size() << std::endl;
*/
  std::cout << "CAMBIANDO DIRECTORIO ACTUAL A urs\n";
  test->setDirectorioActual("home");
  test->insertarNodo("xxx", true);
  test->setDirectorioActual("xxx");
  test->insertarNodo("aaaa", true);
  test->setDirectorioActual("asdf");
  std::cout <<  "DIRECTORIO ACTUAL: "<<  test->getDirectorioActual()->getNombre() << std::endl;
  test->insertarNodo("dentroTMP", true);

  test->imprimir(test->getRoot());


  std::cout << "TODO CORRECTO\n";
  delete test;
  return 0;
}
