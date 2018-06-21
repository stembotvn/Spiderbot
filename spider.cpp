#include "spider.h"
#include "IRremote.h"

spider::spider()
{

}

void spider::init()
{
  _hip1.attach(hip1_pin);
  _knee1.attach(knee1_pin);
  _hip2.attach(hip2_pin);    
  _knee2.attach(knee2_pin);
  _hip3.attach(hip3_pin);
  _knee3.attach(knee3_pin);
  _hip4.attach(hip4_pin);
  _knee4.attach(knee4_pin);
}
void spider::standUp(int t)
{
	_hip1.write(110);
	_hip2.write(70);
 	_hip3.write(70);
	_hip4.write(110);
	delay(100);
	for(int up = 170; up > 90; up--)
	{
    _knee1.write(up);
    _knee3.write(up);
    _knee2.write(up);
    _knee4.write(up);
    delay(t);
	}
}
void spider::layDown(int t)
{
	_hip1.write(110);
	_hip2.write(70);
	_hip3.write(70);
	_hip4.write(110);
  delay(100);
  for(int down = 90; down > 0; down--)
  {
    _knee1.write(down);
    _knee3.write(down);
    _knee2.write(down);
    _knee4.write(down);
    delay(t);
  }
}
void spider::sleep(int t)
{
	_hip1.write(110);
  _hip2.write(70);
  _hip3.write(70);
  _hip4.write(110);
  delay(100);
  for(int slep = 90; slep < 180; slep++)
  {
    _knee1.write(slep);
    _knee3.write(slep);
    _knee2.write(slep);
    _knee4.write(slep);
    delay(t);
  }
}
void spider::stand1()
{
	_hip1.write(90);
  _knee1.write(110);
  _hip2.write(90);
  _knee2.write(110);
  _hip3.write(90);
  _knee3.write(110);
  _hip4.write(90);
  _knee4.write(110); 
}
void spider::stand2()
{
	_hip1.write(110);
  _knee1.write(90);
  _hip2.write(70);
  _knee2.write(90);
  _hip3.write(70);
  _knee3.write(90);
  _hip4.write(110);
  _knee4.write(90); 
}
void spider::stand3()
{
	_hip1.write(160);
  _knee1.write(90);
  _hip2.write(20);
  _knee2.write(90);
  _hip3.write(20);
  _knee3.write(90);
  _hip4.write(160);
  _knee4.write(90); 
}
void spider::start(int t)
{
  int turn1;
	_hip1.write(160);
  _knee1.write(0);
  _hip2.write(160);
  _knee2.write(0);
  _hip3.write(160);
  _knee3.write(0);
  _hip4.write(160);
  _knee4.write(0);
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
	_hip1.write(120);
  _hip2.write(60);
  _hip3.write(60);
  _hip4.write(120);
  _knee1.write(90);
  _knee3.write(90);
  _knee2.write(90);
  _knee4.write(90);
  delay(500);
  _knee1.write(180);
  delay(100);
  while(i < 3)
  {
    for(x = 180; x > 110; x--)
    {
      _knee1.write(x);
      delay(t); 
    }
    for(x = 110; x < 180; x++)
    {
      _knee1.write(x);
      delay(t); 
    }
    i++;
  }
  delay(100);
  _knee1.write(180);
  while(j < 2)
  {
    for(y = 180; y > 90; y --)
    {
      _hip1.write(y);
      delay(t);
    }
    for(y = 90; y <180; y++)
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
	_hip1.write(150);
  _hip2.write(30);
  _hip3.write(30);
  _hip4.write(150);
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
	_knee1.write(150);
  delay(late);
  _hip1.write(120);

  delay(late);
  _knee1.write(110);
  delay(late);
  //////////////
  _knee4.write(150);
  delay(late);
  _hip4.write(70);      
  delay(late);
  _knee4.write(110);
  delay(late);
  delay(late);
  _hip1.write(90);
  _hip2.write(70);
  _hip3.write(70);
  _hip4.write(90);
  delay(late);
  ///////////////////////////////////
  _knee2.write(150);
  delay(late);
  _hip2.write(50);

  delay(late);
  _knee2.write(110);
  delay(late);
  //////////////
  _knee3.write(150);
  delay(late);
  _hip3.write(110);
  delay(late);
  _knee3.write(110);
  delay(late);
  delay(late);
  _hip1.write(110);
  _hip2.write(90);
  _hip3.write(90);
  _hip4.write(110); 
}
void spider::backward(int late)
{
	_knee4.write(150);
  delay(late);
  _hip4.write(120);
    
  delay(late);
  _knee4.write(110);
  delay(late);
  //////////////
  _knee1.write(150);
  delay(late);
  _hip1.write(70);      
  delay(late);
  _knee1.write(110);
  delay(late);
  delay(late);
  _hip4.write(90);
  _hip3.write(70);
  _hip2.write(70);
  _hip1.write(90);
  delay(late);
  ///////////////////////////////////
   _knee3.write(150);
  delay(late);
  _hip3.write(50);

  delay(late);
  _knee3.write(110);
  delay(late);
  //////////////
  _knee2.write(150);
  delay(late);
  _hip2.write(110);
  delay(late);
  _knee2.write(110);
  delay(late);
  delay(late);
  _hip4.write(110);
  _hip3.write(90);
  _hip2.write(90);
  _hip1.write(110);
}
void spider::turnright(int late)
{
	_knee1.write(150);
  _knee4.write(150);
  delay(late);
  _hip1.write(110);
  _hip4.write(110);
  _hip2.write(70);
  _hip3.write(70);
  delay(late);
  _knee1.write(90);
  _knee4.write(90);
  delay(late);
  ///////////////////////////
  _knee2.write(150);
  _knee3.write(150);
  delay(late);
  _hip1.write(160);
  _hip4.write(160);
  _hip2.write(20);
  _hip3.write(20);
  delay(late);
  _knee2.write(90);
  _knee3.write(90);
  delay(late);
}
void spider::turnleft(int late)
{
	_knee2.write(150);
  _knee3.write(150);
  delay(late);
  _hip2.write(70);
  _hip3.write(70);
  _hip1.write(110);
  _hip4.write(110);
  delay(late);
  _knee2.write(90);
  _knee3.write(90);
  delay(late);
  ///////////////////////////
  _knee1.write(150);
  _knee4.write(150);
  delay(late);
  _hip2.write(20);
  _hip3.write(20);
  _hip1.write(160);
  _hip4.write(160);
  delay(late);
  _knee1.write(90);
  _knee4.write(90);
  delay(late);
}
////
void spider::processCommand()
{
  int t;
  if( !strncmp(_buffer,"standUp",7))
  {
    char *ptr=_buffer;
    while(ptr && ptr<_buffer+_sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    standUp(t);
  }
  /////////////////////////////////////////////////
  else if( !strncmp(_buffer,"layDown",7))
  {
    char *ptr=_buffer;
    while(ptr && ptr<_buffer+_sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    layDown(t);
  }
  /////////////////////////////////////////////////
  else if( !strncmp(_buffer,"sleep",5))
  {
    char *ptr=_buffer;
    while(ptr && ptr<_buffer+_sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    sleep(t);
  }

 /////////////////////////////////////////////////
  else if( !strncmp(_buffer,"stand1",6))
  {
    stand1();
  }
  ////////////////////////////////////////////////
  else if( !strncmp(_buffer,"stand2",6))
  {
    stand2();
  }
  ////////////////////////////////////////////////
  else if( !strncmp(_buffer,"stand3",6))
  {
    stand3();
  }
  ////////////////////////////////////////////////
  else if( !strncmp(_buffer,"start",5))
  {
    char *ptr=_buffer;
    while(ptr && ptr<_buffer+_sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    start(t);
  }
  ////////////////////////////////////////////////
  else if( !strncmp(_buffer,"hello",5))
  {
    char *ptr=_buffer;
    while(ptr && ptr<_buffer+_sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    hello(t);
  }
  ////////////////////////////////////////////////
  else if( !strncmp(_buffer,"exercise",8))
  {
    char *ptr=_buffer;
    while(ptr && ptr<_buffer+_sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    exercise(t);
  }
  ////////////////////////////////////////////////
  else if( !strncmp(_buffer,"forward",7))
  {
    char *ptr=_buffer;
    while(ptr && ptr<_buffer+_sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    forward(t);
  }
  ////////////////////////////////////////////////
  else if( !strncmp(_buffer,"backward",8))
  {
    char *ptr=_buffer;
    while(ptr && ptr<_buffer+_sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    backward(t);
  }
  ////////////////////////////////////////////////
  else if( !strncmp(_buffer,"right",5))
  {
    char *ptr=_buffer;
    while(ptr && ptr<_buffer+_sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    turnright(t);
  }
  ////////////////////////////////////////////////
  else if( !strncmp(_buffer,"left",4))
  {
    char *ptr=_buffer;
    while(ptr && ptr<_buffer+_sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    turnleft(t);
  }
}
void spider::listenToSerial()
{
  while(Serial.available() > 0)
  {
    _buffer[_sofar++]=Serial.read();
    if(_buffer[_sofar-1]==';') break;  // in case there are multiple instructions
  }
  // if we hit a semi-colon, assume end of instruction.
  if(_sofar>0 && _buffer[_sofar-1]==';')
  {
    _buffer[_sofar]=0;
    // echo confirmation
    Serial.println(_buffer);
    // do something with the command
    processCommand();
    // reset the buffer
    _sofar=0;
    // echo completion
    Serial.print(F("> "));
  }
}
