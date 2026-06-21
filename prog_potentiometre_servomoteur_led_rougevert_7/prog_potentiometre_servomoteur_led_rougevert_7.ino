#include <Servo.h> 
Servo myServo;
int const potPin = A0;
int potVal;
int angle;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(9);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = analogRead(potPin);
  Serial.print("potVal: ");
  Serial.print(potVal);
  angle = potVal/5.715083799;
  Serial.print(", angle: ");
  Serial.println(angle);
  myServo.write(angle);
  delay(15);
  if (angle > 89.5) {
    digitalWrite(10, HIGH);
    digitalWrite(13, LOW);
  }
  if (angle < 89.5) {
    digitalWrite(10, LOW);
    digitalWrite(13, HIGH);
  }
}
