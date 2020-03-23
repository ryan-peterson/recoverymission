#include <QPainter>
#include "recoveryMap.h"
#include "waypoint.h"

RecoveryMap::RecoveryMap(QWidget *parent) : QWidget(parent)
{
    
}

void RecoveryMap::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter qp(this);
    drawMap(qp);
}

void RecoveryMap::drawMap(QPainter &qp)
{
    qp.setPen(QColor("#228071"));
    qp.setBrush(QColor("#228071"));
    qp.drawRect(0,0,500,500);
    drawHitCircle(qp);
}

void RecoveryMap::drawHitCircle(QPainter &qp)
{
    qp.setPen(Qt::white);
    qp.drawEllipse(225,375,50,50);
}

void RecoveryMap::passWaypoints(Waypoint approachWP, Waypoint engineWP, Waypoint chuteWP, Waypoint runOutWP)
{
    approach=approachWP;
    engine=engineWP;
    chute=chuteWP;
    runOut=runOutWP;
}