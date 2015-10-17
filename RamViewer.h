#ifndef RAMVIEWER_H
#define RAMVIEWER_H

#include <QWidget>

#include "SnesApu.h"

namespace Ui {
    class RamViewer;
}

class RamViewer : public QWidget
{
    Q_OBJECT

public:
    explicit RamViewer(SnesApu *apu, QWidget *parent = 0);
    ~RamViewer();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::RamViewer *ui;

    SnesApu *apu;
};

#endif // RAMVIEWER_H
