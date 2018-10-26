#include "spider.h"

spider robot;

//////////////////////////////////////
void setup()
{
  robot.init();
  robot.stand1();
}
///////////////////////////
void loop()
{
  robot.run();
}

