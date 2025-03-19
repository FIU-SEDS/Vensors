// Main file code for the vertical mass measuring device
#include "main.h"
#include <cmath>

/**
 * File containing code for the standard way of measurement
 */

/**
 * Setup code for the standard measurement setup
 */
void stdMeasSetup()
{
  //calls full setup method
  fullSetup();
}

/**
 * Loop code for the standard measurement loop
 */
void stdMeasLoop()
{
  double readLeft = getLDistanceSensor();
  double readRight = getRDistanceSensor();
  // intial acceleration
  rightFacingForce();
  delay(MEASURE_INTERVAL);

  while (readLeft > MAX_DIST)
  {
    rightFacingForce();
    uint64_t currTime = uint64_t(micros()) * 1000;   // gets time in nanoseconds
    readLeft = getLDistanceSensor();                 // read from left sensor
    readRight = getRDistanceSensor();                // read data from right sensor
    leftMeasurments.push_back({readLeft, currTime}); // reads data into left sensor
    rightMeasurments.push_back({readRight, currTime});
    delay(MEASURE_INTERVAL);
  }
  // deceleration loop
  while (readRight > MAX_DIST)
  {
    leftFacingForce();
    uint64_t currTime = uint64_t(micros()) * 1000; // gets time in nanoseconds
    readLeft = getLDistanceSensor();               // read from left sensor
    readRight = getRDistanceSensor();              // read data from right sensor
    rightMeasurments.push_back({readRight, currTime});
    leftMeasurments.push_back({readLeft, currTime});
    delay(MEASURE_INTERVAL);
  }
  Serial.println(MAX_EXPECTED_MEASURMENTS);
  delay(500);
}
