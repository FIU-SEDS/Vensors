/**
 * Functions and constants related to checking if the device is currently in apogee
 */

/** Threshold around the value zero for the IMU acliremote to consider the
 * device in apogee
 */
const double IMU_Z_THRESH = 0.05;

/** Threshold around the value zero for the Accelerometer acliremote to consider the
 * device in apogee
 */
const double ACCELO_Z_THRESH = 0.05;

/**
 * Is the IMU in apogee
 *
 * Returns true of the value from the z value from the IMU
 * is between +- the IMU_Z_THRESH
 */
bool isIMUApogee()
{
  return false;
}

/**
 * Is the accelerometer in apogee
 *
 * Returns true of the value from the z value from the accelerometer
 * is between +- the ACCELO_Z_THRESH
 */
bool isAcceloAppoge()
{
  return false;
}

bool isInApogee()
{
  return isInApogee() && isAcceloAppoge();
}
