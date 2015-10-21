#ifndef __VOICE_VIEWER_H__
#define __VOICE_VIEWER_H__

#include <QWidget>
#include "SnesApu.h"

namespace Ui {
    class VoiceViewer;
}

class VoiceViewer : public QWidget
{
    Q_OBJECT

public:
    explicit VoiceViewer(SnesApu *apu, int voiceIndex, QWidget *parent = nullptr);
    ~VoiceViewer();

    void Update(Snapshot snapshot);

private slots:
    void on_muted_stateChanged(int state);

private:
    Ui::VoiceViewer *ui;

    SnesApu *apu;

    int voiceIndex;
};

#endif
