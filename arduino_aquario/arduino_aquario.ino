#include <DHT.h>
#include <TM1638.h>
#include <OneWire.h>
#include <stdlib.h>

#define DHTPIN 5     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

int DS18S20_Pin = 7;
int led = 13;
boolean humidity_mode = false;
unsigned long one_hour = 3600000UL;
unsigned long time;

DHT dht(DHTPIN, DHTTYPE);
TM1638 module(3, 2, 4);
OneWire ds(DS18S20_Pin);

void setup() {
  //Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  module.clearDisplay();
  module.setupDisplay(true, 7);
  module.setLED(TM1638_COLOR_NONE, 0);
  module.setLED(TM1638_COLOR_NONE, 1);
  module.setLED(TM1638_COLOR_NONE, 2);
  module.setLED(TM1638_COLOR_NONE, 3);
  module.setLED(TM1638_COLOR_GREEN, 0);
  dht.begin();
  time = millis();
}

void loop() {
  if (millis() - time > (24 * one_hour)) {
    time = millis();
  } else if (millis() - time > (14 * one_hour)) {
    module.setLED(TM1638_COLOR_NONE, 0);
    module.setLED(TM1638_COLOR_NONE, 1);
    module.setLED(TM1638_COLOR_NONE, 2);
    module.setLED(TM1638_COLOR_NONE, 3);
    
    module.setLED(TM1638_COLOR_RED, 3);
    
    digitalWrite(led, LOW);
  } else if (millis() - time > (9 * one_hour)) {
    module.setLED(TM1638_COLOR_NONE, 0);
    module.setLED(TM1638_COLOR_NONE, 1);
    module.setLED(TM1638_COLOR_NONE, 2);
    module.setLED(TM1638_COLOR_NONE, 3);
    
    module.setLED(TM1638_COLOR_GREEN, 2);
    
    digitalWrite(led, HIGH);
  } else if (millis() - time > (5 * one_hour)) {
    module.setLED(TM1638_COLOR_NONE, 0);
    module.setLED(TM1638_COLOR_NONE, 1);
    module.setLED(TM1638_COLOR_NONE, 2);
    module.setLED(TM1638_COLOR_NONE, 3);
    
    module.setLED(TM1638_COLOR_RED, 1);
    
    digitalWrite(led, LOW);
  } else {
    module.setLED(TM1638_COLOR_NONE, 0);
    module.setLED(TM1638_COLOR_NONE, 1);
    module.setLED(TM1638_COLOR_NONE, 2);
    module.setLED(TM1638_COLOR_NONE, 3);
  
    module.setLED(TM1638_COLOR_GREEN, 0);
    digitalWrite(led, HIGH);
  }
  
  float u = getTemp();
  if (!humidity_mode) {
    char intTemp[5];
    dtostrf(u, 5, 2, intTemp);
    module.setDisplayDigit(intTemp[0], 4, false);
    module.setDisplayDigit(intTemp[1], 5, true);
    module.setDisplayDigit(intTemp[3], 6, false);
    module.setDisplayDigit(intTemp[4], 7, false);
  }
    
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(t) || isnan(h)) {
    // Serial.println("Failed to read from DHT");
  } else {
    /*
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Ex temp: "); 
    Serial.print(t);
    Serial.print(" *C\t");
    Serial.print("Un temp: "); 
    Serial.print(u);
    Serial.println(" *C");
    */
    
    char extTemp[5];
    if (humidity_mode) {
      dtostrf(h, 5, 2, extTemp);
      module.setDisplayToString("perc", 0, 4);
    } else {
      dtostrf(t, 5, 2, extTemp);
    }
    module.setDisplayDigit(extTemp[0], 0, false);
    module.setDisplayDigit(extTemp[1], 1, true);
    module.setDisplayDigit(extTemp[3], 2, false);
    module.setDisplayDigit(extTemp[4], 3, false);
  }
  
  if (module.getButtons() == 0b00000001) {
    humidity_mode = true;
  }
  if (module.getButtons() == 0b00000010) {
    humidity_mode = false;
  }
  if (module.getButtons() == 0b00000100) {
    digitalWrite(led, HIGH);
  }
  if (module.getButtons() == 0b00001000) {
    digitalWrite(led, LOW);
  }
  if (module.getButtons() == 0b00010000) {
    module.setupDisplay(false, 7);
  }
  if (module.getButtons() == 0b00100000) {
    module.setupDisplay(true, 7);
  }
}

float getTemp() {
  //returns the temperature from one DS18S20 in DEG Celsius
  byte data[12];
  byte addr[8];

  if (!ds.search(addr)) {
    //no more sensors on chain, reset search
    ds.reset_search();
    return -1001;
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return -1002;
  }

  if (addr[0] != 0x10 && addr[0] != 0x28) {
    Serial.print("Device is not recognized");
    return -1003;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);  
  ds.write(0xBE); // Read Scratchpad
 
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
 
  ds.reset_search();
 
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
 
  return TemperatureSum;
}
