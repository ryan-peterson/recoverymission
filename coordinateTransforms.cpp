#include <math.h>
#include "coordinateTransforms.h"

float dmsToRad(int degrees, int minutes, float seconds, char direction)
{
    float mm = minutes+(seconds/60); // convert the minutes and seconds to decimal minutes
    float dd = mm/60; // convert the decimal minutes to a fraction of a single degree
    float ddd = degrees+dd; // add the degrees to the fractions of a degree to get decimal degrees
    float rads = convertToRadians(ddd); // convert decimal degrees to radians (however, this will always be positive)

    if (direction == 'W' || direction == 'S') // if the coordinates are W or S, the radians should be negative
    {
        return rads*-1;
    }
    else
    {
        return rads;
    }
}

float convertToRadians(float r)
{
    return r*(M_PI/180);
}