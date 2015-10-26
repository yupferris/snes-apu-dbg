#ifndef __VOICE_OUTPUT_VIEWER_H__
#define __VOICE_OUTPUT_VIEWER_H__

#include <QWidget>

#include "../domain-model/SnesApu.h"

namespace Ui {
    class VoiceOutputViewer;
}

class VoiceOutputViewer : public QWidget
{
    Q_OBJECT

public:
    explicit VoiceOutputViewer(int voiceIndex, QWidget *parent = nullptr);
    ~VoiceOutputViewer();

    void Update(Snapshot snapshot);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int calculateYPos(int value);

    Ui::VoiceOutputViewer *ui;

    int voiceIndex;

    Snapshot *snapshot;
};

#endif
