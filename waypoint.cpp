#include "waypoint.h"
#include "recoveryCalculations.h"

Waypoint::Waypoint(double lzLat, double lzLong, double bearing, double windSpeed, double windDir, double lzElev, double recoveryAlt, double recoverySpeed)
{
    airspeed=recoverySpeed;
    height=recoveryAlt;
    landingLat=lzLat;
    landingLong=lzLong;
    approachBearing=bearing;
    wspeed=windSpeed;
    wdir=windDir;
    landingElev=lzElev;
}

void Waypoint::setChuteWP()
{
    wpLat = getParachuteLat(landingLat,landingElev,height,wspeed,wdir);
    wpLong = getParachuteLong(landingLat,landingLong,landingElev,height,wspeed,wdir);
}

void Waypoint::setEngineWP(double chuteLat, double chuteLong)
{
    wpLat = getEngineLat(chuteLat,approachBearing,airspeed);
    wpLong = getEngineLong(chuteLat,chuteLong,approachBearing,airspeed);
}

void Waypoint::setApproachWP(double engineLat, double engineLong)
{
    wpLat = getApproachLat(engineLat,approachBearing);
    wpLong = getApproachLong(engineLat,engineLong,approachBearing);
}

void Waypoint::setRunOutWP(double chuteLat, double chuteLong)
{
    wpLat = getRunOutLat(chuteLat,approachBearing);
    wpLong = getRunOutLong(chuteLat,chuteLong,approachBearing);
}

double Waypoint::getWpLat()
{
    return wpLat;
}

double Waypoint::getWpLong()
{
    return wpLong;
}

double Waypoint::getAirspeed()
{
    return airspeed;
}

double Waypoint::getHeight()
{
    return height;
}