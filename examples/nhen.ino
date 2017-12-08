#include <Servo.h>
Servo hip1;
Servo knee1;
Servo hip2;
Servo knee2;
Servo hip3;
Servo knee3;
Servo hip4;
Servo knee4;
// set variables needed for some tasks
int b;
int x;
int y;
int i;
int j;
int k;
int up;
int down;
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
  hip1.write(90);
  knee2.attach(7);
  hip3.attach(8);
  knee3.attach(9);
  hip4.attach(10);
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
void idle()
{
  delay(80);
}
//////////////////////////////////////
void start()
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
    delay(10);
  }
  delay(500);
  for(turn1 = 20; turn1 <160; turn1++)
  {
    hip1.write(turn1);
    hip2.write(turn1);
    hip3.write(turn1);
    hip4.write(turn1);
    delay(10);
  }
  delay(400);
}
////////////////////////////////////
void hello()
{
  hip1.write(110);
  hip2.write(70);
  hip3.write(70);
  hip4.write(110);
  knee1.write(90);
  knee3.write(90);
  knee2.write(90);
  knee4.write(90);
  delay(500);
  knee1.write(180);
  idle();
  while(i < 3)
  {
    for(x = 180; x > 110; x--)
    {
      knee1.write(x);
      delay(10); 
    }
    for(x = 110; x < 180; x++)
    {
      knee1.write(x);
      delay(10); 
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
      delay(10);
    }
    for(y = 90; y <180; y++)
    {
      hip1.write(y);
      delay(10);
    }
    j++;
  }
}
void standup()
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
    delay(20);
  }
}
//////////////////////////////////////
void laydown()
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
    delay(20);
  }
}
///////////////////////////////////////
void sleep()
{
  // hips
  hip1.write(110);
  hip2.write(70);
  hip3.write(70);
  hip4.write(110);
  // knees
  knee1.write(180);
  knee2.write(180);
  knee3.write(180);
  knee4.write(180);
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
/////////////////////////////////////////////
void exercise()
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
      delay(15); 
    }
    for(x = 180; x >0; x--)
    {
      knee1.write(x);
      knee2.write(x);
      knee3.write(y);
      knee4.write(y);
      y++;
      delay(15); 
    }
    k++;
  }
  y = 0;
}
//////////////////////////////////////////////
void forward()
{
    knee1.write(150);
    idle();
    hip1.write(120);
    
    idle();
    knee1.write(110);
    idle();
    //////////////
    knee4.write(150);
    idle();
    hip4.write(70);      
    idle();
    knee4.write(110);
    idle();
    idle();
    hip1.write(90);
    hip2.write(70);
    hip3.write(70);
    hip4.write(90);
    idle();
    ///////////////////////////////////
    knee2.write(150);
    idle();
    hip2.write(60);

    idle();
    knee2.write(110);
    idle();
    //////////////
    knee3.write(150);
    idle();
    hip3.write(110);
    idle();
    knee3.write(110);
    idle();
    idle();
    hip1.write(110);
    hip2.write(90);
    hip3.write(90);
    hip4.write(110);  
}
///////////////////////////////////////
void turnright()
{
  knee1.write(150);
  knee4.write(150);
  idle();
  hip1.write(110);
  hip4.write(110);
  hip2.write(70);
  hip3.write(70);
  idle();
  knee1.write(90);
  knee4.write(90);
  idle();
  ///////////////////////////
  knee2.write(150);
  knee3.write(150);
  idle();
  hip1.write(160);
  hip4.write(160);
  hip2.write(20);
  hip3.write(20);
  idle();
  knee2.write(90);
  knee3.write(90);
  idle();
}
void turnleft()
{
  knee2.write(150);
  knee3.write(150);
  idle();
  hip2.write(70);
  hip3.write(70);
  hip1.write(110);
  hip4.write(110);
  idle();
  knee2.write(90);
  knee3.write(90);
  idle();
  ///////////////////////////
  knee1.write(150);
  knee4.write(150);
  idle();
  hip2.write(20);
  hip3.write(20);
  hip1.write(160);
  hip4.write(160);
  idle();
  knee1.write(90);
  knee4.write(90);
  idle();
}
///////////////////////////////////////
void loop()
{
  
  standup();
  delay(1000);
  /////////
  hello();
  delay(500);
  /////////
  exercise();
  delay(500);
  ////////
  laydown();
  delay(500);
  while(steps < 2)
  {
    start();  
    steps++;
  }
  delay(1000);
  //////////
  stand2();
  delay(1000);
  while(steps < 5)
  {
    turnleft();
    steps ++;
  }
  stand2();
  delay(1000);
  while(steps > 2)
  {
    turnright();
    steps--;
  }
  /////////////
  stand1();
  delay(2000);
  while(1)
  {
     forward();
  }
}

