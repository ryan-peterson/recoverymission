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