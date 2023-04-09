#include "carInfo.h"

float CarInfo::carLength = 10;
float CarInfo::carHalfLength = 5;

float CarInfo::desiredVelocity = 30;
float CarInfo::minDesiredDistance = 5;

float CarInfo::accelExponent = 4;
float CarInfo::reactionTime = 1.5; //seconds;

float CarInfo::maxAccel = 0.73; //m^2/sec
float CarInfo::comfortDecel = 1.67; //m^2/sec

float CarInfo::slowDownFactor = 1; // alpha < 1
float CarInfo::lockSlowdownLength = 0;
float CarInfo::lockStopLength = 0;