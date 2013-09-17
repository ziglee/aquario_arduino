#include <TM1638.h>  
  
static TM1638 disp(8, 9, 7, true, 7);  
  
void setup() {
  disp.clearDisplay();
  disp.setDisplayToString(" CASSIO ");
  disp.setLED(TM1638_COLOR_GREEN, 0);
  disp.setLED(TM1638_COLOR_GREEN, 1);
  disp.setLED(TM1638_COLOR_GREEN, 2);
  disp.setLED(TM1638_COLOR_GREEN, 3);
  disp.setLED(TM1638_COLOR_GREEN, 4);
  disp.setLED(TM1638_COLOR_GREEN, 5);
  disp.setLED(TM1638_COLOR_GREEN, 6);
  disp.setLED(TM1638_COLOR_GREEN, 7);
  //disp.setDisplayToDecNumber(30, 0, false);
}  
  
void loop() {  
  
}
