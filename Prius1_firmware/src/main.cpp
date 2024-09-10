#include <Arduino.h>
#include <TimerOne.h>

#define open_pin 2  // Valve open signal from ECU, inverted, need pulup
#define close_pin 3 // Valve close signal from ECU, inverted, need pulup
#define pump_pin 4  // Pump control, inverted, need pulup
#define pos_pin 5   // PWM output emulating valve position sensor
#define temp_pin 6  // PWM output emlating temperature sensor

volatile unsigned char pos = 127;
volatile unsigned char temp = 127;

const char pos_incr = 1;

void ontimer()
{
  if (digitalRead(open_pin) == LOW)
  {
    pos += pos_incr;
    analogWrite(pos_pin, pos);
  }
  if (digitalRead(close_pin) == LOW)
  {
    pos -= pos_incr;
    analogWrite(pos_pin, pos);
  }
}

void setup()
{
  // Setting inputs and outputs
  pinMode(open_pin, INPUT_PULLUP);
  pinMode(close_pin, INPUT_PULLUP);
  pinMode(pump_pin, INPUT_PULLUP);
  pinMode(pos_pin, OUTPUT);
  pinMode(temp_pin, OUTPUT);
  analogWrite(pos_pin, pos);
  analogWrite(temp_pin, temp);

  // Starting timer and attach an interrupt to it
  Timer1.initialize(100000);
  Timer1.attachInterrupt(ontimer);
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
    temp = 165;
  }
  String data = "\r                                                             \r" +
                String(digitalRead(2)) + "/" +
                String(digitalRead(3)) + "/" +
                String(digitalRead(4)) + "/" +
                String(digitalRead(5)) + "/" +
                temp + "/" +
                posvol;
  Serial.print(data);
  delay(500);
}
