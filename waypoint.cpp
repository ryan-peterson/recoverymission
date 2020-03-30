#include "waypoint.h"
#include "recoveryCalculations.h"
#include "coordinateCalculations.h"

Waypoint::Waypoint()
{
    
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

void Waypoint::setRecSpeed(double recSpeed)
{
    airspeed=recSpeed;
}

void Waypoint::setLzLat(double lzLat)
{
    landingLat=lzLat;
}

void Waypoint::setLzLong(double lzLong)
{
    landingLong=lzLong;
}

void Waypoint::setLzElev(double lzElev)
{
    landingElev=lzElev;
}

void Waypoint::setBearing(double bearing)
{
    approachBearing=bearing;
}

void Waypoint::setRecAlt(double recAlt)
{
    height=recAlt;
}

void Waypoint::setWindDir(double windDir)
{
    wdir=windDir;
}

void Waypoint::setWindSpeed(double windSpeed)
{
    wspeed=windSpeed;
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

int Waypoint::getDrift()
{
    int fall = height-landingElev;
    int hangTime = fall/5;
    int drift = hangTime*wspeed;
    return drift;
}

double Waypoint::getLzLat()
{
    return landingLat;
}

double Waypoint::getLzLong()
{
    return landingLong;
}

double Waypoint::getBearing()
{
    return approachBearing;
}

double Waypoint::getLzElev()
{
    return landingElev;
}

double Waypoint::getWindSpeed()
{
    return wspeed;
}

double Waypoint::getWindDir()
{
    return wdir;
}