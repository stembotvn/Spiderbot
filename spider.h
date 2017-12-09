/*
Class for Stembot platform 
an open source STEM robotics for kids
http://stembot.vn
*/

#ifndef spider_h
#define spider_h


#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define hip1_pin	4
#define knee1_pin	5
#define hip2_pin	6
#define knee2_pin	7
#define hip3_pin	8
#define knee3_pin	9
#define hip4_pin	10
#define knee4_pin	11
#include <Servo.h>



class spider
{
public:
//	spider(): hip1(),knee1(),hip2(),knee2(),hip3(),knee3(),hip4(),knee4()
//	 {};
	spider();

	void init();
	void standUp(int t);
	void layDown(int t);
	void sleep(int t);
	void stand1();
	void stand2();
	void start(int t);
	void hello(int t);
	void exercise(int t);
	void forward(int late);
	void backward(int late);
	void turnright(int late);
	void turnleft(int late);
private:
    Servo _hip1;
	Servo _knee1;
	Servo _hip2;
	Servo _knee2;
	Servo _hip3;
	Servo _knee3;
	Servo _hip4;
	Servo _knee4;
	
};
#endif 
