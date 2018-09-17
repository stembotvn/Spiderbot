#include <spider.h>
#include "IRremote.h"
#include <Wire.h>
#include "SparkFun_APDS9960.h"

spider robot;
IRrecv irrecv(receiverPin);
decode_results results;

#define APDS9960_INT    2 // Needs to be an interrupt pin

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;
int count;
//////////////////////////////////////
void setup()
{
  robot.init();
  Serial.begin(9600);
  irrecv.enableIRIn();
/////////////////////////////////////////
// Set interrupt pin as input
  pinMode(APDS9960_INT, INPUT);

  // Initialize Serial port
  //Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));
  
  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
  
}
void ReadRemote()
{
  if (irrecv.decode(&results)) // nếu nhận được tín hiệu
  {
    control();
    delay(200);
    irrecv.resume(); // nhận giá trị tiếp theo
  }
}
///////////////////////////
void control()
{
  switch(results.value)
  {
    case irUp: //// tiến
      for(count = 0; count < 5; count++)
      {
        robot.forward(70);
        count++;
      }
      break;
    case irDown: //// lùi
      for(count = 0; count < 5; count++)
      {
        robot.backward(70);
        count++;
      }
      robot.backward(70);
      break;
    case irLeft: //// trái
      robot.turnleft(70);
      break;
    case irRight: //// phải
      robot.turnright(70);
      break;
    case irOK: //// ok
      robot.stand1();
      //robot.start(20);
      break;
    case ir1: //// 1
      robot.standUp(20);
      break;
    case ir2: //// 2
      robot.sleep(20);      
      break;
    case ir3: //// 3
      robot.stand2();      
      break;
    case ir4: //// 4
      robot.hello(10);
      break;
    case ir5: //// 5
      robot.start(20);
      break;
    case ir6: //// 6
      robot.exercise(20);
      break;
    case ir7: //// 7
      robot.layDown(20);
      break;
    case ir8: //// 8
      robot.stand3();
      break;
    case ir9: //// 9
      
      break;
    case ir0: //// 0
      
      break;
    case irStar: //// *
      
      break;
    case irPound: //// #
      
      break;
  } 
}
void loop()
{
  if( isr_flag == 1 ) {
    detachInterrupt(0);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(0, interruptRoutine, FALLING);
  }
  ReadRemote();
}
void interruptRoutine() {
  isr_flag = 1;
}

void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        robot.standUp(20);
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        robot.sleep(20); 
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        robot.turnright(70);
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        robot.turnleft(70);
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        for(count = 0; count < 5; count++)
        {
          robot.backward(70);
          count++;
        }
        
        break;
      case DIR_FAR:
        Serial.println("FAR");
        for(count = 0; count < 5; count++)
        {
          robot.forward(70);
          count++;
        }
        break;
      default:
        Serial.println("NONE");
    }
  }
}

