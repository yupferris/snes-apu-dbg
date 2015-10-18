#include "MainWindow.h"
#include "SnesApu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SnesApu apu;
    if (argc > 1)
        apu.SetSong(argv[1]);

    MainWindow w(&apu);
    w.show();

    return a.exec();
}
