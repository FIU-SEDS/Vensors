#include <cmath>
#include <vector>

/** Size of the carrige
 */
const double CARRIGE_SIZE = 35;

/** Size of the carrige
 */
const double HALF_CARRIGE_SIZE = CARRIGE_SIZE / 2;

/**
 * Measurements bellow this value are declared to be inaccurate.
 *
 * If a measurement is bellow this value another sensor value will be used for calculations
 */
const int MEASUREMENT_CUTTOFF = 30;

/** The maximum distance that the carrige can move between the top in bottom
 * portions in mm
 */
const int MAX_TRAVEL_DISTANCE = 110;

/** Interval in ms when the sensors will measure values
 */
constexpr int MEASURE_INTERVAL = 50;

/** The minimum expected acceleration in m/s to happen when a constant force is applied to the carrige
 * This is used to reserve space in the measurments array
 * If this value is incorrect tis no biggie
 */
constexpr double MIN_EXPECTED_ACCEL = 0.05;

/** When the distance from the sensor to the carrige is less than or equal to this value
 * The carrige will begin decellerating and eventually come to a stop
 */
const int MAX_DIST = 40;

/** The maximum distance in which the carrige will experience a constant force
 */
constexpr int MAX_DIST_CONSTANT_FORCE = MAX_TRAVEL_DISTANCE - MAX_DIST;


constexpr int MAX_EXPECTED_MEASUREMENTS = static_cast<int>(std::sqrt((2 * MAX_TRAVEL_DISTANCE ) / MIN_EXPECTED_ACCEL));

std::vector<measurment> leftMeasurements;
std::vector<measurment> rightMeasurements;

void setupMeasurements()
{
  Serial.println("Reserving space for measurements!");
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

int recordLeftMeas()
{
  int dist = getLDistanceSensor();
  leftMeasurements.push_back({dist, micros()});
  return dist;
}

int recordRightMeas()
{
  int dist = getRDistanceSensor();
  rightMeasurements.push_back({dist, micros()});
  return dist;
}

void recordMeas()
{
  recordLeftMeas();
  recordRightMeas();
}

void clearBothMeas()
{
  leftMeasurements.clear();
  rightMeasurements.clear();
}

std::vector<measurment> combineMeasurements() {
  size_t size = leftMeasurements.size();
  std::vector<measurment> combined(size);

  for (size_t i = 0; i < size; i++) {
    measurment left = leftMeasurements[i];
    measurment right = rightMeasurements[i];

    if (left.distance <= MEASUREMENT_CUTTOFF) {
      combined[i] = {right.distance + HALF_CARRIGE_SIZE, right.time};
    } else if (right.distance <= MEASUREMENT_CUTTOFF) {
      combined[i] = {left.distance + HALF_CARRIGE_SIZE, left.time};
    } else {
      double midpoint = (left.distance + right.distance) / 2;
      u_int64_t midtime = (left.time + right.time) / 2;
      combined[i] = {midpoint, midtime};
    }
  }

    return combined;
}

double getAvgAcceleration()
{
  std::vector<measurment> combinedMeasurements = combineMeasurements();

  return averageAcceleration(combinedMeasurements);
}


/**
 * Calculates the acceleration using the data
 * from both sensors and then clears out the measurements
 */
void calculateMass()
{
  double avgAcc = getAvgAcceleration();

  Serial.print("Avg: ");
  Serial.print(avgAcc);
  Serial.println();

  clearBothMeas();
}
