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

    pixels = new QRgb[256 * 256];
    for (int i = 0; i < 256 * 256; i++)
        pixels[i] = 0;

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

    delete [] pixels;
}

void RamViewer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    auto snapshot = apu->GetRamSnapshot();
    auto data = snapshot.GetData();

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            int dataIndex = y * 256 + x;
            int pixelIndex = (255 - y) * 256 + x;
            auto oldPixel = pixels[pixelIndex];
            auto oldData = qBlue(oldPixel);
            auto newData = data[dataIndex];
            int red = qRed(oldPixel);
            if (newData != oldData)
            {
                red = 255;
            }
            else if (red > 0)
            {
                red -= 20;
                if (red < 0)
                    red = 0;
            }
            pixels[pixelIndex] = qRgba(red, 0, newData, 255);
        }
    }

    painter.drawImage(QRect(0, 0, 512, 512), QImage((unsigned char *)pixels, 256, 256, 256 * sizeof(QRgb), QImage::Format_ARGB32));
}
