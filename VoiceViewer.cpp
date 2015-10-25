#include "VoiceViewer.h"
#include "ui_VoiceViewer.h"

VoiceViewer::VoiceViewer(SnesApu *apu, int voiceIndex, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VoiceViewer)
{
    ui->setupUi(this);

    this->apu = apu;

    this->voiceIndex = voiceIndex;
    ui->groupBox->setTitle("Voice " + QString::number(voiceIndex));

    voiceOutputViewer = new VoiceOutputViewer(voiceIndex, ui->outputViewerContainer);
}

VoiceViewer::~VoiceViewer()
{
    delete ui;
}

void VoiceViewer::Update(Snapshot snapshot)
{
    auto checkState = snapshot.GetVoiceIsMuted(voiceIndex) ? Qt::Checked : Qt::Unchecked;
    if (checkState != ui->muted->checkState())
        ui->muted->setCheckState(checkState);

    voiceOutputViewer->Update(snapshot);
}

void VoiceViewer::on_muted_stateChanged(int state)
{
    bool is_checked = state == Qt::Checked;
    apu->SetVoiceIsMuted(voiceIndex, is_checked);
}
