#include <spider.h>
#include <SPI.h>
#include "RF24.h"
spider Guti;
RF24 radio(CE_PIN, CSN_PIN);
int Data[8]; //Received data array
bool updated = 0;
int F;
int B;
int L;
int R;
int X;
int LED;
int speaker;
int Speed;
void Move()
{
  if(speaker == 0)
  {
    Guti.tone(1000,1000);
  }
  else if(F == 0)

  {
    Guti.forward(70);
    delay(100);
    Guti.stand2();
  }
  else if(B == 0)
  {
    Guti.backward(70);
    delay(100);
    Guti.stand2();
  }
  else if(R == 0)
  {
    Guti.turnright(70);
    delay(100);
    Guti.stand2();
  }
  else if(L == 0)
  {
    Guti.turnleft(70);
    delay(100);
    Guti.stand2();
  }
  else if(X == 0)
  {
    Guti.exercise(20);
    delay(100);
    Guti.stand2();
  }
  else if(LED == 0)
  {
    Guti.start(20);
    delay(100);
    Guti.stand2();
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
    L = Data[2];
    R = Data[3];
    speaker = Data[4];
    X = Data[5];
    LED = Data[6];
    Speed = Data[7];
    updated = 0;
  }
  Move();
}
void setup()
{
  Guti.init();
  Guti.initNRF();
}
void loop() 
{
 Guti.setAddress();
 readRadio();
}
