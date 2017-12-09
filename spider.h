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

Servo hip1;
Servo knee1;
Servo hip2;
Servo knee2;
Servo hip3;
Servo knee3;
Servo hip4;
Servo knee4;

Class 
{
public:
	spider(); 
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
	int b;
	int x;
	int y;
	int i;
	int j;
	int k;
	int up;
	int t;
	int late;
	int down;
	int slep;
	int turn1;
	int steps;
	int rightsteps;
	int leftsteps;
};
#endif 
