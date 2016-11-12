#include "Arbol.h"
#include <iostream>
int main(){

  Arbol *test = new Arbol();

  test->insertarNodo("tmp", true);
  test->insertarNodo("bin", true);
  test->insertarNodo("urs", true);
  test->insertarNodo("home", true);
  test->insertarNodo("var", true);



  std::cout << " DIRECTORIO ACTUAL: ";
  test->setDirectorioActual("urs") ;
  std::cout<<test->getDirectorioActual()->getNombre() << std::endl;
  test->insertarNodo("dentroURS", true);
  test->imprimir(test->getRoot());

  std::cout << "CAMBIANDO DIRECTORIO ACTUAL: ";
  test->setDirectorioActual("tmp");
  std::cout<<test->getDirectorioActual()->getNombre() << std::endl;
  test->insertarNodo("dentroTMP", true);
  test->imprimir(test->getRoot());

  std::cout << "CAMBIANDO DIRECTORIO ACTUAL: ";
  test->setDirectorioActual("dentroTMP");
  std::cout<<test->getDirectorioActual()->getNombre() << std::endl;
  test->insertarNodo("dentroDentroTMP", true);
  test->imprimir(test->getRoot());

  std::cout << "CAMBIANDO DIRECTORIO ACTUAL: ";
  test->setDirectorioActual("bin");
  std::cout<<test->getDirectorioActual()->getNombre() << std::endl;
  test->insertarNodo("dentroBIN", true);
  test->imprimir(test->getRoot());


  std::cout << "TODO CORRECTO\n";
  delete test;
  return 0;
}
