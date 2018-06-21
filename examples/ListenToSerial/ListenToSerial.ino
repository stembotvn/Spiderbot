#include <spider.h>

spider robot;

const int MAX_BUF      = 64;
char buffer[MAX_BUF];
int sofar;
////////////////////////////////////////////////////////////////////////////////////////////
void processCommand() {
  int t;

  if( !strncmp(buffer,"standUp",7))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    robot.standUp(t);
  }
  /////////////////////////////////////////////////
  else if( !strncmp(buffer,"layDown",7))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    robot.layDown(t);
  }
  /////////////////////////////////////////////////
  else if( !strncmp(buffer,"sleep",5))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    robot.sleep(t);
  }

 /////////////////////////////////////////////////
  else if( !strncmp(buffer,"stand1",6))
  {
    robot.stand1();
  }
  ////////////////////////////////////////////////
  else if( !strncmp(buffer,"stand2",6))
  {
    robot.stand2();
  }
  ////////////////////////////////////////////////
  else if( !strncmp(buffer,"stand3",6))
  {
    robot.stand3();
  }
  ////////////////////////////////////////////////
  else if( !strncmp(buffer,"start",5))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    robot.start(t);
  }
  ////////////////////////////////////////////////
  else if( !strncmp(buffer,"hello",5))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    robot.hello(t);
  }
  ////////////////////////////////////////////////
  else if( !strncmp(buffer,"exercise",8))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    robot.exercise(t);
  }
  ////////////////////////////////////////////////
  else if( !strncmp(buffer,"forward",7))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    robot.forward(t);
  }
  ////////////////////////////////////////////////
  else if( !strncmp(buffer,"backward",8))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    robot.backward(t);
  }
  ////////////////////////////////////////////////
  else if( !strncmp(buffer,"right",5))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    robot.turnright(t);
  }
  ////////////////////////////////////////////////
  else if( !strncmp(buffer,"left",4))
  {
    char *ptr=buffer;
    while(ptr && ptr<buffer+sofar)
    {
      ptr=strchr(ptr,' ')+1;
      switch(*ptr)
      {
        case 'T': t=atof(ptr+1); break;
        default: ptr=0; break;
      }
    }
    robot.turnleft(t);
  }

}
//////////////////////////////////////////////////////////////////////////////////
void listenToSerial()
{
  while(Serial.available() > 0)
  {
    buffer[sofar++]=Serial.read();
    if(buffer[sofar-1]==';') break;  // in case there are multiple instructions
  }
  // if we hit a semi-colon, assume end of instruction.
  if(sofar>0 && buffer[sofar-1]==';')
  {
    buffer[sofar]=0;
    // echo confirmation
    Serial.println(buffer);
    // do something with the command
    processCommand();
    // reset the buffer
    sofar=0;
    // echo completion
    Serial.print(F("> "));
  }
}
void setup()
{
  robot.init();
  Serial.begin(9600);
}
void loop()
{
  listenToSerial();
}
