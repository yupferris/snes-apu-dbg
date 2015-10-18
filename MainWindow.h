#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fileOpenSpcFile_triggered(bool checked = false);

    void on_stopButton_clicked();

private:
    Ui::MainWindow *ui;

    RamViewer *ramViewer;

    SnesApu apu;
};

#endif
