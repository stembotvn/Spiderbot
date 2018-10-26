#include "minikame.h"

///MiniKame Guti;
MiniKame Guti(3,4,5,6,7,8,9,10);

void setup()
{
  Guti.init();
}
void loop()
{
  //Guti.run(2,700);
  //Guti.dance(3,600);
  //delay(5000);
  //Guti.moonwalkL(5,2000);
  //Guti.home();
  //delay(3000);
  Guti.walk(4,500);
}
