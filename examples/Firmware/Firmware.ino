#include "spider.h"

spider Guti;

//////////////////////////////////////
void setup()
{
  Guti.init();
  Guti.Robot.zero();
}
///////////////////////////
void loop()
{
  Guti.run();
  //Guti.Robot.walk(4,600);
 // Guti.Robot.home();
  //delay(3000);
}

