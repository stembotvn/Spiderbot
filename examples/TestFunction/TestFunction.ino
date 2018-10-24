#include <spider.h>

spider Guti;

void setup()
{
  Guti.init();
  Guti.stand3();
  delay(1000);
}
void loop() 
{
  //Guti.backward(100);
  Guti.forward(100);
}
