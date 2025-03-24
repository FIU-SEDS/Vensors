#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

const int ACCELEROMETER_SENSOR_ID = 12345;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(ACCELEROMETER_SENSOR_ID);

sensors_event_t event;

double updateAcc() {
  accel.getEvent(&event);
}

/**
 * Returns the acceleration from the Accelerometer in the X direction
 */
float getXAcc()
{
  return event.acceleration.x;
}

/**
 * Returns the acceleration from the Accelerometer in the Y direction
 */
float getAccY()
{
  return event.acceleration.y;
}

/**
 * Returns the acceleration from Accelerometer in the in the Z direction
 */
float getAccZ()
{
  return event.acceleration.z;
}

/**
 * Calculates the magnitude of the acceleration vector.
 */
float getAccelerationMagnitude() {
  return sqrt(getXAcc() * getXAcc() + getAccY() * getAccY() + getAccZ() * getAccZ());
}

/**
 * Initalized the accelerometer and returns a 0 value if successfull.
 * @return 0 on success, non-zero otherwise.
 */
int setupAccelerometer()
{
  if (!accel.begin())
  {
    return -1;
  }

  accel.setRange(ADXL345_RANGE_16_G);
  return 0;
}
