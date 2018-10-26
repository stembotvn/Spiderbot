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
}

