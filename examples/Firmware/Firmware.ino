#include "spider.h"

spider Guti;

//////////////////////////////////////
void setup()
{
  Guti.init(0);
}
///////////////////////////
void loop()
{
  Guti.run();
  //Guti.Robot.walk(4,600);
 // Guti.Robot.home();
  //delay(3000);
}

