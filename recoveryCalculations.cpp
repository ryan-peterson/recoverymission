#include <math.h>
#include "coordinateCalculations.h"
#include "coordinateTransforms.h"

const double bansheeDescentRate = 5;
const double engineStopTime = 6;
const double startApproach = 5000;
const double runOut = 1000;

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

double getEngineLat(double chuteLat, double bearing, double speed)
{
    double distance = speed*engineStopTime;
    double rBearing = reverseBearing(bearing);
    return latitudeAlongBearing(chuteLat,rBearing,distance);
}

double getEngineLong(double chuteLat, double chuteLong, double bearing, double speed)
{
    double distance = speed*engineStopTime;
    double rBearing = reverseBearing(bearing);
    return longitudeAlongBearing(chuteLat,chuteLong,rBearing,distance);
}

double getApproachLat(double engineLat, double bearing)
{
    double rBearing = reverseBearing(bearing);
    return latitudeAlongBearing(engineLat,rBearing,startApproach);
}

double getApproachLong(double engineLat, double engineLong, double bearing)
{
    double rBearing = reverseBearing(bearing);
    return longitudeAlongBearing(engineLat,engineLong,rBearing,startApproach);
}

double getRunOutLat(double chuteLat, double bearing)
{
    return latitudeAlongBearing(chuteLat,bearing,runOut);
}

double getRunOutLong(double chuteLat, double chutLong, double bearing)
{
    return longitudeAlongBearing(chuteLat,chutLong,bearing,runOut);
}