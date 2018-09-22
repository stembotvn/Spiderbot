#include "spider.h"
#include "RF24.h"
#include <EEPROM.h>
//#include "IRremote.h"

void spider::init()
{
  pinMode(SET, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  _hip1.attach(hip1_pin);
  _knee1.attach(knee1_pin);
  _hip2.attach(hip2_pin);    
  _knee2.attach(knee2_pin);
  _hip3.attach(hip3_pin);
  _knee3.attach(knee3_pin);
  _hip4.attach(hip4_pin);
  _knee4.attach(knee4_pin);
  
   Serial.begin(115200);
   initNRF();
   #ifdef DEBUG
   Serial.print("Guit Start, address: ");
   Serial.println(nodeAddress); 
   #endif 
}
void spider::initNRF()
{
//load_address();
radio.begin();
network.begin(108,nodeAddress);
}
////
void spider::load_address()
{ 
  if (nodeAddress=255) nodeAddress = 2; 
  else  nodeAddress = EEPROM.read(0);
  Serial.print("Address: ");
  Serial.println(nodeAddress);
}
/////

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
	_hip1.write(160);
  _knee1.write(170);
  _hip2.write(160);
  _knee2.write(10);
  _hip3.write(160);
  _knee3.write(10);
  _hip4.write(160);
  _knee4.write(170);
  delay(100);
  for( turn1 = 160; turn1 >20; turn1--)
  {
    _hip1.write(turn1);
    _hip2.write(turn1);
    _hip3.write(turn1);
    _hip4.write(turn1);
    delay(t);
  }
  delay(500);
  for(turn1 = 20; turn1 <160; turn1++)
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
    y = 180;
    for( x = 0; x < 180; x++)
    {
      _knee1.write(x);
      _knee2.write(x);
      _knee3.write(y);
      _knee4.write(y);
      y--;
      delay(t); 
    }
    for(x = 180; x >0; x--)
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
  y = 0;
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
void spider::readRF(){
network.update(); 
RFread_size = 0; 

while ( network.available() )  {
  RF24NetworkHeader header;
  network.peek(header);
  if(header.type == 'T'){
    RFread_size = network.read(header,buffer,40);
    isAvailable = true; 
   #ifdef DEBUG 
    Serial.print("received buffer: ");
    PrintDebug(buffer,RFread_size+2);
    Serial.println();
   #endif 
   State = PARSING; //Data available, go to Parsing
    }
  else if(header.type == 'R'){
   RFread_size = network.read(header,RC_buf,20);
   isAvailable = true; 
   State = RC; //RC data read, go to RC running 

   } 
 }
}
////
void spider::PrintDebug(unsigned char *buf,int len){
  for (int i=0;i<len;i++)
    {
      Serial.print(*(buf+i)); Serial.print("-");
    }
    Serial.println();
}
//////////////////////////////////////////////////
/*
mBlock to Robot: 
ff 55 len idx action device port  slot  data \n
0  1   2   3   4      5      6     7     8
//////////////////////
Robot to mBlock (Response Get action) /////////////
ff 55 idx Type  data  0xa  0xd
0  1   2    3     4 
*/
void spider::parseData()
{ 
  ind = 0; //reset RF_buffer (send) index
  isStart = false;
  int idx = buffer[3];
  command_index = (uint8_t)idx;
  int action = buffer[4];
  int device = buffer[5];
  switch(action){
    case GET:{
        if(device != ULTRASONIC_SENSOR){
          writeHead();
          writeBuffer(ind++,idx);
        }
        readSensor(device);
        writeEnd();
        State = WRITE_RF;
     }
     break;
     case RUN:{
       runModule(device);
       callOK();
       State = WRITE_RF;

     }
      break;
     
  }
}
///////////
void spider::writeRF() {
RF24NetworkHeader header(MASTER_NODE,'T'); //marking data stream is PC/Robot
bool OK = network.write(header,RF_buf,ind+1);
if (OK) {
   #ifdef DEBUG 
    Serial.print("Sent buffer: ");
    PrintDebug(RF_buf,ind+1);
    Serial.println();
   #endif 
  }
else {

 }  
ind = 0; 
State = READ_RF; 

}
/////////
void spider::RC_Run(){

}
/////
void spider::setAddress()
{
  if(!digitalRead(SET))
  {
    Serial.println("Set Address");
    Serial.println("Wait 5s...");
    _startTime = millis();
    while(!digitalRead(SET));
    _duration = millis() - _startTime;
    if(_duration > 5000)
    {
      network.begin(108,Default_Addr);

      Serial.println("Ready to receive new address...");
      for(unsigned long starts = millis(); (millis() - starts) < _timeout;)
      { 
        network.update(); 
         
        while(network.available())
        { 
          RF24NetworkHeader header;
         network.peek(header);
         if (header.type == 'P') {
          network.read(header,&new_addr, 2);
          EEPROM.write(0,new_addr);
          nodeAddress = new_addr; 
          network.begin(108,nodeAddress);       
          Serial.println("Set address done.");
          tick(3,1000,200);
          break;
          }
        }
      }
    }
    else
    {
      Serial.println("No change of address.");
      tick(1,1000,1000);
    }

  }
  State = READ_RF;//back to wait RF message
}
/////////////////
void spider::run(){
 switch  (State) {
   case READ_RF: {
   readRF();
   }
   break;
   case PARSING: {
   parseData();
   }
   break;
   case WRITE_RF: {
   writeRF();
   }
   break;
   case RC : {
   RC_Run();
   }
   break;
   case SET_ADDR: {
 //  setAddress();
   }
   break; 
 }
}
///////////////////////////
//Private method for data package
void spider::writeHead(){
  ind = 0;
  RF_buf[ind++]=0xff;
  RF_buf[ind++]=0x55;
}
void spider::writeEnd(){
RF_buf[ind++] = 0xd; 
RF_buf[ind] = 0xa; 
}

unsigned char spider::readBuffer(int index){    
  return buffer[index]; 
}
void spider::writeBuffer(int index,unsigned char c)
{
  RF_buf[index]=c;
}
void spider::callOK()
{ ind = 0;
  writeBuffer(ind++,0xff);
  writeBuffer(ind++,0x55);
  writeEnd();
}
void spider::sendByte(char c)
{
  writeBuffer(ind++,1);
  writeBuffer(ind++,c);
}
void spider::sendString(String s)
{
  int l = s.length();
  writeBuffer(ind++,4);
  writeBuffer(ind++,l);
  for(int i=0;i<l;i++)
  {
    writeBuffer(ind++,s.charAt(i));
  }
}
void spider::sendFloat(float value)
{
  writeBuffer(ind++,0x2);
  val.floatVal = value;
  writeBuffer(ind++,val.byteVal[0]);
  writeBuffer(ind++,val.byteVal[1]);
  writeBuffer(ind++,val.byteVal[2]);
  writeBuffer(ind++,val.byteVal[3]);
}
void spider::sendShort(double value)
{
  writeBuffer(ind++,3);
  valShort.shortVal = value;
  writeBuffer(ind++,valShort.byteVal[0]);
  writeBuffer(ind++,valShort.byteVal[1]);
}
void spider::sendDouble(double value)
{
  writeBuffer(ind++,2);
  valDouble.doubleVal = value;
  writeBuffer(ind++,valDouble.byteVal[0]);
  writeBuffer(ind++,valDouble.byteVal[1]);
  writeBuffer(ind++,valDouble.byteVal[2]);
  writeBuffer(ind++,valDouble.byteVal[3]);
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
  /*****************Recevice******************
      ff 55 len idx action device port slot data a
      0  1  2   3   4      5      6    7    8
      **************Response*****************
      ff 55 idx type data \r \n
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
void spider::_tone(float noteFrequency, long noteDuration, int silentDuration)
{
  if(silentDuration==0)
    silentDuration = 1;
  tone(buzzer, noteFrequency, noteDuration);
  delay(noteDuration);
  delay(silentDuration);
}
void spider::bendTones(float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration)
{
  if(silentDuration==0)
    silentDuration = 1;
  if(initFrequency < finalFrequency)
  {
    for(int i=initFrequency; i<finalFrequency; i=i*prop)
    {
      _tone(i, noteDuration,silentDuration);
    }
  }
  else
  {
    for(int i=initFrequency; i>finalFrequency; i=i/prop)
    {
      _tone(i, noteDuration, silentDuration);
    }
  }
}
void spider::sing(int songName)
{
  switch(songName)
  {
    case S_connection:
      _tone(note_E5,50,30);
      _tone(note_E6,55,25);
      _tone(note_A6,60,10);
      break;
    case S_disconnection:
      _tone(note_E5,50,30);
      _tone(note_A6,55,25);
      _tone(note_E6,50,10);
      break;
    case S_buttonPushed:
      bendTones (note_E6, note_G6, 1.03, 20, 2);
      delay(30);
      bendTones (note_E6, note_D7, 1.04, 10, 2);
      break;
    case S_mode1:
      bendTones (note_E6, note_A6, 1.02, 30, 10);  //1318.51 to 1760
      break;
    case S_mode2:
      bendTones (note_G6, note_D7, 1.03, 30, 10);  //1567.98 to 2349.32
      break;
    case S_mode3:
      _tone(note_E6,50,100); //D6
      _tone(note_G6,50,80);  //E6
      _tone(note_D7,300,0);  //G6
      break;
    case S_surprise:
      bendTones(800, 2150, 1.02, 10, 1);
      bendTones(2149, 800, 1.03, 7, 1);
      break;
    case S_OhOoh:
      bendTones(880, 2000, 1.04, 8, 3); //A5 = 880
      delay(200);
      for (int i=880; i<2000; i=i*1.04)
      {
        _tone(note_B5,5,10);
      }
      break;
    case S_OhOoh2:
      bendTones(1880, 3000, 1.03, 8, 3);
      delay(200);
      for (int i=1880; i<3000; i=i*1.03)
      {
        _tone(note_C6,10,10);
      }
      break;
    case S_cuddly:
      bendTones(700, 900, 1.03, 16, 4);
      bendTones(899, 650, 1.01, 18, 7);
      break;
    case S_sleeping:
      bendTones(100, 500, 1.04, 10, 10);
      bendTones(2499, 1500, 1.05, 25, 8);
      break;
    case S_happy:
      bendTones(1500, 2500, 1.05, 20, 8);
      bendTones(2499, 1500, 1.05, 25, 8);
      break;
    case S_superHappy:
      bendTones(2000, 6000, 1.05, 8, 3);
      delay(50);
      bendTones(5999, 2000, 1.05, 13, 2);
      break;
    case S_happy_short:
      bendTones(1500, 2000, 1.05, 15, 8);
      delay(100);
      bendTones(1900, 2500, 1.05, 10, 8);
      break;
    case S_sad:
      bendTones(880, 669, 1.02, 20, 200);
      break;
    case S_confused:
      bendTones(1000, 1700, 1.03, 8, 2); 
      bendTones(1699, 500, 1.04, 8, 3);
      bendTones(1000, 1700, 1.05, 9, 10);
      break;
    case S_fart1:
      bendTones(1600, 3000, 1.02, 2, 15);
      break;
    case S_fart2:
      bendTones(2000, 6000, 1.02, 2, 20);
      break;
    case S_fart3:
      bendTones(1600, 4000, 1.02, 2, 20);
      bendTones(4000, 3000, 1.02, 2, 20);
      break;
  }
}