#include <vector>
#include <iostream>
#include <cmath>
#include <cstdint> // for uint64_t

// Constants
#define TIME_OF_FLIGHT_OUTLIER_CUTOFF 200  // mm
#define TIME_OF_FLIGHT_OUTLIER_START 0     // mm
#define ZSCORE_MARGIN 2                    // mm margin around z-score range
#define ZSCORE_THRESHOLD 1                 // Standard deviations for z-score filtering
#define TIME_INTERVAL_NANOSECONDS 50000000 // 0.05 seconds in nanoseconds

// Function to filter out outliers based on distance and z-score
std::vector<Measurement> filterOutliersFromTimeOfFlight(const std::vector<double> &rawDistances)
{
  std::vector<Measurement> data;

  // 1. Convert rawDistances to Measurement objects with time values
  for (size_t i = 0; i < rawDistances.size(); ++i)
  {
    Measurement m;
    m.distance = rawDistances[i];
    m.time = i * TIME_INTERVAL_NANOSECONDS;
    data.push_back(m);
  }

  std::vector<Measurement> withinThreshold;

  // 2. Filter based on absolute thresholds
  for (const auto &m : data)
  {
    if (m.distance >= TIME_OF_FLIGHT_OUTLIER_START && m.distance <= TIME_OF_FLIGHT_OUTLIER_CUTOFF)
    {
      withinThreshold.push_back(m);
    }
  }

  // If no data left within the threshold, return an empty vector
  if (withinThreshold.empty())
  {
    return {}; // Or return the original `data` vector if desired, or throw an exception.
  }

  // 3. Calculate mean and standard deviation
  double sum = 0;
  for (const auto &m : withinThreshold)
  {
    sum += m.distance;
  }
  double mean = sum / withinThreshold.size();

  double variance = 0;
  for (const auto &m : withinThreshold)
  {
    variance += std::pow(m.distance - mean, 2);
  }
  double standardDeviation = std::sqrt(variance / withinThreshold.size());

  // Handle cases where standard deviation might be too small (e.g., all values are the same)
  if (standardDeviation <= 1e-6) // Using a small tolerance
  {
    std::cout << "Warning: Standard deviation is too small. Skipping Z-score filtering." << std::endl;
    return withinThreshold; // Return the data filtered by thresholds.
  }

  // 4. Calculate the z-score threshold range
  double zScoreLower = mean - ZSCORE_THRESHOLD * standardDeviation;
  double zScoreUpper = mean + ZSCORE_THRESHOLD * standardDeviation;

  // Apply the margin to the z-score threshold range
  zScoreLower -= ZSCORE_MARGIN;
  zScoreUpper += ZSCORE_MARGIN;

  // 5. Filter based on z-score with a margin applied
  std::vector<Measurement> filtered;
  for (const auto &m : withinThreshold)
  {
    if (m.distance >= zScoreLower && m.distance <= zScoreUpper)
    {
      filtered.push_back(m);
    }
  }

  return filtered;
}

// int main()
// {
//   // Sample distance readings (in mm)
//   std::vector<double> rawDistances = {
//       -49.00,
//       2.00,
//       4.00,
//       8.00,
//       13.00,
//       23.00,
//       30.00,
//       143.00,
//       56.00,
//       170.00,
//       36.00,
//       104.00,
//   };
//   // Run the filter
//   std::vector<Measurement> filtered = filterOutliersFromTimeOfFlight(rawDistances);

//   // Display filtered data
//   std::cout << "Filtered Measurements:\n";
//   for (const auto &m : filtered)
//   {
//     std::cout << "Distance: " << m.distance << " mm, Time: " << m.time << " ns\n";
//   }

//   return 0;
// }
