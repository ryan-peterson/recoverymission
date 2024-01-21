#include <QFile>
#include <QTextStream>
#include <QString>
#include "waypoint.h"

void outputMission(QString fileName, Waypoint approach, Waypoint engine, Waypoint chute, Waypoint runOut)
{
    QFile data(fileName);

    if (data.open(QFile::WriteOnly))
    {
        QTextStream out(&data);
        out << qSetRealNumberPrecision(10);
        out << "waypointCount 4" << endl;
        out << "refLatitude " << chute.getLzLat() << endl;
        out << "refLongitude " << chute.getLzLong() << endl;
        out << "$" << endl;
        out << "airspeed " << approach.getAirspeed() << endl;
        out << "altitude " << approach.getHeight() << endl;
        out << "eastOffset " << approach.getEwOffset() << endl;
        out << "northOffset " << approach.getNsOffset() << endl;
        out << "$" << endl;
        out << "airspeed " << engine.getAirspeed() << endl;
        out << "altitude " << engine.getHeight() << endl;
        out << "eastOffset " << engine.getEwOffset() << endl;
        out << "northOffset " << engine.getNsOffset() << endl;
        out << "$" << endl;
        out << "airspeed " << chute.getAirspeed() << endl;
        out << "altitude " << chute.getHeight() << endl;
        out << "eastOffset " << chute.getEwOffset() << endl;
        out << "northOffset " << chute.getNsOffset() << endl;
        out << "$" << endl;
        out << "airspeed " << runOut.getAirspeed() << endl;
        out << "altitude " << runOut.getHeight() << endl;
        out << "eastOffset " << runOut.getEwOffset() << endl;
        out << "northOffset " << runOut.getNsOffset() << endl;
        out << "$" << endl;
    }
}
