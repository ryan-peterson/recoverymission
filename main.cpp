#include <iostream>
#include <math.h>
#include <QApplication>
#include "waypoint.h"
#include "missionFile.h"
#include "coordinateCalculations.h"
#include "recoveryMap.h"
#include "ParameterInputs.h"
#include "mainMap.h"

int main(int argc, char *argv[])
{
    //double lzLat = 0.12457;
    //double lzLong = -0.214674;
    //double bearing = M_PI/2;
    //double windSpeed = 3;
    //double windDir = M_PI/2;
    //double lzElev = 51;
    //double recoveryAlt = 160;
    //double recoverySpeed = 65;
    QApplication app(argc, argv);
    //Waypoint chuteWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recoveryAlt,recoverySpeed);
    //Waypoint engineWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recoveryAlt,recoverySpeed);
    //Waypoint runOutWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recoveryAlt,recoverySpeed);
    //Waypoint approachWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recoveryAlt,recoverySpeed);
    //chuteWP.setChuteWP();
    //engineWP.setEngineWP(chuteWP.getWpLat(),chuteWP.getWpLong());
    //approachWP.setApproachWP(engineWP.getWpLat(),engineWP.getWpLong());
    //runOutWP.setRunOutWP(chuteWP.getWpLat(),chuteWP.getWpLong());
    //outputMission(chuteWP,engineWP,approachWP,runOutWP);
    //std::cout << approachWP.getEwOffset() << std::endl;
    //std::cout << approachWP.getNsOffset() << std::endl;
    //std::cout << engineWP.getEwOffset() << std::endl;
    //std::cout << engineWP.getNsOffset() << std::endl;
    //std::cout << chuteWP.getEwOffset() << std::endl;
    //std::cout << chuteWP.getNsOffset() << std::endl;
    //std::cout << runOutWP.getEwOffset() << std::endl;
    //std::cout << runOutWP.getNsOffset() << std::endl;
    //std::cout << approachWP.getBearing() << std::endl;
    //ParameterInputs inputWindow;
    //inputWindow.setWindowTitle("Parameter Input");
    //inputWindow.show();
    //RecoveryMap mapWindow;
    //mapWindow.passWaypoints(inputWindow.approachWP,inputWindow.engineWP,inputWindow.chuteWP,inputWindow.runOutWP);
    //mapWindow.resize(510,510);
    //mapWindow.setWindowTitle("Recovery Map");
    //mapWindow.show();
    MainMap mainMap;
    mainMap.resize(730,665);
    mainMap.setWindowTitle("Recovery Mission Generator");
    mainMap.show();
    return app.exec();
}