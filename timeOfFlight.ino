#include <Wire.h>
#include "SparkFun_VL53L1X.h"

/**
 * The buffer in the values in where the sensors will say that the carrige is located in the center
 */
const int CENTER_BUFFER = 4;

const int LEFT_SENSOR_CENTER = 90;
const int RIGHT_SENSOR_CENTER = 110;

/**
 * Returns the distance measured by the left sensor in mm
 */
// create objects for right and left sensor;
SFEVL53L1X right_sensor, left_sensor;
int getLDistanceSensor()
{
  // Simulate reading from a sensor
  // initiate measurement
  left_sensor.startRanging();
  while (!left_sensor.checkForDataReady())
  {
    delay(1);
  }
  // result of the measurement from the sensor
  int distance = left_sensor.getDistance();
  // clears any interrupts
  left_sensor.clearInterrupt();
  // stops measuring distance
  left_sensor.stopRanging();
  // returns left sensor distance
  return distance;
}

/**
 * Returns the distance measured by the right sensor in mm
 */
int getRDistanceSensor()
{
  // Simulate reading from a sensor
  // starts measuring
  // initiate measurement
  right_sensor.startRanging();
  // wait for data to be ready
  while (!right_sensor.checkForDataReady())
  {
    delay(1);
  }
  // result of the measurement from the sensor
  int distance = right_sensor.getDistance();
  // clear any interrupt
  right_sensor.clearInterrupt();
  // stops measuring the distance
  right_sensor.stopRanging();
  // returns right sensor distance
  return distance;
}

/**
 * Initalized the time of flight sensors and returns a 0 value if successfull.
 * @return 0 on success, non-zero otherwise.
 */
int setupTimeOfFlight()
{
  // i2c communitcation
  Wire.begin();
  Serial.begin(115200);
  // begin return 0 if the intialization is good
  if (left_sensor.begin() != 0)
  {
    Serial.println("Left_sensor failed to begin.");
    return 1;
  }
  if (right_sensor.begin() != 0)
  {
    Serial.println("Right sensor failed to begin.");
    return 2;
  }
  Serial.println("Sensor working!");
  return 0;
}

/**
 * Checks if the carriage is near the center based on sensor readings.
 *
 * @return True if the carriage is centered, false otherwise.
 */
bool isInCenter(int leftSensorReading, int rightSensorReading)
{
  return (leftSensorReading >= LEFT_SENSOR_CENTER - CENTER_BUFFER &&
          leftSensorReading <= LEFT_SENSOR_CENTER + CENTER_BUFFER) &&
         (rightSensorReading >= RIGHT_SENSOR_CENTER - CENTER_BUFFER &&
          rightSensorReading <= RIGHT_SENSOR_CENTER + CENTER_BUFFER);
}

bool isInCenter() {
  int left = getLDistanceSensor();
  int right = getLDistanceSensor();

  return isInCenter(left, right);
}
