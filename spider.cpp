#include "spider.h"
#include "RF24.h"
#include "EEPROM.h"

void spider::init()
{
  Serial.begin(9600);
  pinMode(SET, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(SR04_Trig, OUTPUT);
  pinMode(SR04_Echo, INPUT);
  _hip1.attach(hip1_pin);
  _knee1.attach(knee1_pin);
  _hip2.attach(hip2_pin);    
  _knee2.attach(knee2_pin);
  _hip3.attach(hip3_pin);
  _knee3.attach(knee3_pin);
  _hip4.attach(hip4_pin);
  _knee4.attach(knee4_pin);

  LDRR = analogRead(LDR1);
  LDRL = analogRead(LDR2);
  LDRR = map(LDRR,0,800,0,100);
  LDRL = map(LDRL,0,800,0,100);
  medium = (LDRL + LDRR) / 2;
}
void spider::initNRF()
{
  radio.begin();
  radio.setChannel(108);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  convertAdd();
}
void spider::convertAdd()
{
  _readAdd = EEPROM.read(0);
  _AddRandom = (_AddDefault & ~0xFFLL) | _readAdd;
  radio.openReadingPipe(1,_AddRandom);
  radio.startListening();
  Serial.print("Address: ");
  Serial.print((unsigned long)(_AddRandom >> 32), 16);
  Serial.println((unsigned long)_AddRandom, 16); 
  Serial.println("Ready to receive data");
}
void spider::setAddress()
{
  if(!digitalRead(SET))
  {
    Serial.println("Set Address");
    Serial.println("Wait 5s...");
    _startTime = millis();
    while(!digitalRead(SET))
    {
      if(millis() - _startTime == 5000)
      {
        Sound.sing(S_mode3);
      }
    }
    _duration = millis() - _startTime;
    if(_duration > 5000)
    {
      radio.openReadingPipe(1,_AddDefault);
      radio.startListening();
      Serial.println("Ready to receive new address...");
      for(unsigned long starts =  millis(); (millis() - starts) < _timeout;)
      {
        if(radio.available())
        {
          radio.read(_Add, sizeof(_Add));
          _address = _Add[0];
          EEPROM.write(0,_address);
          Serial.println("Set address done.");
          Sound.sing(S_connection);
          break;
        }
      }
      convertAdd();
    }
    else
    {
      Serial.println("The address doesn't change.");
      Sound.sing(S_cuddly);
    }
  }
}
void spider::standUp(int t)
{
	_hip1.write(70);
	_hip2.write(110);
 	_hip3.write(110);
	_hip4.write(70);
	delay(100);
	for(int up = 180; up > 90; up--)
	{
    _knee1.write(180 - up);
    _knee3.write(up);
    _knee2.write(up);
    _knee4.write(180 - up);
    delay(t);
	}
}
void spider::sleep(int t)
{
	_hip1.write(70);
	_hip2.write(110);
	_hip3.write(110);
	_hip4.write(70);
  delay(100);
  for(int down = 90; down > 0; down--)
  {
    _knee1.write(180 - down);
    _knee3.write(down);
    _knee2.write(down);
    _knee4.write(180 - down);
    delay(t);
  }
}
void spider::layDown(int t)
{
	_hip1.write(70);
  _hip2.write(110);
  _hip3.write(110);
  _hip4.write(70);
  delay(100);
  for(int slep = 90; slep < 180; slep++)
  {
    _knee1.write(180 - slep);
    _knee3.write(slep);
    _knee2.write(slep);
    _knee4.write(180 - slep);
    delay(t);
  }
}
void spider::stand1()
{
  _hip1.write(70);
  _hip2.write(110);
  _hip3.write(110);
  _hip4.write(70);

  _knee1.write(70);
  _knee2.write(110);
  _knee3.write(110);
  _knee4.write(70); 
}
void spider::stand2()
{
	_hip1.write(90);
  _hip2.write(90);
  _hip3.write(90);
  _hip4.write(90);

  _knee1.write(70);
  _knee2.write(110);
  _knee3.write(110);
  _knee4.write(70); 
}
void spider::stand3()
{
	_hip1.write(90);
  _hip2.write(90);
  _hip3.write(90);
  _hip4.write(90);

  _knee1.write(90);
  _knee2.write(90);
  _knee3.write(90);
  _knee4.write(90); 
}
void spider::start(int t)
{
  int turn1;
	_hip1.write(150);
  _knee1.write(130);
  _hip2.write(150);
  _knee2.write(50);
  _hip3.write(150);
  _knee3.write(50);
  _hip4.write(150);
  _knee4.write(130);
  delay(100);
  for( turn1 = 150; turn1 > 30; turn1--)
  {
    _hip1.write(turn1);
    _hip2.write(turn1);
    _hip3.write(turn1);
    _hip4.write(turn1);
    delay(t);
  }
  delay(500);
  for(turn1 = 30; turn1 < 150; turn1++)
  {
    _hip1.write(turn1);
    _hip2.write(turn1);
    _hip3.write(turn1);
    _hip4.write(turn1);
    delay(t);
  }
}
void spider::hello(int t) 
{   
  int i = 0;
  int j = 0;
  int x,y;
	_hip1.write(50);
  _hip2.write(150);
  _hip3.write(110);
  _hip4.write(50);
  _knee1.write(90);
  _knee3.write(90);
  _knee2.write(90);
  _knee4.write(90);
  delay(500);
  _knee1.write(10);
  delay(100);
  while(i < 2)
  {
    for(x = 0; x < 60; x++)
    {
      _knee1.write(x);
      delay(t); 
    }
    for(x = 60; x > 0; x--)
    {
      _knee1.write(x);
      delay(t); 
    }
    i++;
  }
  delay(100);
  _knee1.write(10);
  while(j < 2)
  {
    for(y = 30; y < 80; y++)
    {
      _hip1.write(y);
      delay(t);
    }
    for(y = 80; y > 30; y--)
    {
      _hip1.write(y);
      delay(t);
    }
    j++;
  }
}

void spider::exercise(int t)
{   
  int k = 0;
  int x,y; 
	_hip1.write(90);
  _hip2.write(90);
  _hip3.write(90);
  _hip4.write(90);
  _knee1.write(90);
  _knee2.write(90);
  _knee3.write(90);
  _knee4.write(90);
  delay(200);
  while(k < 2)
  {
    y = 120;
    for( x = 60; x < 120; x++)
    {
      _knee1.write(x);
      _knee2.write(x);
      _knee3.write(y);
      _knee4.write(y);
      y--;
      delay(t); 
    }
    for(x = 120; x > 60; x--)
    {
      _knee1.write(x);
      _knee2.write(x);
      _knee3.write(y);
      _knee4.write(y);
      y++;
      delay(t); 
    }
    k++;
  }
  y = 60;
}

void spider::forward(int late)
{
  _knee1.write(40);
  delay(late);
  _hip1.write(40);//----1
  delay(late);
  _knee1.write(90);

  _hip2.write(60);//----

  _knee4.write(40);
  delay(late);
  _hip4.write(140);//----4
  delay(late);
  _knee4.write(90);

  _hip4.write(60);//----

  _knee2.write(140);
  delay(late);
  _hip2.write(140);//----2
  delay(late);
  _knee2.write(90);

  _hip1.write(120);//----

  _knee3.write(140);
  delay(late);
  _hip3.write(40);//----3
  delay(late);
  _knee3.write(90);

  _hip3.write(120);//----

}

void spider::backward(int late)
{

  _knee4.write(40);
  delay(late);
  _hip4.write(40);//----4
  delay(late);

  _knee4.write(90);

  _hip2.write(120);//----

  _knee1.write(40);
  delay(late);
  _hip1.write(140);//----1
  delay(late);
  _knee1.write(90);

  _hip4.write(120);//----

  _knee3.write(140);
  delay(late);
  _hip3.write(140);//----3
  delay(late);
  _knee3.write(90);

  _hip1.write(60);//----

  _knee2.write(140);
  delay(late);
  _hip2.write(40);//----2
  delay(late);
  _knee2.write(90);

  _hip3.write(60);//----

}

void spider::turnright(int late)
{
	_knee1.write(40);
  _knee4.write(40);
  delay(late);
  _hip1.write(60);
  _hip4.write(60);
  _hip2.write(120);
  _hip3.write(120);
  delay(late);
  _knee1.write(90);
  _knee4.write(90);
  delay(late);
  ///////////////////////////
  _knee2.write(140);
  _knee3.write(140);
  delay(late);
  _hip1.write(120);
  _hip4.write(120);
  _hip2.write(60);
  _hip3.write(60);
  delay(late);
  _knee2.write(90);
  _knee3.write(90);
  delay(late);
}
void spider::turnleft(int late)
{
	_knee2.write(140);
  _knee3.write(140);
  delay(late);
  _hip2.write(120);
  _hip3.write(120);
  _hip1.write(60);
  _hip4.write(60);
  delay(late);
  _knee2.write(90);
  _knee3.write(90);
  delay(late);
  ///////////////////////////
  _knee1.write(40);
  _knee4.write(40);
  delay(late);
  _hip2.write(60);
  _hip3.write(60);
  _hip1.write(120);
  _hip4.write(120);
  delay(late);
  _knee1.write(90);
  _knee4.write(90);
  delay(late);
}
///
void spider::tones(uint16_t frequency, uint32_t duration)
{
  int period = 1000000L / frequency;
  int pulse = period / 2;
  for (long i = 0; i < duration * 1000L; i += period)
  {
    digitalWrite(buzzer, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(buzzer, LOW);
    delayMicroseconds(pulse);
  }
}
void spider::tick(int n, uint16_t frequency, int times)
{
  for(int i=0; i<n; i++)
  {
    tones(frequency, times);
    digitalWrite(buzzer, LOW);
    delay(times);
  }
}
////
void spider::readSerial(){
    isAvailable = false;
  if(Serial.available()>0){
    isAvailable = true;
    serialRead = Serial.read();}
}
////
void spider::Scratch_command_processing()
{
 /*  isAvailable = false;
  if(Serial.available()>0){
    isAvailable = true;
    serialRead = Serial.read();
  }*/
  if(isAvailable){
    unsigned char c = serialRead&0xff;
    if(c==0x55&&isStart==false){
     if(prevc==0xff){
      index=1;
      isStart = true;
     }
    }else{
      prevc = c;  
      if(isStart){
        if(index==2){
         dataLen = c; 
        }else if(index>2){
          dataLen--;
        }
      buffer[index]=c;
      }
    }
     index++;
     if(index>51){
      index=0; 
      isStart=false;
     }
     if(isStart&&dataLen==0&&index>3){ 
        isStart = false;
        //parseData(); 
        index=0;
     }
  }
 }


/*
ff 55 len idx action device port  slot  data a
0  1  2   3   4      5      6     7     8
*/
void spider::parseData()
{
  isStart = false;
  int idx = buffer[3];
  command_index = (uint8_t)idx;
  int action = buffer[4];
  int device = buffer[5];
  switch(action){
    case GET:{
        if(device != ULTRASONIC_SENSOR){
          writeHead();
          writeSerial(idx);
        }
        readSensor(device);
        writeEnd();
     }
     break;
     case RUN:{
       runModule(device);
       callOK();
     }
      break;
      case RESET:{
        //reset
        
        callOK();
      }
     break;
     case START:{
        //start
        callOK();
      }
     break;
  }
}
void spider::writeHead()
{
  writeSerial(0xff);
  writeSerial(0x55);
}
void spider::writeEnd()
{
  Serial.println(); 
}
void spider::writeSerial(unsigned char c)
{
  Serial.write(c);
}
unsigned char spider::readBuffer(int index)
{
  return buffer[index]; 
}
void spider::writeBuffer(int index,unsigned char c)
{
  buffer[index]=c;
}
void spider::callOK()
{
  writeSerial(0xff);
  writeSerial(0x55);
  writeEnd();
}
void spider::sendByte(char c)
{
  writeSerial(1);
  writeSerial(c);
}
void spider::sendString(String s)
{
  int l = s.length();
  writeSerial(4);
  writeSerial(l);
  for(int i=0;i<l;i++)
  {
    writeSerial(s.charAt(i));
  }
}
void spider::sendFloat(float value)
{
  writeSerial(0x2);
  val.floatVal = value;
  writeSerial(val.byteVal[0]);
  writeSerial(val.byteVal[1]);
  writeSerial(val.byteVal[2]);
  writeSerial(val.byteVal[3]);
}
void spider::sendShort(double value)
{
  writeSerial(3);
  valShort.shortVal = value;
  writeSerial(valShort.byteVal[0]);
  writeSerial(valShort.byteVal[1]);
}
void spider::sendDouble(double value)
{
  writeSerial(2);
  valDouble.doubleVal = value;
  writeSerial(valDouble.byteVal[0]);
  writeSerial(valDouble.byteVal[1]);
  writeSerial(valDouble.byteVal[2]);
  writeSerial(valDouble.byteVal[3]);
}
short spider::readShort(int idx)
{
  valShort.byteVal[0] = readBuffer(idx);
  valShort.byteVal[1] = readBuffer(idx+1);
  return valShort.shortVal;
}
float spider::readFloat(int idx)
{
  val.byteVal[0] = readBuffer(idx);
  val.byteVal[1] = readBuffer(idx+1);
  val.byteVal[2] = readBuffer(idx+2);
  val.byteVal[3] = readBuffer(idx+3);
  return val.floatVal;
}
long spider::readLong(int idx)
{
  val.byteVal[0] = readBuffer(idx);
  val.byteVal[1] = readBuffer(idx+1);
  val.byteVal[2] = readBuffer(idx+2);
  val.byteVal[3] = readBuffer(idx+3);
  return val.longVal;
}
void spider::playTone(int pin, int hz, int ms)
{
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
void spider::noTone(int pin)
{
  int buzzer_pin = pin;
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, LOW);
}
void spider::runModule(int device)
{
  //0xff 0x55 0x6 0x0 0x1 0xa 0x9 0x0 0x0 0xa
  int port = buffer[6];
  int pin = port;
  switch(device)
  {
    case DIGITAL:
    {
      pinMode(pin,OUTPUT);
      int v = readBuffer(7);
      digitalWrite(pin,v);
    }
    break;
    case PWM:
    {
      pinMode(pin,OUTPUT);
      int v = readBuffer(7);
      analogWrite(pin,v);
    }
    break;
    case TONE:
    {
      pinMode(pin,OUTPUT);
      int hz = readShort(7);
      int ms = readShort(9);
      if(ms>0){
        playTone(pin, hz, ms); 
      }
      else
      {
        noTone(pin); 
      }
    }
    break;
    case SERVO_PIN:
    {
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
    case TIMER:
    {
      lastTime = millis()/1000.0; 
    }
    break;
   /////////////////////////
    case RUN_SPIDER:
    {
      int m = readShort(6);
      int speed = readShort(8);
      switch(m)
      {
        case 1:
        {
          forward(speed);
          break;
        }
        case 2:
        {
          backward(speed);
          break;
        }
        case 3:
        {
          turnleft(speed);
          break;
        }
        case 4:
        {
          turnright(speed);
          break;
        }
      }
    }
    break;
    case SLEEP:
    {
      int v = readShort(6);
      sleep(v);
    }
    break;
    case STANDUP:
    {
      int v = readShort(6);
      standUp(v);
    }
    break;
    case LAYDOWN:
    {
      int v = readShort(6);
      layDown(v);
    }
    break;
    case DANCE:
    {
      int v = readShort(6);
      start(v);
    }
    break;
    case HELLO:
    {
      int v = readShort(6);
      hello(v);
    }
    break;
    case EXERCISE:
    {
      int v = readShort(6);
      exercise(v);
    }
    break;
    case STAND1:
    {
      stand1();
    }
    break;
    case STAND2:
    {
      stand2();
    }
    break;
    case STAND3:
    {
      stand3();
    }
    break;
   ///////////////////////////
  }
}
int spider::searchServoPin(int pin)
{
  for(int i=0;i<8;i++)
  {
      if(servo_pins[i] == pin)
      {
        return i;
      }
      if(servo_pins[i]==0)
      {
        servo_pins[i] = pin;
        return i;
      }
    }
    return 0;
}
void spider::readSensor(int device)
{
  /**************************************************
      ff 55 len idx action device port slot data a
      0  1  2   3   4      5      6    7    8
  ***************************************************/
  float value=0.0;
  int port,slot,pin;
  port = readBuffer(6);
  pin = port;
  switch(device)
  {
    case  DIGITAL:
    {
      pinMode(pin,INPUT);
      sendFloat(digitalRead(pin));
    }
    break;
    case  ANALOG:
    {
      pin = analogs[pin];
      pinMode(pin,INPUT);
      sendFloat(analogRead(pin));
    }
    break;
    case  PULSEIN:
    {
      int pw = readShort(7);
      pinMode(pin, INPUT);
      sendShort(pulseIn(pin,HIGH,pw));
    }
    break;
    case ULTRASONIC_ARDUINO:
    {
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
    case TIMER:
    {
      sendFloat((float)currentTime);
    }
    break;
  } 
}
float spider::readSonar()
{
  float range = Distance.Ranging(CM);
  delay(100);
  return range;
}
void spider::moveLDR()
{
  LDRR = analogRead(LDR1);
  LDRL = analogRead(LDR2);
  LDRR = map(LDRR,0,800,0,100);
  LDRL = map(LDRL,0,800,0,100);
  LDRR = LDRR > 100 ? 100 : LDRR;
  LDRL = LDRL > 100 ? 100 : LDRL;

  if((LDRR < (medium + 10)) && (LDRL < (medium + 10)))
  {
    stand2();
  }
  else if((LDRR > (medium + 20)) && (LDRL > (medium + 20)))
  {
    forward(70);
    forward(70);
  }
  else if((LDRL - LDRR) > 20)
  {
    turnleft(70);
  }
  else if((LDRR - LDRL) > 20)
  {
    turnright(70);
  }
}
int spider::readLDRRight()
{
  LDRR = analogRead(LDR1);
  LDRR = map(LDRR,0,800,0,100);
  LDRR = LDRR > 100 ? 100 : LDRR;
  return LDRR;
}
int spider::readLDRLeft()
{
  LDRL = analogRead(LDR2);
  LDRL = map(LDRL,0,800,0,100);
  LDRL = LDRL > 100 ? 100 : LDRR;
  return LDRL;
}