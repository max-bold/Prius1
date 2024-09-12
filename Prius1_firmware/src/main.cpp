#include <Arduino.h>
#include <TimerOne.h>
#include <EEPROM.h>

#define open_pin 3    // Valve open signal from ECU, inverted, need pullup
#define close_pin 4   // Valve close signal from ECU, inverted, need pullup
#define pump_pin 7    // Pump control, inverted, need pullup
#define p_contr_pin 2 // Power supply control pin, inverted, need pullup
#define pos_pin 5     // PWM output emulating valve position sensor
#define temp_pin 6    // PWM output emulating temperature sensor
#define e_temp_in A0  // ADC input for engine temperature sensor
#define e_temp_out 8  // PWM output emulating engine temperature sensor

#define p_contr_inter digitalPinToInterrupt(p_contr_pin)

const unsigned char initkey = 12;
const int initaddr = 0;
const int dataaddr = 1;

#define debug

struct Data
{
  float pos = 3.5;
  float temp = 40;
  unsigned char upd = 1;
};

volatile Data data;
float e_temp;
float e_temp_emul;

const float pos_incr = 0.1;

int postopwm(float val)
{
  return 0, val * 51 + 0;
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
  }
  if (digitalRead(close_pin) == LOW)
  {
    data.pos -= pos_incr;
  }
}

#ifdef debug
void serialreport()
{
  const String blank = "\r                  \r";

  String s = blank +
             String(digitalRead(open_pin)) + "/" +
             String(digitalRead(close_pin)) + "/" +
             String(digitalRead(pump_pin)) + "/" +
             String(digitalRead(p_contr_pin)) + "/" +
             data.temp + "/" +
             data.pos;
  Serial.print(s);
}
#endif

void savevals()
{
  EEPROM.put(dataaddr, data);
}

void restorevals()
{
  EEPROM.get(dataaddr, data);
}

float adctoetemp(int adc)
{
  return (788.48 - adc) / 5.4272;
}

int etemptopwm(float temp)
{
  return temp * -1.3515 + 196.3;
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

  attachInterrupt(p_contr_inter, savevals, FALLING);

  // Load data from EEPROM and try save it back (for first run)
  unsigned char rkey;
  if (EEPROM.get(initaddr, rkey) == initkey)
  {
    restorevals();
  }
  else
  {
    savevals();
    EEPROM.put(initaddr, initkey);
  }

  Serial.begin(115200);
}
#ifdef debug
unsigned long ctime = 0;
#endif

void loop()
{
#ifdef debug
  if (ctime + 100 < millis())
  {
    serialreport();
    ctime = millis();
  }
#endif

  // Updating analog outputs
  if (data.upd)
  {
    analogWrite(pos_pin, postopwm(data.pos));
    analogWrite(temp_pin, temptopwm(data.temp));
    data.upd = 0;
  }

  // Emulating engine temperature sensor
  e_temp = adctoetemp(analogRead(e_temp_in));
  e_temp_emul = e_temp;
  analogWrite(e_temp_out, etemptopwm(e_temp_emul));
}
