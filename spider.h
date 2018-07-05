/*
Class for Stembot platform 
an open source STEM robotics for kids
http://stembot.vn
*/
/*
			   o o
		--1--=======--2--
			 =======
			 =======
		--3--=======--4--

*/
#ifndef spider_h
#define spider_h

#include <Servo.h>
#include "IRremote.h"

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Scratch.h"

#define hip1_pin	2
#define knee1_pin	3
#define hip2_pin	4
#define knee2_pin	5
#define hip3_pin	6
#define knee3_pin	7
#define hip4_pin	8
#define knee4_pin	9

#define receiverPin A0
// Define IR Remote Button Codes
#define irUp  16736925
#define irDown 16754775
#define irRight 16761405
#define irLeft 16720605
#define irOK 16712445
#define ir1 16738455
#define ir2 16750695
#define ir3 16756815
#define ir4 16724175
#define ir5 16718055
#define ir6 16743045
#define ir7 16716015
#define ir8 16726215
#define ir9 16734885
#define ir0 16730805
#define irStar 16728765
#define irPound 16732845

class spider
{
public:
	spider(){}

	void init();
	void standUp(int t);
	void layDown(int t);
	void sleep(int t);
	void stand1();
	void stand2();
	void stand3();
	void start(int t);
	void hello(int t);
	void exercise(int t);
	void forward(int late);
	void backward(int late);
	void turnright(int late);
	void turnleft(int late);
	void processCommand();
	void parse_SpiderCMD();
	void control();
	void ReadRemote();
	void initRemote();
	void readSerial();
	void Scratch_command_processing();
private:
  Servo _hip1;
	Servo _knee1;
	Servo _hip2;
	Servo _knee2;
	Servo _hip3;
	Servo _knee3;
	Servo _hip4;
	Servo _knee4;
  Servo servos[8];  
    bool _readDone = false; 
    char _buffer[64];
	  int _sofar;
	  int _count;
	  bool  isAvailable = false;
	  char serialRead;
    bool isStart=false;
    unsigned char prevc=0;
    int index = 0;
    int dataLen;
    char buffer[52];
    uint8_t command_index = 0;
    float angleServo = 90.0;
    int servo_pins[8]={0,0,0,0,0,0,0,0};
    double lastTime = 0.0;
    double currentTime = 0.0;
    int analogs[8]={A0,A1,A2,A3,A4,A5,A6,A7};
     ///////////////////////////
    union{
    byte byteVal[4];
    float floatVal;
    long longVal;
   
}val;

union{
  byte byteVal[8];
  double doubleVal;
}valDouble;

union{
  byte byteVal[2];
  short shortVal;
}valShort;
    ////
    IRrecv irrecv= IRrecv(receiverPin);
	decode_results results;
//////////////////////////
    void parseData();

  void writeHead(){
  writeSerial(0xff);
  writeSerial(0x55);
}
void writeEnd(){
  Serial.println(); 

}
void writeSerial(unsigned char c){
 Serial.write(c);

}
/////
unsigned char readBuffer(int index){
 return buffer[index]; 
}
void writeBuffer(int index,unsigned char c){
   buffer[index]=c;
 } 

/////////////////////////////////
void callOK(){
    writeSerial(0xff);
    writeSerial(0x55);
    writeEnd();
}
void sendByte(char c){
  writeSerial(1);
  writeSerial(c);
}
void sendString(String s){
  int l = s.length();
  writeSerial(4);
  writeSerial(l);
  for(int i=0;i<l;i++){
    writeSerial(s.charAt(i));
  }
}
void sendFloat(float value){ 
     writeSerial(0x2);
     val.floatVal = value;
     writeSerial(val.byteVal[0]);
     writeSerial(val.byteVal[1]);
     writeSerial(val.byteVal[2]);
     writeSerial(val.byteVal[3]);
}
void sendShort(double value){
     writeSerial(3);
     valShort.shortVal = value;
     writeSerial(valShort.byteVal[0]);
     writeSerial(valShort.byteVal[1]);
}
void sendDouble(double value){
     writeSerial(2);
     valDouble.doubleVal = value;
     writeSerial(valDouble.byteVal[0]);
     writeSerial(valDouble.byteVal[1]);
     writeSerial(valDouble.byteVal[2]);
     writeSerial(valDouble.byteVal[3]);
}
short readShort(int idx){
  valShort.byteVal[0] = readBuffer(idx);
  valShort.byteVal[1] = readBuffer(idx+1);
  return valShort.shortVal; 
}
float readFloat(int idx){
  val.byteVal[0] = readBuffer(idx);
  val.byteVal[1] = readBuffer(idx+1);
  val.byteVal[2] = readBuffer(idx+2);
  val.byteVal[3] = readBuffer(idx+3);
  return val.floatVal;
}
long readLong(int idx){
  val.byteVal[0] = readBuffer(idx);
  val.byteVal[1] = readBuffer(idx+1);
  val.byteVal[2] = readBuffer(idx+2);
  val.byteVal[3] = readBuffer(idx+3);
  return val.longVal;
}
////
void playTone(int pin, int hz, int ms) {
	 int buzzer_pin = pin;
  int period = 1000000L / hz;
  int pulse = period / 2;
  pinMode(buzzer_pin, OUTPUT);
  for (long i = 0; i < ms * 1000L; i += period) 
  {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(pulse);
   }
}
void noTone(int pin){

  int buzzer_pin = pin;
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, LOW);
}
///
void runModule(int device){
  //0xff 0x55 0x6 0x0 0x1 0xa 0x9 0x0 0x0 0xa
  int port = buffer[6];
  int pin = port;
  switch(device){
    case DIGITAL:{
     pinMode(pin,OUTPUT);
     int v = readBuffer(7);
     digitalWrite(pin,v);
   }
   break;
   case PWM:{
     pinMode(pin,OUTPUT);
     int v = readBuffer(7);
     analogWrite(pin,v);
   }
   break;
   case TONE:{

     pinMode(pin,OUTPUT);
     int hz = readShort(7);
     int ms = readShort(9);
     if(ms>0){
       playTone(pin, hz, ms); 
     }else{
       noTone(pin); 
     }
   }
   break;
   case SERVO_PIN:{
     int v = readBuffer(7);
     Servo sv = servos[searchServoPin(pin)]; 
     if(v >= 0 && v <= 180)
     {
       if(!sv.attached())
       {
         sv.attach(pin);
       }
       sv.write(v);
     }
   }
   break;
   case TIMER:{
    lastTime = millis()/1000.0; 
   }
   break;
  }
}

int searchServoPin(int pin){
    for(int i=0;i<8;i++){
      if(servo_pins[i] == pin){
        return i;
      }
      if(servo_pins[i]==0){
        servo_pins[i] = pin;
        return i;
      }
    }
    return 0;
}
void readSensor(int device){
  /**************************************************
      ff 55 len idx action device port slot data a
      0  1  2   3   4      5      6    7    8
  ***************************************************/
  float value=0.0;
  int port,slot,pin;
  port = readBuffer(6);
  pin = port;
  switch(device){
   
   case  DIGITAL:{
     pinMode(pin,INPUT);
     sendFloat(digitalRead(pin));
   }
   break;
   case  ANALOG:{
     pin = analogs[pin];
     pinMode(pin,INPUT);
     sendFloat(analogRead(pin));
   }
   break;
   case  PULSEIN:{
     int pw = readShort(7);
     pinMode(pin, INPUT);
     sendShort(pulseIn(pin,HIGH,pw));
   }
   break;
   case ULTRASONIC_ARDUINO:{
     int trig = readBuffer(6);
     int echo = readBuffer(7);
     pinMode(trig,OUTPUT);
     digitalWrite(trig,LOW);
     delayMicroseconds(2);
     digitalWrite(trig,HIGH);
     delayMicroseconds(10);
     digitalWrite(trig,LOW);
     pinMode(echo, INPUT);
     sendFloat(pulseIn(echo,HIGH,30000)/58.0);
   }
   break;
   case TIMER:{
     sendFloat((float)currentTime);
   }
   break;
      }	
   }


};

#endif 
