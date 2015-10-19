#include "VoiceViewer.h"
#include "ui_VoiceViewer.h"

VoiceViewer::VoiceViewer(int voiceIndex, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VoiceViewer)
{
    ui->setupUi(this);

    this->voiceIndex = voiceIndex;
    ui->title->setText("Voice " + QString::number(voiceIndex));
}

VoiceViewer::~VoiceViewer()
{
    delete ui;
}
