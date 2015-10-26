#ifndef __RAM_VIEWER_H__
#define __RAM_VIEWER_H__

#include <QWidget>

#include "domain-model/SnesApu.h"

namespace Ui {
    class RamViewer;
}

class RamViewer : public QWidget
{
    Q_OBJECT

public:
    explicit RamViewer(QWidget *parent = nullptr);
    ~RamViewer();

    void Update(Snapshot snapshot);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::RamViewer *ui;

    QRgb *pixels;

    Snapshot *snapshot;
};

#endif
