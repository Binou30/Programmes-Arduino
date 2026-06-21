const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchStateSwitchPin = 5;
const int potPinSpeed = A0;
const int potPinLed = A1;  // Déclare un potentiomètre pour la LED
const int buttonPin = 10;   // Broche du bouton poussoir pour la LED

int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;  // 1 pour avant, 0 pour arrière
int potValLed;
int lcgnLed;

// Variables pour gérer le clignotement de la LED avec millis()
unsigned long previousMillisLed = 0;
unsigned long intervalLed = 0;
bool ledState = false;  // État de la LED (éteinte ou allumée)
bool buttonState = false;  // État du bouton poussoir
bool lastButtonState = false;  // Dernier état du bouton poussoir
bool ledBlinking = false;  // Si la LED doit clignoter ou non

void setup() {
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(7, OUTPUT);  // Broche pour la LED
  pinMode(buttonPin, INPUT_PULLUP);  // Bouton poussoir avec résistance de tirage interne
  
  digitalWrite(enablePin, LOW);  // Le moteur est désactivé au départ
}

void loop() {
  // Lecture des interrupteurs et du potentiomètre pour le moteur
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  directionSwitchState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPinSpeed) / 4;  // Lecture du potentiomètre pour la vitesse

  // Gestion de l'activation/désactivation du moteur (avec debounce)
  if (onOffSwitchState != previousOnOffSwitchState) {
    if (onOffSwitchState == HIGH) {
      motorEnabled = !motorEnabled;
    }
  }

  // Gestion du changement de direction (avec debounce)
  if (directionSwitchState != previousDirectionSwitchState) {
    if (directionSwitchState == HIGH) {
      motorDirection = !motorDirection;
    }
  }

  // Contrôle de la direction du moteur
  if (motorDirection == 1) {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  } else {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }

  // Activation/désactivation du moteur en fonction de l'état
  if (motorEnabled == 1) {
    analogWrite(enablePin, motorSpeed);  // Contrôle de la vitesse via PWM
  } else {
    analogWrite(enablePin, 0);  // Arrêt du moteur
  }

  // Gestion du bouton poussoir pour la LED
  buttonState = digitalRead(buttonPin) == LOW;  // Vérifie si le bouton est pressé (LOW signifie appuyé avec INPUT_PULLUP)

  // Si l'état du bouton change de HIGH à LOW, inverser l'état de la LED
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {  // Si le bouton est appuyé (passage de HIGH à LOW)
      if (ledBlinking == false) {
        ledBlinking = true;  // Activer le clignotement de la LED
      } else {
        ledBlinking = false;  // Désactiver le clignotement de la LED
        digitalWrite(7, LOW); // Éteindre la LED
      }
    }
    delay(50);  // Anti-rebond pour le bouton
  }

  // Si la LED doit clignoter, gérer le clignotement avec le potentiomètre
  if (ledBlinking) {
    potValLed = analogRead(potPinLed);  // Lecture du potentiomètre pour la LED
    lcgnLed = map(potValLed, 0, 1023, 0, 500);  // Conversion de la valeur pour le délai

    // Gestion du clignotement de la LED avec millis()
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisLed >= lcgnLed) {
      ledState = !ledState;  // Inverse l'état de la LED
      digitalWrite(7, ledState ? HIGH : LOW);  // Allume ou éteint la LED
      previousMillisLed = currentMillis;  // Sauvegarde du dernier temps de clignotement
    }
  }

  // Mémorisation des états des interrupteurs pour la prochaine boucle
  previousDirectionSwitchState = directionSwitchState;
  previousOnOffSwitchState = onOffSwitchState;
  lastButtonState = buttonState;  // Sauvegarde de l'état du bouton pour la prochaine boucle
}
