#ifndef __OUTPUT_VIEWER_H__
#define __OUTPUT_VIEWER_H__

#include <QWidget>

#include "domain-model/SnesApu.h"

namespace Ui {
    class OutputViewer;
}

class OutputViewer : public QWidget
{
    Q_OBJECT

public:
    explicit OutputViewer(QWidget *parent = nullptr);
    ~OutputViewer();

    void Update(Snapshot snapshot);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int calculateYPos(int value);

    Ui::OutputViewer *ui;

    Snapshot *snapshot;
};

#endif
