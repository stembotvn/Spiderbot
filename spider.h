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

#include "RF24.h"
#include <SPI.h>
#include <EEPROM.h>
#include <Servo.h>
#include "Sounds.h"

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Scratch.h"

#define buzzer    2
#define hip1_pin	3
#define knee1_pin	4
#define hip2_pin	5
#define knee2_pin	6
#define hip3_pin	7
#define knee3_pin	8
#define hip4_pin	9
#define knee4_pin	10

#define Trig      A0
#define Echo      A1
#define CE_PIN    A2
#define CSN_PIN   A3
#define SET       A4
#define LDR1      A6
#define LDR2      A7

class spider
{
public:
	spider(){}

	void init();
  void initNRF();
  void convertAdd();        // Chuyển đổi địa chỉ lưu từ EEPROM
  void setAddress();        // Nhận địa chỉ ngẫu nhiên từ Transmitter
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
  void tones(uint16_t frequency, uint32_t duration); // Hàm điều chỉnh âm điệu của còi
  void tick(int n, uint16_t frequency, int times);
	void readSerial();
	void Scratch_command_processing();

  void _tone (float noteFrequency, long noteDuration, int silentDuration);
  void bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
  void sing(int songName);
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
  RF24 radio = RF24(CE_PIN, CSN_PIN);

  const uint64_t _AddDefault = 0xF0F0F0F001LL;  // Địa chỉ truyền tín hiệu NRF24L01 mặc định
  uint64_t _AddRandom;              // Địa chỉ set ngẫu nhiên
  byte _readAdd;
  byte _address;
  int _Add[1];
  long _duration;
  long _startTime;
  long _timeout = 10000L;

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
