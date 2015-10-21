#ifndef __VOICE_OUTPUT_VIEWER_H__
#define __VOICE_OUTPUT_VIEWER_H__

#include <QWidget>

namespace Ui {
    class VoiceOutputViewer;
}

class VoiceOutputViewer : public QWidget
{
    Q_OBJECT

public:
    explicit VoiceOutputViewer(QWidget *parent = nullptr);
    ~VoiceOutputViewer();

private:
    Ui::VoiceOutputViewer *ui;
};

#endif
