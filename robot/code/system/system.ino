/**
 * top view of robot and servo names
 * FLO = front-left-outer
 * 
 *    FLO                          FRO
 *         FLM                 FRM
 *              FLI  TOF  FRI
 *                    ^
 *                    y
 * 
 *                   (z)  x >
 *                   IMU
 *
 * 
 *
 *              BLI       BRI
 *         BLM                 BRM
 *    BLO                           BRO
 */

#include "BlueLed.h"
#include "ToFSensor.h"
#include "IMU.h"
#include "ServoMovements.h"
#include "Misc.h"
#include "EspSerial.h"
#include "WorldNavigation.h"
#include "Orientation.h"

void setup()
{
  Serial.begin(115200);
  Serial.println(getBatteryVoltage());
  setupBlueLed();
  setAndCenterServos();
  setupEspSerial();
  setupTof();
  setupImu();

  delay(3000);
  // moveForward4();
}

void loop()
{
  // moveForward3();
  // moveForward4();
}