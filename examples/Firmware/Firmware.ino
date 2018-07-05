#include <spider.h>
#include "IRremote.h"

spider robot;

//////////////////////////////////////
void setup()
{
  robot.init();
  robot.initRemote();
  Serial.begin(115200);
  robot.stand1();
}
///////////////////////////
void loop()
{
  //robot.ReadRemote();
  //delay(10);
  robot.readSerial();
  robot.parse_SpiderCMD();
  robot.Scratch_command_processing();
}

