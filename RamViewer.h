#ifndef __RAM_VIEWER_H__
#define __RAM_VIEWER_H__

#include <QWidget>

#include "SnesApu.h"

namespace Ui {
    class RamViewer;
}

class RamViewer : public QWidget
{
    Q_OBJECT

public:
    explicit RamViewer(SnesApu *apu, QWidget *parent = nullptr);
    ~RamViewer();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::RamViewer *ui;

    SnesApu *apu;

    QRgb *pixels;
};

#endif
