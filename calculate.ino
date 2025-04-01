#include <lib/Eigen/Dense>
#include "Arduino.h"
#include <vector>
#include <numeric> // For std::accumulate

/**
 * Values in the threshold of +- the following value
 * are ignored and are treated as having no change
 *
 * Effectively if if a value changes by this value or less
 * in a time step the change is ignored
 *
 * Increasing this value helps reduce the noise from the mass measuring algorithm
 * by may lead to small values of acceleration being ignored
 */
const int NOISE_THRESHOLD = 3;

/** Returns the the found 'a' in the equation ax^2 + bx + c which fits the line made
 * by the measurements
 *
 * @see https://en.wikipedia.org/wiki/Curve_fitting
 * Replicates the numpy.polyfit method -> https://numpy.org/doc/stable/reference/generated/numpy.polyfit.html
 */
double findAccelerationFit(const std::vector<measurment> &measurements) {
    Eigen::MatrixXd A(measurements.size(), degree + 1);
    for (size_t i = 0; i < measurements.size(); ++i) {
        for (int j = 0; j <= degree; ++j) {
            A(i, j) = pow(measurements.time, j); // Now includes x^2 term
        }
    }

    // Convert y to an Eigen Vector
    Eigen::VectorXd b(measurements.size());
    for (size_t i = 0; i < measurements.size(); ++i) {
        b(i) = measurements.distance;
    }

    // Solve the Least Squares Problem (Recommended method: QR Decomposition)
    Eigen::VectorXd coefficients = A.colPivHouseholderQr().solve(b);

    double last_coeff = coefficients(2);
    return last_coeff
}

/** Returns the average acceleration (in m/s²) over a period
 * The second derivative function above should be used
 */
double averageAcceleration(const std::vector<measurment> &measurements)
{
    double second_deriv = findAccelerationFit(measurements);

    // Convert from mm/ns² to m/s²
    // 1 mm = 10^-3 m, 1 ns² = (10^-9 s)² = 10^-18 s²
    // Therefore, mm/ns² = (10^-3 m) / (10^-18 s²) = 10^15 m/s²
    return second_deriv * 2 * 1e15;
}
