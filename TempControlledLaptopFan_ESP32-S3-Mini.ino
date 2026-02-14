// A simple Arduino project that uses a temperature sensor to control two fans to help cool down a laptop on a laptop stand.
// Power is supplied by any 5V source and a mosfet switch is used to switch the fans on/off based on the current temperature
// under the laptop. I was able to see the fans reduce the temperature under the laptop from 32.8 – 30.8*C within 2 minutes.
// If the fans don't need to be on, the device will switch them off and go into deep sleep for 10 seconds, then check the
// temperature again.
//
// Hardware:
//    ESP32-C3 Super Mini
//    SHT31 temperature sensor
//    N-Channel Mosfet (16A 60V TO-220)
//    5V 0.2Amp Cooler Fans (30 x 30 x 7mm)
//    220 Ohm Resistor

#include <Wire.h>
#include "Adafruit_SHT31.h"

#define DEBUG 1

#ifdef DEBUG
#define DebugPrintf(...) Serial.printf(__VA_ARGS__)
#define DebugPrintln(...) Serial.println(__VA_ARGS__)
#else
#define DebugPrintln(...)
#define DebugPrintf(...)
#endif

// Pin connecting Mosfet gate wire
#define MOSFET_GATE 21

// When hotter than this temp, the fans will switch on. I just determined this by experimenting.
const float TemperatureThreshold = 30.0f;

// If the fans don't need to be on, the device will go into deepsleep for 10 seconds, then check the temperature, then deepsleep again, etc.
const uint64_t waitTimeInSec = 10;
const uint64_t waitTimeInMSec = waitTimeInSec * 1000;
const uint64_t DeepSleepTime = waitTimeInSec * 1000000ULL;

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup()
{
#ifdef DEBUG
  Serial.begin(115200);
  delay(200);
#endif

  DebugPrintf("\n\n********* Temperature controlled laptop fan using ESP32-C3 Super Mini *********\n\n");

  // Init SHT31
  if (!sht31.begin(0x44))
  {
    DebugPrintln("Couldn't find SHT31, sleeping then retrying...");
    DeepSleep();
  }

  pinMode(MOSFET_GATE, OUTPUT);
  TurnFansOff();
}

void loop()
{
  float t = sht31.readTemperature();

  if (isnan(t))
  { 
    DebugPrintln("Failed to read temperature");
    delay(waitTimeInMSec);
    return;
  }

  DebugPrintf("Temp *C = %2.1f\t\t\n", t);

  if (t > TemperatureThreshold)
  {
    TurnFansOn();
  }
  else
  {
    TurnFansOff();
    DeepSleep();
  }

  delay(waitTimeInMSec);
}

void TurnFansOn()
{
  DebugPrintln("Turn fans ON");
  digitalWrite(MOSFET_GATE, HIGH);
}

void TurnFansOff()
{
  DebugPrintln("Turn fans OFF");
  digitalWrite(MOSFET_GATE, LOW);
}

void DeepSleep()
{ 
  DebugPrintln("Going into deep sleep");

#ifdef DEBUG
  Serial.flush();
#endif

  // Go into deep sleep
  esp_sleep_enable_timer_wakeup(DeepSleepTime);
  esp_deep_sleep_start();
}

