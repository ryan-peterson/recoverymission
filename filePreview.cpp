#include "filePreview.h"
#include <QPainter>


FilePreview::FilePreview(QWidget *parent) : QWidget(parent)
{
    fileContents = QString(" ");
}

void FilePreview::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter qp(this);
    qp.setFont(QFont("Courier",8));
    // qp.setRenderHint(QPainter::Antialiasing); // enabling this line makes graphics look smoother, but fuzzier and less accurate
    drawFilePreview(qp);
}

void FilePreview::drawFilePreview(QPainter &qp)
{
    qp.drawText(rect(), Qt::AlignLeft|Qt::AlignTop, fileContents);
}

void FilePreview::updateFileContents(QString newContents)
{
    fileContents=newContents;
}