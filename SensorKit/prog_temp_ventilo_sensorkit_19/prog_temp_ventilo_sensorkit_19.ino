#include "Arduino_SensorKit.h"

#define Environment Environment_I2C

const int motorPin = 12;

String ventilstate = "NON";

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin, OUTPUT);

  Wire.begin();
  Environment.begin();

  Oled.begin();
  Oled.setFlipMode(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Environment.readTemperature() > 19.5) {
    digitalWrite(motorPin, HIGH);
    ventilstate = "OUI";
  }
  else {
    digitalWrite(motorPin, LOW);
    ventilstate = "NON";
  }
  Oled.setFont(u8x8_font_chroma48medium8_r);
  Oled.setCursor(0, 10);
  Oled.print("Temp : ");
  Oled.print(Environment.readTemperature());
  Oled.print(" C");
  Oled.setCursor(0, 20);
  Oled.print("Ventil : ");
  Oled.print(ventilstate);
  Oled.refreshDisplay();
  delay(500);
}
