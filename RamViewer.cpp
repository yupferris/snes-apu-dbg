#include "RamViewer.h"
#include "ui_RamViewer.h"

#include <qevent.h>
#include <qpainter.h>
#include <qtimer.h>

RamViewer::RamViewer(SnesApu *apu, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RamViewer)
{
    ui->setupUi(this);

    this->apu = apu;

    auto updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, [=] ()
    {
        update();
    });
    updateTimer->start(20);
}

RamViewer::~RamViewer()
{
    delete ui;
}

void RamViewer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //painter.setBrush(QColor("#000"));
    //painter.drawRect(0, 0, width(), height());

    auto snapshot = apu->GetRamSnapshot();
    auto data = snapshot.GetData();

    auto pixels = new QRgb[256 * 256];
    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            auto c = data[y * 256 + x];
            pixels[(255 - y) * 256 + x] = qRgba(c, c, c, 255);
        }
    }

    painter.drawImage(QPoint(0, 0), QImage((unsigned char *)pixels, 256, 256, 256 * sizeof(QRgb), QImage::Format_ARGB32));
}
