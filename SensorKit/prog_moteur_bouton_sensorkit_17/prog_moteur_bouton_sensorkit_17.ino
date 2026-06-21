#define button 4
int button_state = 0;
const int motorPin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  button_state = digitalRead(button);
  if (button_state == HIGH) {
    digitalWrite(motorPin, HIGH);
  }
  else {
    digitalWrite(motorPin, LOW);
  }
}
