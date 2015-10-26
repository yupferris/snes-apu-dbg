#include "VoiceOutputViewer.h"
#include "ui_VoiceOutputViewer.h"

#include <qevent.h>
#include <qpainter.h>

VoiceOutputViewer::VoiceOutputViewer(int voiceIndex, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VoiceOutputViewer)
{
    ui->setupUi(this);

    this->voiceIndex = voiceIndex;

    snapshot = nullptr;
}

VoiceOutputViewer::~VoiceOutputViewer()
{
    delete ui;

    if (snapshot)
        delete snapshot;
}

void VoiceOutputViewer::Update(Snapshot snapshot)
{
    if (this->snapshot)
        delete this->snapshot;
    this->snapshot = new Snapshot(snapshot);
    update();
}

void VoiceOutputViewer::paintEvent(QPaintEvent *)
{
    if (!snapshot)
        return;

    QPainter painter(this);

    painter.fillRect(0, 0, width(), height(), Qt::black);

    auto rawOutputBuffer = snapshot->GetVoiceRawOutputBuffer(voiceIndex);
    auto leftOutputBuffer = snapshot->GetVoiceLeftOutputBuffer(voiceIndex);
    auto rightOutputBuffer = snapshot->GetVoiceRightOutputBuffer(voiceIndex);
    painter.setCompositionMode(QPainter::CompositionMode_Plus);
    for (int i = 0; i < 120; i++)
    {
        int centerY = calculateYPos(0);
        painter.setPen(QColor(128, 128, 128));
        painter.drawLine(i, centerY, i, calculateYPos(rawOutputBuffer[i]));
        painter.setPen(QColor(255, 32, 32));
        painter.drawLine(i, centerY, i, calculateYPos(leftOutputBuffer[i]));
        painter.setPen(QColor(32, 255, 255));
        painter.drawLine(i, centerY, i, calculateYPos(rightOutputBuffer[i]));
    }
}

int VoiceOutputViewer::calculateYPos(int value)
{
    return (int)((float)value / 32768.0 * 30.0) + 30;
}
