#include "waypoint.h"
#include "recoveryCalculations.h"
#include "coordinateCalculations.h"

Waypoint::Waypoint()
{
    airspeed=0;
    height=0;
    landingLat=0;
    landingLong=0;
    approachBearing=0;
    wspeed=0;
    wdir=0;
    landingElev=0;
}

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
    ewOffset = calcEwOffset(landingLat,wpLat,landingLong,wpLong);
    nsOffset = calcNwOffset(landingLat,wpLat,landingLong,wpLong);
}

void Waypoint::setEngineWP(double chuteLat, double chuteLong)
{
    wpLat = getEngineLat(chuteLat,approachBearing,airspeed);
    wpLong = getEngineLong(chuteLat,chuteLong,approachBearing,airspeed);
    ewOffset = calcEwOffset(landingLat,wpLat,landingLong,wpLong);
    nsOffset = calcNwOffset(landingLat,wpLat,landingLong,wpLong);
}

void Waypoint::setApproachWP(double engineLat, double engineLong)
{
    wpLat = getApproachLat(engineLat,approachBearing);
    wpLong = getApproachLong(engineLat,engineLong,approachBearing);
    ewOffset = calcEwOffset(landingLat,wpLat,landingLong,wpLong);
    nsOffset = calcNwOffset(landingLat,wpLat,landingLong,wpLong);
}

void Waypoint::setRunOutWP(double chuteLat, double chuteLong)
{
    wpLat = getRunOutLat(chuteLat,approachBearing);
    wpLong = getRunOutLong(chuteLat,chuteLong,approachBearing);
    ewOffset = calcEwOffset(landingLat,wpLat,landingLong,wpLong);
    nsOffset = calcNwOffset(landingLat,wpLat,landingLong,wpLong);
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

int Waypoint::getEwOffset()
{
    return ewOffset;
}

int Waypoint::getNsOffset()
{
    return nsOffset;
}

double Waypoint::getLzLat()
{
    return landingLat;
}

double Waypoint::getLzLong()
{
    return landingLong;
}