#include <spider.h>
#include <SPI.h>
#include "RF24.h"
spider Guti;
RF24 radio(CE_PIN, CSN_PIN);
int Data[9]; //Received data array
bool updated = 0;
int F;
int B;
int L;
int R;
int X;
int Y;
int Led;
int speaker;
int Speed;
void Move()
{
  if(speaker == 0)
  {
    Guti.tone(500,200);
    delay(1000);
  }
  else if(F == 0)

  {
    for(int i=1; i<=5; i++)
    {
      Guti.forward(70);
      delay(100);
    }
  }
  else if(B == 0)
  {
    for(int i=1; i<=5; i++)
    {
      Guti.backward(70);
      delay(100);
    }
  }
  else if(R == 0)
  {
    for(int i=1; i<=5; i++)
    {
      Guti.turnright(70);
      delay(100);
    }
  }
  else if(L == 0)
  {
    for(int i=1; i<=5; i++)
    {
      Guti.turnleft(70);
      delay(100);
    }
  }
}
void readRadio()
{
  if ( radio.available())
  {
    while(radio.available())
    {
      radio.read( Data, sizeof(Data));
      updated = 1;
    }
  }
  ////////////////////////////////
  if(updated)
  {
    F = Data[0];
    B = Data[1];
    R = Data[2];
    L = Data[3];
    Led = Data[4];
    X = Data[5];
    speaker = Data[6];
    Y = Data[7];
    Speed = Data[8];
    updated = 0;
  }
  Move();
}
void setup()
{
  Guti.init();
}
void loop() 
{
 Guti.setAddress();
 readRadio();
}
