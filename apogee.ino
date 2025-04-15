/**
 * Functions and constants related to checking if the device is currently in apogee
 */

/**
 * Threshold for the IMU to consider the device starting apogee
 */
const double STARTING_IMU_THRESH = 0.20;

/**
 * Threshold for the IMU to consider the device starting apogee
 */
const double STARTING_ACC_THRESH = 2 * 9.8;

/**
 * Time in microseconds to run the device once
 * in apogee
 */
const uint64_t TIME_TO_RUN_DEVICE = 45e+7;

/**
 * Is the IMU in apogee
 *
 * Returns true of the value from the z value from the IMU
 * is between +- the IMU_Z_THRESH
 */
bool isIMUApogee()
{
  float totalAccMag = getIMUAccelerationMagnitude();

  return totalAccMag > STARTING_IMU_THRESH;
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
  Serial.println(totalAccMag);
  Serial.println("isaccelappoge");

  return totalAccMag <= STARTING_ACC_THRESH;
}

bool isInApogee()
{
  static uint64_t start_time = -1;


  // Apogee has not started
  if (start_time == -1) {
    delay(10);
    if (isAcceloAppoge() && true) {
      start_time = micros();
      return true;
    } else {
      return false;
    }
  } else {
    if ((micros() - start_time) >= TIME_TO_RUN_DEVICE) {
      return false;
    } else {
      return true;
    }
  }

  return isAcceloAppoge() && true;
}
