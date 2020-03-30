#include "mainMap.h"
#include "recoveryMap.h"
#include "closeUpMap.h"
#include "waypoint.h"
#include "ParameterInputs.h"
#include "missionFile.h"
#include "filePreview.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <iostream>
#include <QRadioButton>
#include <QLabel>
#include <QPalette>
#include <QFileDialog>
#include <QString>
#include <QWidget>

MainMap::MainMap(QWidget *parent) : QWidget(parent)
{
    cLabel = new QLabel("Coordinate Format:",this);
    cLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    cLabel->move(7,7);
    
    dddRadio = new QRadioButton("DDD",this);
    dddRadio->toggle();
    dmmRadio = new QRadioButton("DMM",this);
    dmsRadio = new QRadioButton("DMS",this);
    dddRadio->move(135,5);
    dmmRadio->move(185,5);
    dmsRadio->move(240,5);

    applyRadio = new QPushButton("Apply", this);
    applyRadio->setGeometry(290,2,60,25);

    redrawMap = new QPushButton("Redraw\n\nMap", this);
    redrawMap->setGeometry(632,45,70,70);

    writeFileBtn = new QPushButton("Write File", this);
    writeFileBtn->setGeometry(626,120,86,25);

    theMap = new RecoveryMap(this);
    theMap->setGeometry(5,150,510,510);

    theSmallMap = new CloseUpMap(this);
    theSmallMap->setGeometry(525,460,200,200);

    inputPanel = new ParameterInputs(1,this);
    inputPanel->setGeometry(5,25,500,120);

    theFile = new FilePreview(this);
    theFile->setGeometry(525,150,200,350);
    
    connect(redrawMap,SIGNAL(clicked()),this,SLOT(redrawTheMap()));
    connect(applyRadio,SIGNAL(clicked()),this,SLOT(changeCoordinates()));
    connect(writeFileBtn,SIGNAL(clicked()),this,SLOT(writeFile()));
}

void MainMap::redrawTheMap()
{
    theMap->updateWaypoints(inputPanel->getApproachWP(),inputPanel->getEngineWP(),inputPanel->getChuteWP(),inputPanel->getRunOutWP());
    theMap->update();
    theSmallMap->updateWaypoints(inputPanel->getApproachWP(),inputPanel->getEngineWP(),inputPanel->getChuteWP(),inputPanel->getRunOutWP());
    theSmallMap->update();
    theFile->updateFileContents(inputPanel->getFilePreview());
    theFile->update();
}

void MainMap::changeCoordinates()
{
    if (dddRadio->isChecked()==true)
    {
        inputPanel->hide();
        inputPanel = new ParameterInputs(1,this);
        inputPanel->setGeometry(5,25,500,120);
        inputPanel->show();
    }
    else if (dmmRadio->isChecked()==true)
    {
        inputPanel->hide();
        inputPanel = new ParameterInputs(2,this);
        inputPanel->setGeometry(5,25,633,120);
        inputPanel->show();
    }
    else if (dmsRadio->isChecked()==true)
    {
        inputPanel->hide();
        inputPanel = new ParameterInputs(3,this);
        inputPanel->setGeometry(5,25,600,120);
        inputPanel->show();
    }
}

void MainMap::writeFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As:", "/home"));
    outputMission(fileName, inputPanel->getApproachWP(), inputPanel->getEngineWP(), inputPanel->getChuteWP(), inputPanel->getRunOutWP());
}