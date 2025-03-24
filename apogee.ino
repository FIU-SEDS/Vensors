/**
 * Functions and constants related to checking if the device is currently in apogee
 */
const double STARTING_IMU_THRESH = 0.20;

/** Threshold around the value zero for the IMU acliremote to consider the
 * device in apogee
 */
const double ENDING_IMU_THRESH = -0.5;

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
  updateAcc();

  float totalAccMag = getAccelerationMagnitude();

  return totalAccMag < STARTING_IMU_THRESH && totalAccMag > ENDING_IMU_THRESH;
}

bool isInApogee()
{
  return isAcceloAppoge();
}
