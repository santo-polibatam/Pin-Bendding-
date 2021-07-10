void setup() {

#define A A3
#define B A2
#define C A1 

pinMode(A0,INPUT);
pinMode(C,INPUT);
pinMode(B,INPUT);
pinMode(A,INPUT);

digitalWrite(A0,OUTPUT);
digitalWrite(C,OUTPUT);
digitalWrite(B,OUTPUT);
digitalWrite(A,OUTPUT);

Serial.begin(9600);
Serial.print("Program Start !");
}

void loop() {
  if(digitalRead(A0)==0)Serial.println("A0");
  if(digitalRead(A1)==0)Serial.println("C");
  if(digitalRead(A2)==0)Serial.println("B");
  if(digitalRead(A3)==0)Serial.println("A");
}
