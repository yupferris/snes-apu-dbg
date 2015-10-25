#include <QApplication>
#include <QFile>

#include "MainWindow.h"
#include "SnesApu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SnesApu apu;
    if (argc > 1)
        apu.SetSong(argv[1]);

    QFile stylesheetFile(":/style.qss");
    stylesheetFile.open(QFile::ReadOnly);
    a.setStyleSheet(QLatin1String(stylesheetFile.readAll()));

    MainWindow w(&apu);
    w.show();

    return a.exec();
}
