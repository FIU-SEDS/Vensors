#ifndef DEBUG // prevent multiple inclusions.
#define DEBUG
#endif

struct Measurement
{
  /** Distance in mm from the sensor */
  double distance;

  /** Time in Nano seconds since the microcontroller started */
  uint64_t time;
};
