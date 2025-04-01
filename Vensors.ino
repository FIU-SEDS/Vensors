// Main file code for the vertical mass measuring device
#include "main.h"
#include <cmath>

bool prevIsInApogee = false;

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
  // Entering apogee
  if (!prevIsInApogee && isInApogee()) {
    preApogeeTimeOfFlightSetup();
    prevIsInApogee = true;

    // Exiting apogee
  } else if (prevIsInApogee && !isInApogee()) {
    turnOffTimeOfFlight();
    prevIsInApogee = false;

    // Not in apogee
  } else if (!isInApogee()) {
    return;
  }

  // Begin the measurements

  // stdMeasLoop();

  loopTest();
}
