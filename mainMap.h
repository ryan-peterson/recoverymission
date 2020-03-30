#pragma once

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include "waypoint.h"
#include "recoveryMap.h"
#include "ParameterInputs.h"
#include "closeUpMap.h"
#include "filePreview.h"
#include <QLabel>
#include <QString>

class MainMap : public QWidget
{
    Q_OBJECT

    public:
        MainMap(QWidget *parent = 0);

    private slots:
        void redrawTheMap();
        void changeCoordinates();
        void writeFile();

    private:
        RecoveryMap *theMap;
        ParameterInputs *inputPanel;
        QPushButton *redrawMap;
        QPushButton *applyRadio;
        QPushButton *writeFileBtn;
        CloseUpMap *theSmallMap;
        FilePreview *theFile;
        QRadioButton *dddRadio;
        QRadioButton *dmmRadio;
        QRadioButton *dmsRadio;
        QLabel *cLabel;
};