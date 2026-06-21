	
#include "Arduino_SensorKit.h"
#define Environment Environment_I2C
int light_sensor = A3;
int sound_sensor = A2;
 
void setup() {
  Oled.begin();
  Oled.setFlipMode(true); // Sets the rotation of the screen
  Wire.begin();
  Environment.begin();

}
 
void loop() { 
  int soundValue = 0; //create variable to store many different readings
  for (int i = 0; i < 32; i++) //create a for loop to read 
  { soundValue += analogRead(sound_sensor);  }
  soundValue >>= 5;
  int raw_light = analogRead(light_sensor);
  int light = map(raw_light, 0, 1023, 0, 100);
  Oled.setFont(u8x8_font_chroma48medium8_r); 
  Oled.setCursor(0, 0);    // Set the Coordinates 
  Oled.print("Lumiere : "); // Print the Values  
  Oled.print(light);
  Oled.setCursor(0, 10);
  Oled.print("Son : ");
  Oled.print(soundValue);
  Oled.setCursor(0, 20);
  Oled.print("Temp : ");
  Oled.print(Environment.readTemperature());
  Oled.print(" C");
  Oled.setCursor(0, 30);
  Oled.print("Hum : ");
  Oled.print(Environment.readHumidity());
  Oled.print(" %");
  Oled.refreshDisplay();    // Update the Display 
  delay(1000);
}
