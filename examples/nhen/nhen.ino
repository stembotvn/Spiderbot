#include "spider.h"

spider robot;
//////////////////////////////////////
void setup()
{
  robot.init();
}
///////////////////////////////////////

void loop()
{ 
    robot.standUp(20);
    robot.layDown(20);
    robot.sleep(20);
    robot.stand1();
    robot.stand2();
    robot.start(20);
    robot.hello(20);
    robot.exercise(20);
    robot.forward(70);
    robot.backward(70);
    robot.turnright(70);
    robot.turnleft(70);
}

