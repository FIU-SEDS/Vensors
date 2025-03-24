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

/** The maximum distance that the carrige can move between the top in bottom
 * portions in mm
 */
const int MAX_TRAVEL_DISTANCE = 200;

void setup()
{
  Serial.begin(115200);

  stdMeasSetup();
}

void loop()
{
  if (!isInApogee()) {
    return;
  }

  stdMeasLoop();
}
