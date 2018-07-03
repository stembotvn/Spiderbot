#include <spider.h>
#include "IRremote.h"

spider robot;

//////////////////////////////////////
void setup()
{
  robot.init();
  robot.initRemote();
  Serial.begin(9600);
  robot.stand1();
}
///////////////////////////
void loop()
{
  robot.ReadRemote();
  delay(10);
  robot.listenToSerial();
}

