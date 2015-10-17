#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_songAButton_clicked()
{
    apu.SetSong("/Users/yupferris/dev/projects/spc/ct/102 Chrono Trigger.spc");
}

void MainWindow::on_songBButton_clicked()
{
    apu.SetSong("/Users/yupferris/dev/projects/emu/snes-apu/test/ferris-nu.spc");
}

void MainWindow::on_stopButton_clicked()
{
    apu.SetSong(0); // TODO: C++11
}
