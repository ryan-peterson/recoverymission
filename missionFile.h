#pragma once

#include "waypoint.h"
#include <QTextStream>
#include <QFile>
#include <QString>

void outputMission(QString fileName, Waypoint approach, Waypoint engine, Waypoint chute, Waypoint runOut);