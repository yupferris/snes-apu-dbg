#ifndef __SNES_APU_H__
#define __SNES_APU_H__

#include <QString>

#include "snes_apu_c.h"

class Snapshot
{
public:
    Snapshot(snes_apu_context_t *);
    Snapshot(const Snapshot&);
    ~Snapshot();

    Snapshot& operator =(const Snapshot&);

    QString GetSongName() const;
    const int16_t *GetLeftOutputBuffer() const;
    const int16_t *GetRightOutputBuffer() const;
    const unsigned char *GetRam() const;
    bool GetResamplingModeIsGaussian() const;
    bool GetResamplingModeIsLinear() const;
    bool GetVoiceIsMuted(int) const;
    bool GetVoiceIsSolod(int) const;
    const int32_t *GetVoiceRawOutputBuffer(int) const;
    const int32_t *GetVoiceLeftOutputBuffer(int) const;
    const int32_t *GetVoiceRightOutputBuffer(int) const;

private:
    snes_apu_snapshot_t *snapshot;
};

class SnesApu
{
public:
    SnesApu();
    ~SnesApu();

    void Reset();
    void Stop();
    void SetSong(const QString&);
    void SetResamplingModeGaussian();
    void SetResamplingModeLinear();
    void SetVoiceIsMuted(int, bool);
    void SetVoiceIsSolod(int, bool);
    void MuteAll();
    void ClearMutes();
    void ClearSolos();

    Snapshot GetSnapshot();

private:
    snes_apu_context_t *context;
};

#endif
