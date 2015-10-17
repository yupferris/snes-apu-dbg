#include "MainWindow.h"
#include <QApplication>

#include <iostream>
#include "SnesApu.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    SnesApu apu;

    return a.exec();
}
