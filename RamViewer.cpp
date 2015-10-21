#include "RamViewer.h"
#include "ui_RamViewer.h"

#include <qevent.h>
#include <qpainter.h>

RamViewer::RamViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RamViewer)
{
    ui->setupUi(this);

    pixels = new QRgb[256 * 256];
    for (int i = 0; i < 256 * 256; i++)
        pixels[i] = 0;

    snapshot = nullptr;
}

RamViewer::~RamViewer()
{
    delete ui;

    delete [] pixels;

    if (snapshot)
        delete snapshot;
}

void RamViewer::Update(Snapshot snapshot)
{
    if (this->snapshot)
        delete this->snapshot;
    this->snapshot = new Snapshot(snapshot);
    update();
}

void RamViewer::paintEvent(QPaintEvent *event)
{
    if (!snapshot)
        return;

    QPainter painter(this);

    auto ram = snapshot->GetRam();

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            int dataIndex = y * 256 + x;
            int pixelIndex = (255 - y) * 256 + x;
            auto oldPixel = pixels[pixelIndex];
            auto oldData = qBlue(oldPixel);
            auto newData = ram[dataIndex];
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
