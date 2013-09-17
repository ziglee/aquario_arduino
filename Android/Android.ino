#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

#define  LED_RED       5
#define  LED_GREEN     6
#define  LED_BLUE      7
#define  LED_13        13

AndroidAccessory acc("Manufacturer",
		"Model",
		"Description",
		"1.0",
		"http://yoursite.com",
                "0000000012345678");

void setup();
void loop();

void init_leds() {
  pinMode(LED_13, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_13, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Powering on");
  init_leds();
  acc.powerOn();
  Serial.println("success");
}

void loop() {
  digitalWrite(LED_13, LOW);
  byte msg[3];
  if (acc.isConnected()) {
    int len = acc.read(msg, sizeof(msg), 1);
    if (len > 0) {
      digitalWrite(LED_13, HIGH);
      analogWrite(LED_RED, 255 - msg[0]);
      analogWrite(LED_GREEN, 255 - msg[1]);
      analogWrite(LED_BLUE, 255 - msg[2]);
    }
  } else {
    digitalWrite(LED_13, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
  }
  delay(10);
}
