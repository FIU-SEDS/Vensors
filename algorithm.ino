// #include <WireDual.h>TwoWire I2Ctwo = TwoWire(1);

/**
 * Utility functions for the different variations of the mass
 * measuring algorithm
 */

#define SCL1 16
#define SDA1 15

#define SCL2 5
#define SDA2 4


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
  Serial.println("Starting Setup!");
  Wire.begin(SCL1, SDA1);
  Wire1.begin(SCL2, SDA2);
  Serial.println("Done with wires!");

  int code = 0;

  code = setupTimeOfFlightInitial();
  if (code)
  {
    Serial.print("Failed to setup time of flight sensor, code: ");
    Serial.println(code);
    while(1) {}
  }

  #ifdef DEBUG
    preApogeeTimeOfFlightSetup();
  #endif

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
