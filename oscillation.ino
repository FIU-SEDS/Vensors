/**
 * Setup the oscillation algorithm
 *
 * Setup any necessary pins, variables, and push the carrige all the way to the
 * left side before starting the osc loop code
 *
 * Returns 0 on success, -1 on failure
 */
int oscSetup() {}

bool goingLeft = true;
bool firstOscillation = true;

/**
 * Loop the oscillation algorithm
 *
 * Check if the z acceleration is above the threshold value
 *
 * Starting from the left
 * Push the carrige to the right until `bool isInCenter(int leftSensorReading,
 * int rightSensorReading)` returns true
 *
 * The carrige is now right of the center
 * Push the carrige to the left until `bool isInCenter(int leftSensorReading,
 * int rightSensorReading)` returns true
 *
 * The carrige is now left of the center
 * Push the carrige to the right until `bool isInCenter(int leftSensorReading,
 * int rightSensorReading)` returns true
 *
 * Repeat indefinefly
 *
 *
 * A full oscillation is considered to be when the carrige, starting from the
 * left of the center Moves to the right of the sensor, and then returns back to
 * the left of the sensor
 *
 * Durring a full oscillation the values should be recorded in a measurements
 * list using the functions from the `measurements.ino` file
 *
 * Before clearing calculate the acceleration from the given arrays
 * Using the getLeftAvg, and getRightAvg functions
 *
 */
void oscLoop() {
  delay(50);
  if (firstOscillation) {
    Serial.println("Starting oscillation loop");
    oscInitalSetup();
  }

  int leftDist = recordLeftMeas();
  int rightDist = recordRightMeas();

  Serial.print("L:");
  Serial.print(leftDist);
  Serial.print("R:");
  Serial.print(rightDist);
  Serial.println();

  if (crossedCenter(leftDist, rightDist, goingLeft)) {
    goingLeft = !goingLeft;
    Serial.println("Crossed center");

    if (!firstOscillation) {
      calculateMass();
    }

    if (firstOscillation) {
      firstOscillation = !firstOscillation;
    }

    return;
  }

  if (goingLeft) {
    leftFacingForce(20);
  } else {
    rightFacingForce(20);
  }
}

void oscInitalSetup() {
  // Bring the carrige to the left side
  leftFacingForce(100);
  delay(500);

  firstOscillation = false;
}

bool isNotInRange(int number, int lowerBound, int upperBound) {
  // Check if the number is outside the specified range (inclusive of bounds)
  return (number < lowerBound) || (number > upperBound);
}

bool crossedCenter(int left, int right, bool goingLeft) {
  static bool canCheck = false;

  if (isNotInRange(left, 40, 60) && isNotInRange(right, 40, 60)) {
    canCheck = true;
  }

  if (!canCheck)
    return false;

  if (goingLeft) {
    bool crossed = std::abs(right - left) > 4 * 2;
    if (crossed) {
      canCheck = false;
    }

    return crossed;
  } else {
    bool crossed = std::abs(left - right) > 4 * 2;
    if (crossed) {
      canCheck = false;
    }

    return crossed;
  }
}
