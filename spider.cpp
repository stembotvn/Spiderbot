#include "spider.h"
#include "RF24.h"
#include <EEPROM.h>

void spider::init(int _address)
{ 
  
  pinMode(SET, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  Robot.init();
   Serial.begin(115200);
   initNRF(_address);
   #ifdef DEBUG
   Serial.print("Guit Start, address: ");
   Serial.println(myNode); 
   #endif 
   medium = (getLight(LEFT) + getLight(RIGHT)) / 2;
   //randomSeed(millis());
   Robot.zero();
   Sound.sing(S_connection); 
}
void spider::initNRF(int _address)
{
  //config_Address(2,10); 
  if (!_address){
    #if DEBUG
    Serial.println("Pairing Mode loading...");
    #endif
    load_address();
    connection = PAIRING;
  }
  else  {                  //Network addressing Mode
    myNode = _address;     
    toNode = 0;            //set Master address 
    connection = NETWORK;
  } 
  Radio.init(myNode);    //init with my Node address
  //Radio.Multicast_readingStart();
  first_run = true;      //set first run for next State
}
////

////
void spider::load_address()
{ 
   #ifdef DEBUG
   Serial.println("Loading my Config... ");
   #endif
   myNode = EEPROM_readInt(0);
   toNode = EEPROM_readInt(2);
   #ifdef DEBUG
  Serial.print("My Address: ");
  Serial.println(myNode);
   Serial.print("Target Address: ");
  Serial.println(toNode);
    #endif

 // Radio.init(myNode);    //init with my Node address

}

///
void spider::rest(){

}
/////////
void spider::move(int type, int step,int speed) {
  {
      switch(type)
      { 
        case 0:
           {
          rest();
          break;
        }
        case 1:
        {
          Robot.walk(step, speed);
          break;
        }
        case 2:
        {
          Robot.back(step, speed);
          break;
        }
        case 3:
        {
          Robot.turnL(step,speed);
          break;
        }
        case 4:
        {
          Robot.turnR(step,speed);
          break;
        }
      }
    }
}
////
void spider::action(int types,int speed){
switch (types) {
  case 0 : {

    } break;
  case 1 : {

    } break;   
  }
}
////
void spider::readRF(){
RFread_size = 0; 
//uint8_t pipenum; 
//if ( Radio.RFDataCome(pipenum) )  {
  if ( Radio.RFDataCome() )  {
    Serial.println("RF data come!");
    #ifdef DEBUG
    //  Serial.print("pipenum: ");
    //  Serial.println(pipenum);
    #endif
    while (Radio.RFDataCome()) {
   // if (pipenum==1)    connectionType = PAIRING; 
   // else if (pipenum == 2) connectionType = NETWORK; 
     RFread_size = Radio.RFRead(buffer); 
        }
        isAvailable = true; 
    if (RFread_size <3) return;
    else if (buffer[0]==0xFF && buffer[1] == 0x55 && buffer[2] == (RFread_size - 3)){
      
       #ifdef DEBUG 
    Serial.print("received valid Scratch RF data: ");
    PrintDebug(buffer,RFread_size);
    Serial.println();
   #endif 
     State = PARSING;
     first_run = true;      //set first run for next State
     #ifdef DEBUG
     Serial.println("Go to State 1: PARSING");
     #endif  
     return;
    }
    else  {
      Serial.println("invalid data received"); 
      callOK();
     State = WRITE_RF;  
     first_run = true;      //set first run for next State
     return;
    }
   //Data available, go to Parsing
   
  
 }
else {
  inConfig();  //if not receive RF data, check the config key 
  //State = IN_CONFIG;    //if not received RF message, go to check config mode access
  //first_run = true; 
  if (Mode == RC_MODE && RC_type != RC_MANUAL) { State = RC; first_run = true; } 
  } 
}
////
void spider::PrintDebug(unsigned char *buf,int len){
  for (int i=0;i<len;i++)
    {
      Serial.print(*(buf+i),HEX); Serial.print("-");
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
////////////////////////////////////////////////////
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
      if (connectionType==PAIRING) {
        if(device != ULTRASONIC_SENSOR){
          writeHead();
          writeBuffer(ind++,idx);
        }
        readSensor(device);
        writeEnd();
        State = WRITE_RF;
        first_run = true;      //set first run for next State
      }
      else {
        State = READ_RF;
        first_run = true; 
      }
     }
     break;
     case RUN:{ //need DEBUG Here
       runFunction(device);
       if (Mode == CONFIG_MODE) { 
         if (device == CONFIG) {
           Mode = RUN_MODE; //done config, go back to run mode, no ACK response
         State = READ_RF;
         first_run = true; }
         }
       else if (Mode == RC_MODE) {    //in RC Mode 
          if (RC_type != RC_MANUAL) { 
              callOK();   //response OK to Remote
              writeRF();  //
              State = RC; 
              first_run = true; 

            #ifdef DEBUG 
            Serial.println("RC Auto Mode, Goto RC State");
            #endif
          }
          else {
             
          callOK();   //response OK when complete action
          State = WRITE_RF; 
          Mode = RUN_MODE;          
          first_run = true; 
          }
       }  
       else  {  //in USB wireless mode
       if(connectionType == PAIRING){
          callOK();   //response OK when complete action
          #ifdef DEBUG 
            Serial.println("Scratch command Done, go to send response");
          #endif 
        // delay(2000);
          State = WRITE_RF;
          first_run = true; 
        }
       else{
          State = READ_RF;
          first_run = true; 
        }  //set first run for next State
        }    
       
      
     }
      break;
     
  }
   clearBuffer(buffer,sizeof(buffer));  //clear 20byte of receiving buffers 
}
///////////
void spider::writeRF() {
bool OK = Radio.RFSend(toNode,RF_buf,sizeof(RF_buf));
if (OK) {
   #ifdef DEBUG 
    Serial.print("Sent buffer: ");
    PrintDebug(RF_buf,ind+1);
    Serial.println();
   #endif 
  }
else {
  #ifdef DEBUG 
    Serial.println("Sent FAIL ");
   
   #endif 
 }  
ind = 0; 
State = READ_RF; 
first_run = true;      //set first run for next State


}
/////////
void spider::RC_Run(){
switch (RC_type){ 
  case LIGHT_FOLLOW: {
     int left = getLight(LEFT);
     int right = getLight(RIGHT);
     if((right < (medium + 10)) && (left < medium + 10))
        Robot.home();
     else if((right > (medium + 20)) && (left > medium + 20))
        Robot.walk(2,speed);
     else if((left - right) > 30)
        Robot.turnL(2,speed);
     else if((right - left) > 30)
        Robot.turnR(2,speed);
  } break;

  case AVOID_OBSTACLE: {
     int distance = getDistance();
     if (distance > 15) Robot.walk(2,speed); 
     else { 
       Robot.home();
       Sound.sing(S_confused); 
       Robot.dance(2,speed);
       Robot.back(3,speed);
       Robot.turnL(3,speed); 
       if (getDistance()<15) Robot.turnR(4,speed);
     }
    } break;
  case CREATE_SOUND: {
    Sound.playMusic(songname);
    RC_type = RC_MANUAL;
    songname--;
    if(songname <= 0)  songname = 3;
  } break;
}
 State = READ_RF; 
 first_run = true;
}
/////
bool spider::inConfig() //check if press CONFIG KEY
{
  uint8_t size;
  long _duration=0;
  bool accessed = false;
  if(!digitalRead(SET))
  {
    #ifdef DEBUG
    Serial.println("CONFIG KEY PRESSED!");
    Serial.println("Wait 3s...");
    #endif 
    _startTime = millis();
    while(!digitalRead(SET)) {
    _duration = millis() - _startTime; 
      if(_duration > 3000) {
        accessed = true; 
        Sound.sing(S_buttonPushed);
      }
    }    // wait to check holding key timing
    if(accessed)
    { 
      Radio.init(Default_Addr);  // set Default Address to listen for Config Address Mode 
      #ifdef DEBUG
      Serial.print("GOING TO CONFIG MODE WITH DEFAULT CONFIG ADDRESS...:");Serial.println(Default_Addr);
      #endif 
      Mode = CONFIG_MODE; 
      accessed = false; 
     }
    else
    {
      #ifdef DEBUG
      Serial.println("CONFIG MODE IS NOT ACCESSED!");
      #endif 
     // tick(1,1000,1000);
     Sound.sing(S_disconnection);
    }

  }
  else return 0;
 // State = READ_RF; //back to wait RF message
 // Mode = CONFIG_MODE; 
//  first_run = true; 
}
////////////////
void spider::config_Address(uint16_t myAddress,uint16_t toAddress){

          myNode = myAddress;   //need be checked endianess
          toNode = toAddress;  
          #ifdef DEBUG
          Serial.println("Receive New addressing!");    
          Serial.print("My new Address:"); Serial.println(myNode);
          Serial.print("Sending to Address:"); Serial.println(toNode);
          #endif 
          if (toNode!=0) {   // not in Network mode, do not save     
          EEPROM_writeInt(0,myNode);  //saving my new address
          EEPROM_writeInt(2,toNode);    //saving target address
          }
          #ifdef DEBUG
          Serial.print("Set address to RF:"); Serial.println(myNode);
          #endif
         // myNode = new_addr; 
          //Radio.SetAddress(myNode); 
          
          Radio.init(myNode);    //init with my Node address
      
          #ifdef DEBUG
          Serial.print("Set address done:"); Serial.println(myNode);
          #endif
         // tick(3,1000,200);
                 
}
/////////////////
void spider::run(){
  if (first_run)  {
   timeStart = millis();
   #ifdef DEBUG 
         Serial.print("State No: ");
         Serial.print(State);
         Serial.println("   Running");
   #endif
   first_run = false; 
}  
 switch  (State) {
   case READ_RF: {     //check and read RF data comming if any, if not, go to check setting Address mode
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
  
 }
}

void spider::runFunction(int device)
{
  //0xff 0x55 0x6 0x0 0x1 0xa 0x9 0x0 0x0 0xa
  //int port = buffer[6];
  //int pin = port;
  switch(device)
  {
       
   /////////////////////////
    case RUN_SPIDER:
    {
      int m = readShort(6);
      int speed = readShort(8);
      switch(m)
      {
        case 1:
        {
          Robot.walk(1,speed);
          break;
        }
        case 2:
        {
          Robot.back(1,speed);
          break;
        }
        case 3:
        {
          Robot.turnL(1,speed);
          break;
        }
        case 4:
        {
          Robot.turnR(1,speed);
          break;
        }
      }
    Mode = RUN_MODE;
 
    }
    break;
    case UPDOWN:
    {
      int v = readShort(6);
      Robot.upDown(1,v);
      Mode = RUN_MODE;

    }
    break;
    case PUSHUP:
    {
      int v = readShort(6);
      Robot.pushUp(1,v);
      Mode = RUN_MODE;
    }
    break;
    case DANCE:
    {
      int v = readShort(6);
      Robot.dance(1,v);
      Mode = RUN_MODE;
    }
    break;
    case HELLO:
    {
      Robot.hello();
      Mode = RUN_MODE;
    }
    break;
    case ZERO:
    {
      Robot.zero();
      Mode = RUN_MODE;
    }
    break;
    case HOME:
    {
      Robot.home();
      Mode = RUN_MODE;
    }
    break;
   case SING:
    {
      int song = readShort(6);
      Sound.playMusic(song);
      Mode = RUN_MODE;
    }
    break;
    case CONFIG:
    {
      if (Mode = CONFIG_MODE) {
      uint16_t myAddress = readShort(6);
      uint16_t toAddress = readShort(8);
      config_Address(myAddress,toAddress); //saving new addressing pair
      Sound.sing(S_connection);
      // Mode = RUN_MODE;
   
      }
    }break;

    case RCDATA:
    {
      Mode = RC_MODE; 
      keyState = buffer[6];
      varSlide = buffer[7];
     /* if (keyState!=0) {  //when press; 
      remoteProcessing();      
      }
      else  {
        Robot.home();//RC_type = RC_MANUAL;
      } */
      remoteProcessing();      

    }break;
   ///////////////////////////
   
  }
}
/////////////
void spider::remoteProcessing(){
  ////////////////////////////////////////////////
  ///keyState  7  6  5  4  3  2  1   0        ////
  ///          F4 F3 F2 F1 L  R Bwd Fwd       ////
  ////////////////////////////////////////////////
  bool shift = bitRead(keyState,4);
 speed = map(varSlide,0,100,3000,300); //mapping from 0-100% to real delay value of steps 150 ms - 50ms
if (bitRead(keyState,0)) { //forward
  if(!shift)
  {
    Robot.walk(1,speed);
  }
  else 
    Robot.dance(2,speed);
  RC_type = RC_MANUAL;
 
 } 
else if (bitRead(keyState,1)) {
  if(!shift)
  {
    Robot.back(1,speed);
  }
  else 
    Robot.pushUp(2,speed);
  RC_type = RC_MANUAL;
}
else if (bitRead(keyState,2)) {
  if(!shift)
  {
    Robot.turnR(1,speed);
  }
  else 
    Robot.upDown(2,speed);
  RC_type = RC_MANUAL;
}
else if (bitRead(keyState,3)) {
  if(!shift)
  {
    Robot.turnL(1,speed);
  }
  else
    Robot.hello();
  RC_type = RC_MANUAL;
} 

 if (bitRead(keyState,4)) {   //F1 key press(shift)
   RC_type = RC_MANUAL;

}
else if (bitRead(keyState,5)) {  //F2 key press
   RC_type  = LIGHT_FOLLOW; 
   

}
else if (bitRead(keyState,6)) {  //F3 key press
   RC_type  = AVOID_OBSTACLE; 

   //State = RC; 
}

else if (bitRead(keyState,7)) {  //F4 key press
   RC_type  = CREATE_SOUND; 

    //  State = RC;
}
}     
// /////////////
void spider::readSensor(int device)
{
  /*****************Recevice*************************
      ff 55 len idx action device port slot data a
      0  1  2   3   4      5      6    7    8
  *********************Response**********************
      ff 55 idx type data \r \n
  ***************************************************/
  float value=0.0;
  int port,slot,pin;
  port = readBuffer(6);
  pin = port;
  switch(device)
  {
     case DISTANCE:
    {
      sendFloat((float)getDistance());
    }
    break;

    case LIGHT_LEVEL:
    {
     uint8_t side = readBuffer(6); 
     sendFloat((float)getLight(side));
    }
    break;

    case DONE:
    {
     sendFloat(actionDone);
    }
    break;
  } 
}
///////////////////////////////////////////////
 float spider::getDistance(){
  return SR04.Ranging(CM);
 }
 //////////////////////////////////////////////
int spider::getLight(byte side){
 if (!side) {  //LEFT
  int LDRL = analogRead(LDR2);
  LDRL = map(LDRL,0,800,0,100);
  LDRL = LDRL > 100 ? 100 : LDRL;
  return LDRL;
 } 
 else {
  int LDRR = analogRead(LDR1);
  LDRR = map(LDRR,0,800,0,100);
  LDRR = LDRR > 100 ? 100 : LDRR;
  return LDRR;
 }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////
void spider::EEPROM_writeInt(int address,uint16_t value) {
  
      //Decomposition from a int to 2 bytes by using bitshift.
      //One = Most significant -> Two = Least significant byte
      byte two = (value & 0xFF);
      byte one = ((value >> 8) & 0xFF);
      

      //Write the 2 bytes into the eeprom memory.
      EEPROM.write(address, two);
      EEPROM.write(address + 1, one);
     
     
}
/////////////////////////
uint16_t spider::EEPROM_readInt(int address){
uint16_t two = EEPROM.read(address);
uint16_t one = EEPROM.read(address+1); 
return ((two & 0xFF) + ((one<<8)&0xFFFF));
}
///////////////////////////
void spider::clearBuffer(unsigned char *buf, int leng){
  for (int i=0;i<leng;i++) {
    *(buf+i) = 0; 
  }
}

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