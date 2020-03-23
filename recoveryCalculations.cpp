#include <math.h>
#include "coordinateCalculations.h"

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
    double reverseBearing;
    if (bearing>=M_PI)
    {
        reverseBearing=bearing-M_PI;
    }
    else 
    {
        reverseBearing=bearing+M_PI;
    }
    return latitudeAlongBearing(chuteLat,reverseBearing,distance);
}

double getEngineLong(double chuteLat, double chuteLong, double bearing, double speed)
{
    double distance = speed*engineStopTime;
    double reverseBearing;
    if (bearing>=M_PI)
    {
        reverseBearing=bearing-M_PI;
    }
    else 
    {
        reverseBearing=bearing+M_PI;
    }
    return longitudeAlongBearing(chuteLat,chuteLong,reverseBearing,distance);
}

double getApproachLat(double engineLat, double bearing)
{
    double reverseBearing;
    if (bearing>=M_PI)
    {
        reverseBearing=bearing-M_PI;
    }
    else 
    {
        reverseBearing=bearing+M_PI;
    }
    return latitudeAlongBearing(engineLat,reverseBearing,startApproach);
}

double getApproachLong(double engineLat, double engineLong, double bearing)
{
    double reverseBearing;
    if (bearing>=M_PI)
    {
        reverseBearing=bearing-M_PI;
    }
    else 
    {
        reverseBearing=bearing+M_PI;
    }
    return longitudeAlongBearing(engineLat,engineLong,reverseBearing,startApproach);
}

double getRunOutLat(double chuteLat, double bearing)
{
    return latitudeAlongBearing(chuteLat,bearing,runOut);
}

double getRunOutLong(double chuteLat, double chutLong, double bearing)
{
    return longitudeAlongBearing(chuteLat,chutLong,bearing,runOut);
}