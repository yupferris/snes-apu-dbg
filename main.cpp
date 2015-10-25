#include "MainWindow.h"
#include "SnesApu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SnesApu apu;
    if (argc > 1)
        apu.SetSong(argv[1]);

    a.setStyleSheet("QWidget { color: #ffffff; background-color: #000000; } QPushButton { background-color: #0a0a0a; border: none; } QPushButton:hover { background-color: #1a1a1a; color: #00c6ff; } QPushButton:pressed { background-color: #c6076c; color: #000000; }");

    MainWindow w(&apu);
    w.show();

    return a.exec();
}
