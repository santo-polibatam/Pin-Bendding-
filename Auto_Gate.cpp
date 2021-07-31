#include <Arduino.h>

int FLAG = 0;
unsigned long myTime;

void BUKA_SEDIKIT();
void BUKA_FULL();
void MATIKAN_MOTOR();
void TUTUP();
void MATIKAN_MOTOR();
int BACA_REMOTE();

void setup()
{

#define A A3
#define B A2
#define C A1
#define D A0
#define LS 4
#define PWM 3
#define PS 6
#define DIR 7
#define TimeOut 60000 //60 s

  pinMode(D, INPUT);
  pinMode(C, INPUT);
  pinMode(B, INPUT);
  pinMode(A, INPUT);
  pinMode(LS, INPUT);
  pinMode(PWM, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(PS, OUTPUT);

  digitalWrite(D, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(LS, HIGH);

  digitalWrite(PS, HIGH);
  digitalWrite(DIR, HIGH);

  Serial.begin(115200);
  Serial.println("Program Start !");
}

//Main Program
void loop()
{
  //int index = 0;
  //print waktu per detik ke Serial Port
  if (((millis() % 500) == 0) && myTime > 0)
    Serial.println((millis() - myTime) / 1000);

  //TOMBOL A BUKA SEDIKIT
  if (digitalRead(A) == 0)
  {
    myTime = millis();
    BUKA_SEDIKIT();
  }
  //TOMBOL B BUKA PENUH
  if (digitalRead(B) == 0)
  {
    myTime = millis();
    BUKA_FULL();
  }

  //TOMBOL C
  if (digitalRead(C) == 0)
  {
    myTime = millis();
    TUTUP();
  }

  //TOMBOL D
  if (digitalRead(D) == 0 && FLAG == 0)
  {
    Serial.println("D");
  };

  //LIMIT SWITCH
  if ((digitalRead(LS) == 1 && FLAG == 0) || (digitalRead(D) == 0 && FLAG == 0) || ((millis() - myTime) >= TimeOut && myTime > 0))
  {
    MATIKAN_MOTOR();
    myTime = 0;
  }
}

void BUKA_SEDIKIT()
{
  FLAG = 0;
  int index = 0;
  Serial.println("A");
  while (digitalRead(A) == 0)
  {
  }

  //NYALAKAN PS
  digitalWrite(PS, LOW);
  delay(1000);
  Serial.println("Direction set!");
  digitalWrite(DIR, LOW);
  delay(500);

  Serial.println("LS Realese !");
  for (index = 0; index <= 255; index++)
  {
    //analogWrite(PWM, index);
    analogWrite(PWM, index);
    delay(10);
    Serial.print("Speed:");
    Serial.println(index);
    if (digitalRead(LS) == 0 || digitalRead(D) == 0 || ((millis() - myTime) >= TimeOut && myTime > 0))
      break;
  }

  Serial.println("Akselerasi !");
  for (index = index; index <= 255; index++)
  {
    //analogWrite(PWM, index);
    analogWrite(PWM, index);
    delay(10);
    Serial.print("Speed:");
    Serial.println(index);
    if (digitalRead(LS) == 1 || digitalRead(D) == 0 || ((millis() - myTime) >= TimeOut && myTime > 0))
      break;
  }

  analogWrite(PWM, 255);
  Serial.println("Delay 5s !");
  for (index = 0; index <= 500; index++)
  {
    if (digitalRead(LS) == 1 || digitalRead(D) == 0 || ((millis() - myTime) >= TimeOut && myTime > 0))
      break;
    delay(10);
  }

  //Matikan Motor
  Serial.println("Matikan !");
  analogWrite(PWM, 0);
};

void BUKA_FULL()
{
  FLAG = 0;
  int index = 0;
  Serial.println("B");
  while (digitalRead(B) == 0)
  {
  }

  //NYALAKAN PS
  digitalWrite(PS, LOW);
  delay(1000);
  Serial.println("Direction set!");
  digitalWrite(DIR, LOW);
  delay(500);

  Serial.println("LS Realese !");
  for (index = 0; index <= 255; index++)
  {
    analogWrite(PWM, index);
    delay(10);
    if (digitalRead(LS) == 0 || digitalRead(D) == 0 || ((millis() - myTime) >= TimeOut && myTime > 0))
      break;
  }

  Serial.println("Akselerasi !");
  for (index = index; index <= 255; index++)
  {
    analogWrite(PWM, index);
    delay(10);
    if (digitalRead(LS) == 1 || digitalRead(D) == 0 || ((millis() - myTime) >= TimeOut && myTime > 0))
      break;
  }

  for (index = 0; index <= 10000; index++)
  {
    if (digitalRead(LS) == 1 || digitalRead(D) == 0 || ((millis() - myTime) >= TimeOut && myTime > 0))
      break;
  }
  analogWrite(PWM, 128);
  Serial.println("Wait LS !");
}

void TUTUP()
{
  FLAG = 0;
  int index = 0;
  Serial.println("C");
  while (digitalRead(C) == 0)
  {
  }

  //NYALAKAN PS
  digitalWrite(PS, LOW);
  delay(1000);
  Serial.println("Direction set!");
  digitalWrite(DIR, HIGH);
  delay(500);

  Serial.println("LS Realese !");
  for (index = 0; index <= 255; index++)
  {
    analogWrite(PWM, index);
    delay(10);
    if (digitalRead(LS) == 0 || digitalRead(D) == 0 || ((millis() - myTime) >= TimeOut && myTime > 0))
      break;
  }

  Serial.println("Akselerasi !");
  for (index = index; index <= 255; index++)
  {
    analogWrite(PWM, index);
    delay(10);
    if (digitalRead(LS) == 1 || digitalRead(D) == 0 || ((millis() - myTime) >= TimeOut && myTime > 0))
      break;
  }

  for (index = 0; index <= 10000; index++)
  {
    if (digitalRead(LS) == 1 || digitalRead(D) == 0 || ((millis() - myTime) >= TimeOut && myTime > 0))
      break;
  }
  analogWrite(PWM, 128);
  Serial.println("Wait LS !");
};

void MATIKAN_MOTOR()
{
  FLAG = 1;
  Serial.println("LS ON");
  analogWrite(PWM, 0);
  Serial.println("Motor Stop !");
  delay(1000);
  digitalWrite(DIR, HIGH);
  delay(1000);
  digitalWrite(PS, HIGH);
};

int BACA_REMOTE()
{
  if (digitalRead(A) == 0 || digitalRead(B) == 0 || digitalRead(C) == 0 || digitalRead(D) == 0)
  {
    return 1;
  }
  return 0;
};