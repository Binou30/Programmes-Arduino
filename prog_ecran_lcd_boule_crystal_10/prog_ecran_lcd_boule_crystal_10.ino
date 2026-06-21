#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
int reply;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);
  lcd.print("Demandez a la");
  lcd.setCursor(0, 1);
  lcd.print("Boule Magique!");
}

void loop() {
  // put your main code here, to run repeatedly:
  switchState = digitalRead(switchPin);
  if (switchState != prevSwitchState) {
    if (switchState == LOW) {
      reply = random(13);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("La boule dit:");
      lcd.setCursor(0, 1);
      switch(reply){
        case 0:
        lcd.print("Oui");
        break;
        case 1:
        lcd.print("Probablement");
        break;
        case 2:
        lcd.print("Certainement");
        break;
        case 3: 
        lcd.print("Sans doute");
        break;
        case 4:
        lcd.print("Pas sur");
        break;
        case 5:
        lcd.print("Redemande");
        break;
        case 6:
        lcd.print("Incertain");
        break;
        case 7:
        lcd.print("Non");
        break;
        case 8:
        lcd.print("Je reflechis...");
        break;
        case 9:
        lcd.print("Je sais pas");
        break;
        case 10:
        lcd.print("J'ai la flemme");
        break;
        case 11:
        lcd.print("Mouais Mouais");
        break;
        case 12:
        lcd.print("Y'a moyen");
        break;
      }
    }
  }
  prevSwitchState = switchState;
}
