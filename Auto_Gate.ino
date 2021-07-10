void setup() {

#define A A3
#define B A2
#define C A1
#define D A0
#define LS 4
#define PWM 3

  pinMode(D, INPUT);
  pinMode(C, INPUT);
  pinMode(B, INPUT);
  pinMode(A, INPUT);
  pinMode(LS, INPUT);
  pinMode(PWM, OUTPUT);

  digitalWrite(D, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(LS, HIGH);

  Serial.begin(9600);
  Serial.println("Program Start !");
}

void loop() {

  int index = 0;

  //TOMBOL A
  if (digitalRead(A) == 0) {
    Serial.println("A");
    while (digitalRead(A) == 0) {}

    for (index = 0; index <= 1023; index++) {
      analogWrite(PWM, index);
      delay(2);
      if (digitalRead(LS) == 0) break;
    }

    for (index = 0; index <= 1023; index++) {
      if (digitalRead(LS) == 0) break;
      delay(10);
    }
  };
  //TOMBOL B
  if (digitalRead(B) == 0) {
    Serial.println("B");
    while (digitalRead(B) == 0) {}
  };
  //TOMBOL C
  if (digitalRead(C) == 0) {
    Serial.println("C");
    while (digitalRead(C) == 0) {}
  };
  //TOMBOL D
  if (digitalRead(D) == 0) {
    Serial.println("D");
    while (digitalRead(D) == 0) {}
  };
  //LIMIT SWITCH
  if (digitalRead(LS) == 1) {
    Serial.println("LS");
    analogWrite(PWM, 0);
  };

}
