#include "carInfo.h"

float CarInfo::carLength = 10;
float CarInfo::carHalfLength = 5;

float CarInfo::desiredVelocity = 30;
float CarInfo::minDesiredDistance = 5;

float CarInfo::accelExponent = 4;
float CarInfo::reactionTime = 1.5; //seconds;

float CarInfo::maxAccel = 0.73; //m^2/sec
float CarInfo::comfortDecel = 1.67; //m^2/sec

//need HEAVY REVISION later
float CarInfo::slowDownFactor = 0.9; // alpha < 1
float CarInfo::lockSlowdownLength = 50; //not working as much as acceleration isn't being updated
float CarInfo::lockStopLength = 50; //working