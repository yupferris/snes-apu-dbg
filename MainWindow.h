#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qlayout.h>

#include "RamViewer.h"

#include "SnesApu.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_songAButton_clicked();
    void on_songBButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::MainWindow *ui;

    RamViewer *ramViewer;

    SnesApu apu;
};

#endif
