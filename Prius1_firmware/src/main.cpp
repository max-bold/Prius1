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

const unsigned char initkey = 13;
const int initaddr = 0;
const int dataaddr = 1;

#define debug

class Valve
{
private:
  float pos = 3.5;
  const float posinc = 0.5; // in V/s
  unsigned long lt = 0;

public:
  int topwm()
  {
    return pos * 51 + 0;
  };
  bool isA()
  {
    return pos <= 3.0;
  }
  bool isB()
  {
    return 3.0 < pos && pos < 4.0;
  }
  bool isC()
  {
    return pos >= 4.0;
  }

  void set(float val)
  {
    pos = val;
    update();
  }
  float get()
  {
    return pos;
  }

  void update()
  {
    unsigned long ct = millis();
    if (ct > lt)
    {
      int op_state = digitalRead(open_pin);
      int cp_state = digitalRead(close_pin);
      if (op_state == LOW || cp_state == LOW)
      {
        unsigned long dt = ct - lt;
        float dv = dt * posinc / 1000;
        if (op_state == LOW)
        {
          pos += dv;
        }
        if (cp_state == LOW)
        {
          pos -= dv;
        }
        analogWrite(pos_pin, topwm());
      }
    }
    lt = ct;
  }

} valve;

class Tanktemp
{
private:
  float temp = 40;
  bool upd = true;

public:
  void set(float val)
  {
    temp = val;
    upd = true;
  }
  float get()
  {
    return Tanktemp::temp;
  }
  void update()
  {
    if (upd)
    {
      int val = temp * -1.3515 + 196.3;
      analogWrite(temp_pin, val);
      upd = false;
    }
  }
} ttemp;

class EngineTemp
{
private:
  float temp = 0;

public:
  void update()
  {
    int adc = analogRead(e_temp_in);
    analogWrite(e_temp_out, adc / 4);
    fromadc(adc);
  }
  void fromadc(int adc)
  {
    temp = (788.48 - adc) / 5.4272;
  }

  int topwm()
  {
    return temp * -1.3515 + 196.3;
  }
  float get()
  {
    return temp;
  }
} etemp;

int temptopwm(float val)
{
  return val * 10 + 15;
}

#ifdef debug
class Debugger
{
private:
  void report()
  {
    const char blank[35] = "\r                                \r";

    String s = blank +
               String(digitalRead(open_pin)) + "/" +
               String(digitalRead(close_pin)) + "/" +
               String(digitalRead(pump_pin)) + "/" +
               String(digitalRead(p_contr_pin)) + "/" +
               valve.get() + "/" +
               ttemp.get() + "/" +
               etemp.get();
    Serial.print(s);
  }
  unsigned long lasttime = 0;

public:
  void work()
  {
    if (lasttime + 100 < millis() || lasttime > millis())
    {
      report();
      lasttime = millis();
    }
  }
} debugger;
#endif

class EE
{
private:
  struct Data
  {
    float pos;
    float temp;
  } data;

public:
  void save()
  {
    data.pos = valve.get();
    data.temp = ttemp.get();
    EEPROM.put(dataaddr, data);
    EEPROM.put(initaddr, initkey);
  }
  bool restore()
  {
    unsigned char initval;
    if (EEPROM.get(initaddr, initval) == initkey)
    {
      EEPROM.get(dataaddr, data);
      valve.set(data.pos);
      ttemp.set(data.temp);
      return true;
    }
    else
    {
      return false;
    }
  }

} ee;

void ee_save() { ee.save(); }

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

#ifdef debug
  Serial.begin(115200);
#endif

  attachInterrupt(p_contr_inter, ee_save, FALLING);

  // Load data from EEPROM and try save it back (for first run)
  if (!ee.restore())
  {
    ee.save();
  }

  Serial.begin(115200);
}

void loop()
{

#ifdef debug
  debugger.work();
#endif

  // Updating analog outputs
  valve.update();
  ttemp.update();
  etemp.update();
}
