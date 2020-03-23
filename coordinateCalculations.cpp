#include <math.h>
#include "coordinateCalculations.h"

const double rEarth = 6371000;

double latitudeAlongBearing(double startLat, double bearing, double distance)
{
    double angularDistance = distance/rEarth;
    double endLat = asin((sin(startLat)*cos(angularDistance))+(cos(startLat)*sin(angularDistance)*cos(bearing)));
    return endLat;
}

double longitudeAlongBearing(double startLat, double startLong, double bearing, double distance)
{
    double angularDistance = distance/rEarth;
    double endLat = latitudeAlongBearing(startLat, bearing, distance);
    double endLong = startLong+(atan2((sin(bearing)*sin(angularDistance)*cos(startLat)),(cos(angularDistance)-(sin(startLat)*sin(endLat)))));
    return endLong;
}

double calcBearing(double startLat, double startLong, double endLat, double endLong)
{
    double deltaLong = endLong-startLong;
    return atan2((sin(deltaLong)*cos(endLat)),((cos(startLat)*sin(endLat))-(sin(startLat)*cos(endLat)*cos(deltaLong))));
}

double calcDistance(double startLat, double startLong, double endLat, double endLong)
{
    double a, c, deltaLat, deltaLong;
    deltaLat = startLat-endLat;
    deltaLong = startLong-endLong;
    a = pow(sin(deltaLat/2),2)+(cos(startLat)*cos(endLat)*(pow(sin(deltaLong/2),2)));
    c = 2*atan2(sqrt(a),sqrt(1-a));
    return c*rEarth;
}

int calcEwOffset(double startLat, double endLat, double startLong, double endLong)
{
    double bearing = calcBearing(startLat,startLong,endLat,endLong);
    double distance = calcDistance(startLat,startLong,endLat,endLong);
    if (bearing==0||bearing==M_PI||bearing==M_PI*-1)
    {
       return 0;
    }
    else if(bearing==M_PI/2)
    {
       return distance;
    }
    else if(bearing==M_PI/-2)
    {
       return distance*-1;
    }
    else
    {
       return sin(bearing)*distance;
    }
}

int calcNwOffset(double startLat, double endLat, double startLong, double endLong)
{
    double bearing = calcBearing(startLat,startLong,endLat,endLong);
    double distance = calcDistance(startLat,startLong,endLat,endLong);
    if (bearing==0)
    {
       return distance;
    }
    else if (bearing==M_PI||bearing==M_PI*-1)
    {
        return distance*-1;
    }
    else if(bearing==M_PI/2||bearing==M_PI/-2)
    {
       return 0;
    }
    else
    {
       return cos(bearing)*distance;
    }
}