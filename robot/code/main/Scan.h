#include "ScanHelpers.h"

/**
 * @brief runCount is referring to which sweep is running
 * there are three: top, middle, bottom
 * the count determines where the robot is pointing (left/right)
 * and this is important to not jump positions and not scan the same place
 * if you were to return to the middle everytime
 * 
 * @param {int} runCount 
 * @param {bool} scan - means no sampling/fast
 */
void sweep(int runCount, bool scan = false, String scanType = "")
{
  bool useSerial = dumpSerial; // true means it goes to monitor for manual copy/paste capture

  if (runCount == 1)
  {
    sampleDepth = true;
    sampleGyroZ = true;
    pivotRight();
    pivotCenterFromRight();
    pivotLeft();
    sampleDepth = false;
    sampleGyroZ = false;
    if (!scanType) dumpData(useSerial, scanType);
  } else if (runCount == 2)
  {
    sampleDepth = true;
    sampleGyroZ = true;
    pivotCenterFromLeft();
    pivotRight();
    sampleDepth = false;
    sampleGyroZ = false;
    if (!scanType) dumpData(useSerial, scanType);
  } else
  {
    if (scan)
    {
      sampleDepth = true;
      sampleGyroZ = true;
    }

    pivotCenterFromRight();
    pivotLeft();
    pivotCenterFromLeft();

    if (scan)
    {
      sampleDepth = false;
      sampleGyroZ = false;
      if (!scanType) dumpData(useSerial, scanType);
    }
  }

  performObstacleCheck(scanType);
}

void performFullScan(bool addDelayBetweenSamples = false)
{
  bool printData = dumpSerial; // to serial monitor
  tiltUp1();
  tiltUp2();
  delay(1000); // wait to stop moving
  sweep(1, true, printData ? "" : "u2"); // second param means no delay

  if (addDelayBetweenSamples)
  {
    delay(10000); // for manual serial dump copy paste into excel
  }

  tiltCenterFromUp2();
  delay(1000); // wait to stop moving
  sweep(2, true, printData ? "" : "u1");

  if (addDelayBetweenSamples)
  {
    delay(10000);
  }

  tiltCenterFromUp1();
  delay(1000); // wait to stop moving
  sweep(3, true, printData ? "" : "m1");

  if (addDelayBetweenSamples)
  {
    delay(10000);
  }

  tiltDown1();
  delay(1000); // wait to stop moving
  sweep(1, true, printData ? "" : "d1");

  if (addDelayBetweenSamples)
  {
    delay(10000);
  }

  tiltDown2();
  delay(1000); // wait to stop moving
  sweep(2, true, printData ? "" : "d2");

  if (addDelayBetweenSamples)
  {
    delay(10000);
  }

  tiltCenterFromDown2();
  tiltCenterFromDown1();
  sweep(3, false);
}