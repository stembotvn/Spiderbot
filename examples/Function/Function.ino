#include "spider.h"

spider Guti;

void setup()
{
  Guti.init();
}
void loop()
{
  Guti.Robot.run(2,500);
  //delay(3000);
}
