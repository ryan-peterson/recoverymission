#include <iostream>
#include <QPainter>
#include <math.h>
#include "closeUpMap.h"
#include "waypoint.h"
#include "coordinateTransforms.h"

int smallScaling=6;

CloseUpMap::CloseUpMap(QWidget *parent) : QWidget(parent)
{
    
}

void CloseUpMap::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter qp(this);
    qp.setRenderHint(QPainter::Antialiasing); // enabling this line makes graphics look smoother, but fuzzier and less accurate
    drawMap(qp);
}

void CloseUpMap::drawMap(QPainter &qp)
{
    qp.setPen(QColor("#000000"));
    qp.setBrush(QColor("#008080"));
    qp.drawRect(0,0,200,200);
    QPointF lz;
    lz.setX(100);
    lz.setY(100);
    drawHitCircle(qp,lz);
    drawFlightPath(qp,lz);
    drawWP(qp,lz.x()+(approach.getEwOffset()/smallScaling),lz.y()-(approach.getNsOffset()/smallScaling));
    drawWP(qp,lz.x()+(engine.getEwOffset()/smallScaling),lz.y()-(engine.getNsOffset()/smallScaling));
    drawWP(qp,lz.x()+(chute.getEwOffset()/smallScaling),lz.y()-(chute.getNsOffset()/smallScaling));
    drawWP(qp,lz.x()+(runOut.getEwOffset()/smallScaling),lz.y()-(runOut.getNsOffset()/smallScaling));
    drawScale(qp);
}

void CloseUpMap::drawHitCircle(QPainter &qp, QPointF lz)
{
    int drift = chute.getDrift();
    qp.setPen(Qt::white);
    qp.drawEllipse(lz,drift/smallScaling,drift/smallScaling);
    drawLZWP(qp,lz);
}

void CloseUpMap::drawLZWP(QPainter &qp, QPointF lz)
{
    qp.setPen(QPen(QBrush("#FF0000"), 2));
    qp.setBrush(QBrush(QColor("#FFFF00")));
    QPolygon outsideRed({QPoint(lz.x(),lz.y()-7),QPoint(lz.x()+7,lz.y()),QPoint(lz.x(),lz.y()+7),QPoint(lz.x()-7,lz.y())});
    qp.drawPolygon(outsideRed);
    qp.setPen(QPen(QBrush("#0000FF"),1));
    qp.drawLine(lz.x(),lz.y()-5,lz.x(),lz.y()+5);
    qp.drawLine(lz.x()-5,lz.y(),lz.x()+5,lz.y());
}

void CloseUpMap::drawWP(QPainter &qp, int x, int y)
{
    QPointF wpCenter(x,y);
    qp.setPen(QPen(QBrush("#FFFF00"), 2));
    qp.setBrush(QBrush(QColor("#FFFF00")));
    QPolygon outsideRed({QPoint(x,y-7),QPoint(x+7,y),QPoint(x,y+7),QPoint(x-7,y)});
    qp.drawPolygon(outsideRed);
    qp.setPen(QPen(QBrush("#FF0000"), 1));
    qp.drawEllipse(wpCenter,5,5);
    qp.setPen(QPen(QBrush("#0000FF"),1));
    qp.drawLine(x,y-5,x,y+5);
    qp.drawLine(x-5,y,x+5,y);
}

void CloseUpMap::drawFlightPath(QPainter &qp, QPointF lz)
{
    double arrowLength = 7;
    double arrowAngle1 = 90-(convertTo360Degrees(approach.getBearing()))+205;
    double arrowAngle2 = 90-(convertTo360Degrees(approach.getBearing()))+155;
    qp.setPen(QPen(QBrush("#00FF00"),1));
    QPointF approachPoint(lz.x()+(approach.getEwOffset()/smallScaling),lz.y()-(approach.getNsOffset()/smallScaling));
    QPointF enginePoint(lz.x()+(engine.getEwOffset()/smallScaling),lz.y()-(engine.getNsOffset()/smallScaling));
    QPointF chutePoint(lz.x()+(chute.getEwOffset()/smallScaling),lz.y()-(chute.getNsOffset()/smallScaling));
    QPointF runOutPoint(lz.x()+(runOut.getEwOffset()/smallScaling),lz.y()-(runOut.getNsOffset()/smallScaling));
    QPointF aeMidpoint((approachPoint.x()+enginePoint.x())/2,(approachPoint.y()+enginePoint.y())/2);
    QPointF ecMidpoint((chutePoint.x()+enginePoint.x())/2,(chutePoint.y()+enginePoint.y())/2);
    QPointF crMidpoint((chutePoint.x()+runOutPoint.x())/2,(chutePoint.y()+runOutPoint.y())/2);
    qp.drawLine(approachPoint,enginePoint);
    qp.drawLine(enginePoint,chutePoint);
    qp.drawLine(chutePoint,runOutPoint);
    QLineF aeArrow1(0,0,1,1);
    QLineF aeArrow2(0,0,1,1);
    QLineF ecArrow1(0,0,1,1);
    QLineF ecArrow2(0,0,1,1);
    QLineF crArrow1(0,0,1,1);
    QLineF crArrow2(0,0,1,1);
    aeArrow1.setLength(arrowLength);
    aeArrow1.setAngle(arrowAngle1);
    aeArrow2.setLength(arrowLength);
    aeArrow2.setAngle(arrowAngle2);
    ecArrow1 = aeArrow1;
    crArrow1 = aeArrow1;
    ecArrow2 = aeArrow2;
    crArrow2 = aeArrow2;
    aeArrow1.translate(aeMidpoint);
    aeArrow2.translate(aeMidpoint);
    qp.drawLine(aeArrow1);
    qp.drawLine(aeArrow2);
    ecArrow1.translate(ecMidpoint);
    ecArrow2.translate(ecMidpoint);
    qp.drawLine(ecArrow1);
    qp.drawLine(ecArrow2);
    crArrow1.translate(crMidpoint);
    crArrow2.translate(crMidpoint);
    qp.drawLine(crArrow1);
    qp.drawLine(crArrow2);
}

void CloseUpMap::drawScale(QPainter &qp)
{
    qp.setPen(QPen(QBrush("#000000"),2));
    QPointF scaleStart(width()-20,height()-20);
    QLineF scale(0,0,1,1);
    QLineF scaleRight(width()-20,height()-25,width()-20,height()-15);
    QLineF scaleLeft(width()-20-(250/smallScaling),height()-25,width()-20-(250/smallScaling),height()-15);
    scale.setAngle(180);
    scale.setLength(250/smallScaling);
    scale.translate(scaleStart);
    qp.drawLine(scale);
    qp.drawLine(scaleRight);
    qp.drawLine(scaleLeft);
    qp.drawText(width()-20-(250/smallScaling/2)-17,height()-4,"250m");
}

void CloseUpMap::passWaypoints(Waypoint approachWP, Waypoint engineWP, Waypoint chuteWP, Waypoint runOutWP)
{
    approach=approachWP;
    engine=engineWP;
    chute=chuteWP;
    runOut=runOutWP;
}

void CloseUpMap::updateWaypoints(Waypoint approachWP, Waypoint engineWP, Waypoint chuteWP, Waypoint runOutWP)
{
    approach.setLzLat(approachWP.getLzLat());
    approach.setLzLong(approachWP.getLzLong());
    approach.setLzElev(approachWP.getLzElev());
    approach.setBearing(approachWP.getBearing());
    approach.setRecAlt(approachWP.getHeight());
    approach.setRecSpeed(approachWP.getAirspeed());
    approach.setWindDir(approachWP.getWindDir());
    approach.setWindSpeed(approachWP.getWindSpeed());
    engine.setLzLat(engineWP.getLzLat());
    engine.setLzLong(engineWP.getLzLong());
    engine.setLzElev(engineWP.getLzElev());
    engine.setBearing(engineWP.getBearing());
    engine.setRecAlt(engineWP.getHeight());
    engine.setRecSpeed(engineWP.getAirspeed());
    engine.setWindDir(engineWP.getWindDir());
    engine.setWindSpeed(engineWP.getWindSpeed());
    chute.setLzLat(chuteWP.getLzLat());
    chute.setLzLong(chuteWP.getLzLong());
    chute.setLzElev(chuteWP.getLzElev());
    chute.setBearing(chuteWP.getBearing());
    chute.setRecAlt(chuteWP.getHeight());
    chute.setRecSpeed(chuteWP.getAirspeed());
    chute.setWindDir(chuteWP.getWindDir());
    chute.setWindSpeed(chuteWP.getWindSpeed());
    runOut.setLzLat(runOutWP.getLzLat());
    runOut.setLzLong(runOutWP.getLzLong());
    runOut.setLzElev(runOutWP.getLzElev());
    runOut.setBearing(runOutWP.getBearing());
    runOut.setRecAlt(runOutWP.getHeight());
    runOut.setRecSpeed(runOutWP.getAirspeed());
    runOut.setWindDir(runOutWP.getWindDir());
    runOut.setWindSpeed(runOutWP.getWindSpeed());
    chute.setChuteWP();
    engine.setEngineWP(chute.getWpLat(),chute.getWpLong());
    approach.setApproachWP(engine.getWpLat(),engine.getWpLong());
    runOut.setRunOutWP(chute.getWpLat(),chute.getWpLong());
}