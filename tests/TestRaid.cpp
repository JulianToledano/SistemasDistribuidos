#include "Raid.h"

// Comprobar que funciona el sistema raid antes de tocar las funciones
// lupload, etc.

int main(){

  Raid *test = new Raid();
  test->writeBlock("test",0);
  test->writeBlock("test",1);
  test->writeBlock("test",2);
  test->writeBlock("test",3);
  test->writeBlock("test",4);


  return 0;
}
