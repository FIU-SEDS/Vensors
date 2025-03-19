#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
 /**
 * Returns the acceleration from the Accelerometer in the X direction
 */
int getXAcc()
{
  sensors_event_t event;
  accel.getEvent(&event);
  return (int)event.acceleration.x;
}
/**
 * Returns the acceleration from the Accelerometer in the Y direction
 */
int getAccY()
{
  sensors_event_t event;
  accel.getEvent(&event);
  return (int)event.acceleration.y;
}
/**
 * Returns the acceleration from Accelerometer in the in the Z direction
 */
int getAccZ()
{
  sensors_event_t event;
  accel.getEvent(&event);
  return (int)event.acceleration.z;
}

/**
 * Initalized the accelerometer and returns a 0 value if successfull.
 * @return 0 on success, non-zero otherwise.
 */
int setupAccelerometer()
{
  if(!accel.begin()){
    return -1;
  }
  return 0;
}

}

