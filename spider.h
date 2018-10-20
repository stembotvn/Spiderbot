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
#define DEBUG 1
//#include "RF24.h"
//#include "RF24Network.h"
#include "EasyRF.h"
#include <SPI.h>
#include <EEPROM.h>
#include <Servo.h>
#include "Sounds.h"
#include "EasySonar.h"

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
////////define State 
#define READ_RF   0
#define PARSING   1
#define RUN_CMD  2
#define GET_DATA 3
#define RC       4
#define WRITE_RF 5
#define IN_CONFIG 6
///define for operation Mode
#define RUN_MODE 0
#define CONFIG_MODE 1
#define RC_MODE 2
///
#define MASTER_NODE 0
class spider 
{
public:

	spider(){}
  RF24 myRadio=RF24(CE_PIN,CSN_PIN);
  EasyRF Radio = EasyRF(myRadio);
 /////system function///
	void init();
  void initNRF();
  void load_address();        // Chuyển đổi địa chỉ lưu từ EEPROM
  void inConfig();        // Nhận địa chỉ ngẫu nhiên từ Transmitter
//////Robot Action//////
  void move(int type,int speed);
  void action(int type,int t);
  void rest();
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
  void _tone (float noteFrequency, long noteDuration, int silentDuration);
  void bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
  void sing(int songName);
  float  getDistance();        //get Distance in CM
  int  getLight(byte side);  // get Light  level in %
  ///State Function/////
  void config_Address(uint16_t myaddress,uint16_t toAddress);
  void readRF();
  void parseData();
  void writeRF();
  void RC_Run();
  void run();
  ////
  void PrintDebug(unsigned char *buf,int len);
  void remoteProcessing();
  ///
  int State = 0; 
  uint8_t keyState = 0;
  uint8_t varSlide = 0;
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
  EasySonar SR04 = EasySonar(Trig,Echo);
  double timeStart; 
  uint16_t myNode = 2; 
  uint16_t toNode;
  uint16_t new_addr; 
  uint16_t  Default_Addr = 1000;
  uint16_t  Multicast_Node = 255;
  bool first_run = true;
  uint8_t Mode = RUN_MODE; 
  int _Add[1];
  long _startTime;
  long _timeout = 10000L;
  int  RFread_size; 
  bool _readDone = false; 
  char _buffer[64];
	bool  isAvailable = false;
  bool isStart=false;
  unsigned char prevc=0;
  int index = 0;
  int ind = 0; 
  int dataLen;
  unsigned char buffer[32]; //for reading RF
  unsigned char RF_buf[32]; //for writing RF
  unsigned char RC_buf[20]; //for Reading Remote
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
  void writeHead();
  void writeEnd();
  /////////////////////////////////////////
  unsigned char readBuffer(int index);  //read RF Comming buffer
  void writeBuffer(int index,unsigned char c); //write to RF Sending Buffer
  void clearBuffer(unsigned char *buf, int leng);
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
  //////////////////////////////////////////
  void playTone(int pin, int hz, int ms);
  void noTone(int pin);
  //////////////////////////////////////////
  void runFunction(int device);
  int searchServoPin(int pin);
  void readSensor(int device);
  //////////////////////////////////////////
  void EEPROM_writeInt(int address,uint16_t value);
  uint16_t EEPROM_readInt(int address);
};
#endif 
