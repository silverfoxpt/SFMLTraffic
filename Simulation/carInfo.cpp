#include "carInfo.h"

float CarInfo::carLength = 10;
float CarInfo::carHalfLength = 5;

//16.6m/s == 60km/h
float CarInfo::desiredVelocity = 33.2; // m/s 
float CarInfo::minDesiredDistance = 7;

float CarInfo::safetyInputJammedRoad = 20;

float CarInfo::accelExponent = 4;
float CarInfo::reactionTime = 1.5; //seconds;

float CarInfo::maxAccel = 1.44; //m^2/sec
float CarInfo::comfortDecel = 4.61; //m^2/sec

//need HEAVY REVISION later
//UPDATE: VERY, VERY HEAVY REVISION
float CarInfo::slowDownFactor = 0.99; // alpha < 1
float CarInfo::lockSlowdownLength = 0; //not working as much as acceleration isn't being updated, almost fixed... -> MKR NOT WORKING 
float CarInfo::lockStopLength = 50; //working