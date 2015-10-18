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

    ramViewer = new RamViewer(apu, ui->ramViewerContainer);

    ui->fileOpenSpcFile->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileOpenSpcFile_triggered(bool checked)
{
    auto filename = QFileDialog::getOpenFileName(this, "Open SPC File", "", "SPC File (*.spc);;All Files (*)").toStdString();
    if (!filename.size())
        return;
    apu->SetSong(filename.c_str());
}

void MainWindow::on_stopButton_clicked()
{
    apu->SetSong(nullptr);
}
