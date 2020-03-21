#include <math.h>
#include "coordinateCalculations.h"

const double bansheeDescentRate = 5;
const double engineStopTime = 6;

double getParachuteLat(double lzLat, double lzElev, double recoveryAlt, double windSpeed, double windDir)
{
    double fallDistance = recoveryAlt-lzElev;
    double hangTime = fallDistance/bansheeDescentRate;
    double drift = hangTime*windSpeed;
    return latitudeAlongBearing(lzLat,windDir,drift);
}

double getParachuteLong(double lzLat, double lzLong, double lzElev, double recoveryAlt, double windSpeed, double windDir)
{
    double fallDistance = recoveryAlt-lzElev;
    double hangTime = fallDistance/bansheeDescentRate;
    double drift = hangTime*windSpeed;
    return longitudeAlongBearing(lzLat,lzLong,windDir,drift);
}