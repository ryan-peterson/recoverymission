#pragma once

#include <QWidget>
#include "waypoint.h"

class RecoveryMap : public QWidget
{
    Q_OBJECT

    public:
        RecoveryMap(QWidget *parent = 0);
        void passWaypoints(Waypoint approachWP, Waypoint engineWP, Waypoint chuteWP, Waypoint runOutWP);

    protected:
        void paintEvent(QPaintEvent *);
        void drawMap(QPainter &);
        void drawHitCircle(QPainter &);

    private:
        Waypoint approach;
        Waypoint engine;
        Waypoint chute;
        Waypoint runOut;
};