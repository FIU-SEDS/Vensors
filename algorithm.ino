/**
 * Utility functions for the different variations of the mass
 * measuring algorithm
 */

/**
 * Function which calls all the setup methods for the following:
 *
 * Time of fight sensor
 * Accelerometer
 * IMU
 * Measurements
 *
 * Hangs program if any of the called setup functions
 * return a non 0 code
 */
void fullSetup()
{
  int code = 0;

  code = setupTimeOfFlight();
  if (code)
  {
    Serial.print("Failed to setup time of flight sensor, code: ");
    Serial.println(code);
    while(1) {}
  }

  return;

  code = setupIMU();
  if (code) {
    Serial.print("Failed to setup time of IMU sensor, code: ");
    Serial.println(code);
    while(1) {}
  }

  code = setupAccelerometer();
  if (code) {
    while(1) {}
  }

  setupMeasurements();
}
