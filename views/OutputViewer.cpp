#include "OutputViewer.h"
#include "ui_OutputViewer.h"

#include <qevent.h>
#include <qpainter.h>

OutputViewer::OutputViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputViewer)
{
    ui->setupUi(this);

    snapshot = nullptr;
}

OutputViewer::~OutputViewer()
{
    delete ui;

    if (snapshot)
        delete snapshot;
}

void OutputViewer::Update(Snapshot snapshot)
{
    if (this->snapshot)
        delete this->snapshot;
    this->snapshot = new Snapshot(snapshot);
    update();
}

void OutputViewer::paintEvent(QPaintEvent *)
{
    if (!snapshot)
        return;

    QPainter painter(this);

    painter.fillRect(0, 0, width(), height(), Qt::black);

    auto leftOutputBuffer = snapshot->GetLeftOutputBuffer();
    auto rightOutputBuffer = snapshot->GetRightOutputBuffer();
    painter.setCompositionMode(QPainter::CompositionMode_Plus);
    for (int i = 0; i < 290; i++)
    {
        int centerY = calculateYPos(0);
        painter.setPen(QColor(255, 32, 32));
        painter.drawLine(i, centerY, i, calculateYPos(leftOutputBuffer[i]));
        painter.setPen(QColor(32, 255, 255));
        painter.drawLine(i, centerY, i, calculateYPos(rightOutputBuffer[i]));
    }
}

int OutputViewer::calculateYPos(int value)
{
    return (int)((float)value / 32768.0 * 95.0) + 95;
}
