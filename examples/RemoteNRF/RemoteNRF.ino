#include <spider.h>

spider Guti;

int Data[9];
int old_Data[9];

bool updated = 0;
int F;
int B;
int L;
int R;
int X;
int Y;
int D;
int BZ;
int Speed;

void Move()
{
  if(F == 1)
  {
    Guti.forward(70);
    delay(100);
    Guti.stand2();
  }
  else if(B == 1)
  {
    Guti.backward(70);
    delay(100);
    Guti.stand2();
  }
  else if(R == 1)
  {
    Serial.println("Turn right");
    Guti.turnright(70);
    delay(100);
    Guti.stand2();
  }
  else if(L == 1)
  {
    Serial.println("Turn left");
    Guti.turnleft(70);
    delay(100);
    Guti.stand2();
  }
  ////////////////////////////////////////////
  else if(X == 1)
  {
    Guti.Sound.sing(S_mode1);
    while(1)
    {
      Guti.moveLDR();
      readRadio();
      if(F==1 || B==1 || L==1 || R==1 || Y==1 || D==1 || BZ==1)
        break;
    }
  }
  else if (Y == 1)
  {
    Guti.Sound.sing(S_mode2);
    while(1)
    {
      Avoid_obstacle();
      readRadio();
      if(F==1 || B==1 || L==1 || R==1 || X==1 || D==1 || BZ==1)
        break;
    }
  }
  else if(D == 1)
  {
    dance();
  }
  else if(BZ == 1)
  {
    Serial.println(" BZ = 1 ");
    SingSong();
  }
}
void dance()
{
  int dances = random(0,4);
  switch(dances)
  {
    case 0:
      Guti.hello(20);
      break;
    case 1:
      Guti.exercise(20);
      break;
    case 2:
      Guti.start(20);
      break;
    case 3:
      Guti.layDown(20);
      Guti.standUp(20);
      break;
    case 4:
      Guti.sleep(20);
      break;
  }
}
void SingSong()
{
  Serial.println("Sing song");
  int song = random(0,18);
  switch(song)
  {
    case 0:
      Guti.Sound.sing(S_connection);
      break;
    case 1:
      Guti.Sound.sing(S_disconnection);
      break;
    case 2:
      Guti.Sound.sing(S_buttonPushed);
      break;
    case 3:
      Guti.Sound.sing(S_mode1);
      break;
    case 4:
      Guti.Sound.sing(S_mode2);
      break;
    case 5:
      Guti.Sound.sing(S_mode3);
      break;
    case 6:
      Guti.Sound.sing(S_surprise);
      break;
    case 7:
      Guti.Sound.sing(S_OhOoh);
      break;
    case 8:
      Guti.Sound.sing(S_OhOoh2);
      break;
    case 9:
      Guti.Sound.sing(S_cuddly);
      break;
    case 10:
      Guti.Sound.sing(S_sleeping);
      break;
    case 11:
      Guti.Sound.sing(S_happy);
      break;
    case 12:
      Guti.Sound.sing(S_superHappy);
      break;
    case 13:
      Guti.Sound.sing(S_happy_short);
      break;
    case 14:
      Guti.Sound.sing(S_sad);
      break;
    case 15:
      Guti.Sound.sing(S_confused);
      break;
    case 16:
      Guti.Sound.sing(S_fart1);
      break;
    case 17:
      Guti.Sound.sing(S_fart2);
      break;
    case 18:
      Guti.Sound.sing(S_fart3);
      break;
  }
  
}
void Avoid_obstacle()
{
  int distance = Guti.readSonar();
  Serial.println(distance);
  if(distance < 25)
  {
    Guti.Sound.sing(S_OhOoh);
    Guti.stand2();
    delay(1000);
    Guti.turnright(70);
    Guti.turnright(70);
    Guti.stand2(); 
    distance = Guti.readSonar();
    if(distance > 25)
      Guti.Sound.sing(S_happy);
  }
  else 
    Guti.forward(70);
}
void readRadio()
{
  if (Guti.radio.available())
  {
    while(Guti.radio.available())
    {
      Guti.radio.read(Data, sizeof(Data));
        F = Data[0];
        B = Data[1];
        L = Data[2];
        R = Data[3];
        BZ = Data[4];
        D = Data[5];
        X = Data[6];
        Y = Data[7];
        Speed = Data[8];
    }
  }
}
//////////////////////////////////////////////
void setup()
{
  Guti.init();
  Guti.initNRF();
  randomSeed(analogRead(A5));
  Guti.Sound.sing(S_connection);
  delay(1000);
}
void loop() 
{
  Guti.setAddress();
  readRadio();
  Move();
}
