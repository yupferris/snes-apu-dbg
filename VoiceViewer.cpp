#include "VoiceViewer.h"
#include "ui_VoiceViewer.h"

VoiceViewer::VoiceViewer(SnesApu *apu, int voiceIndex, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VoiceViewer)
{
    ui->setupUi(this);

    this->apu = apu;

    this->voiceIndex = voiceIndex;
    ui->title->setText("Voice " + QString::number(voiceIndex));
}

VoiceViewer::~VoiceViewer()
{
    delete ui;
}

void VoiceViewer::on_muted_stateChanged(int state) {
    bool is_checked = state == Qt::Checked;
    if (is_checked != apu->GetVoiceIsMuted(voiceIndex))
        apu->SetVoiceIsMuted(voiceIndex, is_checked);
}
