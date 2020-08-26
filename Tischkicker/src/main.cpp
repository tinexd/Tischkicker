#include <Arduino.h>

int A_links_einstellig = 17, B_links_einstellig = 16, C_links_einstellig = 14, D_links_einstellig = 12,
    E_links_einstellig = 11, F_links_einstellig = 19, G_links_einstellig = 20, DP_links = 15;
int A_links_zweistellig = 27, B_links_zweistellig = 26, C_links_zweistellig = 24, D_links_zweistellig = 22,
    E_links_zweistellig = 21, F_links_zweistellig = 29, G_links_zweistellig = 30;

int A_rechts_einstellig = 37, B_rechts_einstellig = 36, C_rechts_einstellig = 34, D_rechts_einstellig = 32,
    E_rechts_einstellig = 31, F_rechts_einstellig = 39, G_rechts_einstellig = 40, DP_rechts = 35;
int A_rechts_zweistellig = 47, B_rechts_zweistellig = 46, C_rechts_zweistellig = 44, D_rechts_zweistellig = 42,
    E_rechts_zweistellig = 41, F_rechts_zweistellig = 9, G_rechts_zweistellig = 10;

int taster_links = 2, taster_rechts = 3;
int sensor_links = A0, sensor_rechts = A1;
int punkte_links = 0, punkte_rechts = 0;

//volatile bool reset_status = 1;
//volatile unsigned long last_time_ISR = 0;
//const int debounce_time = 250;

unsigned int dauer_taster = 800;

unsigned int blink_dauer = 500;

unsigned int dauer_sensor_blockieren = 1000;

//void interruptRoutine();
void anzeigeAus();
void anzeigeLinksEinstellig(int wert);
void anzeigeLinksZweistellig(int wert);
void anzeigeRechtsEinstellig(int wert);
void anzeigeRechtsZweistellig(int wert);

void setup()
{
  Serial.begin(9600);
  pinMode(taster_links, INPUT_PULLUP);
  pinMode(taster_rechts, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(taster_links), interruptRoutine, FALLING);
  //attachInterrupt(digitalPinToInterrupt(taster_rechts), interruptRoutine, FALLING);
  pinMode(A_links_einstellig, OUTPUT);
  pinMode(B_links_einstellig, OUTPUT);
  pinMode(C_links_einstellig, OUTPUT);
  pinMode(D_links_einstellig, OUTPUT);
  pinMode(E_links_einstellig, OUTPUT);
  pinMode(F_links_einstellig, OUTPUT);
  pinMode(G_links_einstellig, OUTPUT);
  pinMode(DP_links, OUTPUT);
  pinMode(A_links_zweistellig, OUTPUT);
  pinMode(B_links_zweistellig, OUTPUT);
  pinMode(C_links_zweistellig, OUTPUT);
  pinMode(D_links_zweistellig, OUTPUT);
  pinMode(E_links_zweistellig, OUTPUT);
  pinMode(F_links_zweistellig, OUTPUT);
  pinMode(G_links_zweistellig, OUTPUT);
  pinMode(A_rechts_einstellig, OUTPUT);
  pinMode(B_rechts_einstellig, OUTPUT);
  pinMode(C_rechts_einstellig, OUTPUT);
  pinMode(D_rechts_einstellig, OUTPUT);
  pinMode(E_rechts_einstellig, OUTPUT);
  pinMode(F_rechts_einstellig, OUTPUT);
  pinMode(G_rechts_einstellig, OUTPUT);
  pinMode(DP_rechts, OUTPUT);
  pinMode(A_rechts_zweistellig, OUTPUT);
  pinMode(B_rechts_zweistellig, OUTPUT);
  pinMode(C_rechts_zweistellig, OUTPUT);
  pinMode(D_rechts_zweistellig, OUTPUT);
  pinMode(E_rechts_zweistellig, OUTPUT);
  pinMode(F_rechts_zweistellig, OUTPUT);
  pinMode(G_rechts_zweistellig, OUTPUT);
  pinMode(sensor_links, INPUT);
  pinMode(sensor_rechts, INPUT);
}

void loop()
{
  static bool ende = 0, blinken = 0, reset_status = 1;;
  static unsigned long zeitpunkt_toggle = 0, zeitpunkt_punktestand_erhoet = 0, zeitpunkt_taster_low = 0;
  if (!(digitalRead(taster_links) == 0 || digitalRead(taster_rechts) == 0))zeitpunkt_taster_low = millis();
  if (millis() - zeitpunkt_taster_low > dauer_taster) reset_status = 1;
  if (reset_status == 1)
  {
    ende = 0;
    punkte_links = 0;
    punkte_rechts = 0;
    blinken = 0;
    reset_status = 0;
  }

  if (ende == 0)
  {
    int sensor_wert_links = analogRead(sensor_links);
    int sensor_wert_rechts = analogRead(sensor_rechts);

    if (sensor_wert_links < 500 && millis() - zeitpunkt_punktestand_erhoet > dauer_sensor_blockieren)
    {
      punkte_links++;
      zeitpunkt_punktestand_erhoet = millis();
    }

    if (sensor_wert_rechts < 500 && millis() - zeitpunkt_punktestand_erhoet > dauer_sensor_blockieren)
    {
      punkte_rechts++;
      zeitpunkt_punktestand_erhoet = millis();
    }
  }

  if (punkte_links >= 10 && punkte_links - punkte_rechts >= 2 || punkte_rechts >= 10 && punkte_rechts - punkte_links >= 2 ||
      punkte_links >= 25 || punkte_rechts >= 25)
    ende = 1;

  int punkte_links_einstellig = punkte_links % 10;
  int punkte_links_zweistellig = punkte_links / 10;
  int punkte_rechts_einstellig = punkte_rechts % 10;
  int punkte_rechts_zweistellig = punkte_rechts / 10;

  if (ende == 1 && millis() - zeitpunkt_toggle > blink_dauer)
  {
    blinken = !blinken;
    zeitpunkt_toggle = millis();
  }

  if (blinken == 0)
  {
    anzeigeLinksEinstellig(punkte_links_einstellig);
    anzeigeLinksZweistellig(punkte_links_zweistellig);
    anzeigeRechtsEinstellig(punkte_rechts_einstellig);
    anzeigeRechtsZweistellig(punkte_rechts_zweistellig);
    digitalWrite(DP_links, HIGH);
    digitalWrite(DP_rechts, HIGH);
  }
  else
    anzeigeAus();

  /*
  Serial.println(sensor_wert_1);
  Serial.println(sensor_wert_2);
  delay(1000);
  Serial.println();
  */
}

void anzeigeAus()
{
  digitalWrite(A_links_einstellig, LOW);
  digitalWrite(B_links_einstellig, LOW);
  digitalWrite(C_links_einstellig, LOW);
  digitalWrite(D_links_einstellig, LOW);
  digitalWrite(E_links_einstellig, LOW);
  digitalWrite(F_links_einstellig, LOW);
  digitalWrite(G_links_einstellig, LOW);
  digitalWrite(DP_links, LOW);

  digitalWrite(A_links_zweistellig, LOW);
  digitalWrite(B_links_zweistellig, LOW);
  digitalWrite(C_links_zweistellig, LOW);
  digitalWrite(D_links_zweistellig, LOW);
  digitalWrite(E_links_zweistellig, LOW);
  digitalWrite(F_links_zweistellig, LOW);
  digitalWrite(G_links_zweistellig, LOW);

  digitalWrite(A_rechts_einstellig, LOW);
  digitalWrite(B_rechts_einstellig, LOW);
  digitalWrite(C_rechts_einstellig, LOW);
  digitalWrite(D_rechts_einstellig, LOW);
  digitalWrite(E_rechts_einstellig, LOW);
  digitalWrite(F_rechts_einstellig, LOW);
  digitalWrite(G_rechts_einstellig, LOW);
  digitalWrite(DP_rechts, LOW);

  digitalWrite(A_rechts_zweistellig, LOW);
  digitalWrite(B_rechts_zweistellig, LOW);
  digitalWrite(C_rechts_zweistellig, LOW);
  digitalWrite(D_rechts_zweistellig, LOW);
  digitalWrite(E_rechts_zweistellig, LOW);
  digitalWrite(F_rechts_zweistellig, LOW);
  digitalWrite(G_rechts_zweistellig, LOW);
}

void anzeigeLinksEinstellig(int wert)
{
  switch (wert)
  {
  case 0:
    digitalWrite(A_links_einstellig, HIGH);
    digitalWrite(B_links_einstellig, HIGH);
    digitalWrite(C_links_einstellig, HIGH);
    digitalWrite(D_links_einstellig, HIGH);
    digitalWrite(E_links_einstellig, HIGH);
    digitalWrite(F_links_einstellig, HIGH);
    digitalWrite(G_links_einstellig, LOW);
    break;

  case 1:
    digitalWrite(A_links_einstellig, LOW);
    digitalWrite(B_links_einstellig, HIGH);
    digitalWrite(C_links_einstellig, HIGH);
    digitalWrite(D_links_einstellig, LOW);
    digitalWrite(E_links_einstellig, LOW);
    digitalWrite(F_links_einstellig, LOW);
    digitalWrite(G_links_einstellig, LOW);
    break;

  case 2:
    digitalWrite(A_links_einstellig, HIGH);
    digitalWrite(B_links_einstellig, HIGH);
    digitalWrite(C_links_einstellig, LOW);
    digitalWrite(D_links_einstellig, HIGH);
    digitalWrite(E_links_einstellig, HIGH);
    digitalWrite(F_links_einstellig, LOW);
    digitalWrite(G_links_einstellig, HIGH);
    break;

  case 3:
    digitalWrite(A_links_einstellig, HIGH);
    digitalWrite(B_links_einstellig, HIGH);
    digitalWrite(C_links_einstellig, HIGH);
    digitalWrite(D_links_einstellig, HIGH);
    digitalWrite(E_links_einstellig, LOW);
    digitalWrite(F_links_einstellig, LOW);
    digitalWrite(G_links_einstellig, HIGH);
    break;

  case 4:
    digitalWrite(A_links_einstellig, LOW);
    digitalWrite(B_links_einstellig, HIGH);
    digitalWrite(C_links_einstellig, HIGH);
    digitalWrite(D_links_einstellig, LOW);
    digitalWrite(E_links_einstellig, LOW);
    digitalWrite(F_links_einstellig, HIGH);
    digitalWrite(G_links_einstellig, HIGH);
    break;

  case 5:
    digitalWrite(A_links_einstellig, HIGH);
    digitalWrite(B_links_einstellig, LOW);
    digitalWrite(C_links_einstellig, HIGH);
    digitalWrite(D_links_einstellig, HIGH);
    digitalWrite(E_links_einstellig, LOW);
    digitalWrite(F_links_einstellig, HIGH);
    digitalWrite(G_links_einstellig, HIGH);
    break;

  case 6:
    digitalWrite(A_links_einstellig, HIGH);
    digitalWrite(B_links_einstellig, LOW);
    digitalWrite(C_links_einstellig, HIGH);
    digitalWrite(D_links_einstellig, HIGH);
    digitalWrite(E_links_einstellig, HIGH);
    digitalWrite(F_links_einstellig, HIGH);
    digitalWrite(G_links_einstellig, HIGH);
    break;

  case 7:
    digitalWrite(A_links_einstellig, HIGH);
    digitalWrite(B_links_einstellig, HIGH);
    digitalWrite(C_links_einstellig, HIGH);
    digitalWrite(D_links_einstellig, LOW);
    digitalWrite(E_links_einstellig, LOW);
    digitalWrite(F_links_einstellig, LOW);
    digitalWrite(G_links_einstellig, LOW);
    break;

  case 8:
    digitalWrite(A_links_einstellig, HIGH);
    digitalWrite(B_links_einstellig, HIGH);
    digitalWrite(C_links_einstellig, HIGH);
    digitalWrite(D_links_einstellig, HIGH);
    digitalWrite(E_links_einstellig, HIGH);
    digitalWrite(F_links_einstellig, HIGH);
    digitalWrite(G_links_einstellig, HIGH);
    break;

  case 9:
    digitalWrite(A_links_einstellig, HIGH);
    digitalWrite(B_links_einstellig, HIGH);
    digitalWrite(C_links_einstellig, HIGH);
    digitalWrite(D_links_einstellig, HIGH);
    digitalWrite(E_links_einstellig, LOW);
    digitalWrite(F_links_einstellig, HIGH);
    digitalWrite(G_links_einstellig, HIGH);
    break;
  }
}

void anzeigeLinksZweistellig(int wert)
{
  switch (wert)
  {
  case 0:
    digitalWrite(A_links_zweistellig, LOW);
    digitalWrite(B_links_zweistellig, LOW);
    digitalWrite(C_links_zweistellig, LOW);
    digitalWrite(D_links_zweistellig, LOW);
    digitalWrite(E_links_zweistellig, LOW);
    digitalWrite(F_links_zweistellig, LOW);
    digitalWrite(G_links_zweistellig, LOW);
    break;

  case 1:
    digitalWrite(A_links_zweistellig, LOW);
    digitalWrite(B_links_zweistellig, HIGH);
    digitalWrite(C_links_zweistellig, HIGH);
    digitalWrite(D_links_zweistellig, LOW);
    digitalWrite(E_links_zweistellig, LOW);
    digitalWrite(F_links_zweistellig, LOW);
    digitalWrite(G_links_zweistellig, LOW);
    break;

  case 2:
    digitalWrite(A_links_zweistellig, HIGH);
    digitalWrite(B_links_zweistellig, HIGH);
    digitalWrite(C_links_zweistellig, LOW);
    digitalWrite(D_links_zweistellig, HIGH);
    digitalWrite(E_links_zweistellig, HIGH);
    digitalWrite(F_links_zweistellig, LOW);
    digitalWrite(G_links_zweistellig, HIGH);
    break;

  case 3:
    digitalWrite(A_links_zweistellig, HIGH);
    digitalWrite(B_links_zweistellig, HIGH);
    digitalWrite(C_links_zweistellig, HIGH);
    digitalWrite(D_links_zweistellig, HIGH);
    digitalWrite(E_links_zweistellig, LOW);
    digitalWrite(F_links_zweistellig, LOW);
    digitalWrite(G_links_zweistellig, HIGH);
    break;

  case 4:
    digitalWrite(A_links_zweistellig, LOW);
    digitalWrite(B_links_zweistellig, HIGH);
    digitalWrite(C_links_zweistellig, HIGH);
    digitalWrite(D_links_zweistellig, LOW);
    digitalWrite(E_links_zweistellig, LOW);
    digitalWrite(F_links_zweistellig, HIGH);
    digitalWrite(G_links_zweistellig, HIGH);
    break;

  case 5:
    digitalWrite(A_links_zweistellig, HIGH);
    digitalWrite(B_links_zweistellig, LOW);
    digitalWrite(C_links_zweistellig, HIGH);
    digitalWrite(D_links_zweistellig, HIGH);
    digitalWrite(E_links_zweistellig, LOW);
    digitalWrite(F_links_zweistellig, HIGH);
    digitalWrite(G_links_zweistellig, HIGH);
    break;

  case 6:
    digitalWrite(A_links_zweistellig, HIGH);
    digitalWrite(B_links_zweistellig, LOW);
    digitalWrite(C_links_zweistellig, HIGH);
    digitalWrite(D_links_zweistellig, HIGH);
    digitalWrite(E_links_zweistellig, HIGH);
    digitalWrite(F_links_zweistellig, HIGH);
    digitalWrite(G_links_zweistellig, HIGH);
    break;

  case 7:
    digitalWrite(A_links_zweistellig, HIGH);
    digitalWrite(B_links_zweistellig, HIGH);
    digitalWrite(C_links_zweistellig, HIGH);
    digitalWrite(D_links_zweistellig, LOW);
    digitalWrite(E_links_zweistellig, LOW);
    digitalWrite(F_links_zweistellig, LOW);
    digitalWrite(G_links_zweistellig, LOW);
    break;

  case 8:
    digitalWrite(A_links_zweistellig, HIGH);
    digitalWrite(B_links_zweistellig, HIGH);
    digitalWrite(C_links_zweistellig, HIGH);
    digitalWrite(D_links_zweistellig, HIGH);
    digitalWrite(E_links_zweistellig, HIGH);
    digitalWrite(F_links_zweistellig, HIGH);
    digitalWrite(G_links_zweistellig, HIGH);
    break;

  case 9:
    digitalWrite(A_links_zweistellig, HIGH);
    digitalWrite(B_links_zweistellig, HIGH);
    digitalWrite(C_links_zweistellig, HIGH);
    digitalWrite(D_links_zweistellig, HIGH);
    digitalWrite(E_links_zweistellig, LOW);
    digitalWrite(F_links_zweistellig, HIGH);
    digitalWrite(G_links_zweistellig, HIGH);
    break;
  }
}

void anzeigeRechtsEinstellig(int wert)
{
  switch (wert)
  {
  case 0:
    digitalWrite(A_rechts_einstellig, HIGH);
    digitalWrite(B_rechts_einstellig, HIGH);
    digitalWrite(C_rechts_einstellig, HIGH);
    digitalWrite(D_rechts_einstellig, HIGH);
    digitalWrite(E_rechts_einstellig, HIGH);
    digitalWrite(F_rechts_einstellig, HIGH);
    digitalWrite(G_rechts_einstellig, LOW);
    break;

  case 1:
    digitalWrite(A_rechts_einstellig, LOW);
    digitalWrite(B_rechts_einstellig, HIGH);
    digitalWrite(C_rechts_einstellig, HIGH);
    digitalWrite(D_rechts_einstellig, LOW);
    digitalWrite(E_rechts_einstellig, LOW);
    digitalWrite(F_rechts_einstellig, LOW);
    digitalWrite(G_rechts_einstellig, LOW);
    break;

  case 2:
    digitalWrite(A_rechts_einstellig, HIGH);
    digitalWrite(B_rechts_einstellig, HIGH);
    digitalWrite(C_rechts_einstellig, LOW);
    digitalWrite(D_rechts_einstellig, HIGH);
    digitalWrite(E_rechts_einstellig, HIGH);
    digitalWrite(F_rechts_einstellig, LOW);
    digitalWrite(G_rechts_einstellig, HIGH);
    break;

  case 3:
    digitalWrite(A_rechts_einstellig, HIGH);
    digitalWrite(B_rechts_einstellig, HIGH);
    digitalWrite(C_rechts_einstellig, HIGH);
    digitalWrite(D_rechts_einstellig, HIGH);
    digitalWrite(E_rechts_einstellig, LOW);
    digitalWrite(F_rechts_einstellig, LOW);
    digitalWrite(G_rechts_einstellig, HIGH);
    break;

  case 4:
    digitalWrite(A_rechts_einstellig, LOW);
    digitalWrite(B_rechts_einstellig, HIGH);
    digitalWrite(C_rechts_einstellig, HIGH);
    digitalWrite(D_rechts_einstellig, LOW);
    digitalWrite(E_rechts_einstellig, LOW);
    digitalWrite(F_rechts_einstellig, HIGH);
    digitalWrite(G_rechts_einstellig, HIGH);
    break;

  case 5:
    digitalWrite(A_rechts_einstellig, HIGH);
    digitalWrite(B_rechts_einstellig, LOW);
    digitalWrite(C_rechts_einstellig, HIGH);
    digitalWrite(D_rechts_einstellig, HIGH);
    digitalWrite(E_rechts_einstellig, LOW);
    digitalWrite(F_rechts_einstellig, HIGH);
    digitalWrite(G_rechts_einstellig, HIGH);
    break;

  case 6:
    digitalWrite(A_rechts_einstellig, HIGH);
    digitalWrite(B_rechts_einstellig, LOW);
    digitalWrite(C_rechts_einstellig, HIGH);
    digitalWrite(D_rechts_einstellig, HIGH);
    digitalWrite(E_rechts_einstellig, HIGH);
    digitalWrite(F_rechts_einstellig, HIGH);
    digitalWrite(G_rechts_einstellig, HIGH);
    break;

  case 7:
    digitalWrite(A_rechts_einstellig, HIGH);
    digitalWrite(B_rechts_einstellig, HIGH);
    digitalWrite(C_rechts_einstellig, HIGH);
    digitalWrite(D_rechts_einstellig, LOW);
    digitalWrite(E_rechts_einstellig, LOW);
    digitalWrite(F_rechts_einstellig, LOW);
    digitalWrite(G_rechts_einstellig, LOW);
    break;

  case 8:
    digitalWrite(A_rechts_einstellig, HIGH);
    digitalWrite(B_rechts_einstellig, HIGH);
    digitalWrite(C_rechts_einstellig, HIGH);
    digitalWrite(D_rechts_einstellig, HIGH);
    digitalWrite(E_rechts_einstellig, HIGH);
    digitalWrite(F_rechts_einstellig, HIGH);
    digitalWrite(G_rechts_einstellig, HIGH);
    break;

  case 9:
    digitalWrite(A_rechts_einstellig, HIGH);
    digitalWrite(B_rechts_einstellig, HIGH);
    digitalWrite(C_rechts_einstellig, HIGH);
    digitalWrite(D_rechts_einstellig, HIGH);
    digitalWrite(E_rechts_einstellig, LOW);
    digitalWrite(F_rechts_einstellig, HIGH);
    digitalWrite(G_rechts_einstellig, HIGH);
    break;
  }
}

void anzeigeRechtsZweistellig(int wert)
{
  switch (wert)
  {
  case 0:
    digitalWrite(A_rechts_zweistellig, LOW);
    digitalWrite(B_rechts_zweistellig, LOW);
    digitalWrite(C_rechts_zweistellig, LOW);
    digitalWrite(D_rechts_zweistellig, LOW);
    digitalWrite(E_rechts_zweistellig, LOW);
    digitalWrite(F_rechts_zweistellig, LOW);
    digitalWrite(G_rechts_zweistellig, LOW);
    break;

  case 1:
    digitalWrite(A_rechts_zweistellig, LOW);
    digitalWrite(B_rechts_zweistellig, HIGH);
    digitalWrite(C_rechts_zweistellig, HIGH);
    digitalWrite(D_rechts_zweistellig, LOW);
    digitalWrite(E_rechts_zweistellig, LOW);
    digitalWrite(F_rechts_zweistellig, LOW);
    digitalWrite(G_rechts_zweistellig, LOW);
    break;

  case 2:
    digitalWrite(A_rechts_zweistellig, HIGH);
    digitalWrite(B_rechts_zweistellig, HIGH);
    digitalWrite(C_rechts_zweistellig, LOW);
    digitalWrite(D_rechts_zweistellig, HIGH);
    digitalWrite(E_rechts_zweistellig, HIGH);
    digitalWrite(F_rechts_zweistellig, LOW);
    digitalWrite(G_rechts_zweistellig, HIGH);
    break;

  case 3:
    digitalWrite(A_rechts_zweistellig, HIGH);
    digitalWrite(B_rechts_zweistellig, HIGH);
    digitalWrite(C_rechts_zweistellig, HIGH);
    digitalWrite(D_rechts_zweistellig, HIGH);
    digitalWrite(E_rechts_zweistellig, LOW);
    digitalWrite(F_rechts_zweistellig, LOW);
    digitalWrite(G_rechts_zweistellig, HIGH);
    break;

  case 4:
    digitalWrite(A_rechts_zweistellig, LOW);
    digitalWrite(B_rechts_zweistellig, HIGH);
    digitalWrite(C_rechts_zweistellig, HIGH);
    digitalWrite(D_rechts_zweistellig, LOW);
    digitalWrite(E_rechts_zweistellig, LOW);
    digitalWrite(F_rechts_zweistellig, HIGH);
    digitalWrite(G_rechts_zweistellig, HIGH);
    break;

  case 5:
    digitalWrite(A_rechts_zweistellig, HIGH);
    digitalWrite(B_rechts_zweistellig, LOW);
    digitalWrite(C_rechts_zweistellig, HIGH);
    digitalWrite(D_rechts_zweistellig, HIGH);
    digitalWrite(E_rechts_zweistellig, LOW);
    digitalWrite(F_rechts_zweistellig, HIGH);
    digitalWrite(G_rechts_zweistellig, HIGH);
    break;

  case 6:
    digitalWrite(A_rechts_zweistellig, HIGH);
    digitalWrite(B_rechts_zweistellig, LOW);
    digitalWrite(C_rechts_zweistellig, HIGH);
    digitalWrite(D_rechts_zweistellig, HIGH);
    digitalWrite(E_rechts_zweistellig, HIGH);
    digitalWrite(F_rechts_zweistellig, HIGH);
    digitalWrite(G_rechts_zweistellig, HIGH);
    break;

  case 7:
    digitalWrite(A_rechts_zweistellig, HIGH);
    digitalWrite(B_rechts_zweistellig, HIGH);
    digitalWrite(C_rechts_zweistellig, HIGH);
    digitalWrite(D_rechts_zweistellig, LOW);
    digitalWrite(E_rechts_zweistellig, LOW);
    digitalWrite(F_rechts_zweistellig, LOW);
    digitalWrite(G_rechts_zweistellig, LOW);
    break;

  case 8:
    digitalWrite(A_rechts_zweistellig, HIGH);
    digitalWrite(B_rechts_zweistellig, HIGH);
    digitalWrite(C_rechts_zweistellig, HIGH);
    digitalWrite(D_rechts_zweistellig, HIGH);
    digitalWrite(E_rechts_zweistellig, HIGH);
    digitalWrite(F_rechts_zweistellig, HIGH);
    digitalWrite(G_rechts_zweistellig, HIGH);
    break;

  case 9:
    digitalWrite(A_rechts_zweistellig, HIGH);
    digitalWrite(B_rechts_zweistellig, HIGH);
    digitalWrite(C_rechts_zweistellig, HIGH);
    digitalWrite(D_rechts_zweistellig, HIGH);
    digitalWrite(E_rechts_zweistellig, LOW);
    digitalWrite(F_rechts_zweistellig, HIGH);
    digitalWrite(G_rechts_zweistellig, HIGH);
    break;
  }
}


/*
void interruptRoutine()
{
  if (millis() - last_time_ISR > debounce_time)
  {
    reset_status = 1;
    last_time_ISR = millis();
  }
}

*/