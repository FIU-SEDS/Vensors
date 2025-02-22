// Main file code for the vertical mass measuring device
#include "main.h"
#include <cmath>


// magneto motor pins (s). default pin number
  static int motorPin=0001;
  static int magPinFirstRight=00;
  static int magPinSecRight=01;
  static const int intial_ACCEL=0;
 // function for right pillar movement
 void startRightPillars()
 {
    analogWrite(motorPin,MIN_EXPECTED_ACCEL);
    digitalWrite(magPinFirstRight,MIN_EXPECTED_ACCEL);
    digitalWrite(magPinSecRight,MIN_EXPECTED_ACCEL);
 }
 void stopRightPillar()
 {
    analogWrite(motorPin,intial_ACCEL);
    digitalWrite(magPinFirstRight,intial_ACCEL);
    digitalWrite(magPinSecRight,intial_ACCEL);
 }
 //function for left pillar movement
 void startLeftPillars(){}
 void stopLeftPillars(){}
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
  //track distance and time
  bool movingRight=true;
  uint64_t timeI=0;
  uint64_t timeII;
  
  /* start movement towards the right*/
  if(movingRight)
  {
    if(timeI==0){
    timeI=millis();
    startRightPillars();
    }
    //time taken
    timeII=millis()-timeI;
    //converts it to seconds
    double duration_time= timeII/1000.0;
    //distance formula 1/2a(t)^2
    int raiseToThePowTwo=2;
    double distance= 0.5 * MIN_EXPECTED_ACCEL*pow(duration_time,raiseToThePowTwo);
    if(distance >=(MAX_TRAVEL_DISTANCE-MAX_DIST))
    {
      stopRightPillar();
      movingRight=false;
    }
    //decceleration statement can go here

  }
    Serial.println(MAX_EXPECTED_MEASURMENTS);
    delay(500);
}
