// Main file code for the vertical mass measuring device
#include "main.h"
#include <cmath>


struct measurment {
  /** Distance in mm from the sensor */
  double distance;

  /** Time in Nano seconds since the microcontroller started */
  uint64_t time;
};

/** The maximum distance that the carrige can move between the top in bottom
 * portions in mm
 */
const int MAX_TRAVEL_DISTANCE = 200;

/** When the distance from the sensor to the carrige is less than or equal to this value
 * The carrige will begin decellerating and eventually come to a stop
 */
const int MAX_DIST = 40;

/** The maximum distance in which the carrige will experience a constant force
 */
constexpr int MAX_DIST_CONSTANT_FORCE = MAX_TRAVEL_DISTANCE - MAX_DIST;

/** Interval in ms when the sensors will measure values
 */
constexpr int MEASURE_INTERVAL = 100;

/** The minimum expected acceleration in m/s to happen when a constant force is applied to the carrige
 * This is used to reserve space in the measurments array
 * If this value is incorrect tis no biggie
 */
constexpr double MIN_EXPECTED_ACCEL = 0.05;

/** The maximum number of measurments to be done for a given period of constant acceleration
 */
constexpr int MAX_EXPECTED_MEASURMENTS = static_cast<int>( std::sqrt((2 * MAX_DIST_CONSTANT_FORCE) / MIN_EXPECTED_ACCEL) );

std::vector<measurment> leftMeasurments;
std::vector<measurment> rightMeasurments;

void setup() {
  Serial.begin(115200);

  leftMeasurments.reserve(MAX_EXPECTED_MEASURMENTS);
  rightMeasurments.reserve(MAX_EXPECTED_MEASURMENTS);

  Serial.println(MAX_EXPECTED_MEASURMENTS);
  
}

void loop() {
  // accelerating to the right ensuring distance is greater than 40
  double readLeft=readLeftSensor();
  double readRight=readRightSensor();
  //intial acceleration
  rightFacingForce();
  delay(MEASURE_INTERVAL);

    while(readLeft > MAX_DIST)
    {
      rightFacingForce();
      uint64_t currTime=uint64_t(micros())*1000; //gets time in nanoseconds
       readLeft= readLeftSensor();  //read from left sensor
       readRight=readRightSensor(); // read data from right sensor
       leftMeasurments.push_back({readLeft,currTime}); // reads data into left sensor
       rightMeasurments.push_back({readRight,currTime});
       delay(MEASURE_INTERVAL);
    }
    //deceleration loop
    while(readRight > MAX_DIST)
    {
      leftFacingForce();
      uint64_t currTime=uint64_t(micros())*1000; //gets time in nanoseconds
       readLeft= readLeftSensor();  //read from left sensor
       readRight=readRightSensor(); // read data from right sensor
       rightMeasurments.push_back({readRight,currTime});
       leftMeasurments.push_back({readLeft,currTime});
       delay(MEASURE_INTERVAL);
    }
    Serial.println(MAX_EXPECTED_MEASURMENTS);
    delay(500);
}
