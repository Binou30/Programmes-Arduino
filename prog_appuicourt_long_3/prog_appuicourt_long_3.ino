int nivInt = 0;
int press = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(8, INPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  nivInt = digitalRead(8);
  if (nivInt == LOW) {
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
  }
  if (nivInt == HIGH) {
    press = 1;
    while (nivInt == LOW);
      delay(250);
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);    
      delay(2000);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      press = 0;
  }
  if (nivInt == HIGH && press == 0) {
    delay(2000);
    if (nivInt == HIGH);
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      delay(2000);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);

  }

}