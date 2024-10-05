#include <Arduino.h>
#include <EEPROM.h>
#include <TimerOne.h>

#define open_pin 3     // Valve open signal from ECU, inverted, need pullup
#define close_pin 4    // Valve close signal from ECU, inverted, need pullup
#define pump_pin 7     // Pump control, inverted, need pullup
#define p_contr_pin 2  // Power supply control pin, inverted, need pullup
#define pos_pin 9      // PWM output emulating valve position sensor
#define temp_pin 10    // PWM output emulating temperature sensor
#define e_temp_in A0   // ADC input for engine temperature sensor
#define e_temp_out 11  // PWM output emulating engine temperature sensor

#define p_contr_inter digitalPinToInterrupt(p_contr_pin)

const unsigned char initkey = 13;
const int initaddr = 0;
const int dataaddr = 1;

#define debug

class PWM {
 private:
  /* data */
 public:
  void init() {
    DDRB |= B00001110;   // Enable outputs OC1A, OC1B, OC2A
                         // Initialising TC1
    TCCR1A = B10100001;  // Clear OC1A/OC1B (pins D9, D10) on Compare Match
    TCCR1B = B00001001;  // set Fast PWM, 8-bit mode, with top at 0x00FF, set No prescaling (62.5 kHz)
    TCCR1C = B00000000;  // Disable Force Output Compare
    OCR1A = 0;           // Set A duty
    OCR1B = 0;           // Set B duty
                         // Initialising TC2
    TCCR2A = B10000011;  // Clear OC2A (pin D11) on Compare Match (non-inverting mode)
    TCCR2B = B00000001;  // Set Fast PWM with top at 0xFF (62.5 kHz), disable Force Output Compare, set No prescaling
    OCR2A = 0;           // Set A duty
  }
  void D9(int val) {
    OCR1A = max(0, min(val, 255));
  }
  void D10(int val) {
    OCR1B = max(0, min(val, 255));
  }
  void D11(int val) {
    OCR2A = max(0, min(val, 255));
  }
  int D9() {
    return OCR1A;
  }
  int D10() {
    return OCR1B;
  }
  int D11() {
    return OCR2A;
  }
} pwm;

class Valve {
 private:
  float pos = 3.5;
  const float posinc = 0.5;  // in V/s
  unsigned long lt = 0;      // Last run time in millis
  bool firstrun = true;

 public:
  int topwm() { return max(0, min(pos * 51 + 0, 255)); };
  bool isA() { return pos <= 3.0; }
  bool isB() { return 3.0 < pos && pos < 4.0; }
  bool isC() { return pos >= 4.0; }

  void set(float val) {
    pos = val;
    update();
  }
  float get() { return pos; }

  void update() {
    unsigned long ct = millis();
    if (ct > lt || firstrun) {
      int op_state = digitalRead(open_pin);
      int cp_state = digitalRead(close_pin);
      if (op_state == LOW || cp_state == LOW || firstrun) {
        unsigned long dt = ct - lt;
        float dv = dt * posinc / 1000;
        if (op_state == LOW) {
          pos += dv;
        }
        if (cp_state == LOW) {
          pos -= dv;
        }
        pwm.D9(topwm());
      }
    }
    lt = ct;
  }

} valve;

class Tanktemp {
 private:
  float temp = 40;
  bool upd = true;

 public:
  void set(float val) {
    temp = val;
    upd = true;
  }
  float get() { return Tanktemp::temp; }
  void update() {
    if (upd) {
      int val = temp * -1.3515 + 196.3;
      pwm.D10(val);
      upd = false;
    }
  }
} ttemp;

class EngineTemp {
 private:
  float temp = 0;

 public:
  void update() {
    int adc = analogRead(e_temp_in);
    pwm.D11(adc / 4);
    fromadc(adc);
  }
  void fromadc(int adc) { temp = (788.48 - adc) / 5.4272; }

  int topwm() { return temp * -1.3515 + 196.3; }
  float get() { return temp; }
} etemp;

int temptopwm(float val) { return val * 10 + 15; }

#ifdef debug
class Debugger {
 private:
  void report() {
    const char blank[35] = "\r                                \r";

    String s = blank + String(digitalRead(open_pin)) + "/" +
               String(digitalRead(close_pin)) + "/" +
               String(digitalRead(pump_pin)) + "/" +
               String(digitalRead(p_contr_pin)) + "/" +
               valve.get() + "/" +
               ttemp.get() + "/" +
               etemp.get();
    Serial.print(s);
  }
  void senddata() {
    struct SendData {
      int op = digitalRead(open_pin);
      int cp = digitalRead(close_pin);
      int pp = digitalRead(pump_pin);
      int pcp = digitalRead(p_contr_pin);
      float vp = valve.get();
      float tt = ttemp.get();
      float et = etemp.get();
      const char end[2]{'\r', '\n'};

    } d;
    Serial.write((char *)&d, sizeof(d));
  }
  unsigned long lasttime = 0;

 public:
  enum SendMode { ASCII,
                  BYTES,
                  PWM };

  void work(SendMode mode) {
    if (lasttime + 100 < millis() || lasttime > millis()) {
      if (mode == ASCII) {
        report();
      } else if (mode == BYTES) {
        senddata();
      } else if (mode == PWM) {
        Serial.println(valve.topwm());
      }

      lasttime = millis();
    }
  }

} debugger;
#endif

class EE {
 private:
 public:
  struct Data {
    float pos;
    float temp;
  } data;
  void save() {
    data.pos = valve.get();
    data.temp = ttemp.get();
    EEPROM.put(dataaddr, data);
    EEPROM.put(initaddr, initkey);
  }

  bool restore() {
    unsigned char initval;
    if (EEPROM.get(initaddr, initval) == initkey) {
      EEPROM.get(dataaddr, data);
      valve.set(data.pos);
      ttemp.set(data.temp);
      return true;
    } else {
      return false;
    }
  }

} ee;

ISR(INT0_vect) {
  EEPROM.put(dataaddr, ee.data);
  EEPROM.put(initaddr, initkey);
  // EEPtr e = dataaddr;
  // const uint8_t *ptr = (const uint8_t *)&ee.data;
  // for (int count = sizeof(ee.data); count; --count, ++e) {
  //   *e = *ptr++;
  // };
}

void setup() {
  // Setting inputs and outputs
  pinMode(open_pin, INPUT_PULLUP);
  pinMode(close_pin, INPUT_PULLUP);
  pinMode(pump_pin, INPUT_PULLUP);
  pinMode(p_contr_pin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

#ifdef debug
  Serial.begin(115200);
#endif

  // Load data from EEPROM and try save it back (for first run)
  if (!ee.restore()) {
    ee.save();
  }

  // attachInterrupt(p_contr_inter, ee_save, RISING);
  pwm.init();

  // Enable INT0 interupts
  EICRA |= B00000011;
  EIMSK |= B00000001;
}

void loop() {
#ifdef debug
  debugger.work(Debugger::SendMode::BYTES);
#endif

  // Updating analog outputs
  valve.update();
  ttemp.update();
  etemp.update();

  ee.data.pos = valve.get();
  ee.data.temp = ttemp.get();
}
