#include <Servo.h>
Servo hip1;
Servo knee1;
Servo hip2;
Servo knee2;
Servo hip3;
Servo knee3;
Servo hip4;
Servo knee4;
/////
// set variables needed for some tasks
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
//////////////////////////////////////
void setup()
{
  pinMode(13, OUTPUT);  // LED pin
  // assign servos to pins and center servos
  hip1.attach(4);
  knee1.attach(5);
  hip2.attach(6);    
  knee2.attach(7);
  hip3.attach(8);
  knee3.attach(9);
  hip4.attach(10);
  knee4.attach(11);
  
  knee1.write(90);
  hip2.write(90);
  knee2.write(90);
  hip3.write(90);
  knee3.write(90);
  hip4.write(90);
  knee4.write(90);
}
//void idle()
//{
//  delay(late);
//}
///////////////////////////////
void standup(int t)
{
  hip1.write(110);
  hip2.write(70);
  hip3.write(70);
  hip4.write(110);
  delay(100);
  for(up = 170; up > 90; up--)
  {
    knee1.write(up);
    knee3.write(up);
    knee2.write(up);
    knee4.write(up);
    delay(t);
  }
}
//////////////////////////////////////
void laydown(int t)
{
  hip1.write(110);
  hip2.write(70);
  hip3.write(70);
  hip4.write(110);
  delay(100);
  for(down = 90; down > 0; down--)
  {
    knee1.write(down);
    knee3.write(down);
    knee2.write(down);
    knee4.write(down);
    delay(t);
  }
}
/////////////////////////////////////
void sleep(int t)
{
  hip1.write(110);
  hip2.write(70);
  hip3.write(70);
  hip4.write(110);
  delay(100);
  for(slep = 90; slep < 180; slep++)
  {
    knee1.write(slep);
    knee3.write(slep);
    knee2.write(slep);
    knee4.write(slep);
    delay(t);
  }
}
//////////////////////////////////////
void stand1()
{
  hip1.write(90);
  knee1.write(110);
  hip2.write(90);
  knee2.write(110);
  hip3.write(90);
  knee3.write(110);
  hip4.write(90);
  knee4.write(110); 
}
/////////////////////////////////////
void stand2()
{
  hip1.write(110);
  knee1.write(90);
  hip2.write(70);
  knee2.write(90);
  hip3.write(70);
  knee3.write(90);
  hip4.write(110);
  knee4.write(90); 
}
//////////////////////////////////////
void start(int t)
{
  hip1.write(160);
  knee1.write(0);
  hip2.write(160);
  knee2.write(0);
  hip3.write(160);
  knee3.write(0);
  hip4.write(160);
  knee4.write(0);
  delay(100);
  for(turn1 = 160; turn1 >20; turn1--)
  {
    hip1.write(turn1);
    hip2.write(turn1);
    hip3.write(turn1);
    hip4.write(turn1);
    delay(t);
  }
  delay(500);
  for(turn1 = 20; turn1 <160; turn1++)
  {
    hip1.write(turn1);
    hip2.write(turn1);
    hip3.write(turn1);
    hip4.write(turn1);
    delay(t);
  }
  delay(400);
}
////////////////////////////////////
void hello(int t)
{
  hip1.write(120);
  hip2.write(60);
  hip3.write(60);
  hip4.write(120);
  knee1.write(90);
  knee3.write(90);
  knee2.write(90);
  knee4.write(90);
  delay(500);
  knee1.write(180);
  delay(late);
  while(i < 3)
  {
    for(x = 180; x > 110; x--)
    {
      knee1.write(x);
      delay(t); 
    }
    for(x = 110; x < 180; x++)
    {
      knee1.write(x);
      delay(t); 
    }
    i++;
  }
  delay(100);
  knee1.write(180);
  while(j < 2)
  {
    for(y = 180; y > 90; y --)
    {
      hip1.write(y);
      delay(t);
    }
    for(y = 90; y <180; y++)
    {
      hip1.write(y);
      delay(t);
    }
    j++;
  }
}

/////////////////////////////////////////////
void exercise(int t)
{
  hip1.write(150);
  hip2.write(30);
  hip3.write(30);
  hip4.write(150);
  knee1.write(90);
  knee2.write(90);
  knee3.write(90);
  knee4.write(90);
  delay(200);
  while(k < 2)
  {
    y = 180;
    for(x = 0; x < 180; x++)
    {
      knee1.write(x);
      knee2.write(x);
      knee3.write(y);
      knee4.write(y);
      y--;
      delay(t); 
    }
    for(x = 180; x >0; x--)
    {
      knee1.write(x);
      knee2.write(x);
      knee3.write(y);
      knee4.write(y);
      y++;
      delay(t); 
    }
    k++;
  }
  y = 0;
}
//////////////////////////////////////////////
void forward(int late)
{
    knee1.write(150);
    delay(late);
    hip1.write(120);
    
    delay(late);
    knee1.write(110);
    delay(late);
    //////////////
    knee4.write(150);
    delay(late);
    hip4.write(70);      
    delay(late);
    knee4.write(110);
    delay(late);
    delay(late);
    hip1.write(90);
    hip2.write(70);
    hip3.write(70);
    hip4.write(90);
    delay(late);
    ///////////////////////////////////
    knee2.write(150);
    delay(late);
    hip2.write(60);

    delay(late);
    knee2.write(110);
    delay(late);
    //////////////
    knee3.write(150);
    delay(late);
    hip3.write(110);
    delay(late);
    knee3.write(110);
    delay(late);
    delay(late);
    hip1.write(110);
    hip2.write(90);
    hip3.write(90);
    hip4.write(110);  
}
void backward(int late)
{
    knee4.write(150);
    delay(late);
    hip4.write(120);
    
    delay(late);
    knee4.write(110);
    delay(late);
    //////////////
    knee1.write(150);
    delay(late);
    hip1.write(70);      
    delay(late);
    knee1.write(110);
    delay(late);
    delay(late);
    hip4.write(90);
    hip3.write(70);
    hip2.write(70);
    hip1.write(90);
    delay(late);
    ///////////////////////////////////
    knee3.write(150);
    delay(late);
    hip3.write(60);

    delay(late);
    knee3.write(110);
    delay(late);
    //////////////
    knee2.write(150);
    delay(late);
    hip2.write(110);
    delay(late);
    knee2.write(110);
    delay(late);
    delay(late);
    hip4.write(110);
    hip3.write(90);
    hip2.write(90);
    hip1.write(110);  
}
///////////////////////////////////////
void turnright(int late)
{
  knee1.write(150);
  knee4.write(150);
  delay(late);
  hip1.write(110);
  hip4.write(110);
  hip2.write(70);
  hip3.write(70);
  delay(late);
  knee1.write(90);
  knee4.write(90);
  delay(late);
  ///////////////////////////
  knee2.write(150);
  knee3.write(150);
  delay(late);
  hip1.write(160);
  hip4.write(160);
  hip2.write(20);
  hip3.write(20);
  delay(late);
  knee2.write(90);
  knee3.write(90);
  delay(late);
}
void turnleft(int late)
{
  knee2.write(150);
  knee3.write(150);
  delay(late);
  hip2.write(70);
  hip3.write(70);
  hip1.write(110);
  hip4.write(110);
  delay(late);
  knee2.write(90);
  knee3.write(90);
  delay(late);
  ///////////////////////////
  knee1.write(150);
  knee4.write(150);
  delay(late);
  hip2.write(20);
  hip3.write(20);
  hip1.write(160);
  hip4.write(160);
  delay(late);
  knee1.write(90);
  knee4.write(90);
  delay(late);
}
///////////////////////////////////////
void loop()
{
    forward(70);
  
}

