#include <vector>
#include <numeric>  // For std::accumulate

/** Returns the values of the second derivative of a list of measurments
 * The units of the returned values are mm / ns ^ 2 -> (10^-3 m) / (10^-6 s) ^ 2
 * @example
 * measurments = { { 0, 0 }, { 2.8353, 100005 }, { 11.3502, 200090 }};
 * secondDerivative(measurments) -> { 0.566996 * 10^-9}
 */ 
std::vector<double> secondDerivative(std::vector<measurment> measurements) {
    std::vector <double> result;
  if (measurements.size() < 3){
      return result;
  }
  
  for(size_t i = 1; i < measurements.size() - 1; ++i){
    double f_xh = measurements[i - 1].distance;
    double f_x = measurements[i].distance;
    double f_xmh = measurements[i + 1].distance;
  
    uint64_t t_xh = measurements[i - 1].time;
    uint64_t t_x = measurements[i].time;
    uint64_t t_xmh = measurements[i + 1].time;
  
      
  
      double h_squared = std::pow(static_cast<double>(t_xmh - t_xh) / 2.0, 2);
      double SecondDeriv = (f_xh - 2 * f_x + f_xmh) / h_squared;
      result.push_back(SecondDeriv);
  
  }
  
    return result;
}



/** Returns the mean of the given values */
double average(const std::vector<double>& values) {
    if (values.empty()) return 0.0; // Avoid division by zero
    return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
}

/** Returns the average acceleration (in m/s²) over a period
 * The second derivative function above should be used
 */
double averageAcceleration(const std::vector<measurment>& measurments) {
    std::vector<double> second_derivatives = secondDerivative(measurments);
    double avg_second_derivative = average(second_derivatives);

    // Convert from mm/ns² to m/s²
    // 1 mm = 10^-3 m, 1 ns² = (10^-9 s)² = 10^-18 s²
    // Therefore, mm/ns² = (10^-3 m) / (10^-18 s²) = 10^15 m/s²
    return avg_second_derivative * 1e15;
}

