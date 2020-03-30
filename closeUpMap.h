#pragma once

#include <QWidget>
#include "waypoint.h"
#include <QPainter>

class CloseUpMap : public QWidget
{
    Q_OBJECT

    public:
        CloseUpMap(QWidget *parent = 0);
        void passWaypoints(Waypoint approachWP, Waypoint engineWP, Waypoint chuteWP, Waypoint runOutWP);
        void drawMap(QPainter &);
        QPainter qp;
        Waypoint approach;
        Waypoint engine;
        Waypoint chute;
        Waypoint runOut;
        void updateWaypoints(Waypoint approachWP, Waypoint engineWP, Waypoint chuteWP, Waypoint runOutWP);

    protected:
        void paintEvent(QPaintEvent *);
        void drawHitCircle(QPainter &, QPointF lz);
        void drawLZWP(QPainter &, QPointF lz);
        void drawWP(QPainter &, int x, int y);
        void drawFlightPath(QPainter &, QPointF lz);
        void drawScale(QPainter &);
};