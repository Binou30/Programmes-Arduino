#include <U8g2lib.h>
#include <Wire.h>

const int controlPin1 = 12;
const int controlPin2 = 10;
const int enablePin = 9;
const int onOffSwitchStateSwitchPin = 4;
const int potPin = A0;

int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 0;

// Paramètres roue
const float rayon = 0.0625; // 125 mm = 0,125 m / 2
const float vmax = 2.0;     // vitesse max m/s (à ajuster selon ton moteur)

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2); // écran inversé 180°

void setup() {
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  digitalWrite(enablePin, LOW);
  u8g2.begin();
}

void loop() {
  // --- Lecture switch et moteur ---
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  delay(1);

  motorSpeed = analogRead(potPin) / 4;  // 0-255 PWM

  if (onOffSwitchState != previousOnOffSwitchState) {
    if (onOffSwitchState == HIGH) {
      motorEnabled = !motorEnabled;
    }
  }

  digitalWrite(controlPin1, HIGH);
  digitalWrite(controlPin2, LOW);

  if (motorEnabled) {
    analogWrite(enablePin, motorSpeed);
  } else {
    analogWrite(enablePin, 0);
  }

  // --- Calcul km/h ---
  float fractionPWM = motorSpeed / 255.0;
  float vitesse = fractionPWM * vmax; // vitesse en m/s
  float kmh = vitesse * 3.6;          // conversion km/h

  // --- AFFICHAGE OLED ---
  u8g2.clearBuffer();

  // Texte centré avec km/h (1 décimale)
  char buffer[10];
  dtostrf(kmh, 4, 1, buffer);  // km/h avec 1 décimale

  u8g2.setFont(u8g2_font_ncenB08_tr);

  // calculer largeur totale du texte à afficher
  int16_t textWidth = u8g2.getStrWidth(buffer) + u8g2.getStrWidth(" km/h");
  int16_t tx = (128 - textWidth) / 2;
  int16_t ty = 20;

  u8g2.setDrawColor(0);
  u8g2.drawBox(0, 0, 128, 24); // efface zone texte

  u8g2.setDrawColor(1);
  u8g2.setCursor(tx, ty);
  u8g2.print(buffer);
  u8g2.print(" km/h");

  // Barre de progression
  int largeur = map(motorSpeed, 0, 255, 0, 128);
  u8g2.setDrawColor(0);
  u8g2.drawBox(0, 40, 128, 10); // efface barre précédente

  if (motorEnabled) {
    // barre blanche
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, 40, largeur, 10);
  } else {
    // barre hachurée pour simuler gris
    u8g2.setDrawColor(1);
    for (int x = 0; x < largeur; x += 2) {
      u8g2.drawVLine(x, 40, 10);
    }
  }

  u8g2.sendBuffer(); // envoie tout à l'écran
  previousOnOffSwitchState = onOffSwitchState;
  delay(50);
}
