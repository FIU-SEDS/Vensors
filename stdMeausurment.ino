/**
 * File containing code for the standard way of measurement
 */


/**
 * Setup code for the standard measurement setup
 */
void stdMeasSetup()
{
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

    recordLeftMeas();
    recordRightMeas();
    delay(MEASURE_INTERVAL);
  }
  // deceleration loop
  while (readRight > MAX_DIST)
  {
    leftFacingForce();
    uint64_t currTime = uint64_t(micros()) * 1000; // gets time in nanoseconds
    readLeft = getLDistanceSensor();               // read from left sensor
    readRight = getRDistanceSensor();              // read data from right sensor

    recordLeftMeas();
    recordRightMeas();
    delay(MEASURE_INTERVAL);
  }
  // Serial.println(MAX_EXPECTED_MEASURMENTS);
  delay(500);
}
