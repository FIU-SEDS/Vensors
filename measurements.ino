#include <cmath>
#include <vector>

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

constexpr int MAX_EXPECTED_MEASUREMENTS = static_cast<int>(std::sqrt((2 * MAX_DIST_CONSTANT_FORCE) / MIN_EXPECTED_ACCEL));

std::vector<measurment> leftMeasurements;
std::vector<measurment> rightMeasurements;

void setupMeasurements()
{
  leftMeasurements.reserve(MAX_EXPECTED_MEASUREMENTS);
  rightMeasurements.reserve(MAX_EXPECTED_MEASUREMENTS);
}

std::vector<measurment> *getLeftMeasurements()
{
  return &leftMeasurements;
}

std::vector<measurment> *getRightMeasurements()
{
  return &rightMeasurements;
}

void addLeftMeas(double distance, uint64_t time)
{
  leftMeasurements.push_back({distance, time});
}

void addRightMeas(double distance, uint64_t time)
{
  rightMeasurements.push_back({distance, time});
}

void recordLeftMeas()
{
  leftMeasurements.push_back({getLDistanceSensor(), micros()});
}

void recordRightMeas()
{
  rightMeasurements.push_back({getRDistanceSensor(), micros()});
}

void recordMeas() {
  recordLeftMeas();
  recordRightMeas();
}

void clearBothMeas()
{
  leftMeasurements.clear();
  rightMeasurements.clear();
}

double getLeftAvg()
{
  return averageAcceleration(leftMeasurements);
}

double getRightAvg()
{
  return averageAcceleration(rightMeasurements);
}


/**
 * Calculates the acceleration using the data
 * from both sensors and then clears out the measurements
 */
void calculateMass() {
  double leftAvg = getLeftAvg();
  double rightAvg = getRightAvg();

  Serial.print("Left avg: ");
  Serial.print(leftAvg);

  Serial.print(",");

  Serial.print("Right avg: ");
  Serial.print(rightAvg);

  clearBothMeas();
}
