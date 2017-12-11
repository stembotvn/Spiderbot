#include "spider.h"
#include "IRremote.h"

#define receiverPin A0

// Define IR Remote Button Codes
#define irUp  16736925
#define irDown 16754775
#define irRight 16761405
#define irLeft 16720605
#define irOK 16712445
#define ir1 16738455
#define ir2 16750695
#define ir3 16756815
#define ir4 16724175
#define ir5 16718055
#define ir6 16743045
#define ir7 16716015
#define ir8 16726215
#define ir9 16734885
#define ir0 16730805
#define irStar 16728765
#define irPound 16732845

spider robot;
IRrecv irrecv(receiverPin);
decode_results results;
int count;
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
    case irUp: //// tiến
      for(count = 0; count < 5; count++)
      {
        robot.forward(70);
        count++;
      }
      break;
    case irDown: //// lùi
      for(count = 0; count < 5; count++)
      {
        robot.backward(70);
        count++;
      }
      robot.backward(70);
      break;
    case irLeft: //// trái
      robot.turnleft(70);
      break;
    case irRight: //// phải
      robot.turnright(70);
      break;
    case irOK: //// ok
      robot.stand2();
      break;
    case ir1: //// 1
      robot.standUp(20);
      break;
    case ir2: //// 2
      robot.sleep(20);      
      break;
    case ir3: //// 3
      robot.stand1();      
      break;
    case ir4: //// 4
      robot.hello(10);
      break;
    case ir5: //// 5
      robot.start(20);
      break;
    case ir6: //// 6
      robot.exercise(20);
      break;
    case ir7: //// 7
      robot.layDown(20);
      break;
    case ir8: //// 8
      robot.stand3();
      break;
    case ir9: //// 9
      
      break;
    case ir0: //// 0
      
      break;
    case irStar: //// *
      
      break;
    case irPound: //// #
      
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

