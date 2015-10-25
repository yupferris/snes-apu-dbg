#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <qlayout.h>
#include <qfiledialog.h>

MainWindow::MainWindow(SnesApu *apu, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    this->apu = apu;

    ramViewer = new RamViewer(ui->ramViewerContainer);

    voiceViewers = new VoiceViewer*[8];
    voiceViewers[0] = new VoiceViewer(apu, 0, ui->voiceViewer0Container);
    voiceViewers[1] = new VoiceViewer(apu, 1, ui->voiceViewer1Container);
    voiceViewers[2] = new VoiceViewer(apu, 2, ui->voiceViewer2Container);
    voiceViewers[3] = new VoiceViewer(apu, 3, ui->voiceViewer3Container);
    voiceViewers[4] = new VoiceViewer(apu, 4, ui->voiceViewer4Container);
    voiceViewers[5] = new VoiceViewer(apu, 5, ui->voiceViewer5Container);
    voiceViewers[6] = new VoiceViewer(apu, 6, ui->voiceViewer6Container);
    voiceViewers[7] = new VoiceViewer(apu, 7, ui->voiceViewer7Container);

    outputViewer = new OutputViewer(ui->outputViewerContainer);

    ui->fileOpenSpcFile->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));

    Update(apu->GetSnapshot());

    auto updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, [=] ()
    {
        Update(apu->GetSnapshot());
    });
    updateTimer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete [] voiceViewers;
}

void MainWindow::Update(Snapshot snapshot)
{
    ramViewer->Update(snapshot);

    for (int i = 0; i < 8; i++)
    {
        voiceViewers[i]->Update(snapshot);
    }

    outputViewer->Update(snapshot);

    auto gaussianChecked = snapshot.GetResamplingModeIsGaussian();
    if (gaussianChecked != ui->gaussianRadioButton->isChecked())
        ui->gaussianRadioButton->setChecked(gaussianChecked);

    auto linearChecked = snapshot.GetResamplingModeIsLinear();
    if (linearChecked != ui->linearRadioButton->isChecked())
    ui->linearRadioButton->setChecked(linearChecked);
}

void MainWindow::on_fileOpenSpcFile_triggered(bool checked)
{
    auto filename = QFileDialog::getOpenFileName(this, "Open SPC File", "", "SPC File (*.spc);;All Files (*)").toStdString();
    if (!filename.size())
        return;
    apu->SetSong(filename.c_str());
}

void MainWindow::on_resetButton_clicked()
{
    apu->Reset();
}

void MainWindow::on_stopButton_clicked()
{
    apu->Stop();
}

void MainWindow::on_gaussianRadioButton_toggled(bool checked)
{
    if (checked)
        apu->SetResamplingModeGaussian();
}

void MainWindow::on_linearRadioButton_toggled(bool checked)
{
    if (checked)
        apu->SetResamplingModeLinear();
}
