#ifndef __VOICE_VIEWER_H__
#define __VOICE_VIEWER_H__

#include <QWidget>

namespace Ui {
    class VoiceViewer;
}

class VoiceViewer : public QWidget
{
    Q_OBJECT

public:
    explicit VoiceViewer(int voiceIndex, QWidget *parent = nullptr);
    ~VoiceViewer();

private:
    Ui::VoiceViewer *ui;

    int voiceIndex;
};

#endif
