#include <Arduino.h>
#include <TimerOne.h>
#include <EEPROM.h>

#define open_pin 3    // Valve open signal from ECU, inverted, need pullup
#define close_pin 4   // Valve close signal from ECU, inverted, need pullup
#define pump_pin 5    // Pump control, inverted, need pullup
#define p_contr_pin 2 // Power supply control pin, inverted, need pullup
#define pos_pin 6     // PWM output emulating valve position sensor
#define temp_pin 7    // PWM output emulating temperature sensor

// #define debug

volatile float pos = 3.5;
volatile float temp = 35;

const float pos_incr = 0.1;

int postopwm(float val)
{
  const float A = 10;
  const float B = 15;
  return min(max(0, val * A + B), 255);
}

int temptopwm(float val)
{
  return val * 10 + 15;
}

void ontimer()
{
  if (digitalRead(open_pin) == LOW)
  {
    pos += pos_incr;
    analogWrite(pos_pin, postopwm(pos));
  }
  if (digitalRead(close_pin) == LOW)
  {
    pos -= pos_incr;
    analogWrite(pos_pin, postopwm(pos));
  }
}

const String blank = "\r                                                             \r";

#ifdef debug
void serialreport()
{
  String data = blank +
                String(digitalRead(2)) + "/" +
                String(digitalRead(3)) + "/" +
                String(digitalRead(4)) + "/" +
                String(digitalRead(5)) + "/" +
                temp + "/" +
                pos;
  Serial.print(data);
}
#endif

void savevals()
{
  // EEPROM.write(0,[pos,temp]);
}

void restorevals() {}

void setup()
{
  // Setting inputs and outputs
  pinMode(open_pin, INPUT_PULLUP);
  pinMode(close_pin, INPUT_PULLUP);
  pinMode(pump_pin, INPUT_PULLUP);
  pinMode(p_contr_pin, INPUT_PULLUP);
  pinMode(pos_pin, OUTPUT);
  pinMode(temp_pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  analogWrite(pos_pin, pos);
  analogWrite(temp_pin, temp);

  // Starting timer and attach an interrupt to it
  Timer1.initialize(100000);
  Timer1.attachInterrupt(ontimer);
#ifdef debug
  Serial.begin(115200);
#endif

  attachInterrupt(digitalPinToInterrupt(p_contr_pin), savevals, FALLING);
  restorevals();

  Serial.begin(115200);
}

union
{
  float f[2];
  byte c[8];
} fc;

void loop()
{
// char data
// String str = Serial.readStringUntil('\n');
// digitalWrite(LED_BUILTIN, str.toInt());
// if (digitalRead(2))
// {
//   temp = 21;
// }
// else
// {
//   temp = 165;
// }
#ifdef debug
  serialreport();
  delay(100);
#endif
  delay(500);
  fc.f[0]=pos;
  fc.f[1]=temp;
   for (int i = 0; i < 8; i++)
  {
    Serial.print(fc.c[i], HEX);
    Serial.print("/");

  }
  Serial.println();
}
