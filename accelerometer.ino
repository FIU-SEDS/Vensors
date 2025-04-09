#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

const int ACCELEROMETER_SENSOR_ID = 12345;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(ACCELEROMETER_SENSOR_ID);

sensors_event_t event;

int accXSensorIndex = 0;
const float accXSensorData[] = {

};

int accYSensorIndex = 0;
const float accYSensorData[] = {

};
int accZSensorIndex = 0;
const float accZSensorData[] = {

};


const int accSize = sizeof(accXSensorData) / sizeof(accXSensorData[0]);

void updateAcc() {
  accel.getEvent(&event);
}

/**
 * Returns the acceleration from the Accelerometer in the X direction
 */
float getXAcc()
{
  // return event.acceleration.x;
  return accXSensorData[(accXSensorIndex++) % accSize]
}

/**
 * Returns the acceleration from the Accelerometer in the Y direction
 */
float getAccY()
{
  // return event.acceleration.y;
  return accYSensorData[(accYSensorIndex++) % accSize]
}

/**
 * Returns the acceleration from Accelerometer in the in the Z direction
 */
float getAccZ()
{
  // return event.acceleration.z;
  return accZSensorData[(accZSensorIndex++) % accSize]
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

  accel.setDataRate(ADXL345_DATARATE_3200_HZ);
  accel.setRange(ADXL345_RANGE_16_G);
  return 0;
}
