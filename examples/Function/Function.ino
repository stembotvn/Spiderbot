#include "minikame.h"

MiniKame Guti;

void setup()
{
  Guti.init();
  delay(3000);
}
void loop()
{
  //Guti.run(2,700);
  //Guti.dance(3,600);
  //delay(5000);
  Guti.moonwalkL(5,2000);
    Guti.run(2,700);

  //Guti.home();
  //delay(3000);
}
