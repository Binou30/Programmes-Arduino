const int greenLEDPin = 9;
const int redLEDPin = 10;
const int blueLEDPin = 11;

const int blueSensorPin = A2;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

int blueSensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  blueSensorValue = analogRead(blueSensorPin);
  Serial.print("Valeurs brutes \t bleu: ");
  Serial.print(blueSensorValue);
  blueValue = blueSensorValue/4;
  Serial.print("Valeurs recalculees \t bleu: ");
  Serial.print(blueValue);
  analogWrite(blueLEDPin, blueValue);
  analogWrite(greenLEDPin, blueValue);
  analogWrite(redLEDPin, blueValue);

}
