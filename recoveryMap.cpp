#include <iostream>
#include <QPainter>
#include <math.h>
#include "recoveryMap.h"
#include "waypoint.h"
#include "coordinateTransforms.h"

int scaling=16;

RecoveryMap::RecoveryMap(QWidget *parent) : QWidget(parent)
{
    
}

void RecoveryMap::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter qp(this);
    qp.setRenderHint(QPainter::Antialiasing); // enabling this line makes graphics look smoother, but fuzzier and less accurate
    drawMap(qp);
}

void RecoveryMap::drawMap(QPainter &qp)
{
    qp.setPen(QColor("#000000"));
    qp.setBrush(QColor("#008080"));
    qp.drawRect(0,0,510,510);
    QPointF lz = determineSector();
    drawHitCircle(qp,lz);
    drawFlightPath(qp,lz);
    drawWP(qp,lz.x()+(approach.getEwOffset()/scaling),lz.y()-(approach.getNsOffset()/scaling));
    drawWP(qp,lz.x()+(engine.getEwOffset()/scaling),lz.y()-(engine.getNsOffset()/scaling));
    drawWP(qp,lz.x()+(chute.getEwOffset()/scaling),lz.y()-(chute.getNsOffset()/scaling));
    drawWP(qp,lz.x()+(runOut.getEwOffset()/scaling),lz.y()-(runOut.getNsOffset()/scaling));
    drawScale(qp);
}

void RecoveryMap::drawHitCircle(QPainter &qp, QPointF lz)
{
    int drift = chute.getDrift();
    qp.setPen(Qt::white);
    qp.drawEllipse(lz,drift/scaling,drift/scaling);
    drawLZWP(qp,lz);
}

void RecoveryMap::drawLZWP(QPainter &qp, QPointF lz)
{
    qp.setPen(QPen(QBrush("#FF0000"), 2));
    qp.setBrush(QBrush(QColor("#FFFF00")));
    QVector<QPoint> vector(0);
    QPoint point1(lz.x(),lz.y()-7);
    QPoint point2(lz.x()+7,lz.y());
    QPoint point3(lz.x(),lz.y()+7);
    QPoint point4(lz.x()-7,lz.y());
    vector.append(point1);
    vector.append(point2);
    vector.append(point3);
    vector.append(point4);
    QPolygon outsideRed(vector);
    qp.drawPolygon(outsideRed);
    qp.setPen(QPen(QBrush("#0000FF"),1));
    qp.drawLine(lz.x(),lz.y()-5,lz.x(),lz.y()+5);
    qp.drawLine(lz.x()-5,lz.y(),lz.x()+5,lz.y());
}

void RecoveryMap::drawWP(QPainter &qp, int x, int y)
{
    QPointF wpCenter(x,y);
    qp.setPen(QPen(QBrush("#FFFF00"), 2));
    qp.setBrush(QBrush(QColor("#FFFF00")));
    QVector<QPoint> vector(0);
    QPoint point1(x,y-7);
    QPoint point2(x+7,y);
    QPoint point3(x,y+7);
    QPoint point4(x-7,y);
    vector.append(point1);
    vector.append(point2);
    vector.append(point3);
    vector.append(point4);
    QPolygon outsideRed(vector);
    qp.drawPolygon(outsideRed);
    qp.setPen(QPen(QBrush("#FF0000"), 1));
    qp.drawEllipse(wpCenter,5,5);
    qp.setPen(QPen(QBrush("#0000FF"),1));
    qp.drawLine(x,y-5,x,y+5);
    qp.drawLine(x-5,y,x+5,y);
}

void RecoveryMap::drawFlightPath(QPainter &qp, QPointF lz)
{
    double arrowLength = 7;
    double arrowAngle1 = 90-(convertTo360Degrees(approach.getBearing()))+205;
    double arrowAngle2 = 90-(convertTo360Degrees(approach.getBearing()))+155;
    qp.setPen(QPen(QBrush("#00FF00"),1));
    QPointF approachPoint(lz.x()+(approach.getEwOffset()/scaling),lz.y()-(approach.getNsOffset()/scaling));
    QPointF enginePoint(lz.x()+(engine.getEwOffset()/scaling),lz.y()-(engine.getNsOffset()/scaling));
    QPointF chutePoint(lz.x()+(chute.getEwOffset()/scaling),lz.y()-(chute.getNsOffset()/scaling));
    QPointF runOutPoint(lz.x()+(runOut.getEwOffset()/scaling),lz.y()-(runOut.getNsOffset()/scaling));
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

void RecoveryMap::drawScale(QPainter &qp)
{
    qp.setPen(QPen(QBrush("#000000"),2));
    QPointF scaleStart(width()-20,height()-20);
    QLineF scale(0,0,1,1);
    QLineF scaleRight(width()-20,height()-25,width()-20,height()-15);
    QLineF scaleLeft(width()-20-(1000/scaling),height()-25,width()-20-(1000/scaling),height()-15);
    scale.setAngle(180);
    scale.setLength(1000/scaling);
    scale.translate(scaleStart);
    qp.drawLine(scale);
    qp.drawLine(scaleRight);
    qp.drawLine(scaleLeft);
    qp.drawText(width()-20-(1000/scaling/2)-11,height()-7,"1km");
}

void RecoveryMap::passWaypoints(Waypoint approachWP, Waypoint engineWP, Waypoint chuteWP, Waypoint runOutWP)
{
    approach=approachWP;
    engine=engineWP;
    chute=chuteWP;
    runOut=runOutWP;
}

void RecoveryMap::updateWaypoints(Waypoint approachWP, Waypoint engineWP, Waypoint chuteWP, Waypoint runOutWP)
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

QPointF RecoveryMap::determineSector()
{
    QPointF point;
    if (approach.getBearing()>=(337.5*(M_PI/180)) || approach.getBearing()<(22.5*(M_PI/180))) // north sector
    {
        point.setX(255);
        point.setY(120);
        return point;
    }
    else if (approach.getBearing()>=(22.5*(M_PI/180)) && approach.getBearing()<(67.5*(M_PI/180))) // northeast sector
    {
        point.setX(390);
        point.setY(120);
        return point;
    }
    else if (approach.getBearing()>=(67.5*(M_PI/180)) && approach.getBearing()<(112.5*(M_PI/180))) // east sector
    {
        point.setX(390);
        point.setY(255);
        return point;
    }
    else if (approach.getBearing()>=(112.5*(M_PI/180)) && approach.getBearing()<(157.5*(M_PI/180))) // southeast sector
    {
        point.setX(390);
        point.setY(390);
        return point;
    }
    else if (approach.getBearing()>=(157.5*(M_PI/180)) && approach.getBearing()<(202.5*(M_PI/180))) // south sector
    {
        point.setX(255);
        point.setY(390);
        return point;
    }
    else if (approach.getBearing()>=(292.5*(M_PI/180)) && approach.getBearing()<(337.5*(M_PI/180))) // northwest sector
    {
        point.setX(120);
        point.setY(120);
        return point;
    }
    else if (approach.getBearing()>=(247.5*(M_PI/180)) && approach.getBearing()<(292.5*(M_PI/180))) // west sector
    {
        point.setX(120);
        point.setY(255);
        return point;
    }
    else if (approach.getBearing()>=(202.5*(M_PI/180)) && approach.getBearing()<(247.5*(M_PI/180))) // southwest sector
    {
        point.setX(120);
        point.setY(390);
        return point;
    }
}

void RecoveryMap::spitShit()
{
    std::cout << "refLatitude " << chute.getLzLat() << std::endl;
    std::cout << "refLongitude " << chute.getLzLong() << std::endl;
    std::cout << "$" << std::endl;
    std::cout << "airspeed " << approach.getAirspeed() << std::endl;
    std::cout << "altitude " << approach.getHeight() << std::endl;
    std::cout << "eastOffset " << approach.getEwOffset() << std::endl;
    std::cout << "northOffset " << approach.getNsOffset() << std::endl;
    std::cout << "$" << std::endl;
    std::cout << "airspeed " << engine.getAirspeed() << std::endl;
    std::cout << "altitude " << engine.getHeight() << std::endl;
    std::cout << "eastOffset " << engine.getEwOffset() << std::endl;
    std::cout << "northOffset " << engine.getNsOffset() << std::endl;
    std::cout << "$" << std::endl;
    std::cout << "airspeed " << chute.getAirspeed() << std::endl;
    std::cout << "altitude " << chute.getHeight() << std::endl;
    std::cout << "eastOffset " << chute.getEwOffset() << std::endl;
    std::cout << "northOffset " << chute.getNsOffset() << std::endl;
    std::cout << "$" << std::endl;
    std::cout << "airspeed " << runOut.getAirspeed() << std::endl;
    std::cout << "altitude " << runOut.getHeight() << std::endl;
    std::cout << "eastOffset " << runOut.getEwOffset() << std::endl;
    std::cout << "northOffset " << runOut.getNsOffset() << std::endl;
    std::cout << "$" << std::endl;
}