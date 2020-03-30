#include "ParameterInputs.h"
#include "coordinateTransforms.h"
#include <iostream>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QString>
#include <QDoubleValidator>
#include <QValidator>

class MyValidator : public QDoubleValidator
{
public:
    MyValidator(double bottom, double top, int decimals, QObject * parent) :
        QDoubleValidator(bottom, top, decimals, parent)
    {
    }

    QValidator::State validate(QString &s, int &i) const
    {
        if (s.isEmpty() || s == "-") {
            return QValidator::Intermediate;
        }

        QChar decimalPoint = locale().decimalPoint();

        if(s.indexOf(decimalPoint) != -1) {
            int charsAfterPoint = s.length() - s.indexOf(decimalPoint) - 1;

            if (charsAfterPoint > decimals()) {
                return QValidator::Invalid;
            }
        }

        bool ok;
        double d = locale().toDouble(s, &ok);

        if (ok && d >= bottom() && d <= top()) {
            return QValidator::Acceptable;
        } else {
            return QValidator::Invalid;
        }
    }
};

ParameterInputs::ParameterInputs(int panelType, QWidget *parent) : QWidget(parent)
{
    if (panelType==1)
    {
    QLabel *lzLatLabel = new QLabel("LZ Latitude:",this);
    lzLatLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzLongLabel = new QLabel("LZ Longitude:",this);
    lzLongLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzElevLabel = new QLabel("LZ Elevation:",this);
    lzElevLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *bearingLabel = new QLabel("Approach Heading:",this);
    bearingLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *recAltLabel = new QLabel("Recovery Altitude:",this);
    recAltLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *recSpeedLabel = new QLabel("Recovery Speed:",this);
    recSpeedLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *windDirLabel = new QLabel("Wind Direction:",this);
    windDirLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *windSpeedLabel = new QLabel("Wind Speed:",this);
    windSpeedLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *mPerSLabel1 = new QLabel("m/s",this);
    mPerSLabel1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *mLabel1 = new QLabel("m",this);
    mLabel1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *degreeLabel1 = new QLabel(QChar(0x00B0),this);
    degreeLabel1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *degreeLabel2 = new QLabel(QChar(0x00B0),this);
    degreeLabel2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *degreeLabel3 = new QLabel(QChar(0x00B0),this);
    degreeLabel3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *degreeLabel4 = new QLabel(QChar(0x00B0),this);
    degreeLabel4->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *mLabel2 = new QLabel("m",this);
    mLabel2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *mPerSLabel2 = new QLabel("m/s",this);
    mPerSLabel2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QLineEdit *lzLatEdit = new QLineEdit(this);
    QLineEdit *lzLongEdit = new QLineEdit(this);
    QLineEdit *lzElevEdit = new QLineEdit(this);
    QLineEdit *bearingEdit = new QLineEdit(this);
    QLineEdit *recAltEdit = new QLineEdit(this);
    QLineEdit *recSpeedEdit = new QLineEdit(this);
    QLineEdit *windDirEdit = new QLineEdit(this);
    QLineEdit *windSpeedEdit = new QLineEdit(this);

    QGridLayout *grid = new QGridLayout();

    grid->addWidget(lzLatLabel,0,0);
    grid->addWidget(lzLongLabel,1,0);
    grid->addWidget(lzElevLabel,2,0);
    grid->addWidget(bearingLabel,3,0);
    grid->addWidget(lzLatEdit,0,1);
    grid->addWidget(lzLongEdit,1,1);
    grid->addWidget(lzElevEdit,2,1);
    grid->addWidget(bearingEdit,3,1);
    grid->addWidget(degreeLabel1,0,2);
    grid->addWidget(degreeLabel2,1,2);
    grid->addWidget(mLabel1,2,2);
    grid->addWidget(degreeLabel3,3,2);
    grid->addWidget(recAltLabel,0,3);
    grid->addWidget(recSpeedLabel,1,3);
    grid->addWidget(windDirLabel,2,3);
    grid->addWidget(windSpeedLabel,3,3);
    grid->addWidget(recAltEdit,0,4);
    grid->addWidget(recSpeedEdit,1,4);
    grid->addWidget(windDirEdit,2,4);
    grid->addWidget(windSpeedEdit,3,4);
    grid->addWidget(mLabel2,0,5);
    grid->addWidget(mPerSLabel1,1,5);
    grid->addWidget(degreeLabel4,2,5);
    grid->addWidget(mPerSLabel2,3,5);

    lzLat = 0;
    lzLong = 0;
    lzElev = 0;
    bearing = 0;
    recAlt = 0;
    recSpeed = 0;
    windDir = 0;
    windSpeed = 0;

    approachWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recAlt,recSpeed);
    engineWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recAlt,recSpeed);
    chuteWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recAlt,recSpeed);
    runOutWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recAlt,recSpeed);

    MyValidator *lzLatValid = new MyValidator(-90.0,90.0,6,this);
    MyValidator *lzLongValid = new MyValidator(-180.0,180.0,6,this);
    MyValidator *lzElevValid = new MyValidator(-100.0,9999.0,0,this);
    MyValidator *bearingValid = new MyValidator(0.0,359.0,0,this);
    MyValidator *recAltValid = new MyValidator(-100.0,9999.0,0,this);
    MyValidator *recSpeedValid = new MyValidator(0.0,205.0,0,this);
    MyValidator *windDirValid = new MyValidator(0.0,359.0,0,this);
    MyValidator *windSpeedValid = new MyValidator(0.0,999.0,0,this);

    lzLatEdit->setValidator(lzLatValid);
    lzLatEdit->setText(QString::number(lzLat));
    lzLongEdit->setValidator(lzLongValid);
    lzLongEdit->setText(QString::number(lzLong));
    lzElevEdit->setValidator(lzElevValid);
    lzElevEdit->setText(QString::number(lzElev));
    bearingEdit->setValidator(bearingValid);
    bearingEdit->setText(QString::number(bearing));
    recAltEdit->setValidator(recAltValid);
    recAltEdit->setText(QString::number(recAlt));
    recSpeedEdit->setValidator(recSpeedValid);
    recSpeedEdit->setText(QString::number(recSpeed));
    windDirEdit->setValidator(windDirValid);
    windDirEdit->setText(QString::number(windDir));
    windSpeedEdit->setValidator(windSpeedValid);
    windSpeedEdit->setText(QString::number(windSpeed));

    connect(lzLatEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzLat(QString)));
    connect(lzLongEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzLong(QString)));
    connect(lzElevEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzElev(QString)));
    connect(bearingEdit, SIGNAL(textEdited(QString)), this, SLOT(updateBearing(QString)));
    connect(recAltEdit, SIGNAL(textEdited(QString)), this, SLOT(updateRecAlt(QString)));
    connect(recSpeedEdit, SIGNAL(textEdited(QString)), this, SLOT(updateRecSpeed(QString)));
    connect(windDirEdit, SIGNAL(textEdited(QString)), this, SLOT(updateWindDir(QString)));
    connect(windSpeedEdit, SIGNAL(textEdited(QString)), this, SLOT(updateWindSpeed(QString)));

    setLayout(grid);
    }
    else if (panelType==2)
    {
    QLabel *lzLatLabel = new QLabel("<b>LZ Latitude:</b>",this);
    lzLatLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzLatDegLabel = new QLabel("Deg:",this);
    lzLatDegLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzLatMinLabel = new QLabel("Min:",this);
    lzLatMinLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzLongLabel = new QLabel("<b>LZ Longitude:</b>",this);
    lzLongLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzLongDegLabel = new QLabel("Deg:",this);
    lzLongDegLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzLongMinLabel = new QLabel("Min:",this);
    lzLongMinLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzElevLabel = new QLabel("LZ Elevation:",this);
    lzElevLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *bearingLabel = new QLabel("Approach Heading:",this);
    bearingLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *recAltLabel = new QLabel("Recovery Altitude:",this);
    recAltLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *recSpeedLabel = new QLabel("Recovery Speed:",this);
    recSpeedLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *windDirLabel = new QLabel("Wind Direction:",this);
    windDirLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *windSpeedLabel = new QLabel("Wind Speed:",this);
    windSpeedLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *mPerSLabel1 = new QLabel("m/s",this);
    mPerSLabel1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *mLabel1 = new QLabel("m",this);
    mLabel1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *degreeLabel1 = new QLabel(QChar(0x00B0),this);
    degreeLabel1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *degreeLabel2 = new QLabel(QChar(0x00B0),this);
    degreeLabel2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *mLabel2 = new QLabel("m",this);
    mLabel2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *mPerSLabel2 = new QLabel("m/s",this);
    mPerSLabel2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QLineEdit *lzLatDegEdit = new QLineEdit(this);
    QLineEdit *lzLatMinEdit = new QLineEdit(this);
    QLineEdit *lzLongDegEdit = new QLineEdit(this);
    QLineEdit *lzLongMinEdit = new QLineEdit(this);
    QLineEdit *lzElevEdit = new QLineEdit(this);
    QLineEdit *bearingEdit = new QLineEdit(this);
    QLineEdit *recAltEdit = new QLineEdit(this);
    QLineEdit *recSpeedEdit = new QLineEdit(this);
    QLineEdit *windDirEdit = new QLineEdit(this);
    QLineEdit *windSpeedEdit = new QLineEdit(this);

    QGridLayout *grid1 = new QGridLayout();

    grid1->addWidget(lzLatLabel,0,0,2,1);
    grid1->addWidget(lzLatDegLabel,0,1);
    grid1->addWidget(lzLatMinLabel,1,1);
    grid1->addWidget(lzLatDegEdit,0,2);
    grid1->addWidget(lzLatMinEdit,1,2);
    grid1->addWidget(lzLongLabel,2,0,2,1);
    grid1->addWidget(lzLongDegLabel,2,1);
    grid1->addWidget(lzLongMinLabel,3,1);
    grid1->addWidget(lzLongDegEdit,2,2);
    grid1->addWidget(lzLongMinEdit,3,2);

    grid1->addWidget(lzElevLabel,0,3);
    grid1->addWidget(lzElevEdit,0,4);
    grid1->addWidget(mLabel1,0,5);

    grid1->addWidget(bearingLabel,1,3);
    grid1->addWidget(bearingEdit,1,4);
    grid1->addWidget(degreeLabel1,1,5);

    grid1->addWidget(recAltLabel,2,3);
    grid1->addWidget(recAltEdit,2,4);
    grid1->addWidget(mLabel2,2,5);

    grid1->addWidget(recSpeedLabel,3,3);
    grid1->addWidget(recSpeedEdit,3,4);
    grid1->addWidget(mPerSLabel1,3,5);

    grid1->addWidget(windDirLabel,0,6);
    grid1->addWidget(windDirEdit,0,7);
    grid1->addWidget(degreeLabel2,0,8);
       
    grid1->addWidget(windSpeedLabel,1,6);
    grid1->addWidget(windSpeedEdit,1,7);
    grid1->addWidget(mPerSLabel2,1,8);

    lzLatDeg = 0;
    lzLatMin = 0;
    lzLongDeg = 0;
    lzLongMin = 0;
    lzElev = 0;
    bearing = 0;
    recAlt = 0;
    recSpeed = 0;
    windDir = 0;
    windSpeed = 0;

    approachWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recAlt,recSpeed);
    engineWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recAlt,recSpeed);
    chuteWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recAlt,recSpeed);
    runOutWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recAlt,recSpeed);

    MyValidator *lzLatDegValid = new MyValidator(-90.0,90.0,0,this);
    MyValidator *lzLatMinValid = new MyValidator(0,59.999999,4,this);
    MyValidator *lzLongDegValid = new MyValidator(-180.0,180.0,0,this);
    MyValidator *lzLongMinValid = new MyValidator(0,59.999999,4,this);
    MyValidator *lzElevValid = new MyValidator(-100.0,9999.0,0,this);
    MyValidator *bearingValid = new MyValidator(0.0,359.0,0,this);
    MyValidator *recAltValid = new MyValidator(-100.0,9999.0,0,this);
    MyValidator *recSpeedValid = new MyValidator(0.0,205.0,0,this);
    MyValidator *windDirValid = new MyValidator(0.0,359.0,0,this);
    MyValidator *windSpeedValid = new MyValidator(0.0,999.0,0,this);

    lzLatDegEdit->setValidator(lzLatDegValid);
    lzLatDegEdit->setText(QString::number(lzLatDeg));
    lzLatMinEdit->setValidator(lzLatMinValid);
    lzLatMinEdit->setText(QString::number(lzLatMin));
    lzLongDegEdit->setValidator(lzLongDegValid);
    lzLongDegEdit->setText(QString::number(lzLongDeg));
    lzLongMinEdit->setValidator(lzLongMinValid);
    lzLongMinEdit->setText(QString::number(lzLongMin));
    lzElevEdit->setValidator(lzElevValid);
    lzElevEdit->setText(QString::number(lzElev));
    bearingEdit->setValidator(bearingValid);
    bearingEdit->setText(QString::number(bearing));
    recAltEdit->setValidator(recAltValid);
    recAltEdit->setText(QString::number(recAlt));
    recSpeedEdit->setValidator(recSpeedValid);
    recSpeedEdit->setText(QString::number(recSpeed));
    windDirEdit->setValidator(windDirValid);
    windDirEdit->setText(QString::number(windDir));
    windSpeedEdit->setValidator(windSpeedValid);
    windSpeedEdit->setText(QString::number(windSpeed));

    connect(lzLatDegEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzLatDegDMM(QString)));
    connect(lzLatMinEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzLatMinDMM(QString)));
    connect(lzLongDegEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzLongDegDMM(QString)));
    connect(lzLongMinEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzLongMinDMM(QString)));
    connect(lzElevEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzElev(QString)));
    connect(bearingEdit, SIGNAL(textEdited(QString)), this, SLOT(updateBearing(QString)));
    connect(recAltEdit, SIGNAL(textEdited(QString)), this, SLOT(updateRecAlt(QString)));
    connect(recSpeedEdit, SIGNAL(textEdited(QString)), this, SLOT(updateRecSpeed(QString)));
    connect(windDirEdit, SIGNAL(textEdited(QString)), this, SLOT(updateWindDir(QString)));
    connect(windSpeedEdit, SIGNAL(textEdited(QString)), this, SLOT(updateWindSpeed(QString)));

    setLayout(grid1);
    }
    else if (panelType==3)
    {
    QLabel *lzLatLabel = new QLabel("<b>LZ Latitude:</b>",this);
    lzLatLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzLatDegLabel = new QLabel("Deg:",this);
    lzLatDegLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzLatMinLabel = new QLabel("Min:",this);
    lzLatMinLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzLatSecLabel = new QLabel("Sec:",this);
    lzLatSecLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzLongLabel = new QLabel("<b>LZ Longitude:</b>",this);
    lzLongLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzLongDegLabel = new QLabel("Deg:",this);
    lzLongDegLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzLongMinLabel = new QLabel("Min:",this);
    lzLongMinLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzLongSecLabel = new QLabel("Sec:",this);
    lzLongSecLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *lzElevLabel = new QLabel("LZ Elevation:",this);
    lzElevLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *bearingLabel = new QLabel("Approach Heading:",this);
    bearingLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *recAltLabel = new QLabel("Recovery Altitude:",this);
    recAltLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *recSpeedLabel = new QLabel("Recovery Speed:",this);
    recSpeedLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *windDirLabel = new QLabel("Wind Direction:",this);
    windDirLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *windSpeedLabel = new QLabel("Wind Speed:",this);
    windSpeedLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *mPerSLabel1 = new QLabel("m/s",this);
    mPerSLabel1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *mLabel1 = new QLabel("m",this);
    mLabel1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *degreeLabel1 = new QLabel(QChar(0x00B0),this);
    degreeLabel1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *degreeLabel2 = new QLabel(QChar(0x00B0),this);
    degreeLabel2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *mLabel2 = new QLabel("m",this);
    mLabel2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QLabel *mPerSLabel2 = new QLabel("m/s",this);
    mPerSLabel2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QLineEdit *lzLatDegEdit = new QLineEdit(this);
    QLineEdit *lzLatMinEdit = new QLineEdit(this);
    QLineEdit *lzLatSecEdit = new QLineEdit(this);
    QLineEdit *lzLongDegEdit = new QLineEdit(this);
    QLineEdit *lzLongMinEdit = new QLineEdit(this);
    QLineEdit *lzLongSecEdit = new QLineEdit(this);
    QLineEdit *lzElevEdit = new QLineEdit(this);
    QLineEdit *bearingEdit = new QLineEdit(this);
    QLineEdit *recAltEdit = new QLineEdit(this);
    QLineEdit *recSpeedEdit = new QLineEdit(this);
    QLineEdit *windDirEdit = new QLineEdit(this);
    QLineEdit *windSpeedEdit = new QLineEdit(this);

    QGridLayout *grid2 = new QGridLayout();

    grid2->addWidget(lzLatLabel,0,0,1,2);
    grid2->addWidget(lzLatDegLabel,1,0);
    grid2->addWidget(lzLatMinLabel,2,0);
    grid2->addWidget(lzLatDegEdit,1,1);
    grid2->addWidget(lzLatMinEdit,2,1);
    grid2->addWidget(lzLatSecLabel,3,0);
    grid2->addWidget(lzLatSecEdit,3,1);

    grid2->addWidget(lzLongLabel,0,2,1,2);
    grid2->addWidget(lzLongDegLabel,1,2);
    grid2->addWidget(lzLongMinLabel,2,2);
    grid2->addWidget(lzLongDegEdit,1,3);
    grid2->addWidget(lzLongMinEdit,2,3);
    grid2->addWidget(lzLongSecLabel,3,2);
    grid2->addWidget(lzLongSecEdit,3,3);

    grid2->addWidget(lzElevLabel,0,4);
    grid2->addWidget(lzElevEdit,0,5);
    grid2->addWidget(mLabel1,0,6);

    grid2->addWidget(bearingLabel,1,4);
    grid2->addWidget(bearingEdit,1,5);
    grid2->addWidget(degreeLabel1,1,6);

    grid2->addWidget(recAltLabel,2,4);
    grid2->addWidget(recAltEdit,2,5);
    grid2->addWidget(mLabel2,2,6);

    grid2->addWidget(recSpeedLabel,3,4);
    grid2->addWidget(recSpeedEdit,3,5);
    grid2->addWidget(mPerSLabel1,3,6);

    grid2->addWidget(windDirLabel,0,7);
    grid2->addWidget(windDirEdit,0,8);
    grid2->addWidget(degreeLabel2,0,9);
       
    grid2->addWidget(windSpeedLabel,1,7);
    grid2->addWidget(windSpeedEdit,1,8);
    grid2->addWidget(mPerSLabel2,1,9);

    lzLatDeg = 0;
    lzLatMin = 0;
    lzLatSec = 0;
    lzLongDeg = 0;
    lzLongMin = 0;
    lzLongSec = 0;
    lzElev = 0;
    bearing = 0;
    recAlt = 0;
    recSpeed = 0;
    windDir = 0;
    windSpeed = 0;

    approachWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recAlt,recSpeed);
    engineWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recAlt,recSpeed);
    chuteWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recAlt,recSpeed);
    runOutWP = Waypoint(lzLat,lzLong,bearing,windSpeed,windDir,lzElev,recAlt,recSpeed);

    MyValidator *lzLatDegValid = new MyValidator(-90.0,90.0,0,this);
    MyValidator *lzLatMinValid = new MyValidator(0,59.0,0,this);
    MyValidator *lzLatSecValid = new MyValidator(0,59.99,2,this);
    MyValidator *lzLongDegValid = new MyValidator(-180.0,180.0,0,this);
    MyValidator *lzLongMinValid = new MyValidator(0,59.0,0,this);
    MyValidator *lzLongSecValid = new MyValidator(0,59.99,2,this);
    MyValidator *lzElevValid = new MyValidator(-100.0,9999.0,0,this);
    MyValidator *bearingValid = new MyValidator(0.0,359.0,0,this);
    MyValidator *recAltValid = new MyValidator(-100.0,9999.0,0,this);
    MyValidator *recSpeedValid = new MyValidator(0.0,205.0,0,this);
    MyValidator *windDirValid = new MyValidator(0.0,359.0,0,this);
    MyValidator *windSpeedValid = new MyValidator(0.0,999.0,0,this);

    lzLatDegEdit->setValidator(lzLatDegValid);
    lzLatDegEdit->setText(QString::number(lzLatDeg));
    lzLatMinEdit->setValidator(lzLatMinValid);
    lzLatMinEdit->setText(QString::number(lzLatMin));
    lzLatSecEdit->setValidator(lzLatSecValid);
    lzLatSecEdit->setText(QString::number(lzLatSec));
    lzLongDegEdit->setValidator(lzLongDegValid);
    lzLongDegEdit->setText(QString::number(lzLongDeg));
    lzLongMinEdit->setValidator(lzLongMinValid);
    lzLongMinEdit->setText(QString::number(lzLongMin));
    lzLongSecEdit->setValidator(lzLongSecValid);
    lzLongSecEdit->setText(QString::number(lzLongSec));
    lzElevEdit->setValidator(lzElevValid);
    lzElevEdit->setText(QString::number(lzElev));
    bearingEdit->setValidator(bearingValid);
    bearingEdit->setText(QString::number(bearing));
    recAltEdit->setValidator(recAltValid);
    recAltEdit->setText(QString::number(recAlt));
    recSpeedEdit->setValidator(recSpeedValid);
    recSpeedEdit->setText(QString::number(recSpeed));
    windDirEdit->setValidator(windDirValid);
    windDirEdit->setText(QString::number(windDir));
    windSpeedEdit->setValidator(windSpeedValid);
    windSpeedEdit->setText(QString::number(windSpeed));

    connect(lzLatDegEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzLatDegDMS(QString)));
    connect(lzLatMinEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzLatMinDMS(QString)));
    connect(lzLatSecEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzLatSecDMS(QString)));
    connect(lzLongDegEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzLongDegDMS(QString)));
    connect(lzLongMinEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzLongMinDMS(QString)));
    connect(lzLongSecEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzLongSecDMS(QString)));
    connect(lzElevEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLzElev(QString)));
    connect(bearingEdit, SIGNAL(textEdited(QString)), this, SLOT(updateBearing(QString)));
    connect(recAltEdit, SIGNAL(textEdited(QString)), this, SLOT(updateRecAlt(QString)));
    connect(recSpeedEdit, SIGNAL(textEdited(QString)), this, SLOT(updateRecSpeed(QString)));
    connect(windDirEdit, SIGNAL(textEdited(QString)), this, SLOT(updateWindDir(QString)));
    connect(windSpeedEdit, SIGNAL(textEdited(QString)), this, SLOT(updateWindSpeed(QString)));

    setLayout(grid2);
    }
}

void ParameterInputs::updateLzLat(QString input)
{
    lzLat = input.toDouble();
    approachWP.setLzLat(convertToRadians(lzLat));
    engineWP.setLzLat(convertToRadians(lzLat));
    chuteWP.setLzLat(convertToRadians(lzLat));
    runOutWP.setLzLat(convertToRadians(lzLat));
    updateWPs();
}

void ParameterInputs::updateLzLatDegDMM(QString input)
{
    lzLatDeg = input.toDouble();
    lzLat = dmmToDdd(lzLatDeg,lzLatMin);
    approachWP.setLzLat(convertToRadians(lzLat));
    engineWP.setLzLat(convertToRadians(lzLat));
    chuteWP.setLzLat(convertToRadians(lzLat));
    runOutWP.setLzLat(convertToRadians(lzLat));
    updateWPs();
}

void ParameterInputs::updateLzLatMinDMM(QString input)
{
    lzLatMin = input.toDouble();
    lzLat = dmmToDdd(lzLatDeg,lzLatMin);
    approachWP.setLzLat(convertToRadians(lzLat));
    engineWP.setLzLat(convertToRadians(lzLat));
    chuteWP.setLzLat(convertToRadians(lzLat));
    runOutWP.setLzLat(convertToRadians(lzLat));
    updateWPs();
}

void ParameterInputs::updateLzLatDegDMS(QString input)
{
    lzLatDeg = input.toDouble();
    lzLat = dmsToDdd(lzLatDeg,lzLatMin,lzLatSec);
    approachWP.setLzLat(convertToRadians(lzLat));
    engineWP.setLzLat(convertToRadians(lzLat));
    chuteWP.setLzLat(convertToRadians(lzLat));
    runOutWP.setLzLat(convertToRadians(lzLat));
    updateWPs();
}

void ParameterInputs::updateLzLatMinDMS(QString input)
{
    lzLatMin = input.toDouble();
    lzLat = dmsToDdd(lzLatDeg,lzLatMin,lzLatSec);
    approachWP.setLzLat(convertToRadians(lzLat));
    engineWP.setLzLat(convertToRadians(lzLat));
    chuteWP.setLzLat(convertToRadians(lzLat));
    runOutWP.setLzLat(convertToRadians(lzLat));
    updateWPs();
}

void ParameterInputs::updateLzLatSecDMS(QString input)
{
    lzLatSec = input.toDouble();
    lzLat = dmsToDdd(lzLatDeg,lzLatMin,lzLatSec);
    approachWP.setLzLat(convertToRadians(lzLat));
    engineWP.setLzLat(convertToRadians(lzLat));
    chuteWP.setLzLat(convertToRadians(lzLat));
    runOutWP.setLzLat(convertToRadians(lzLat));
    updateWPs();
}

void ParameterInputs::updateLzLong(QString input)
{
    lzLong = input.toDouble();
    approachWP.setLzLong(convertToRadians(lzLong));
    engineWP.setLzLong(convertToRadians(lzLong));
    chuteWP.setLzLong(convertToRadians(lzLong));
    runOutWP.setLzLong(convertToRadians(lzLong));
    updateWPs();
}

void ParameterInputs::updateLzLongDegDMM(QString input)
{
    lzLongDeg = input.toDouble();
    lzLong = dmmToDdd(lzLongDeg,lzLongMin);
    approachWP.setLzLong(convertToRadians(lzLong));
    engineWP.setLzLong(convertToRadians(lzLong));
    chuteWP.setLzLong(convertToRadians(lzLong));
    runOutWP.setLzLong(convertToRadians(lzLong));
    updateWPs();
}

void ParameterInputs::updateLzLongMinDMM(QString input)
{
    lzLongMin = input.toDouble();
    lzLong = dmmToDdd(lzLongDeg,lzLongMin);
    approachWP.setLzLong(convertToRadians(lzLong));
    engineWP.setLzLong(convertToRadians(lzLong));
    chuteWP.setLzLong(convertToRadians(lzLong));
    runOutWP.setLzLong(convertToRadians(lzLong));
    updateWPs();
}

void ParameterInputs::updateLzLongDegDMS(QString input)
{
    lzLongDeg = input.toDouble();
    lzLong = dmsToDdd(lzLongDeg,lzLongMin,lzLongSec);
    approachWP.setLzLong(convertToRadians(lzLong));
    engineWP.setLzLong(convertToRadians(lzLong));
    chuteWP.setLzLong(convertToRadians(lzLong));
    runOutWP.setLzLong(convertToRadians(lzLong));
    updateWPs();
}

void ParameterInputs::updateLzLongMinDMS(QString input)
{
    lzLongMin = input.toDouble();
    lzLong = dmsToDdd(lzLongDeg,lzLongMin,lzLongSec);
    approachWP.setLzLong(convertToRadians(lzLong));
    engineWP.setLzLong(convertToRadians(lzLong));
    chuteWP.setLzLong(convertToRadians(lzLong));
    runOutWP.setLzLong(convertToRadians(lzLong));
    updateWPs();
}

void ParameterInputs::updateLzLongSecDMS(QString input)
{
    lzLongSec = input.toDouble();
    lzLong = dmsToDdd(lzLongDeg,lzLongMin,lzLongSec);
    approachWP.setLzLong(convertToRadians(lzLong));
    engineWP.setLzLong(convertToRadians(lzLong));
    chuteWP.setLzLong(convertToRadians(lzLong));
    runOutWP.setLzLong(convertToRadians(lzLong));
    updateWPs();
}

void ParameterInputs::updateLzElev(QString input)
{
    lzElev = input.toDouble();
    approachWP.setLzElev(lzElev);
    engineWP.setLzElev(lzElev);
    chuteWP.setLzElev(lzElev);
    runOutWP.setLzElev(lzElev);
    updateWPs();
}

void ParameterInputs::updateBearing(QString input)
{
    bearing = input.toDouble();
    approachWP.setBearing(convertToRadians(bearing));
    engineWP.setBearing(convertToRadians(bearing));
    chuteWP.setBearing(convertToRadians(bearing));
    runOutWP.setBearing(convertToRadians(bearing));
    updateWPs();
}

void ParameterInputs::updateRecAlt(QString input)
{
    recAlt = input.toDouble();
    approachWP.setRecAlt(recAlt);
    engineWP.setRecAlt(recAlt);
    chuteWP.setRecAlt(recAlt);
    runOutWP.setRecAlt(recAlt);
    updateWPs();
}

void ParameterInputs::updateRecSpeed(QString input)
{
    recSpeed = input.toDouble();
    approachWP.setRecSpeed(recSpeed);
    engineWP.setRecSpeed(recSpeed);
    chuteWP.setRecSpeed(recSpeed);
    runOutWP.setRecSpeed(recSpeed);
    updateWPs();
}

void ParameterInputs::updateWindDir(QString input)
{
    windDir = input.toDouble();
    approachWP.setWindDir(convertToRadians(windDir));
    engineWP.setWindDir(convertToRadians(windDir));
    chuteWP.setWindDir(convertToRadians(windDir));
    runOutWP.setWindDir(convertToRadians(windDir));
    updateWPs();
}
void ParameterInputs::updateWindSpeed(QString input)
{
    windSpeed = input.toDouble();
    approachWP.setWindSpeed(windSpeed);
    engineWP.setWindSpeed(windSpeed);
    chuteWP.setWindSpeed(windSpeed);
    runOutWP.setWindSpeed(windSpeed);
    updateWPs();
}

void ParameterInputs::updateWPs()
{
    chuteWP.setChuteWP();
    engineWP.setEngineWP(chuteWP.getWpLat(),chuteWP.getWpLong());
    approachWP.setApproachWP(engineWP.getWpLat(),engineWP.getWpLong());
    runOutWP.setRunOutWP(chuteWP.getWpLat(),chuteWP.getWpLong());
}

Waypoint ParameterInputs::getApproachWP()
{
    return approachWP;
}

Waypoint ParameterInputs::getEngineWP()
{
    return engineWP;
}

Waypoint ParameterInputs::getChuteWP()
{
    return chuteWP;
}

Waypoint ParameterInputs::getRunOutWP()
{
    return runOutWP;
}

QString ParameterInputs::getFilePreview()
{
    QString theText = "refLatitude ";
    theText.append(QString::number(chuteWP.getLzLat()));
    theText.append("\nrefLongitude ");
    theText.append(QString::number(chuteWP.getLzLong()));
    theText.append("\n$\nairspeed ");
    theText.append(QString::number(approachWP.getAirspeed()));
    theText.append("\naltitude ");
    theText.append(QString::number(approachWP.getHeight()));
    theText.append("\neastOffset ");
    theText.append(QString::number(approachWP.getEwOffset()));
    theText.append("\nnorthOffset ");
    theText.append(QString::number(approachWP.getNsOffset()));
    theText.append("\n$\nairspeed ");
    theText.append(QString::number(engineWP.getAirspeed()));
    theText.append("\naltitude ");
    theText.append(QString::number(engineWP.getHeight()));
    theText.append("\neastOffset ");
    theText.append(QString::number(engineWP.getEwOffset()));
    theText.append("\nnorthOffset ");
    theText.append(QString::number(engineWP.getNsOffset()));
    theText.append("\n$\nairspeed ");
    theText.append(QString::number(chuteWP.getAirspeed()));
    theText.append("\naltitude ");
    theText.append(QString::number(chuteWP.getHeight()));
    theText.append("\neastOffset ");
    theText.append(QString::number(chuteWP.getEwOffset()));
    theText.append("\nnorthOffset ");
    theText.append(QString::number(chuteWP.getNsOffset()));
    theText.append("\n$\nairspeed ");
    theText.append(QString::number(runOutWP.getAirspeed()));
    theText.append("\naltitude ");
    theText.append(QString::number(runOutWP.getHeight()));
    theText.append("\neastOffset ");
    theText.append(QString::number(runOutWP.getEwOffset()));
    theText.append("\nnorthOffset ");
    theText.append(QString::number(runOutWP.getNsOffset()));
    theText.append("\n$");
    return theText;
}