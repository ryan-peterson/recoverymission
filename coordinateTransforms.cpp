#include <math.h>
#include <iostream>
#include <stdio.h>
#include "coordinateTransforms.h"

double dmsToDdd(int degrees, int minutes, double seconds)
{
    double mm = minutes+(seconds/60.0); // convert the minutes and seconds to decimal minutes
    double dd = mm/60.0; // convert the decimal minutes to a fraction of a single degree
    double ddd = degrees+dd; // add the degrees to the fractions of a degree to get decimal degrees
    return ddd;
}

double convertToRadians(double d) // input is in decimal degrees
{
    return d*(M_PI/180.0);
}

double convertToDegrees(double r) // input is in radians
{
    return r/(M_PI/180.0);
}

double convertTo360Degrees(double r)
{
    if ((r/(M_PI/180.0))>=0)
        return r/(M_PI/180.0);
    else
        return (r/(M_PI/180.0))+360;
}

double dmmToDdd(int degrees, double minutes) // returns decimal degrees from a degree and decimal minute input
{
    double dd = minutes/60.0;
    double ddd = degrees+dd;
    return ddd;
}

double getDecimalMinutes(double ddd) // returns the decimal minute part of a decimal degree
{
    double fractpart, intpart;
    fractpart = std::modf(ddd, &intpart);
    return abs(fractpart)*60;
}

double getDecimalSeconds(double ddd) // returns the decimal second part of a decimal degree
{
    double fractpart, intpart;
    double decimalMinutes = getDecimalMinutes(ddd);
    fractpart = std::modf(decimalMinutes, &intpart);
    return abs(fractpart)*60;
}

double getMinutes(double ddd) // returns the integer minute from a decimal degree
{
    double fractpart, intpart;
    double decimalMinutes = getDecimalMinutes(ddd);
    fractpart = std::modf(decimalMinutes, &intpart);
    return abs(intpart);
}

double getDegrees(double ddd) // returns the integer degree from a decimal degree
{
    double fractpart, intpart;
    fractpart = std::modf(ddd, &intpart);
    return intpart;
}

double reverseBearing(double bearing) // returns a bearing 180 degrees from the input bearing
{
    if (bearing==0)
    {
        return M_PI;
    }
    else if (bearing==M_PI)
    {
        return 0;
    }
    else if (bearing<0)
    {
        return bearing+M_PI;
    }
    else
    {
        return bearing-M_PI;
    }
}