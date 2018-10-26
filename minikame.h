#ifndef minikame_h
#define minikame_h

#include <Servo.h>
#include <Octosnake.h>

class MiniKame{
public:
    //MiniKame(){}
    MiniKame (int hip1, int knee1, int hip2, int knee2, int hip3, int knee3, int hip4, int knee4);
    void init();
    void runs(float steps, int period);
    void walk(float steps, int period);
    void back(float steps, int period);
    void turnL(float steps, int period);
    void turnR(float steps, int period);
    void dance(float steps, int period);
    void upDown(float steps, int period);
    void pushUp(float steps, int period);
    void hello();
    void home();
    void zero();

    void setServo(int id, float target);
    void reverseServo(int id);
    float getServo(int id);
    void moveServos(int time, float target[8]);

private:
    Oscillator oscillator[8];
    Servo servo[8];
    int board_pins[8];
    int trim[8];
    bool reverse[8];
    unsigned long _init_time;
    unsigned long _final_time;
    unsigned long _partial_time;
    float _increment[8];
    float _servo_position[8];

    int angToUsec(float value);
    void execute(float steps, int period[8], int amplitude[8], int offset[8], int phase[8]);

protected:
	int pin0;
    int pin1;
    int pin2;
    int pin3;
    int pin4;
    int pin5;
    int pin6;
    int pin7;

};

#endif
