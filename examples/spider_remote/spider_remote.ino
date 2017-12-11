#include "spider.h"
#include "IRremote.h"

#define receiverPin A0
spider robot;
IRrecv irrecv(receiverPin);
decode_results results;
int dem;
//////////////////////////////////////
void setup()
{
  robot.init();
  Serial.begin(9600);
  irrecv.enableIRIn();
}
void ReadRemote()
{
  switch(results.value)
  {
    case 16736925: //// tiến
      for(dem = 0; dem < 5; dem++)
      {
        robot.forward(70);
        dem++;
      }
      break;
    case 16754775: //// lùi
      for(dem = 0; dem < 5; dem++)
      {
        robot.backward(70);
        dem++;
      }
      robot.backward(70);
      break;
    case 16720605: //// trái
      robot.turnleft(70);
      break;
    case 16761405: //// phải
      robot.turnright(70);
      break;
    case 16712445: //// ok
      robot.stand2();
      break;
    case 16738455: //// 1
      robot.standUp(20);
      break;
    case 16750695: //// 2
      robot.sleep(20);      
      break;
    case 16756815: //// 3
      robot.stand1();      
      break;
    case 16724175: //// 4
      robot.hello(10);
      break;
    case 16718055: //// 5
      robot.start(20);
      break;
    case 16743045: //// 6
      robot.exercise(20);
      break;
    case 16716015: //// 7
      robot.layDown(20);
      break;
    case 16726215: //// 8
      robot.stand3();
      break;
    case 16734885: //// 9
      
      break;
    case 16730805: //// 0
      
      break;
    case 16728765: //// *
      
      break;
    case 16732845: //// #
      
      break;
  }
}
void loop()
{
  if (irrecv.decode(&results)) // nếu nhận được tín hiệu
  {
    Serial.println(results.value, HEX); // in ra Serial Monitor
    ReadRemote();
    delay(200);
    irrecv.resume(); // nhận giá trị tiếp theo
  }
  
}

