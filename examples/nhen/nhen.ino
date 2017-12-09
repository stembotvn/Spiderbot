#include "spider.h"

spider robot;
//////////////////////////////////////
void setup()
{
  robot.init();
}
//void idle()
//{
//  delay(late);
//}

///////////////////////////////////////
void loop()
{
robot.standUp(20);
delay(1000);
robot.layDown(20);
robot.stand1();    
}

