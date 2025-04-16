/**
 * File containing code for the standard way of measurement
 */

bool initialSetup = true;

int CENTER = 100;

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
  // initial acceleration

  if (initialSetup)
  {
    smdMeasInitialSetup();
  }

  int leftDist = recordLeftMeas();
  int rightDist = recordRightMeas();
  int readLeft = 0;
  int readRight = 0;

  // int distToCenter =
  int center = 5;

  rightFacingForce(center - leftDist);
  delay(MEASURE_INTERVAL);

  while (leftDist > MAX_DIST)
  {
    rightFacingForce(20);
    uint64_t currTime = uint64_t(micros()) * 1000; // gets time in nanoseconds
    readLeft = getLDistanceSensor();               // read from left sensor
    readRight = getRDistanceSensor();              // read data from right sensor

    recordLeftMeas();
    recordRightMeas();
    delay(MEASURE_INTERVAL);
  }
  // deceleration loop
  while (readRight > MAX_DIST)
  {
    leftFacingForce(20);
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

void smdMeasInitialSetup()
{
  leftFacingForce(100);
  delay(500);

  initialSetup = false;
}
