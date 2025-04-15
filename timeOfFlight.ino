#include <Wire.h>
#include <VL53L1X.h>

#define TOF_XSHUT_A 10
#define TOF_XSHUT_B 9

#define TOF_DISTANCE_MODE VL53L1X::DistanceMode::Short

// Timing Budget in microseconds
#define TOF_TIMING_BUDGET 40000

// Time in MS in which the sensor will wait until, giving up on th reading
#define TOF_TIMEOUT 500

// Time in MS to wait durring the seutp proceess for the sensor to read the shutoff command
#define TOF_SHUNT_WAIT 50

/**
 * The buffer in the values in where the sensors will say that the carrige is located in the center
 */
const int CENTER_BUFFER = 4;

const int LEFT_SENSOR_CENTER = 90;
const int RIGHT_SENSOR_CENTER = 110;

VL53L1X sensor_A;
VL53L1X sensor_B;

int LTOFSensorIndex = 0;
const int leftTimeOfFlightSensorData[] = {
  1, 3, 8, 14, 19, 27, 35, 45, 56, 67, 76, 82, 90, 90, 90, 90, 90, 90, 89, 88, 87, 83, 77, 71, 63, 55, 45, 35, 30, 21, 18, 13, 10, 11, 11, 11, 12, 14, 17, 22, 29, 35, 46, 54, 63, 72, 78, 82, 86, 88, 90, 90, 89, 90, 86, 83, 77, 71, 64, 55, 44, 37, 29, 23, 16, 14, 10, 9, 11, 10, 11, 14, 16, 22, 30, 36, 46, 54, 65, 71, 77, 83, 86, 90, 89, 90, 90, 90, 87, 82, 78, 72, 63, 56, 46, 37, 30, 22, 16, 13, 10, 9, 9, 9, 10, 14, 18, 23, 28, 36, 45, 56, 63, 70, 77, 81, 85, 90, 90, 90, 90, 88, 86, 82, 78, 70, 64, 56, 46, 36, 28, 22, 18, 14, 12, 10, 11, 11, 12, 15, 16, 22, 29, 35, 46, 56, 63, 71, 78, 82, 86, 90, 90, 90, 90, 88, 87, 83, 76, 71, 63, 55, 45, 36, 30, 23, 17, 14, 12, 11, 10, 9, 12, 14, 18, 21, 30, 37, 45, 55, 64, 70, 77, 82, 87, 90, 90, 90, 89, 89, 86, 83, 78, 72, 64, 55, 46, 37, 30, 21, 18, 13, 10, 11, 10, 10, 10, 15, 17, 23, 30, 37, 45, 56, 65, 70, 76, 83, 86, 90, 89, 90, 90, 89, 87, 82, 76, 70, 63, 54, 46, 36, 29, 23, 16, 15, 11, 10, 10, 11, 10, 13, 18, 23, 28, 35, 44, 55, 63, 71, 78, 83, 86, 88, 90, 90, 90, 90, 86, 81, 77, 72, 65, 55, 46, 35, 30, 21, 17, 14, 12, 10, 11, 10, 12, 15, 17, 21, 28, 35, 44, 55, 64, 71, 76, 82, 87, 88, 90, 90, 90, 90, 86, 83, 77, 72, 65, 56, 45, 36, 30, 22, 16, 13, 11, 11, 11, 10, 11, 15, 16, 23, 28, 35, 45, 54, 63, 72, 76, 81, 85, 90, 90, 89, 90, 89, 86, 82, 76, 72, 63, 54, 46, 37, 29, 21, 18, 13, 11, 10, 11, 9, 12, 15, 18, 21, 28, 35, 46, 54, 63, 72, 77, 83, 85, 89, 90, 90, 90, 88, 85, 82, 76, 72, 65, 55, 45, 35, 28, 23, 18, 13, 10, 11, 10, 10, 10, 15, 17, 23, 30, 37, 46, 55, 63, 70, 78, 83, 86, 89, 90, 90, 90, 90, 85, 81, 76, 70, 64, 56
};

int RTOFSensorIndex = 0;
const int rightTimeOfFlightSensorData[] = {
  99, 97, 92, 86, 81, 73, 65, 55, 44, 33, 24, 18, 10, 10, 10, 10, 10, 10, 11, 12, 13, 17, 23, 29, 37, 45, 55, 65, 70, 79, 82, 87, 90, 89, 89, 89, 88, 86, 83, 78, 71, 65, 54, 46, 37, 28, 22, 18, 14, 12, 10, 10, 11, 10, 14, 17, 23, 29, 36, 45, 56, 63, 71, 77, 84, 86, 90, 91, 89, 90, 89, 86, 84, 78, 70, 64, 54, 46, 35, 29, 23, 17, 14, 10, 11, 10, 10, 10, 13, 18, 22, 28, 37, 44, 54, 63, 70, 78, 84, 87, 90, 91, 91, 91, 90, 86, 82, 77, 72, 64, 55, 44, 37, 30, 23, 19, 15, 10, 10, 10, 10, 12, 14, 18, 22, 30, 36, 44, 54, 64, 72, 78, 82, 86, 88, 90, 89, 89, 88, 85, 84, 78, 71, 65, 54, 44, 37, 29, 22, 18, 14, 10, 10, 10, 10, 12, 13, 17, 24, 29, 37, 45, 55, 64, 70, 77, 83, 86, 88, 89, 90, 91, 88, 86, 82, 79, 70, 63, 55, 45, 36, 30, 23, 18, 13, 10, 10, 10, 11, 11, 14, 17, 22, 28, 36, 45, 54, 63, 70, 79, 82, 87, 90, 89, 90, 90, 90, 85, 83, 77, 70, 63, 55, 44, 35, 30, 24, 17, 14, 10, 11, 10, 10, 11, 13, 18, 24, 30, 37, 46, 54, 64, 71, 77, 84, 85, 89, 90, 90, 89, 90, 87, 82, 77, 72, 65, 56, 45, 37, 29, 22, 17, 14, 12, 10, 10, 10, 10, 14, 19, 23, 28, 35, 45, 54, 65, 70, 79, 83, 86, 88, 90, 89, 90, 88, 85, 83, 79, 72, 65, 56, 45, 36, 29, 24, 18, 13, 12, 10, 10, 10, 10, 14, 17, 23, 28, 35, 44, 55, 64, 70, 78, 84, 87, 89, 89, 89, 90, 89, 85, 84, 77, 72, 65, 55, 46, 37, 28, 24, 19, 15, 10, 10, 11, 10, 11, 14, 18, 24, 28, 37, 46, 54, 63, 71, 79, 82, 87, 89, 90, 89, 91, 88, 85, 82, 79, 72, 65, 54, 46, 37, 28, 23, 17, 15, 11, 10, 10, 10, 12, 15, 18, 24, 28, 35, 45, 55, 65, 72, 77, 82, 87, 90, 89, 90, 90, 90, 85, 83, 77, 70, 63, 54, 45, 37, 30, 22, 17, 14, 11, 10, 10, 10, 10, 15, 19, 24, 30, 36, 44
};

const int tofSize = sizeof(leftTimeOfFlightSensorData) / sizeof(leftTimeOfFlightSensorData[0]);

/**
 * Returns the distance measured by the left sensor in mm
 */
int getLDistanceSensor()
{
  // return sensor_A.read();
  return leftTimeOfFlightSensorData[(LTOFSensorIndex++) % tofSize];
}

/**
 * Returns the distance measured by the right sensor in mm
 */
int getRDistanceSensor()
{
  // return sensor_B.read();
  return rightTimeOfFlightSensorData [(RTOFSensorIndex++) % tofSize];
}

/**
 * Initializes the time of flight sensors before liftoff
 * @return 0 on success, non-zero otherwise.
 */
int setupTimeOfFlightInitial() {
  sensor_A.setBus(&Wire1);
  sensor_B.setBus(&Wire1);

  //Set the pin mode to output
  pinMode(TOF_XSHUT_A, OUTPUT);
  pinMode(TOF_XSHUT_B, OUTPUT);

  turnOffTimeOfFlight();

  return 0;
}

/**
 * Initializes the time of flight sensors durring launch
 * @return 0 on success, non-zero otherwise.
 */
int preApogeeTimeOfFlightSetup() {
  return 0;
  //-----------------------------------------------------------------

  //FIRST WE WILL CONFIGURE AND SETUP SENSOR_A
  //-----------------------------------------------------------------
  delay(TOF_SHUNT_WAIT);
  digitalWrite(TOF_XSHUT_A, HIGH); //Turn sensor_A on
  delay(TOF_SHUNT_WAIT);

  sensor_A.setTimeout(TOF_TIMEOUT); //Set the sensors timeout

  if (!sensor_A.init())//try to initilise the sensor
  {
      //Sensor does not respond within the timeout time
      Serial.println("Sensor_A is not responding, check your wiring");
      return -1;
  }
  else
  {
      sensor_A.setAddress(42); //Set the sensors I2C address
      sensor_A.setDistanceMode(TOF_DISTANCE_MODE); //Set the sensor to maximum range of 4 meters
      sensor_A.setMeasurementTimingBudget(TOF_TIMING_BUDGET); //Set its timing budget in microseconds longer timing budgets will give more accurate measurements
      sensor_A.startContinuous(45); //Sets the interval where a measurement can be requested in milliseconds
  }

    //-----------------------------------------------------------------
    //NOW CONFIGURE AND SETUP SENSOR_B
    //-----------------------------------------------------------------
    delay(TOF_SHUNT_WAIT);
    digitalWrite(TOF_XSHUT_B, HIGH); //Turn sensor_A on
    delay(TOF_SHUNT_WAIT);

    sensor_B.setTimeout(TOF_TIMEOUT); //Set the sensors timeout

    if (!sensor_B.init())//try to initilise the sensor
    {
        //Sensor does not respond within the timeout time
        Serial.println("Sensor_B is not responding, check your wiring");
        return 1;
    }
    else
    {
        sensor_B.setAddress(43); //Set the sensors I2C address
        sensor_B.setDistanceMode(TOF_DISTANCE_MODE); //Set the sensor to maximum range of 4 meters
        sensor_B.setMeasurementTimingBudget(TOF_TIMING_BUDGET); //Set its timing budget in microseconds longer timing budgets will give more accurate measurements
        sensor_B.startContinuous(45); //Sets the interval where a measurement can be requested in milliseconds
    }

  Serial.println("TOF Initialized");
  return 0;
}

void turnOffTimeOfFlight() {
  digitalWrite(TOF_XSHUT_A, LOW);
  digitalWrite(TOF_XSHUT_B, LOW);
}

void turnONTimeOfFlight() {
  digitalWrite(TOF_XSHUT_A, HIGH);
  digitalWrite(TOF_XSHUT_B, HIGH);
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
