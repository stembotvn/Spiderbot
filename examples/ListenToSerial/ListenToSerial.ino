#include <Servo.h>
#include "spider.h"

spider robot;

void setup(){
    robot.init();
    Serial.begin(9600);
    robot.stand1();
}

void loop(){
    //robot.forward(100);
    robot.listenToSerial();
}
