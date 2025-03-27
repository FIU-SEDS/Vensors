// Main file code for the vertical mass measuring device
#include "main.h"
#include <cmath>

struct measurment
{
  /** Distance in mm from the sensor */
  double distance;

  /** Time in Nano seconds since the microcontroller started */
  uint64_t time;
};


void setup()
{
  Serial.begin(115200);

  fullSetup();
  // stdMeasSetup();

  setupTest();
}

void loop()
{
  // if (!isInApogee()) {
  //   return;
  // }

  // stdMeasLoop();

  loopTest();
}
