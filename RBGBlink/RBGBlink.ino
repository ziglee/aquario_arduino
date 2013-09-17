/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int blu = 9;
int red = 11;
int gre = 10;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(blu, OUTPUT);  
  pinMode(red, OUTPUT);
  pinMode(gre, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(blu, HIGH);
  delay(1000);
  digitalWrite(blu, LOW);
  delay(1000);
  digitalWrite(red, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
  delay(1000);
  digitalWrite(gre, HIGH);
  delay(1000);
  digitalWrite(gre, LOW);
  delay(1000);
  
  digitalWrite(blu, HIGH);
  digitalWrite(red, HIGH);
  digitalWrite(gre, HIGH);
  delay(1000);
  digitalWrite(blu, LOW);
  digitalWrite(red, LOW);
  digitalWrite(gre, LOW);
  delay(1000);
}
