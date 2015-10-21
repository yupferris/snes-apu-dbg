#include "VoiceOutputViewer.h"
#include "ui_VoiceOutputViewer.h"

VoiceOutputViewer::VoiceOutputViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VoiceOutputViewer)
{
    ui->setupUi(this);
}

VoiceOutputViewer::~VoiceOutputViewer()
{
    delete ui;
}
