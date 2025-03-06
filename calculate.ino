#include <vector>

// Some randomly generated calculations for testing
std::vector<measurment> testingLeftMeasurments = {
  { 0, 0 },
  { 2.8353, 100005 },
  { 11.3502, 200090 },
  { 25.525, 300058 },
  { 45.3847, 400108 },
  { 70.8892, 500050 },
  { 102.056, 599987 },
  { 138.917, 700005 },
  { 181.487, 800103 },
  { 229.738, 900201 },
  { 283.572, 1000127 },
  { 343.147, 1100179 },
  { 408.348, 1200158 },
  { 479.196, 1300110 },
  { 555.738, 1400097 },
  { 637.937, 1500072 },
};

std::vector<measurment> testingRightMeasurments = {
  { 0, 0 },
  { 2.82728, 99863 },
  { 11.3209, 199831 },
  { 25.4909, 299858 },
  { 45.3103, 399780 },
  { 70.7768, 499653 },
  { 101.887, 599492 },
  { 138.699, 699455 },
  { 181.203, 799477 },
  { 229.308, 899358 },
  { 283.131, 999349 },
  { 342.574, 1099260 },
  { 407.744, 1199271 },
  { 478.471, 1299125 },
  { 555.023, 1399197 },
  { 637.131, 1499125 },
};

/** Returns the values of the second derivative of a list of measurments
 * The units of the returned values are mm / ns ^ 2 -> (10^-3 m) / (10^-6 s) ^ 2
 * @example
 * measurments = { { 0, 0 }, { 2.8353, 100005 }, { 11.3502, 200090 }};
 * secondDerivative(measurments) -> { 0.566996 * 10^-9}
 */ 
std::vector<double> secondDerivative(std::vector<measurment> measurments) {
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

/** Returns the mean of the given values
 */
double average(std::vector<double> values) {

}

/** Returns the average accleeration (in m/s^2) over a period 
 * The second derivative funcion above should be used
 */
double averageAcceleration(std::vector<measurment> measurments) {

}
