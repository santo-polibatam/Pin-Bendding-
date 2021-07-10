void setup() {

#define A A3
#define B A2
#define C A1

  pinMode(A0, INPUT);
  pinMode(C, INPUT);
  pinMode(B, INPUT);
  pinMode(A, INPUT);

  digitalWrite(A0, OUTPUT);
  digitalWrite(C, OUTPUT);
  digitalWrite(B, OUTPUT);
  digitalWrite(A, OUTPUT);

  Serial.begin(9600);
  Serial.println("Program Start !");
}

void loop() {
  if (digitalRead(A0) == 0) {
    Serial.println("A0");
    while (digitalRead(A0) == 0) {}
  };
  if (digitalRead(A1) == 0) {
    Serial.println("C"); while (digitalRead(C) == 0) {}
  };
  if (digitalRead(A2) == 0) {
    Serial.println("B"); while (digitalRead(B) == 0) {}
  };
  if (digitalRead(A3) == 0) {
    Serial.println("A"); while (digitalRead(A) == 0) {}
  };
}
