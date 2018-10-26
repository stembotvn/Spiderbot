#include "minikame.h"

MiniKame::MiniKame(int hip1, int knee1, int hip2, int knee2, int hip3, int knee3, int hip4, int knee4):
    pin0(hip1),
    pin1(hip2),
    pin2(knee1),
    pin3(knee2),
    pin4(hip3),
    pin5(hip4),
    pin6(knee3),
    pin7(knee4)
{
    ////////////////////////////////
    board_pins[0] = pin0; // Servo S0
    board_pins[1] = pin1; // Servo S1
    board_pins[2] = pin2; // Servo S2
    board_pins[3] = pin3; // Servo S3
    board_pins[4] = pin4; // Servo S4
    board_pins[5] = pin5; // Servo S5
    board_pins[6] = pin6; // Servo S6
    board_pins[7] = pin7; // Servo S7

    // Trim values for zero position calibration.
    trim[0] = 0;
    trim[1] = -8;
    trim[2] = 8;
    trim[3] = 5;
    trim[4] = 2;
    trim[5] = -6;
    trim[6] = 6;
    trim[7] = 5;

    // Set reverse movement
    for (int i=0; i<8; i++) reverse[i] = false;

    // Init an oscillator for each servo
    for(int i=0; i<8; i++){
        oscillator[i].start();
        servo[i].attach(board_pins[i]);
    }
    zero();
}
/*
void MiniKame::init(){
    // Map between servos and board pins
    board_pins[0] = 3; // Servo S0
    board_pins[1] = 5; // Servo S1
    board_pins[2] = 4; // Servo S2
    board_pins[3] = 6; // Servo S3
    board_pins[4] = 7; // Servo S4
    board_pins[5] = 9; // Servo S5
    board_pins[6] = 8; // Servo S6
    board_pins[7] = 10; // Servo S7

    // Trim values for zero position calibration.
    trim[0] = 0;
    trim[1] = -8;
    trim[2] = 8;
    trim[3] = 5;
    trim[4] = 2;
    trim[5] = -6;
    trim[6] = 6;
    trim[7] = 5;

    // Set reverse movement
    for (int i=0; i<8; i++) reverse[i] = false;

    // Init an oscillator for each servo
    for(int i=0; i<8; i++){
        oscillator[i].start();
        servo[i].attach(board_pins[i]);
    }
    zero();
}
*/
void MiniKame::turnR(float steps, int T=600){
    int x_amp = -15;
    int z_amp = -15;
    int ap = 15;
    int hi = 23;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    int phase[] = {0,180,90,90,180,0,90,90};

    execute(steps, period, amplitude, offset, phase);
}

void MiniKame::turnL(float steps, int T=600){
    int x_amp = -15;
    int z_amp = -15;
    int ap = 15;
    int hi = 23;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    int phase[] = {180,0,90,90,0,180,90,90};

    execute(steps, period, amplitude, offset, phase);
}

void MiniKame::dance(float steps, int T=600){
    int x_amp = 0;
    int z_amp = -40;
    int ap = -30;
    int hi = 0;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    int phase[] = {0,0,0,270,0,0,90,180};

    execute(steps, period, amplitude, offset, phase);
}

void MiniKame::run(float steps, int T=5000){
    int x_amp = -15;
    int z_amp = -15;
    int ap = 15;
    int hi = 15;
    int front_x = 6;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {    90+ap-front_x,
                        90-ap+front_x,
                        90-hi,
                        90+hi,
                        90-ap-front_x,
                        90+ap+front_x,
                        90+hi,
                        90-hi
                    };
    int phase[] = {0,0,90,90,180,180,90,90};

    execute(steps, period, amplitude, offset, phase);
}
void MiniKame::walk(float steps, int T=5000){
    int x_amp = -15;
    int z_amp = -20;
    int ap = -20;
    int hi = 10;
    int front_x = 12;
    int period[] = {T, T, T/2, T/2, T, T, T/2, T/2};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {   90+ap-front_x,
                                90-ap+front_x,
                                90-hi,
                                90+hi,
                                90-ap-front_x,
                                90+ap+front_x,
                                90+hi,
                                90-hi
                    };
    int  phase[] = {90, 90, 270, 90, 270, 270, 90, 270};

    for (int i=0; i<8; i++){
        oscillator[i].reset();
        oscillator[i].setPeriod(period[i]);
        oscillator[i].setAmplitude(amplitude[i]);
        oscillator[i].setPhase(phase[i]);
        oscillator[i].setOffset(offset[i]);
    }

    _final_time = millis() + period[0]*steps;
    _init_time = millis();
    bool side;
    while (millis() < _final_time){
        side = (int)((millis()-_init_time) / (period[0]/2)) % 2;
        setServo(0, oscillator[0].refresh());
        setServo(1, oscillator[1].refresh());
        setServo(4, oscillator[4].refresh());
        setServo(5, oscillator[5].refresh());

        if (side == 0){
            setServo(3, oscillator[3].refresh());
            setServo(6, oscillator[6].refresh());
        }
        else{
            setServo(2, oscillator[2].refresh());
            setServo(7, oscillator[7].refresh());
        }
        delay(1);
    }
}

void MiniKame::back(float steps, int T=5000){
    int x_amp = -15;
    int z_amp = -15;
    int ap = -10;
    int hi = 15;
    int front_x = 6;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {    90+ap-front_x,
                        90-ap+front_x,
                        90-hi,
                        90+hi,
                        90-ap-front_x,
                        90+ap+front_x,
                        90+hi,
                        90-hi
                    };
    int phase[] = {180,180,90,90,0,0,90,90};

    execute(steps, period, amplitude, offset, phase);
}

void MiniKame::upDown(float steps, int T=5000){
    int x_amp = 0;
    int z_amp = -35;
    int ap = -20;
    int hi = 30;
    int front_x = 0;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {x_amp,x_amp,z_amp,z_amp,x_amp,x_amp,z_amp,z_amp};
    int offset[] = {    90+ap-front_x,
                        90-ap+front_x,
                        90-hi,
                        90+hi,
                        90-ap-front_x,
                        90+ap+front_x,
                        90+hi,
                        90-hi
                    };
    int phase[] = {0,0,90,270,180,180,270,90};

    execute(steps, period, amplitude, offset, phase);
}


void MiniKame::pushUp(float steps, int T=600){
    int z_amp = -40;
    int x_amp = -65;
    int hi = 30;
    int period[] = {T, T, T, T, T, T, T, T};
    int amplitude[] = {0,0,z_amp,z_amp,0,0,0,0};
    int offset[] = {90,90,90-hi,90+hi,90-x_amp,90+x_amp,90+hi,90-hi};
    int phase[] = {0,0,0,180,0,0,0,180};

    execute(steps, period, amplitude, offset, phase);
}

void MiniKame::home(){
    int ap = -20;
    int hi = 10;
    int position[] = {90+ap,90-ap,90-hi,90+hi,90-ap,90+ap,90+hi,90-hi};
    for (int i=0; i<8; i++) setServo(i, position[i]);
}

void MiniKame::zero(){
    for (int i=0; i<8; i++) setServo(i, 90);
}

void MiniKame::reverseServo(int id){
    if (reverse[id])
        reverse[id] = 0;
    else
        reverse[id] = 1;
}


void MiniKame::setServo(int id, float target){
    if (!reverse[id])
        servo[id].writeMicroseconds(angToUsec(target+trim[id]));
    else
        servo[id].writeMicroseconds(angToUsec(180-(target+trim[id])));
    _servo_position[id] = target;
}

float MiniKame::getServo(int id){
    return _servo_position[id];
}


void MiniKame::moveServos(int time, float target[8]) {
    if (time>10){
        for (int i = 0; i < 8; i++)	_increment[i] = (target[i] - _servo_position[i]) / (time / 10.0);
        _final_time =  millis() + time;

        while (millis() < _final_time){
            _partial_time = millis() + 10;
            for (int i = 0; i < 8; i++) setServo(i, _servo_position[i] + _increment[i]);
            while (millis() < _partial_time); //pause
        }
    }
    else{
        for (int i = 0; i < 8; i++) setServo(i, target[i]);
    }
    for (int i = 0; i < 8; i++) _servo_position[i] = target[i];
}

void MiniKame::execute(float steps, int period[8], int amplitude[8], int offset[8], int phase[8]){

    for (int i=0; i<8; i++){
        oscillator[i].setPeriod(period[i]);
        oscillator[i].setAmplitude(amplitude[i]);
        oscillator[i].setPhase(phase[i]);
        oscillator[i].setOffset(offset[i]);
    }

    unsigned long global_time = millis();

    for (int i=0; i<8; i++) oscillator[i].setTime(global_time);

    _final_time = millis() + period[0]*steps;
    while (millis() < _final_time){
        for (int i=0; i<8; i++){
            setServo(i, oscillator[i].refresh());
        }
        yield();
    }
}

int MiniKame::angToUsec(float value){
    return value/180 * (MAX_PULSE_WIDTH-MIN_PULSE_WIDTH) + MIN_PULSE_WIDTH;
}
