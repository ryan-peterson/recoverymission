#pragma once

#include <QWidget>
#include <QPainter>

class FilePreview : public QWidget
{
    Q_OBJECT

    public:
        FilePreview(QWidget *parent = 0);
        QPainter qp;
        QString fileContents;
        void updateFileContents(QString newContents);

    protected:
        void paintEvent(QPaintEvent *);
        void drawFilePreview(QPainter &qp);
};