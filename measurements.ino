#include <vector>

std::vector<measurment> leftMeasurements;
std::vector<measurment> rightMeasurements;

std::vector<measurment> *getLeftMeasurements
{
  return leftMeasurements;
}

std::vector<measurment> *getLeftMeasurements
{
  return rightMeasurements;
}

void addLeftMeas(double distance, uint64_t time)
{
  leftMeasurements.push_back({distance, time});
}

void addRightMeas(double distance, uint64_t time)
{
  rightMeasurements.push_back({distance, time});
}

void clearBothMeas()
{
  leftMeasurements.clear();
  rightMeasurements.clear();
}
