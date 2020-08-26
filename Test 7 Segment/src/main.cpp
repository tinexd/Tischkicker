#include <Arduino.h>

int A_1 = 17, B_1 = 16, C_1 = 14, D_1 = 12, E_1 = 11, F_1 = 19, G_1 = 20, DP_1 = 15;
int A_2 = 27, B_2 = 26, C_2 = 24, D_2 = 22, E_2 = 21, F_2 = 29, G_2 = 30;
int A_3 = 37, B_3 = 36, C_3 = 34, D_3 = 32, E_3 = 31, F_3 = 39, G_3 = 40, DP_3 = 35;
int A_4 = 47, B_4 = 46, C_4 = 44, D_4 = 42, E_4 = 41, F_4 = 9, G_4 = 10;

int taster_1 = 2;
int taster_2 = 3;

int sensor_1 = A0;
int sensor_2 = A1;

volatile int status = 0;
volatile unsigned long last_time_ISR = 0;
const int debounce_time = 250;

void interruptRoutine();

void setup()
{
  Serial.begin(9600);
  pinMode(taster_1, INPUT_PULLUP);
  pinMode(taster_2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(taster_1), interruptRoutine, FALLING);
  attachInterrupt(digitalPinToInterrupt(taster_2), interruptRoutine, FALLING);
  pinMode(A_1, OUTPUT);
  pinMode(B_1, OUTPUT);
  pinMode(C_1, OUTPUT);
  pinMode(D_1, OUTPUT);
  pinMode(E_1, OUTPUT);
  pinMode(F_1, OUTPUT);
  pinMode(G_1, OUTPUT);
  pinMode(DP_1, OUTPUT);
  pinMode(A_2, OUTPUT);
  pinMode(B_2, OUTPUT);
  pinMode(C_2, OUTPUT);
  pinMode(D_2, OUTPUT);
  pinMode(E_2, OUTPUT);
  pinMode(F_2, OUTPUT);
  pinMode(G_2, OUTPUT);
  pinMode(A_3, OUTPUT);
  pinMode(B_3, OUTPUT);
  pinMode(C_3, OUTPUT);
  pinMode(D_3, OUTPUT);
  pinMode(E_3, OUTPUT);
  pinMode(F_3, OUTPUT);
  pinMode(G_3, OUTPUT);
  pinMode(DP_3, OUTPUT);
  pinMode(A_4, OUTPUT);
  pinMode(B_4, OUTPUT);
  pinMode(C_4, OUTPUT);
  pinMode(D_4, OUTPUT);
  pinMode(E_4, OUTPUT);
  pinMode(F_4, OUTPUT);
  pinMode(G_4, OUTPUT);
  pinMode(sensor_1, INPUT);
  pinMode(sensor_2, INPUT);
}

void loop()
{
  int sensor_wert_1 = analogRead(sensor_1);
  int sensor_wert_2 = analogRead(sensor_2);
  Serial.println(sensor_wert_1);
  Serial.println(sensor_wert_2);
  delay(1000);
  Serial.println();

  switch (status)
  {
  case 0:
    digitalWrite(A_1, LOW);
    digitalWrite(B_1, LOW);
    digitalWrite(C_1, LOW);
    digitalWrite(D_1, LOW);
    digitalWrite(E_1, LOW);
    digitalWrite(F_1, LOW);
    digitalWrite(G_1, LOW);
    digitalWrite(DP_1, LOW);
    digitalWrite(A_2, LOW);
    digitalWrite(B_2, LOW);
    digitalWrite(C_2, LOW);
    digitalWrite(D_2, LOW);
    digitalWrite(E_2, LOW);
    digitalWrite(F_2, LOW);
    digitalWrite(G_2, LOW);
    digitalWrite(A_3, LOW);
    digitalWrite(B_3, LOW);
    digitalWrite(C_3, LOW);
    digitalWrite(D_3, LOW);
    digitalWrite(E_3, LOW);
    digitalWrite(F_3, LOW);
    digitalWrite(G_3, LOW);
    digitalWrite(DP_3, LOW);
    digitalWrite(A_4, LOW);
    digitalWrite(B_4, LOW);
    digitalWrite(C_4, LOW);
    digitalWrite(D_4, LOW);
    digitalWrite(E_4, LOW);
    digitalWrite(F_4, LOW);
    digitalWrite(G_4, LOW);
    break;

  case 1:
    digitalWrite(A_1, HIGH);
    digitalWrite(A_2, HIGH);
    digitalWrite(A_3, HIGH);
    digitalWrite(A_4, HIGH);
    break;

  case 2:
    digitalWrite(B_1, HIGH);
    digitalWrite(B_2, HIGH);
    digitalWrite(B_3, HIGH);
    digitalWrite(B_4, HIGH);
    break;

  case 3:
    digitalWrite(C_1, HIGH);
    digitalWrite(C_2, HIGH);
    digitalWrite(C_3, HIGH);
    digitalWrite(C_4, HIGH);
    break;

  case 4:
    digitalWrite(D_1, HIGH);
    digitalWrite(D_2, HIGH);
    digitalWrite(D_3, HIGH);
    digitalWrite(D_4, HIGH);
    break;

  case 5:
    digitalWrite(E_1, HIGH);
    digitalWrite(E_2, HIGH);
    digitalWrite(E_3, HIGH);
    digitalWrite(E_4, HIGH);
    break;

  case 6:
    digitalWrite(F_1, HIGH);
    digitalWrite(F_2, HIGH);
    digitalWrite(F_3, HIGH);
    digitalWrite(F_4, HIGH);
    break;

  case 7:
    digitalWrite(G_1, HIGH);
    digitalWrite(G_2, HIGH);
    digitalWrite(G_3, HIGH);
    digitalWrite(G_4, HIGH);
    break;

  case 8:
    digitalWrite(DP_1, HIGH);
    digitalWrite(DP_3, HIGH);
    break;
  }
}

void interruptRoutine()
{
  if (millis() - last_time_ISR > debounce_time)
  {
    if (status < 8)
      status++;
    else
      status = 0;
    last_time_ISR = millis();
  }
}