#include <Arduino.h>

#define pin 2

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  Serial.setTimeout(10);
}

int led = 0;
float temp = 21;
float posvol = 4.2;

void loop()
{
  // char data
  // String str = Serial.readStringUntil('\n');
  // digitalWrite(LED_BUILTIN, str.toInt());
  if (digitalRead(2))
  {
    temp = 21;
  }
  else
  {
    temp = 65;
  }
  String data = String(digitalRead(2)) + "/" +
                String(digitalRead(3)) + "/" +
                String(digitalRead(4)) + "/" +
                String(digitalRead(5)) + "/" +
                temp + "/" +
                posvol;
  Serial.println(data);
  delay(500);
}
