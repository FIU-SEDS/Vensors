/**
 * Setup the oscillation algorithm
 *
 * Setup any necessary pins, variables, and push the carrige all the way to the left side before starting
 * the osc loop code
 *
 * Returns 0 on success, -1 on failure
 */
int oscSetup()
{
  return 0;
}

/**
 * Loop the oscillation algorithm
 *
 * Starting from the left
 * Push the carrige to the right until `bool isInCenter(int leftSensorReading, int rightSensorReading)` returns true
 *
 * The carrige is now right of the center
 * Push the carrige to the left until `bool isInCenter(int leftSensorReading, int rightSensorReading)` returns true
 *
 * The carrige is now left of the center
 * Push the carrige to the right until `bool isInCenter(int leftSensorReading, int rightSensorReading)` returns true
 *
 * Repeat indefinefly
 *
 *
 * A full oscillation is considered to be when the carrige, starting from the left of the center
 * Moves to the right of the sensor, and then returns back to the left of the sensor
 *
 * Durring a full oscillation the values should be recorded in a measurements list
 * using the functions from the `measurements.ino` file
 *
 */
void oscLoop()
{
  // Implement your oscillation logic here
}
