#include <QApplication>
#include <QFile>

#include "domain-model/SnesApu.h"
#include "MainWindow.h"

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
