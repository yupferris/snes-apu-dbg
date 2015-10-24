#ifndef __SNES_APU_H__
#define __SNES_APU_H__

#include "snes_apu_c.h"

class Snapshot
{
public:
    Snapshot(snes_apu_context_t *);
    Snapshot(const Snapshot&);
    ~Snapshot();

    Snapshot& operator =(const Snapshot&);

    const unsigned char *GetRam() const;
    bool GetResamplingModeIsGaussian() const;
    bool GetResamplingModeIsLinear() const;
    bool GetVoiceIsMuted(int) const;
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
    void SetSong(const char*);
    void SetResamplingModeGaussian();
    void SetResamplingModeLinear();
    void SetVoiceIsMuted(int, bool);

    Snapshot GetSnapshot();

private:
    snes_apu_context_t *context;
};

#endif
