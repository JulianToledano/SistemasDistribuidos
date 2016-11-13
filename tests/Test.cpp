#include "Arbol.h"
#include <iostream>
int main(){

  Arbol *test = new Arbol();

  test->insertarNodo("tmp", true);
  test->insertarNodo("bin", true);
  test->insertarNodo("urs", true);
  test->insertarNodo("home", true);
  test->insertarNodo("var", true);

  std::cout << "Introducimos subdirectorios:\n";
  test->setDirectorioActual("urs") ;
  test->insertarNodo("dentroURS", true);
  test->setDirectorioActual("tmp");
  test->insertarNodo("dentroTMP", false);
  test->setDirectorioActual("home");
  test->insertarNodo("dentroHOME", true);
  test->setDirectorioActual("var");
  test->insertarNodo("dentroVAR", true);
  test->setDirectorioActual("dentroHOME");
  test->insertarNodo("dentroDentroHOME", true);
  test->imprimir(test->getRoot(), 0);

  // Para eliminar debe de estar dentro de la carpeta actual
  std::cout << "\n\nEliminamos directorios:\n";
  test->setDirectorioActual("/");
  test->eliminarNodo("bin");
  test->setDirectorioActual("dentroHOME");
  test->eliminarNodo("dentroDentroHOME");
  test->imprimir(test->getRoot(), 0);

  // Modificar Nodo
  std::cout << "\n\Modificando directorios:\n";
  test->modificarNodo(test->buscarNodo("var"),"VAR");
  test->modificarNodo(test->buscarNodo("dentroHOME"),NULL, 4789);
  std::cout << "tamano dentroHOME: " << test->buscarNodo("dentroHOME")->getTamano() << std::endl;
  test->imprimir(test->getRoot(), 0);

  std::cout << "TODO CORRECTO\n";
  delete test;
  return 0;
}
