#pragma once

#include <QWidget>
#include <QLineEdit>
#include "waypoint.h"

class ParameterInputs : public QWidget
{
    Q_OBJECT

    public:
        ParameterInputs(int panelType, QWidget *parent = 0);
        Waypoint approachWP;
        Waypoint engineWP;
        Waypoint chuteWP;
        Waypoint runOutWP;
        Waypoint getApproachWP();
        Waypoint getEngineWP();
        Waypoint getChuteWP();
        Waypoint getRunOutWP();
        QString getFilePreview();

    private slots:
        void updateLzLat(QString input);
        void updateLzLatDegDMM(QString input);
        void updateLzLatMinDMM(QString input);
        void updateLzLatDegDMS(QString input);
        void updateLzLatMinDMS(QString input);
        void updateLzLatSecDMS(QString input);
        void updateLzLong(QString input);
        void updateLzLongDegDMM(QString input);
        void updateLzLongMinDMM(QString input);
        void updateLzLongDegDMS(QString input);
        void updateLzLongMinDMS(QString input);
        void updateLzLongSecDMS(QString input);
        void updateLzElev(QString input);
        void updateBearing(QString input);
        void updateRecAlt(QString input);
        void updateRecSpeed(QString input);
        void updateWindDir(QString input);
        void updateWindSpeed(QString input);
        void updateWPs();

    private:
        double lzLat;
        double lzLatDeg;
        double lzLatMin;
        double lzLatSec;
        double lzLong;
        double lzLongDeg;
        double lzLongMin;
        double lzLongSec;
        double lzElev;
        double bearing;
        double recAlt;
        double recSpeed;
        double windDir;
        double windSpeed;
};