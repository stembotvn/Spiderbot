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
#include "EasySonar.h"
#include "NegendoSounds.h"
#include "motion.h"

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
////////////////////////////
#define RC_MANUAL  0
#define LIGHT_FOLLOW    1
#define AVOID_OBSTACLE 2
#define CREATE_SOUND  3
///////////////////////////
#define NETWORK 1
#define PAIRING 0
///////////////////////////
#define LEFT 0
#define RIGHT 1

////
#define MASTER_NODE 0
class spider 
{
public:

	spider(){}
  RF24 myRadio=RF24(CE_PIN,CSN_PIN);
  EasyRF Radio = EasyRF(myRadio);
 /////system function//////
	void init(int _address);
  void initNRF(int _address);
  void load_address();        // Chuyển đổi địa chỉ lưu từ EEPROM
  bool inConfig();        // Nhận địa chỉ ngẫu nhiên từ Transmitter
//////Robot Action//////
  void move(int type,int step, int speed);
  void action(int type,int t);
  void rest();

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
  uint8_t RC_type = RC_MANUAL;
  bool connection = PAIRING; 
  NegendoSounds Sound = NegendoSounds(buzzer);
  Motion Robot = Motion(hip1_pin, knee1_pin, hip2_pin, knee2_pin, hip3_pin, knee3_pin, hip4_pin, knee4_pin);

private:

  EasySonar SR04 = EasySonar(Trig,Echo);
  double timeStart;
  int speed = 70;

  int medium;

  uint16_t myNode = 2; 
  uint16_t toNode;
  uint16_t new_addr; 
  uint16_t  Default_Addr = 1000;
  uint16_t  Multicast_Node = 255;
  bool first_run = true;
  bool actionDone = false; 
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
  uint8_t command_index = 0;
  float angleServo = 90.0;
  int servo_pins[8]={0,0,0,0,0,0,0,0};
  double lastTime = 0.0;
  double currentTime = 0.0;
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

  void runFunction(int device);
  int searchServoPin(int pin);
  void readSensor(int device);
  //////////////////////////////////////////
  void EEPROM_writeInt(int address,uint16_t value);
  uint16_t EEPROM_readInt(int address);
};
#endif 
