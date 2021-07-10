int FLAG = 0;

void setup()
{

#define A A3
#define B A2
#define C A1
#define D A0
#define LS 4
#define PWM 3
#define DIR 6

  pinMode(D, INPUT);
  pinMode(C, INPUT);
  pinMode(B, INPUT);
  pinMode(A, INPUT);
  pinMode(LS, INPUT);
  pinMode(PWM, OUTPUT);
  pinMode(DIR, OUTPUT);

  digitalWrite(D, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(LS, HIGH);

  Serial.begin(115200);
  Serial.println("Program Start !");
}

void loop()
{
  int index = 0;

  //TOMBOL A BUKA SEDIKIT
  if (digitalRead(A) == 0)
    BUKA_SEDIKIT();

  //TOMBOL B BUKA PENUH
  if (digitalRead(B) == 0)
    BUKA_FULL();

  //TOMBOL C
  if (digitalRead(C) == 0)
    TUTUP();

  //TOMBOL D
  if (digitalRead(D) == 0 && FLAG == 0)
  {
    Serial.println("D");
    //while (digitalRead(D) == 0);
  };

  //LIMIT SWITCH
  if ((digitalRead(LS) == 1 && FLAG == 0) || (digitalRead(D) == 0 && FLAG == 0))
    CEK_LS();
}

void BUKA_SEDIKIT()
{
  FLAG = 0;
  int index = 0;
  Serial.println("A");
  while (digitalRead(A) == 0)
  {
  }

  Serial.println("Direction set!");
  digitalWrite(DIR, LOW);
  delay(1000);

  Serial.println("Akselerasi !");
  for (index = 0; index <= 255; index++)
  {
    //analogWrite(PWM, index);
    analogWrite(PWM, index);
    delay(10);
    Serial.print("Speed:");
    Serial.println(index);
    if (digitalRead(LS) == 1 || digitalRead(D) == 0)
      break;
  }

  analogWrite(PWM, 255);
  Serial.println("Delay 10s !");
  for (index = 0; index <= 1000; index++)
  {
    if (digitalRead(LS) == 1 || digitalRead(D) == 0)
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

  Serial.println("Direction set!");
  digitalWrite(DIR, LOW);
  delay(1000);

  Serial.println("Akselerasi !");
  for (index = 0; index <= 255; index++)
  {
    analogWrite(PWM, index);
    delay(10);
    if (digitalRead(LS) == 1 || digitalRead(D) == 0)
      break;
  }
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
  Serial.println("Direction Set!");
  digitalWrite(DIR, HIGH);
  delay(1000);

  Serial.println("Akselerasi !");
  for (index = 0; index <= 255; index++)
  {
    analogWrite(PWM, index);
    delay(10);
    if (digitalRead(LS) == 1 || digitalRead(D) == 0)
      break;
  }
  Serial.println("Wait LS !");
};

void CEK_LS()
{
  FLAG = 1;
  Serial.println("LS ON");
  analogWrite(PWM, 0);
  Serial.println("Motor Stop !");
};
