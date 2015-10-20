#ifndef __SNES_APU_H__
#define __SNES_APU_H__

#include "snes_apu_c.h"

class Snapshot
{
public:
    Snapshot(snes_apu_context_t *);
    ~Snapshot();

    const unsigned char *GetRam() const;

private:
    snes_apu_snapshot_t *snapshot;
};

class SnesApu
{
public:
    SnesApu();
    ~SnesApu();

    void SetSong(const char*);

    Snapshot GetSnapshot();

private:
    snes_apu_context_t *context;
};

#endif
