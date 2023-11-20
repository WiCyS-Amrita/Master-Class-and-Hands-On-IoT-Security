const int ledPin1 = 4; 
const int ledPin2 = 2; 

  

void setup() {
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == 'A') {
      digitalWrite(ledPin1, HIGH);
    }
    else if (receivedChar == 'a') {
      digitalWrite(ledPin1, LOW);
    }
    else if (receivedChar == 'B') {
      digitalWrite(ledPin2, HIGH);
    }
    else if (receivedChar == 'b') {
      digitalWrite(ledPin2, LOW);
    }
    else if (receivedChar == 'z') {
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin1, LOW);
    }
    else if (receivedChar == 'Z') {
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin1, HIGH);
    }
  }
}