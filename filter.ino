#include <vector>

#define TIME_OF_FLIGHT_OUTLIER_CUTOFF 150
#define TIME_OF_FLIGHT_OUTLIER_START 40

/**
 * Filters outliers from list of measurements from the time of flight sensor
 *
 * Filters out values that are either too large or too small
 *
 * Additionally this should implement the z score algorithm to remove outliers that come out
 * This should be fine tuned to keep all data in the range of noise of +- 3mm
 */
std::vector<Measurement> filterOutliersFromTimeOfFlight(std::vector<Measurment> data)
{
}
