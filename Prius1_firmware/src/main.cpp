#include <Arduino.h>
#include <TimerOne.h>
#include <EEPROM.h>

#define open_pin 3    // Valve open signal from ECU, inverted, need pullup
#define close_pin 4   // Valve close signal from ECU, inverted, need pullup
#define pump_pin 5    // Pump control, inverted, need pullup
#define p_contr_pin 2 // Power supply control pin, inverted, need pullup
#define pos_pin 6     // PWM output emulating valve position sensor
#define temp_pin 7    // PWM output emulating temperature sensor

const unsigned char initkey = 10;
const int initaddr = 0;
const int dataaddr = 1;

#define debug

struct Data
{
  float pos = 3.5;
  float temp = 40;
};

volatile Data data;

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
    data.pos += pos_incr;
    analogWrite(pos_pin, postopwm(data.pos));
  }
  if (digitalRead(close_pin) == LOW)
  {
    data.pos -= pos_incr;
    analogWrite(pos_pin, postopwm(data.pos));
  }
}

const String blank = "\r                                                             \r";

#ifdef debug
void serialreport()
{
  String s = blank +
             String(digitalRead(2)) + "/" +
             String(digitalRead(3)) + "/" +
             String(digitalRead(4)) + "/" +
             String(digitalRead(5)) + "/" +
             data.temp + "/" +
             data.pos;
  Serial.print(s);
}
#endif

void savevals()
{
  EEPROM.put(initaddr, initkey);
  EEPROM.put(dataaddr, data);
}

void restorevals()
{
  unsigned char rkey;
  EEPROM.get(initkey, rkey);
  if (rkey == initkey)
  {
    EEPROM.get(dataaddr, data);
  }
}

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
  analogWrite(pos_pin, data.pos);
  analogWrite(temp_pin, data.temp);

  // Starting timer and attach an interrupt to it
  Timer1.initialize(100000);
  Timer1.attachInterrupt(ontimer);
#ifdef debug
  Serial.begin(115200);
#endif

  attachInterrupt(digitalPinToInterrupt(p_contr_pin), savevals, FALLING);
  restorevals();
  savevals();

  Serial.begin(115200);
}

void loop()
{
#ifdef debug
  serialreport();
  delay(100);
#endif
}
