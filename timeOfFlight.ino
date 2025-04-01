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

/**
 * Returns the distance measured by the left sensor in mm
 */
int getLDistanceSensor()
{
  return sensor_A.read();
}

/**
 * Returns the distance measured by the right sensor in mm
 */
int getRDistanceSensor()
{
  return sensor_B.read();
}

/**
 * Initializes the time of flight sensors before liftoff
 * @return 0 on success, non-zero otherwise.
 */
int setupTimeOfFlightInitial() {
  sensor_A.setBus(&Wire1);
  sensor_B.setBus(&Wire1);

  //Set the pin mode to output
  pinMode(TOF_XSHUT_A ,OUTPUT);
  pinMode(TOF_XSHUT_B ,OUTPUT);

  turnOffTimeOfFlight();

  return 0;
}

/**
 * Initializes the time of flight sensors durring launch
 * @return 0 on success, non-zero otherwise.
 */
int preApogeeTimeOfFlightSetup() {
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
