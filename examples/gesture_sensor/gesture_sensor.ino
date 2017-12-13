/*
Hardware Connections:
IMPORTANT: The APDS-9960 can only accept 3.3V!
 
 Arduino Pin  APDS-9960 Board  Function
 
 3.3V         VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock
 2            INT              Interrupt
*/

#include <Wire.h>
#include "SparkFun_APDS9960.h"
#include <spider.h>

spider robot;
// Pins
#define APDS9960_INT    2 // Needs to be an interrupt pin

// Constants

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;
int count;

void setup() 
{
  robot.init();
  // Set interrupt pin as input
  pinMode(APDS9960_INT, INPUT);

  // Initialize Serial port
  Serial.begin(9600);
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

void loop() 
{
  if( isr_flag == 1 ) {
    detachInterrupt(0);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(0, interruptRoutine, FALLING);
  }
}

void interruptRoutine() 
{
  isr_flag = 1;
}

void handleGesture() 
{
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

