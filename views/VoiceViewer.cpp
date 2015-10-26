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
    auto mutedCheckState = snapshot.GetVoiceIsMuted(voiceIndex) ? Qt::Checked : Qt::Unchecked;
    if (mutedCheckState != ui->muted->checkState())
        ui->muted->setCheckState(mutedCheckState);

    auto solodCheckState = snapshot.GetVoiceIsSolod(voiceIndex) ? Qt::Checked : Qt::Unchecked;
    if (solodCheckState != ui->solod->checkState())
        ui->solod->setCheckState(solodCheckState);

    voiceOutputViewer->Update(snapshot);
}

void VoiceViewer::on_muted_stateChanged(int state)
{
    bool is_checked = state == Qt::Checked;
    apu->SetVoiceIsMuted(voiceIndex, is_checked);
}

void VoiceViewer::on_solod_stateChanged(int state)
{
    bool is_checked = state == Qt::Checked;
    apu->SetVoiceIsSolod(voiceIndex, is_checked);
}
