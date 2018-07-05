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
  union
  {
    byte byteVal[4];
    float floatVal;
    long longVal;
   
  }val;

  union
  {
    byte byteVal[8];
    double doubleVal;
  }valDouble;

  union
  {
    byte byteVal[2];
    short shortVal;
  }valShort;
    ////
  IRrecv irrecv= IRrecv(receiverPin);
	decode_results results;
  /////////////////////////////////////////
  void parseData();
  void writeHead();
  void writeEnd();
  void writeSerial(unsigned char c);
  /////////////////////////////////////////
  unsigned char readBuffer(int index);
  void writeBuffer(int index,unsigned char c);
  /////////////////////////////////
  void callOK();
  void sendByte(char c);
  void sendString(String s);
  void sendFloat(float value);
  void sendShort(double value);
  void sendDouble(double value);
  short readShort(int idx);
  float readFloat(int idx);
  long readLong(int idx);
  ////
  void playTone(int pin, int hz, int ms);
  void noTone(int pin);
  ///
  void runModule(int device);
  int searchServoPin(int pin);
  void readSensor(int device);
};

#endif 
