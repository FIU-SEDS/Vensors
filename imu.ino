#include <Adafruit_MPU6050.h>

#define IMU_ACC_RANGE MPU6050_RANGE_8_G
#define IMU_GYRO_RANGE MPU6050_RANGE_500_DEG
#define IMU_REFRESH_RATE MPU6050_BAND_21_HZ


Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

int imuXSensorIndex = 0;
const float imuXSensorData[] = {

};

int imuYSensorIndex = 0;
const float imuYSensorData[] = {

};
int imuZSensorIndex = 0;
const float imuZSensorData[] = {

};
const int imuSize = sizeof(imuXSensorData) / sizeof(imuXSensorData[0]);

void updateIMU() {
  mpu.getEvent(&a, &g, &temp);
}

/**
 *  Returns the acceleration from the IMU in the X direction.
 */
double getIMUXAcc()
{
  // return a.acceleration.x; // Preserve precision
  return XSensorData[(XSensorIndex++) % Size]
}

/**
 * Returns the acceleration from the IMU in the Y direction.
 */
double getIMUYAcc()
{
  // return a.acceleration.y * 100;
  return imuYSensorData[(imuYSensorIndex++) % imuSize]
}

/**
 * Returns the acceleration from the IMU in the Z direction.
 */
double getIMUZAcc()
{
  // return a.acceleration.z;
  return imuZSensorData[(imuZSensorIndex++) % imuSize]
}

/**
 * Returns the gyroscope value from the IMU in the X direction.
 */
double getIMUXGyro()
{
  return g.gyro.x;
}

/**
 * Returns the gyroscope value from the IMU in the Y direction.
 */
double getIMUYGyro()
{
  return g.gyro.y;
}

/**
 * Returns the gyroscope value from the IMU in the Z direction.
 */
double getIMUZGyro()
{
  return g.gyro.z;
}

/**
 * Returns the temperature from the IMU in Celsius.
 */
double getIMUZTemp()
{
  return temp.temperature;
}

/**
 * Initalized the IMU and returns a 0 value if successfull.
 * @return 0 on success, non-zero otherwise.
 */
int setupIMU()
{
  if (!mpu.begin()) return -1;

  mpu.setAccelerometerRange(IMU_ACC_RANGE);
  mpu.setGyroRange(IMU_GYRO_RANGE);
  mpu.setFilterBandwidth(IMU_REFRESH_RATE);

  return 0;
}

/**
 * Calculates the magnitude of the acceleration vector.
 *
 * @return The magnitude of the acceleration vector.
 */
float getIMUAccelerationMagnitude()
{
  int x = getIMUXAcc();
  int y = getIMUYAcc();
  int z = getIMUZAcc();

  // Calculate the magnitude using the Pythagorean theorem: sqrt(x^2 + y^2 + z^2)
  return sqrt(x * x + y * y + z * z);
}
