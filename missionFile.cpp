#include <QFile>
#include <QTextStream>
#include "waypoint.h"

void outputMission(Waypoint chute, Waypoint engine, Waypoint approach, Waypoint runOut)
{
    QFile data("recovery");

    if (data.open(QFile::WriteOnly))
    {
        QTextStream out(&data);
        out << qSetRealNumberPrecision(10);
        out << "refLatitude " << "0" << endl;
        out << "refLongitude " << "0" << endl;
        out << "$" << endl;
        out << "airspeed " << approach.getAirspeed() << endl;
        out << "altitude " << approach.getHeight() << endl;
        out << "eastOffset " << approach.getWpLong() << endl;
        out << "northOffset " << approach.getWpLat() << endl;
        out << "$" << endl;
        out << "airspeed " << engine.getAirspeed() << endl;
        out << "altitude " << engine.getHeight() << endl;
        out << "eastOffset " << engine.getWpLong() << endl;
        out << "northOffset " << engine.getWpLat() << endl;
        out << "$" << endl;
        out << "airspeed " << chute.getAirspeed() << endl;
        out << "altitude " << chute.getHeight() << endl;
        out << "eastOffset " << chute.getWpLong() << endl;
        out << "northOffset " << chute.getWpLat() << endl;
        out << "$" << endl;
        out << "airspeed " << runOut.getAirspeed() << endl;
        out << "altitude " << runOut.getHeight() << endl;
        out << "eastOffset " << runOut.getWpLong() << endl;
        out << "northOffset " << runOut.getWpLat() << endl;
        out << "$" << endl;
    }
}